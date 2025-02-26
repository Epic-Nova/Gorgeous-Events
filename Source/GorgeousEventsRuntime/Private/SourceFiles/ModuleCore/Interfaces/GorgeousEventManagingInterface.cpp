// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|      that is has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "GorgeousEvent.h"
#include "GorgeousEvents_GIS.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"

UGorgeousEventManagingInterface* UGorgeousEventManagingInterface::SingletonInstance = nullptr;

UGorgeousEventManagingInterface* UGorgeousEventManagingInterface::GetEventManagingInterface()
{
	UGorgeousEvents_GIS* Events_GIS = GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UGorgeousEvents_GIS>();
	return Cast<UGorgeousEventManagingInterface>(Events_GIS->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
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
	if (IsValid(ConstructionHandle))
	{
		const TSubclassOf<UGorgeousEvent> EventToRegister = ConstructionHandle->EventClass;

		if (const TObjectPtr<UGorgeousEventConstructionInterface> ConstructionInterface = UGorgeousEventConstructionInterface::GetEventConstructionInterface();
			ConstructionInterface->IsEventInConstructionQueue(ConstructionHandle->UniqueEventIdentifier))
		{
			if (EventToRegister.GetDefaultObject()->bUniqueClassspaceExecution)
			{
				bool bIsExecutionAllowed = true;
				
				for (const auto Event : GetRegisteredEvents())
				{
					if (Event->GetClass()->IsChildOf(EventToRegister.GetDefaultObject()->ClassspaceParent))
					{
						bIsExecutionAllowed = false;
						break;
					}
				}

				if (!bIsExecutionAllowed)
				{
					UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The Execution of the Event is currently not allowed, this could be because another Event in the same Class-space is currently performing its execution.",
						"GT.Events.Managing.RegisterEvent.ExecutionNotAllowed");
					return false;
				}
			}

			if (EventToRegister.GetDefaultObject()->bIsUnique && IsEventOfClassRegistered(EventToRegister))
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The event cannot be registered because it was marked as unique and another instance of the same class is already active.",
					"GT.Events.Managing.RegisterEvent.Unique");
				return false;
			}


			UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("The evaluation of whether the event can be registered has been successfully completed. An attempt is now made to register the event and put it into active status.",
				"GT.Events.Managing.RegisterEvent.EvaluationCompleted");

			TObjectPtr<UGorgeousEvent> NewEvent = NewObject<UGorgeousEvent>(ConstructionHandle, EventToRegister);

			ConstructionHandle->OnConstructionStartedDelegate.Broadcast(NewEvent);
			
			FTimerHandle EventProcessingLoopTimer;
			GetWorld()->GetTimerManager().SetTimer(EventProcessingLoopTimer, [NewEvent]
			{
				NewEvent->ContinuousProcessingLoopDelegate.Broadcast();
			}, NewEvent->CurrentProcessingLoopDelay, true);

			CurrentRegisteredEvents.Add(NewEvent, EventProcessingLoopTimer);

			ConstructionHandle->OnConstructionFinishedDelegate.AddLambda([&ConstructionHandle]
			{
				ConstructionHandle->OnConstructionCleanupDelegate.Broadcast();
			});


			UGorgeousLoggingBlueprintFunctionLibrary::LogSuccessMessage("The event was successfully registered, that's Gorgeous!","GT.Events.Managing.RegisterEvent.Success");
			
			RegisteredEvent = NewEvent;
			return ConstructionInterface->RemoveConstructionHandleFromQueue(ConstructionHandle);
		}

		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The Event is not registered in the construction queue, therefore it cannot be constructed.","GT.Events.Construction.Queue.NotInQueue");
		return false;
	}
	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("Construction Handle reference is not valid, aborting Event registration.","GT.Events.Construction.Queue.InvalidHandle");
	return false;
}

