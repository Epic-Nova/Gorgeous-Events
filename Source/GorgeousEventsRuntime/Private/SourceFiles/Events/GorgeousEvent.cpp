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
#include "GorgeousEvent.h"

#include "ConstructionHandles/GorgeousConstructionHandle.h"
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "Interfaces/GorgeousEventStatisticsInterface.h"

void UGorgeousEvent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UGorgeousEvent::PostInitProperties()
{
	Super::PostInitProperties();

	OnEventStateChangeDelegate.AddLambda([this](const EGorgeousEventState_E OldEventState, const EGorgeousEventState_E NewEventState)
	{
		OnEventStateChanged_Internal(OldEventState, NewEventState);
		OnEventStateChanged(OldEventState, NewEventState);
	});

	ContinuousProcessingLoopDelegate.AddLambda([this](const EGorgeousEventState_E CurrentLoopState, const float DeltaTime, const int64 CurrentProcessingLoopCount)
	{
		ContinuousEventProcessingLoop_Internal(CurrentLoopState, DeltaTime, CurrentProcessingLoopCount);
		ContinuousEventProcessingLoop(CurrentLoopState, DeltaTime, CurrentProcessingLoopCount);
	});

	OnEventTriggeredDelegate.AddLambda([this]()
	{
		OnEventTriggered_Internal();
		OnEventTriggered();
	});

	OnEventInitializedDelegate.AddLambda([this]()
	{
		OnEventInitialized_Internal();
		OnEventInitialized();
	});

	OnEventStartedDelegate.AddLambda([this]()
	{
		OnEventStarted_Internal();
		OnEventStarted();
	});
	
	OnEventProcessingDelegate.AddLambda([this]()
	{
		OnEventProcessing_Internal();
		OnEventProcessing();
	});

	OnEventFinishedDelegate.AddLambda([this]()
	{
		OnEventFinished_Internal();
		OnEventFinished();
	});

	OnEventCanceledDelegate.AddLambda([this]()
	{
		OnEventCanceled_Internal();
		OnEventCanceled();
	});

	OnEventVoidedDelegate.AddLambda([this]()
	{
		OnEventVoided_Internal();
		OnEventVoided();
	});

	OnEventCleanupDelegate.AddLambda([this]()
	{
		OnEventCleanup_Internal();
		OnEventCleanup();
	});
}

void UGorgeousEvent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);


	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGorgeousEvent, bPersist))
	{
		if (bPersist)
		{
			bDestroyImmediately = false;
		}
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGorgeousEvent, bIsDebuggingMode))
	{
		if (!bIsDebuggingMode)
		{
			DebugNotSetVariables.Empty();
		}
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGorgeousEvent, ClassspaceParent))
	{
		if (!ClassspaceParent)
		{
			bUniqueClassspaceExecution = false;
		}
	}
}

UGorgeousEvent::UGorgeousEvent(): TriggerType(EGorgeousEventTriggerType_E::Event_Trigger_Manual), EventState(EGorgeousEventState_E::Event_State_Invalid), bShouldSwitchToOngoing(false),
                                  ConstructionHandleClass(UGorgeousConstructionHandle::StaticClass()), CallingEvent(nullptr), bIsDebuggingMode(false), TriggerReference(nullptr),
                                  GlobalLoggingKey(FGameplayTag::RequestGameplayTag("GT.Events.Global")), SecondsToWait(0.1), EventTimeout(120), CurrentProcessingLoopDelay(1),
                                  PreviousEventState(EGorgeousEventState_E::Event_State_Invalid), bIsUnique(false), AgainstCheck(StaticClass()),
                                  bPersist(false), bDestroyImmediately(false), bUniqueClassspaceExecution(false), bIsEventFinished(false)
{
}

UGorgeousEvent::~UGorgeousEvent()
{
}


