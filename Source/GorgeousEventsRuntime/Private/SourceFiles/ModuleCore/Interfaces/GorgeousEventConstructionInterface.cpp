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
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "GorgeousEvent.h"
#include "GorgeousEvents_GIS.h"

UGorgeousEventConstructionInterface* UGorgeousEventConstructionInterface::SingletonInstance = nullptr;

UGorgeousEventConstructionInterface* UGorgeousEventConstructionInterface::GetEventConstructionInterface()
{
	//@TODO: Probably problematic for Dedicated server scenarios
	UGorgeousEvents_GIS* Events_GIS = GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UGorgeousEvents_GIS>();
	return Cast<UGorgeousEventConstructionInterface>(Events_GIS->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

void UGorgeousEventConstructionInterface::QueueEventConstruction(const TSoftClassPtr<UGorgeousEvent> EventToConstruct, FGuid UniqueEventIdentifierOverride, const FOnEventConstructionQueued& OnEventConstructionQueued)
{
	if (!UniqueEventIdentifierOverride.IsValid())
		UniqueEventIdentifierOverride = FGuid::NewGuid();

	if (!IsEventInConstructionQueue(UniqueEventIdentifierOverride))
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Queued event construction for: %s with unique identifier: %s"),
			*EventToConstruct.ToString(), *UniqueEventIdentifierOverride.ToString()),
			"GT.Events.Construction.Queue.Queued", 5.0f, true, true, this);
		
		UGorgeousEventManagingInterface* EventManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
		
		EventManagingInterface->LoadEventNative(EventToConstruct, FOnEventLoadedNative::CreateLambda([this, UniqueEventIdentifierOverride, OnEventConstructionQueued](const TSubclassOf<UGorgeousEvent>& LoadedEvent)
		{
			if (LoadedEvent)
			{
				UGorgeousConstructionHandle* NewConstructionHandle = NewObject<UGorgeousConstructionHandle>(this, LoadedEvent.GetDefaultObject()->ConstructionHandleClass);
				NewConstructionHandle->EventClass = LoadedEvent;
				NewConstructionHandle->UniqueEventIdentifier = UniqueEventIdentifierOverride;

				ConstructionQueue.Add(UniqueEventIdentifierOverride, NewConstructionHandle);

				UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Successfully queued event: %s with unique identifier: %s and construction handle: %s"),
					*LoadedEvent->GetName(), *UniqueEventIdentifierOverride.ToString(), *NewConstructionHandle->GetName()),
					"GT.Events.Construction.Queue.Successful", 5.0f, false, true, this);

				NewConstructionHandle->OnConstructionQueuedDelegate.Broadcast();
				OnEventConstructionQueued.ExecuteIfBound(NewConstructionHandle);
			}
			else
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("Failed to construct event with unique identifier: %s"), *UniqueEventIdentifierOverride.ToString()),
					"GT.Events.Construction.Queue.Failed", 5.0f, this);
			}
			
		}));

		return;
	}

	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("Event is already in construction queue.", "GT.Events.Construction.Queue.AlreadyInQueue");
}

bool UGorgeousEventConstructionInterface::CancelEventConstruction(UGorgeousConstructionHandle* ConstructionToCancel)
{
	if (IsValid(ConstructionToCancel))
	{
		if (IsEventInConstructionQueue(ConstructionToCancel->UniqueEventIdentifier))
		{
			ConstructionToCancel->OnConstructionCleanupDelegate.Broadcast();

			RemoveConstructionHandleFromQueue(ConstructionToCancel, true);

			UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Canceled event construction for: %s with unique identifier: %s"),
				*ConstructionToCancel->EventClass->GetName(), *ConstructionToCancel->UniqueEventIdentifier.ToString()),
				"GT.Events.Construction.Queue.Canceled", 2.0f, true, true, this);

			return true;
		}
		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("Event is not registered with the construction queue.", "GT.Events.Construction.Queue.NotInQueue");
		return false;
	}
	UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage("The parsed construction handle is not valid.", "GT.Events.Construction.Queue.InvalidHandle");
	return false;
}

bool UGorgeousEventConstructionInterface::CancelEventConstructionByGuid(const FGuid EventGuid)
{
	return CancelEventConstruction(GetConstructionHandleByGuid(EventGuid));
}

TArray<UGorgeousConstructionHandle*> UGorgeousEventConstructionInterface::GetEventConstructionQueue()
{
	bool bAllQueuedHandlesValid;
	int32 NumInvalidEvents;
	return ValidateConstructionQueue(true, true, bAllQueuedHandlesValid, NumInvalidEvents);
}

bool UGorgeousEventConstructionInterface::IsEventInConstructionQueue(const FGuid EventToCheck)
{
	for (const auto& ConstructionHandle : ConstructionQueue)
	{
		if (ConstructionHandle.Key == EventToCheck)
		{
			return true;
		}
	}
	return false;
}

