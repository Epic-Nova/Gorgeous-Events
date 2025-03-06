// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|         that has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "GorgeousEvent.h"
#include "GorgeousEvents_GIS.h"
#include "GorgeousEventWithSubEvents.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "SubEvents/GorgeousSubEvent.h"
#include "VoidingContexts/GorgeousClassspaceExecutionVoidingContext.h"
#include "VoidingContexts/GorgeousSubEventExecutionVoidingContext.h"

UGorgeousEventManagingInterface* UGorgeousEventManagingInterface::SingletonInstance = nullptr;

UGorgeousEventManagingInterface* UGorgeousEventManagingInterface::GetEventManagingInterface()
{
	return Cast<UGorgeousEventManagingInterface>(UGorgeousEvents_GIS::StaticEventsGISInstance->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

void UGorgeousEventManagingInterface::LoadEvent(const TSoftClassPtr<UGorgeousEvent> EventToLoad,
                                                const FOnEventLoaded& OnEventLoaded)
{
	LoadEventNative(EventToLoad, FOnEventLoadedNative::CreateLambda([OnEventLoaded](const TSubclassOf<UGorgeousEvent>& LoadedEvent)
	{
		OnEventLoaded.Execute(LoadedEvent);
	}));
}

bool UGorgeousEventManagingInterface::RegisterEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& RegisteredEvent)
{
	return RegisterEvent_Internal(ConstructionHandle, RegisteredEvent);
}

bool UGorgeousEventManagingInterface::RegisterEvent_Internal(UGorgeousConstructionHandle* ConstructionHandle,
	UGorgeousEvent*& RegisteredEvent, UGorgeousEvent* AlreadyInstancedEvent)
{
	if (IsValid(ConstructionHandle))
	{
		const TSubclassOf<UGorgeousEvent> EventToRegister = ConstructionHandle->EventClass;

		if (const TObjectPtr<UGorgeousEventConstructionInterface> ConstructionInterface = UGorgeousEventConstructionInterface::GetEventConstructionInterface();
			ConstructionInterface->IsEventInConstructionQueue(ConstructionHandle->UniqueEventIdentifier))
		{
			if (EventToRegister == (AlreadyInstancedEvent ? AlreadyInstancedEvent->AgainstCheck : EventToRegister.GetDefaultObject()->AgainstCheck))
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("This class can not be used as an event class, because this is a base class that provides master functionality for children.",
					"GT.Events.Managing.RegisterEvent.Against_Check");
				ConstructionInterface->RemoveConstructionHandleFromQueue(ConstructionHandle, true);
				return false;
			}
			
			UGorgeousEvent* IncomingParent = nullptr;
			
			bool bIsExecutionAllowed = true;
			
			for (const auto Event : GetRegisteredEvents())
			{
				if (Event->GetClass()->IsChildOf(AlreadyInstancedEvent ? AlreadyInstancedEvent->ClassspaceParent : EventToRegister.GetDefaultObject()->ClassspaceParent))
				{
					if (AlreadyInstancedEvent ? AlreadyInstancedEvent->bUniqueClassspaceExecution : EventToRegister.GetDefaultObject()->bUniqueClassspaceExecution)
					{
						bIsExecutionAllowed = false;
						break;
					}
					IncomingParent = Event;
					break;
				}

				if (AlreadyInstancedEvent && Event->IsA<UGorgeousEventWithSubEvents>())
				{
					for (const auto SubEvent : Cast<UGorgeousEventWithSubEvents>(Event)->SubEvents)
					{
						if (SubEvent == AlreadyInstancedEvent)
						{
							IncomingParent = Event;
							break;
						}
					}
				}
			}

			if (!bIsExecutionAllowed)
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The Execution of the Event is currently not allowed, this could be because another Event in the same Class-space is currently performing its execution.",
					"GT.Events.Managing.RegisterEvent.Execution_Not_Allowed");
				ConstructionInterface->RemoveConstructionHandleFromQueue(ConstructionHandle, true);
				return false;
			}

			if (AlreadyInstancedEvent ? AlreadyInstancedEvent->bIsUnique : EventToRegister.GetDefaultObject()->bIsUnique && IsEventOfClassRegistered(EventToRegister))
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The event cannot be registered because it was marked as unique and another instance of the same class is already active.",
					"GT.Events.Managing.RegisterEvent.Unique");
				ConstructionInterface->RemoveConstructionHandleFromQueue(ConstructionHandle, true);
				return false;
			}


			UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("The evaluation of whether the event can be registered has been successfully completed. An attempt is now made to register the event and put it into active status.",
				"GT.Events.Managing.RegisterEvent.Evaluation_Completed");

			const TObjectPtr<UGorgeousEvent> NewEvent = AlreadyInstancedEvent ? AlreadyInstancedEvent : NewObject<UGorgeousEvent>(ConstructionHandle, EventToRegister);
			NewEvent->UniqueIdentifier = ConstructionHandle->UniqueEventIdentifier;

			// Sets this event interface as the cached owner. This is a fallback for when the outer reference is lost because of any reason I can not imagine (Absolute failsafe)
			NewEvent->CachedOwner = this;

			//Makes the event eligible for Runtime Object Variables
			IncomingParent ? IncomingParent->RegisterWithRegistry(NewEvent) : UGorgeousRootObjectVariable::GetRootObjectVariable()->RegisterWithRegistry(NewEvent);
			IncomingParent ? NewEvent->SetParent(IncomingParent) : NewEvent->SetParent(UGorgeousRootObjectVariable::GetRootObjectVariable());
			
			ConstructionHandle->OnConstructionStartedDelegate.Broadcast(NewEvent);

			CurrentRegisteredEvents.Add(NewEvent, SetupProcessingLoopForEvent(NewEvent));

			ConstructionHandle->OnConstructionFinishedDelegate.AddLambda([&ConstructionHandle]
			{
				ConstructionHandle->OnConstructionCleanupDelegate.Broadcast();
			});
			
			UGorgeousLoggingBlueprintFunctionLibrary::LogSuccessMessage("The event was successfully registered, that's Gorgeous!","GT.Events.Managing.RegisterEvent.Success");
			
			RegisteredEvent = NewEvent;
			
			const EGorgeousEventState_E PreviousEventState = RegisteredEvent->EventState;
			RegisteredEvent->EventState = EGorgeousEventState_E::Event_State_Initialized;
			RegisteredEvent->OnEventStateChangeDelegate.Broadcast(PreviousEventState, RegisteredEvent->EventState);
			RegisteredEvent->OnEventInitializedDelegate.Broadcast();
			
			return ConstructionInterface->RemoveConstructionHandleFromQueue(ConstructionHandle);
		}

		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The Event is not registered in the construction queue, therefore it cannot be constructed.","GT.Events.Construction.Queue.Not_In_Queue");
		return false;
	}
	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("Construction Handle reference is not valid, aborting Event registration.","GT.Events.Construction.Queue.Invalid_Handle");
	return false;
}


