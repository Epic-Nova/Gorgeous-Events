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
#include "GorgeousEventWithSubEvents.h"
#include "SubEvents/GorgeousSubEvent.h"

void UGorgeousEventWithSubEvents::ContinuousEventProcessingLoop_Internal(EGorgeousEventState_E CurrentLoopState,
                                                                         float DeltaTime, int64 CurrentProcessingLoopCount)
{
	Super::ContinuousEventProcessingLoop_Internal(CurrentLoopState, DeltaTime, CurrentProcessingLoopCount);

	for (const auto SubEvent : SubEvents)
	{
		if (SubEvent->RunOnParentState == CurrentLoopState)
		{
			SubEvent->SetParent(this);
			SubEvent->CallingEvent = this;
			SubEvent->InvokeInstancedFunctionality();
		}
	}
}