bool UGorgeousEventManagingInterface::UnregisterEvent(UGorgeousEvent* EventToUnregister)
{
	if (IsEventRegistered(EventToUnregister))
	{
		for (auto Pair : CurrentRegisteredEvents)
		{
			if (Pair.Key == EventToUnregister)
			{
				Pair.Value.Invalidate();
				EventToUnregister->GetOuterUGorgeousConstructionHandle()->MarkAsGarbage();
				return true;
			}
		}
	}
	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The requested event is not registered, aborting unregistration!","GT.Events.Managing.RegisterEvent.NotRegistered");
	return false;
}

bool UGorgeousEventManagingInterface::CancelEvent(UGorgeousEvent* EventToCancel)
{
	if (const bool bUnregistered = UnregisterEvent(EventToCancel))
	{
		EventToCancel->OnEventCanceledDelegate.Broadcast();

		const EGorgeousEventState_E PreviousEventState = EventToCancel->EventState;
		EventToCancel->EventState = EGorgeousEventState_E::Event_State_Canceled;
		EventToCancel->OnEventStateChangeDelegate.ExecuteIfBound(PreviousEventState, EventToCancel->EventState);

		EventToCancel->OnEventCleanupDelegate.Broadcast();
		RemoveUnregisteredEvent(EventToCancel);
		return bUnregistered;
	}
	return false;
}

bool UGorgeousEventManagingInterface::TriggerEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& TriggeredEvent)
{
	if (UGorgeousEvent* RegisteredEvent; RegisterEvent(ConstructionHandle, RegisteredEvent))
	{
		RegisteredEvent->OnEventTriggeredDelegate.Broadcast();

		const EGorgeousEventState_E PreviousEventState = RegisteredEvent->EventState;
		RegisteredEvent->EventState = EGorgeousEventState_E::Event_State_Triggered;
		RegisteredEvent->OnEventStateChangeDelegate.ExecuteIfBound(PreviousEventState, RegisteredEvent->EventState);

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
		EventToComplete->OnEventStateChangeDelegate.ExecuteIfBound(PreviousEventState, EventToComplete->EventState);

		EventToComplete->OnEventCleanupDelegate.Broadcast();
		RemoveUnregisteredEvent(EventToComplete);
		EventToComplete->bIsEventFinished = true;
		return true;
	}

	return false;
}

bool UGorgeousEventManagingInterface::IsEventOfClassRegistered(const TSubclassOf<UGorgeousEvent>& EventClassToCheck) const
{
	for (const auto Event : GetRegisteredEvents())
	{
		if (Event->GetClass() == EventClassToCheck)
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

bool UGorgeousEventManagingInterface::RemoveUnregisteredEvents()
{
	//@TODO
	return false;
}

bool UGorgeousEventManagingInterface::RemoveUnregisteredEventsOfClass(TSubclassOf<UGorgeousEvent> EventClassToRemove)
{
	//@TODO
	return false;
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

bool UGorgeousEventManagingInterface::ValidateRegisteredEvents(bool bShouldRemoveInvalidEvents,
	bool bApplyValidationToInstancedVariable, bool& bAllRegisteredEventsValid, int32& NumInvalidEvents)
{
	//@TODO bApplyValidationToInstancedVariable => Voiding system, if the ptr itself is invalid then remove the entry
	return false;
}

void UGorgeousEventManagingInterface::LoadEventNative(TSoftClassPtr<UGorgeousEvent> EventToLoad,
	const FOnEventLoadedNative& OnEventLoaded)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Attempting to load event: %s"), *EventToLoad.ToString()), Logging_Information,
        "GT.Events.Managing.LoadEvent.Attempt", 2.0f, true, true, false, this);
	
    if (EventToLoad.IsValid())
    {
        UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Starting async load for event: %s"), *EventToLoad.ToString()), Logging_Information,
            "GT.Events.Managing.LoadEvent.StartAsync", 2.0f, true, true, false, this);
    	
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