void UGorgeousEventManagingInterface::ReregisterEvent(UGorgeousEvent* Event)
{
	CurrentRegisteredEvents.Add(Event, SetupProcessingLoopForEvent(Event));
}

bool UGorgeousEventManagingInterface::UnregisterEvent(UGorgeousEvent* EventToUnregister)
{
	if (IsEventRegistered(EventToUnregister))
	{
		for (auto Pair : CurrentRegisteredEvents)
		{
			if (Pair.Key == EventToUnregister)
			{
				GetWorld()->GetTimerManager().ClearTimer(Pair.Value);

				UGorgeousEventVoidingInterface* VoidingInterface = UGorgeousEventVoidingInterface::GetEventVoidingInterface();
				bool bVoidedInstead = false;
				
				if (EventToUnregister->GetClassspaceChildren().Num() > 0)
				{
					VoidingInterface->VoidEvent(EventToUnregister, UGorgeousClassspaceExecutionVoidingContext::StaticClass());
					bVoidedInstead = true;
					
					UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("The event you are trying to unregister is currently providing data to class-space children, therefore it cannot be unregistered. It got moved into the voiding system instead where it will idle until all children are finished with execution.",
						"GT.Events.Managing.UnregisterEvent.Voided_Instead");
				}

				if (!VoidingInterface->IsEventVoided(EventToUnregister) && EventToUnregister->IsA<UGorgeousEventVoidingInterface>())
				{
					bool bAllSubEventsCompleted = false;
					for (const auto SubEvent : Cast<UGorgeousEventWithSubEvents>(EventToUnregister)->SubEvents)
					{
						if (EventToUnregister->IsSubEventFinished(SubEvent))
						{
							bAllSubEventsCompleted = true;
						}
						else
						{
							bAllSubEventsCompleted = false;
							break;
						}
					}

					if (!bAllSubEventsCompleted)
					{
						VoidingInterface->VoidEvent(EventToUnregister, UGorgeousSubEventExecutionVoidingContext::StaticClass());
						bVoidedInstead = true;
						
						UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("The event you are trying to unregister has currently sub events performing their execution. It got moved into the voiding system instead where it will idle until all children are finished with execution.",
							"GT.Events.Managing.UnregisterEvent.Voided_Instead");
					}
				}
				
				if (bVoidedInstead)
				{
					const EGorgeousEventState_E PreviousEventState = EventToUnregister->EventState;
					EventToUnregister->EventState = EGorgeousEventState_E::Event_State_Voided;
					EventToUnregister->OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventToUnregister->EventState);
					EventToUnregister->OnEventVoidedDelegate.Broadcast();

					return true;
				}
				
				UGorgeousRootObjectVariable::GetRootObjectVariable()->RemoveVariableFromRegistry(Pair.Key);
				EventToUnregister->GetOuter()->MarkAsGarbage();
				return RemoveUnregisteredEvent(EventToUnregister);
			}
		}
	}
	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The requested event is not registered, aborting unregistration!","GT.Events.Managing.RegisterEvent.Not_Registered");
	return false;
}

