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
#include "AsyncActions/GorgeousEventAsyncAction.h"

void UGorgeousEventAsyncAction::Activate()
{
	FTimerHandle TimerHandle;
	GWorld->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		OnCompleted.Broadcast(EventName + TEXT(" Completed!"));
	}, 2.0f, false);
}

UGorgeousEventAsyncAction* UGorgeousEventAsyncAction::TriggerGorgeousEvent(FString EventName)
{
	UGorgeousEventAsyncAction* Action = NewObject<UGorgeousEventAsyncAction>();
	Action->EventName = EventName;
	return Action;
}
