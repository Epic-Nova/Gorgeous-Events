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

#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEventAction.generated.h"

class UGorgeousEvent;
DECLARE_MULTICAST_DELEGATE(FOnEventActionStarted);
DECLARE_MULTICAST_DELEGATE(FOnEventActionCompleted);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEventActionTick, float, int64);

UCLASS(Abstract, Blueprintable, BlueprintType, Category = "Gorgeous Events|Actions", ClassGroup = "Gorgeous Events", EditInlineNew, Experimental,
	meta = (ToolTip = "The base class for all Gorgeous Sub Events."))
class UGorgeousEventAction final : public UObject
{
	GENERATED_BODY()

public:

	friend class UGorgeousEventActionsInterface;
	
	virtual void PostInitProperties() override;
	
protected:

	// The class constructor in the protected section, to prevent direct instantiation of this class, and only allow it through friend classes.
	explicit UGorgeousEventAction();

	// The class destructor in the protected section, to prevent direct deletion of this class, and only allow it through friend classes.
	virtual ~UGorgeousEventAction() override;
	
public:

	FOnEventActionStarted OnEventActionStartedDelegate;
	FOnEventActionCompleted OnEventActionCompletedDelegate;
	FOnEventActionTick OnEventActionTickDelegate;


	/**
	 * @brief Called when the SkipType is Conditional Skippable to determine if the event is skipable with custom conditioning.
	 * @return true if the event is skippable, false otherwise
	 * @TODO: Default: The player can skip the event under the default condition that it already has been played at some point in the corresponding save game.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, Category = "Gorgeous Events|Actions")
	bool IsEventActionSkippable();

	/**
	 * @brief Calls CompleteAction on the Event Action Interface to mark the execution of this event action als completed.
	 */
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Actions")
	void CompleteAction() const;
	

	/**
	 * @brief Called when action starts
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Aciton Started", Category = "Gorgeous Events|Actions|Action Callbacks")
	void OnEventActionStarted();

	/**
	 * @brief Called when action completes
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Aciton Completed", Category = "Gorgeous Events|Actions|Action Callbacks")
	void OnEventActionCompleted();
  
	/**
	 * @brief Called when action ticks, this forwards the Current Processing Loop from the event up to the aciton.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Aciton Tick", Category = "Gorgeous Events|Actions|Action Callbacks")
	void OnEventActionTick(float DeltaTime, int64 CurrentProcessingLoopCount);

protected:
	
	//Ruleset for if the action is skippable or not
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events|Actions")
	EGorgeousEventSkipType_E SkipType;
	
	//The reference to the event that is executing this action.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events|Actions")
	UGorgeousEvent* EventReference;
	
protected:

	// The internal function that is called when the event action starts,
	virtual void OnEventActionStarted_Internal();

	// The internal function that is called when the event action completes,
	virtual void OnEventActionCompleted_Internal();

	// The internal function that is called when the event action ticks,
	virtual void OnEventActionTick_Internal(float DeltaTime, int64 CurrentProcessingLoopCount);

private:

	//Weather the event action execution is finished.
	bool bIsRunning;

	//The event action tick delegate handle.
	FDelegateHandle OnEventActionTickDelegateHandle;

	//The name for this action.
	FName ActionName;
	
};