bool UGorgeousEventManagingInterface::CancelEvent(UGorgeousEvent* EventToCancel)
{
	if (UnregisterEvent(EventToCancel))
	{
		EventToCancel->OnEventCanceledDelegate.Broadcast();

		const EGorgeousEventState_E PreviousEventState = EventToCancel->EventState;
		EventToCancel->EventState = EGorgeousEventState_E::Event_State_Canceled;
		EventToCancel->OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventToCancel->EventState);

		EventToCancel->OnEventCleanupDelegate.Broadcast();
		return true;
	}
	return false;
}

bool UGorgeousEventManagingInterface::TriggerEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& TriggeredEvent)
{
	return TriggerEvent_Internal(ConstructionHandle, TriggeredEvent);
}

bool UGorgeousEventManagingInterface::TriggerEvent_Internal(UGorgeousConstructionHandle* ConstructionHandle,
	UGorgeousEvent*& TriggeredEvent, UGorgeousEvent* AlreadyInstancedEvent)
{
	if (UGorgeousEvent* RegisteredEvent; RegisterEvent_Internal(ConstructionHandle, RegisteredEvent, AlreadyInstancedEvent))
	{
		RegisteredEvent->OnEventTriggeredDelegate.Broadcast();

		const EGorgeousEventState_E PreviousEventState = RegisteredEvent->EventState;
		RegisteredEvent->EventState = EGorgeousEventState_E::Event_State_Triggered;
		RegisteredEvent->OnEventStateChangeDelegate.Broadcast(PreviousEventState, RegisteredEvent->EventState);

		if (RegisteredEvent->SecondsToWait != 0.f)
		{
			FTimerHandle SwitchFromTriggeredToProcessingStateTimer;
			GetWorld()->GetTimerManager().SetTimer(SwitchFromTriggeredToProcessingStateTimer, [RegisteredEvent]
			{
				RegisteredEvent->SwitchToStartedState_Internal();
			}, RegisteredEvent->SecondsToWait, false);
		}
		else
		{
			RegisteredEvent->SwitchToStartedState_Internal();
		}
		
		TriggeredEvent = RegisteredEvent;
		return true;
	}

	return false;
}