UGorgeousConstructionHandle* UGorgeousEventConstructionInterface::GetConstructionHandle(
	const UGorgeousEvent* EventToGetHandleFor)
{
	for (const auto& ConstructionHandle : ConstructionQueue)
	{
		if (ConstructionHandle.Value->EventClass == EventToGetHandleFor->GetClass())
		{
			return ConstructionHandle.Value;
		}
	}
	return nullptr;
}

UGorgeousConstructionHandle* UGorgeousEventConstructionInterface::GetConstructionHandleByGuid(const FGuid EventGuid)
{
	if (IsEventInConstructionQueue(EventGuid))
	{
		return ConstructionQueue[EventGuid];
	}
	return nullptr;
}

bool UGorgeousEventConstructionInterface::RemoveConstructionHandleFromQueue(UGorgeousConstructionHandle* HandleToRemove, const bool bDeleteHandle)
{
	return RemoveConstructionHandleFromQueueByGuid(HandleToRemove->UniqueEventIdentifier, bDeleteHandle);
}

bool UGorgeousEventConstructionInterface::RemoveConstructionHandleFromQueueByGuid(const FGuid EventGuid, const bool bDeleteHandle)
{
	if (IsEventInConstructionQueue(EventGuid))
	{
		UGorgeousConstructionHandle* Handle = GetConstructionHandleByGuid(EventGuid);
		ConstructionQueue.Remove(EventGuid);
		
		UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Removed construction handle for event: %s with unique identifier: %s from construction queue!"),
			*Handle->EventClass->GetName(), *EventGuid.ToString()),
			"GT.Events.Construction.Queue.RemovedHandle", 2.0f, false, true, this);

		if (bDeleteHandle)
		{
			Handle->MarkAsGarbage();
		}
		
		return true;
	}
	return false;
}

TArray<UGorgeousConstructionHandle*> UGorgeousEventConstructionInterface::ValidateConstructionQueue(
	const bool bShouldRemoveInvalidHandles, const bool bApplyValidationToInstancedVariable, bool& bAllQueuedHandlesValid,
	int32& NumInvalidEvents)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Starting Construction Queue Validation with: \n bShouldRemoveInvalidHandles: %s \n bApplyValidationToInstancedVariable: %s"),
		bShouldRemoveInvalidHandles ? TEXT("True") : TEXT("False"), bApplyValidationToInstancedVariable ? TEXT("True") : TEXT("False")), Logging_Information,
		"GT.Events.Construction.Queue.Validation.Start", 5.0f, true, true, false, this);

	TMap<FGuid, TObjectPtr<UGorgeousConstructionHandle>> TempConstructionQueue = ConstructionQueue;
	
	for ( const auto& ConstructionHandle : TempConstructionQueue)
	{
		if (IsValid(ConstructionHandle.Value))
		{
			UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Construction handle for event: %s is valid"),
				*ConstructionHandle.Value->UniqueEventIdentifier.ToString()), Logging_Success,
				"GT.Events.Construction.Queue.Validation.Valid", 2.0f, false, true, false, this);
		}
		else
		{
			UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Construction handle for event: %s is invalid"),
				*ConstructionHandle.Key.ToString()), Logging_Warning,
				"GT.Events.Construction.Queue.Validation.Invalid", 2.0f, false, true, true, this);

			NumInvalidEvents++;

			if (bShouldRemoveInvalidHandles)
			{
				ConstructionHandle.Value->MarkAsGarbage();
				TempConstructionQueue.Remove(ConstructionHandle.Key);
				UGorgeousLoggingBlueprintFunctionLibrary::LogMessage(FString::Printf(TEXT("Removed construction handle for event: %s"),
					*ConstructionHandle.Key.ToString()), Logging_Information,
					"GT.Events.Construction.Queue.Validation.Removed", 2.0f, false, true, false, this);
			}
		}
	}

	bAllQueuedHandlesValid = NumInvalidEvents == 0;
	
	if (bApplyValidationToInstancedVariable)
	{
		ConstructionQueue = TempConstructionQueue;

		UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("Applied Construction Queue validation from temp queue to main queue.",
			"GT.Events.Construction.Queue.Validation.Applied", 2.0f, false, true, this);
	}
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogSuccessMessage(FString::Printf(TEXT("Finished Construction Queue Validation with: \n bShouldRemoveInvalidHandles: %s \n bApplyValidationToInstancedVariable: %s \n bAllQueuedHandlesValid: %s \n NumInvalidEvents: %d"),
		bShouldRemoveInvalidHandles ? TEXT("True") : TEXT("False"), bApplyValidationToInstancedVariable ? TEXT("True") : TEXT("False"), bAllQueuedHandlesValid ? TEXT("True") : TEXT("False"), NumInvalidEvents),
		"GT.Events.Construction.Queue.Validation.Finished", 5.0f, true, true, this);
	
	TArray<UGorgeousConstructionHandle*> ConstructionQueueArray;
	for (const auto& ConstructionHandle : TempConstructionQueue)
	{
		ConstructionQueueArray.Add(ConstructionHandle.Value);
	}
	return ConstructionQueueArray;
}