void UGorgeousEvent::ContinuousEventProcessingLoop_Internal(EGorgeousEventState_E CurrentLoopState, float DeltaTime,
                                                            int64 CurrentProcessingLoopCount)
{
	switch (CurrentLoopState) {
	case EGorgeousEventState_E::Event_State_Invalid:
		break;
	case EGorgeousEventState_E::Event_State_Triggered:
		break;
	case EGorgeousEventState_E::Event_State_Initialized:
		break;
	case EGorgeousEventState_E::Event_State_Started:
		if (bShouldSwitchToOngoing)
		{
			SwitchToProcessingState_Internal();
		}
		break;
	case EGorgeousEventState_E::Event_State_Processing:
		break;
	case EGorgeousEventState_E::Event_State_Finished:
		break;
	case EGorgeousEventState_E::Event_State_Canceled:
		break;
	case EGorgeousEventState_E::Event_State_Voided:
		break;
	case EGorgeousEventState_E::Event_State_MAX:
		break;
	}
}

void UGorgeousEvent::OnEventStateChanged_Internal(const EGorgeousEventState_E OldEventState,
	const EGorgeousEventState_E NewEventState)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Task %s switched state from: %s to %s"),
	*UniqueIdentifier.ToString(), *GorgeousEnumToString(OldEventState), *GorgeousEnumToString(NewEventState)), EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventTriggered_Internal()
{
	if (CallingEvent)
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("This event: %s was called by another Event: %s"),
			*UniqueIdentifier.ToString(), *CallingEvent->UniqueIdentifier.ToString()), EventLoggingKey.ToString(), 2.f, false, true, this);

		CallingEvent->OnEventFinishedDelegate.AddLambda([this]()
		{
			if (!bPersist)
			{
				UGorgeousEventManagingInterface* EventManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
				if (bDestroyImmediately)
				{
					EventManagingInterface->UnregisterEvent(this);
				}
				else
				{
					EventManagingInterface->CompleteEvent(this);
				}
			}
		});
	}

	if (bIsDebuggingMode)
	{
		UGorgeousEventStatisticsInterface* StatisticsInterface = UGorgeousEventStatisticsInterface::GetEventStatisticsInterface();
		StatisticsInterface->StartEventHeapSnapshot(this);
	}
}

void UGorgeousEvent::OnEventInitialized_Internal()
{
}

void UGorgeousEvent::OnEventStarted_Internal()
{
}

void UGorgeousEvent::OnEventProcessing_Internal()
{
	if (EventTimeout != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(EventTimeoutTimerHandle, [this]
		{
			if (!bIsEventFinished)
			{
				UGorgeousEventManagingInterface* EventManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
				EventManagingInterface->CancelEvent(this);
			}
		}, EventTimeout, false);
	}
}

void UGorgeousEvent::OnEventFinished_Internal()
{
	if (bIsDebuggingMode)
	{
		UGorgeousEventStatisticsInterface* StatisticsInterface = UGorgeousEventStatisticsInterface::GetEventStatisticsInterface();
		StatisticsInterface->StopEventHeapSnapshot(this);
	}
}

void UGorgeousEvent::OnEventCanceled_Internal()
{
}

void UGorgeousEvent::OnEventVoided_Internal()
{
}

void UGorgeousEvent::OnEventCleanup_Internal()
{
}

void UGorgeousEvent::SwitchToStartedState_Internal()
{
	PreviousEventState = EventState;
	EventState = EGorgeousEventState_E::Event_State_Started;
	OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventState);
	OnEventStartedDelegate.Broadcast();
}

void UGorgeousEvent::SwitchToProcessingState_Internal()
{
	PreviousEventState = EventState;
	EventState = EGorgeousEventState_E::Event_State_Processing;
	OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventState);
	OnEventProcessingDelegate.Broadcast();
}

void UGorgeousEvent::OnEventStateChanged_Implementation(const EGorgeousEventState_E OldEventState,
                                                        const EGorgeousEventState_E NewEventState)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventStateChanged for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
		EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::ContinuousEventProcessingLoop_Implementation(EGorgeousEventState_E CurrentLoopState,
                                                                  float DeltaTime, int64 CurrentProcessingLoopCount)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of ContinuousEventProcessingLoop for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
	EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventTriggered_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventTriggered for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventInitialized_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventInitialized for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventStarted_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventStarted for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventProcessing_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventProcessing for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventFinished_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventFinished for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventCanceled_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventCanceled for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventVoided_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventVoided for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEvent::OnEventCleanup_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventCleanup for event with identifier: %s called, no action is performed!"), *UniqueIdentifier.ToString()),
EventLoggingKey.ToString(), 2.f, false, true, this);
}