bool UGorgeousEventManagingInterface::CompleteEvent(UGorgeousEvent* EventToComplete)
{
	if (UnregisterEvent(EventToComplete))
	{
		EventToComplete->OnEventFinishedDelegate.Broadcast();

		const EGorgeousEventState_E PreviousEventState = EventToComplete->EventState;
		EventToComplete->EventState = EGorgeousEventState_E::Event_State_Finished;
		EventToComplete->OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventToComplete->EventState);

		EventToComplete->OnEventCleanupDelegate.Broadcast();
		EventToComplete->bIsEventFinished = true;
		return true;
	}

	return false;
}

bool UGorgeousEventManagingInterface::IsEventOfClassRegistered(const TSubclassOf<UGorgeousEvent>& EventClassToCheck, const bool bIncludeSubclassCheck) const
{
	for (const auto Event : GetRegisteredEvents())
	{
		if (Event->GetClass() == EventClassToCheck || (bIncludeSubclassCheck && Event->GetClass()->IsChildOf(EventClassToCheck)))
		{
			return true;
		}
	}
	return false;
}

bool UGorgeousEventManagingInterface::RemoveUnregisteredEvent(UGorgeousEvent* Event)
{
	return CurrentRegisteredEvents.Remove(Event) >= 1;
}

TArray<UGorgeousEvent*> UGorgeousEventManagingInterface::GetRegisteredEvents() const
{
	TArray<TObjectPtr<UGorgeousEvent>> RegisteredEvents;
	CurrentRegisteredEvents.GetKeys(RegisteredEvents);

	return RegisteredEvents;
}

bool UGorgeousEventManagingInterface::IsEventRegistered(UGorgeousEvent* EventToCheck) const
{
	return CurrentRegisteredEvents.Contains(EventToCheck);
}

void UGorgeousEventManagingInterface::LoadEventNative(TSoftClassPtr<UGorgeousEvent> EventToLoad,
	const FOnEventLoadedNative& OnEventLoaded)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Attempting to load event: %s"), *EventToLoad.ToString()), Logging_Information,
        "GT.Events.Managing.LoadEvent.Attempt", 2.0f, true, true, false, this);
	
    if (EventToLoad.IsValid())
    {
        UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Starting async load for event: %s"), *EventToLoad.ToString()), Logging_Information,
            "GT.Events.Managing.LoadEvent.Start_Async", 2.0f, true, true, false, this);
    	
        FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
        StreamableManager.RequestAsyncLoad(EventToLoad.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([&, EventToLoad, OnEventLoaded]()
        {
            if (EventToLoad.IsValid())
            {
                UGorgeousLoggingBlueprintFunctionLibrary::LogSuccessMessage(FString::Printf(TEXT("Successfully loaded event: %s"), *EventToLoad.ToString()),
                    "GT.Events.Managing.LoadEvent.Success", 2.f, true, true, this);
            	
                const TSubclassOf<UGorgeousEvent> LoadedEvent = EventToLoad.Get();
                if (OnEventLoaded.IsBound())
                {
	                OnEventLoaded.Execute(LoadedEvent);
                }
            	
            }
            else
            {
                UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("Failed to load event: %s"), *EventToLoad.ToString()),
                    "GT.Events.Managing.LoadEvent.Failure");
            }
        }));
    }
    else
    {
        UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("Invalid event to load: %s"), *EventToLoad.ToString()),
            "GT.Events.Managing.LoadEvent.Invalid");
    }
}

FTimerHandle UGorgeousEventManagingInterface::SetupProcessingLoopForEvent(UGorgeousEvent* Event) const
{
	FTimerHandle EventProcessingLoopTimer;
	GetWorld()->GetTimerManager().SetTimer(EventProcessingLoopTimer, [Event, this]
	{
		const float DeltaTime = GetWorld()->GetDeltaSeconds();
		static int64 CurrentProcessingLoopCount = 0;
		CurrentProcessingLoopCount++;

		if (Event)
		{
			Event->ContinuousProcessingLoopDelegate.Broadcast(Event->EventState, DeltaTime, CurrentProcessingLoopCount);
		}
	}, Event->CurrentProcessingLoopDelay, true);

	return EventProcessingLoopTimer;
}