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
#include "GorgeousEvent.h"

#include "ConstructionHandles/GorgeousConstructionHandle.h"

void UGorgeousEvent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
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
}

void UGorgeousEvent::OnEventTriggered_Internal()
{
}

void UGorgeousEvent::OnEventInitialized_Internal()
{
}

void UGorgeousEvent::OnEventStarted_Internal()
{
}

void UGorgeousEvent::OnEventProcessing_Internal()
{
}

void UGorgeousEvent::OnEventFinished_Internal()
{
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

void UGorgeousEvent::ContinuousEventProcessingLoop_Implementation(EGorgeousEventState_E CurrentLoopState,
                                                                  float DeltaTime, int64 CurrentProcessingLoopCount)
{
}

void UGorgeousEvent::OnEventTriggered_Implementation()
{
}

void UGorgeousEvent::OnEventInitialized_Implementation()
{
}

void UGorgeousEvent::OnEventStarted_Implementation()
{
}

void UGorgeousEvent::OnEventProcessing_Implementation()
{
}

void UGorgeousEvent::OnEventFinished_Implementation()
{
}

void UGorgeousEvent::OnEventCanceled_Implementation()
{
}

void UGorgeousEvent::OnEventVoided_Implementation()
{
}

void UGorgeousEvent::OnEventCleanup_Implementation()
{
}



