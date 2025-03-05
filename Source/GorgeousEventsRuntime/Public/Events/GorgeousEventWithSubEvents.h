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
#pragma once
#include "GorgeousEvent.h"
#include "GorgeousEventWIthSubEvents.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, Category = "Gorgeous Events", ClassGroup = "Gorgeous Events", Experimental, NotPlaceable,
	meta = (ToolTip = "The base class for all Gorgeous Events with Sub Events."))
class UGorgeousEventWithSubEvents : public UGorgeousEvent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events", Instanced)
	TArray<UGorgeousSubEvent*> SubEvents;

protected:

	virtual void ContinuousEventProcessingLoop_Internal(EGorgeousEventState_E CurrentLoopState, float DeltaTime, int64 CurrentProcessingLoopCount) override;
};
