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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events", Instanced)
	TArray<UGorgeousSubEvent*> SubEvents;

	/**
	 * @brief Weather the execution of a specific sub event is finished or not
	 * @param SubEvent The sub event to perform the check on
	 * @return True if the execution is finished.
	 */
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Sub Events")
	bool IsSubEventFinished(const UGorgeousSubEvent* SubEvent);

	/**
	 * @brief Registers a new Sub Event to this event
	 *
	 * @param EventToTrigger The event that should be registered to the sub events.
	 */
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Sub Events")
	void ManuallyRegisterSubEvent(TSoftClassPtr<UGorgeousSubEvent> EventToTrigger);
	
	/**
	 * @brief Called when ManuallyRegisterSubEvent is called to assign the construction event variables.
	 * 
	 * @param ConstructionHandle The construction handle of a queried event to register
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Gorgeous Events")
	void AssignConstructionEventVariables(UGorgeousConstructionHandle* ConstructionHandle);

protected:

	virtual void ContinuousEventProcessingLoop_Internal(EGorgeousEventState_E CurrentLoopState, float DeltaTime, int64 CurrentProcessingLoopCount) override;

	UFUNCTION()
	void OnEventConstructionQueued(UGorgeousConstructionHandle* ConstructionHandle);
};
