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

#include "GorgeousSubEvent.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, Category = "Gorgeous Events|Sub Events", ClassGroup = "Gorgeous Events", EditInlineNew, Experimental, NotPlaceable,
	meta = (ToolTip = "The base class for all Gorgeous Sub Events."))
class UGorgeousSubEvent : public UGorgeousEvent
{
	GENERATED_BODY()
	
	friend class UGorgeousEvent;

public:

	//The state that the executing event needs for this event to be kicked off.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events")
	EGorgeousEventState_E RunOnParentState;
};

//@TODO: Subevents are events that use the data from the invoking event to satisfy their execution. So they theoretically don't need extra data and can be invoked by the parent event at any given time