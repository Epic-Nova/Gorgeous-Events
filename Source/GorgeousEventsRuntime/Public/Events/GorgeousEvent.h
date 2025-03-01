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

//<=============================--- Pragmas ---==============================>
#pragma once
//<-------------------------------------------------------------------------->

//<=============================--- Includes ---=============================>
//<-------------------------=== Module Includes ===-------------------------->
#include "GorgeousBaseWorldContextUObject.h"
#include "GorgeousEventsRuntimeMinimal.h"
//--------------=== Third Party & Miscellaneous Includes ===----------------->
#include "GorgeousEvent.generated.h"
//<-------------------------------------------------------------------------->

//<===========--- Forward Declarations ---===========>
class UGorgeousConstructionHandle;
class AEventTrigger_A;
//<-------------------------------------------------->

//<=================--- Delegates ---=================>

// The delegate for the state change of the event.
DECLARE_MULTICAST_DELEGATE_TwoParams(FGorgeousEventStateChanged, EGorgeousEventState_E, EGorgeousEventState_E);

// The delegate for the continuous processing loop
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGorgeousEventContinuousProcessingLoop, EGorgeousEventState_E, float, int64);

// The delegate for the event trigger.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventTriggered);

// The delegate for the event initialization.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventInitialized);

// The delegate for the event start.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventStarted);

// The delegate for the event processing.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventProcessing);

// The delegate for the event finish.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventFinished);

// The delegate for the event cancel.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventCanceled);

// The delegate for the event void.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventVoided);

// The delegate for the event cleanup.
DECLARE_MULTICAST_DELEGATE(FGorgeousEventCleanup);

//<--------------------------------------------------->

//<=====================--- Class Macro Definitions ---======================>
//<-------------------------------------------------------------------------->

/*============================--- Class Info ---============================>
<-----------------------------=== Quick Info ===---------------------------->
| Display Name: Gorgeous Event
| Functional Name: GorgeousEvent
| Parent Class: /Script/Engine.UObject
| Class Suffix: GE
| Author: Nils Bergemann
<--------------------------------------------------------------------------->
<--------------------------=== Class Description ===------------------------>
| The Gorgeous Event class is responsible, for, to provide the overridable
| handle functions that are used by the child events.
| Also it provides the basic functionality for the event system, that is
| tightly integrated by most of the Gorgeous Things plugins.
<--------------------------------------------------------------------------->
<---------------------------=== TODOs & Notes ===--------------------------->
<--------------------------------------------------------------------------->
<==========================================================================*/
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "Gorgeous Event", Category = "Gorgeous Events", ClassGroup = "Gorgeous Events", EditInlineNew, Experimental, NotPlaceable, PerObjectConfig, Transient, Within = GorgeousConstructionHandle,
	meta = (ToolTip = "The base class for all Gorgeous Events.", ShortTooltip = "Gorgeous Event", ExposedAsyncProxy = GorgeousEventAsyncAction))
class GORGEOUSEVENTSRUNTIME_API UGorgeousEvent : public UGorgeousObjectVariable
{
	GENERATED_BODY()

	//<================--- Friend Classes ---================>
	friend class UGorgeousEventManagingInterface;
	friend class UGorgeousUniqueClassspaceExecutionVoidingContext;
	//<------------------------------------------------------>
	
	
	//<============================--- Overrides ---============================>
public:

	// Definition for variables that are replicated.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// The equivalent to the OnConstruction function in the Unreal Engine.
	virtual void PostInitProperties() override;
	
	// Used to change the values of properties to comply with the edit condition meta tags
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
protected:

	// The class constructor in the protected section, to prevent direct instantiation of this class, and only allow it through friend classes.
	explicit UGorgeousEvent();

	// The class destructor in the protected section, to prevent direct deletion of this class, and only allow it through friend classes.
	virtual ~UGorgeousEvent() override;

	
private:
	
	//<------------------------------------------------------------------------->

	
	//<============================--- Callbacks ---============================>
public:

	FGorgeousEventStateChanged OnEventStateChangeDelegate;

	FGorgeousEventContinuousProcessingLoop ContinuousProcessingLoopDelegate;

	FGorgeousEventTriggered OnEventTriggeredDelegate;

	FGorgeousEventInitialized OnEventInitializedDelegate;

	FGorgeousEventStarted OnEventStartedDelegate;

	FGorgeousEventProcessing OnEventProcessingDelegate;

	FGorgeousEventFinished OnEventFinishedDelegate;

	FGorgeousEventCanceled OnEventCanceledDelegate;

	FGorgeousEventVoided OnEventVoidedDelegate;

	FGorgeousEventCleanup OnEventCleanupDelegate;
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<=======================--- Blueprint Functions ---=======================>
public:
	
	/**
	 * @brief Called when this event is processing continuously. This function is used to process the event continuously.
	 * 
	 * @param CurrentLoopState The current event state in the loop.
	 * @param DeltaTime The time that has passed since the last loop.
	 * @param CurrentProcessingLoopCount The current loop count.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "Continuous Event Processing Loop", Category = "Gorgeous Events|Event Callbacks")
	void ContinuousEventProcessingLoop(EGorgeousEventState_E CurrentLoopState, float DeltaTime, int64 CurrentProcessingLoopCount);

	/**
	 * @brief Called when this event state changes.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On State Changed", Category = "Gorgeous Events|Event Callbacks")
	void OnEventStateChanged(EGorgeousEventState_E OldEventState, EGorgeousEventState_E NewEventState);
	
	/**
	 * @brief Called when this event is triggered. This function is used to start the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Triggered", Category = "Gorgeous Events|Event Callbacks")
	void OnEventTriggered();

	/**
	 * @brief Called when this event is initialized. This function is used to initialize the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Initialized", Category = "Gorgeous Events|Event Callbacks")
	void OnEventInitialized();

	/**
	 * @brief Called when this event is started. This function is used to start the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Started", Category = "Gorgeous Events|Event Callbacks")
	void OnEventStarted();

	/**
	 * @brief Called when this event is processing. This function is used to process the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Processing", Category = "Gorgeous Events|Event Callbacks")
	void OnEventProcessing();

	/**
	 * @brief Called when this event is finished. This function is used to finish the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Finished", Category = "Gorgeous Events|Event Callbacks")
	void OnEventFinished();

	/**
	 * @brief Called when this event is canceled. This function is used to cancel the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Canceled", Category = "Gorgeous Events|Event Callbacks")
	void OnEventCanceled();

	/**
	 * @brief Called when this event is voided. This function is used to void the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Voided", Category = "Gorgeous Events|Event Callbacks")
	void OnEventVoided();
	
	/**
	 * @brief Called when this event is cleaned up. This function is used to clean up the event.
	 */
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Event Cleanup", Category = "Gorgeous Events|Event Callbacks")
	void OnEventCleanup();


	/**
	 * @brief Returns the class-space parent that is sharing data with its child events.
	 * @return The classspace parent that provides data to children 
	 */
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Classspace")
	UGorgeousEvent* GetClassspaceParent() const;

	/**
	 * @brief Return the children within a class-space. This function only works on class-pace parents.
	 * @return Child events contained in the clas-space.
	 */
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Classspace")
	TArray<UGorgeousEvent*> GetClassspaceChildren() const;
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<====================--- UAT/UBT Exposed Variables ---====================>
public:

	//Under what condition will this event be triggered.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events")
	EGorgeousEventTriggerType_E TriggerType;

	//THe current state of the event.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events")
	EGorgeousEventState_E EventState;

	//Weather the event should switch to the ongoing state. This can be used by events that called another event, after the property initialisation.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gorgeous Events")
	bool bShouldSwitchToOngoing;
	
	
	//The class pointer reference to the default construction handle for this event.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events|Construction")
	TSubclassOf<UGorgeousConstructionHandle> ConstructionHandleClass;
	
	
	//A pointer to the event that called this one if any.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events|Calling Event")
	UGorgeousEvent* CallingEvent;


	//Weather this event should be in the debugging mode to provide more infos that usual.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gorgeous Events|Debugging")
	bool bIsDebuggingMode;
	
	//A list of variables that should me simulated to be not set, including Object Variables.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gorgeous Events|Debugging", meta = (EditCondition = "bIsDebuggingMode"))
	TArray<FName> DebugNotSetVariables;

protected:
	
	//The trigger that kicked off the execution of this event.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events")
	AEventTrigger_A* TriggerReference;
	
	//The logging key that should be used for global logging entries.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events|Logging")
	FGameplayTag GlobalLoggingKey;

	//The logging key that should be used for logging entries specific to this event.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events|Logging")
	FGameplayTag EventLoggingKey;

private:
	
	//The seconds to wait for the switch from the triggered state to the started state of the event.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events", DisplayName = "Seconds to Wait (on Triggered to Started state)")
	float SecondsToWait;
	
	//The timeout in seconds for the processing state of the event.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events", DisplayName = "Event Timeout (Processing State)")
	float EventTimeout;
	
	//The delay between the processing loop ticks.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events")
	float CurrentProcessingLoopDelay;
	
	//The event state before the current event state.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events", meta = (AllowPrivateAccess))
	EGorgeousEventState_E PreviousEventState;

	//Weather only one instance if this class should be able to be executed at the same time.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events")
	bool bIsUnique;
	
	//The class to check against for to determine if this class is a class providing base event functionality.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events")
	TSubclassOf<UGorgeousEvent> AgainstCheck;

	
	//Should this event persist after the execution of the calling event is finished.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gorgeous Events|Calling Event", DisplayName = "Persist aftter Calling Event is Completed", meta = (AllowPrivateAccess))
	bool bPersist;

	//Should this event be destroyed immediately after the calling event is finished or should the destruction process be initiated.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gorgeous Events|Calling Event", meta = (EditCondition = "!bPersist", AllowPrivateAccess))
	bool bDestroyImmediately;

	
	//Only one Event Execution of childs are allowed that inherit from ClassspaceParent.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events|Classspace", meta = (EditCondition = "ClassspaceParent != nullptr", EditConditionHides))
	bool bUniqueClassspaceExecution;

	//The class that should be used for the classspace against check.
	UPROPERTY(EditDefaultsOnly, Category = "Gorgeous Events|Classspace")
	TSubclassOf<UGorgeousEvent> ClassspaceParent;
	//<------------------------------------------------------------------------->

	
	//<============================--- C++ Only ---=============================>
public:

protected:

	/**
	 * @brief The internal function that is called when the event is processing continuously.
	 * 
	 * @param CurrentLoopState The current event state in the loop.
	 * @param DeltaTime The time that has passed since the last loop.
	 * @param CurrentProcessingLoopCount The current loop count.
	 */
	virtual void ContinuousEventProcessingLoop_Internal(EGorgeousEventState_E CurrentLoopState, float DeltaTime, int64 CurrentProcessingLoopCount);

	// The internal function that is called when the event state changes
	virtual void OnEventStateChanged_Internal(EGorgeousEventState_E OldEventState, EGorgeousEventState_E NewEventState);
	
	// The internal function that is called when the event is triggered.
	virtual void OnEventTriggered_Internal();

	// The internal function that is called when the event is initialized.
	virtual void OnEventInitialized_Internal();
	
	// The internal function that is called when the event is started.
	virtual void OnEventStarted_Internal();
	
	// The internal function that is called when the event is processing.
	virtual void OnEventProcessing_Internal();

	// The internal function that is called when the event is finished.
	virtual void OnEventFinished_Internal();

	// The internal function that is called when the event is canceled.
	virtual void OnEventCanceled_Internal();
	
	// The internal function that is called when the event is voided.
	virtual void OnEventVoided_Internal();

	// The internal function that is called when the event is cleaned up.
	virtual void OnEventCleanup_Internal();
	
private:

	// The internal function that is called when the event should switch to the ongoing state
	void SwitchToStartedState_Internal();
	
	// The internal function that is called when the event should switch to the ongoing state
	void SwitchToProcessingState_Internal();

	//<------------------------------------------------------------------------->

	
	//<============================--- Variables ---============================>
public:
	
protected:

private:

	//Weather the event execution is finished and nothing else is going to kick of anymore.
	bool bIsEventFinished;

	//The timer handle to the event timeout. Only valid if the event timeout variable is set.
	FTimerHandle EventTimeoutTimerHandle;
	
	//<------------------------------------------------------------------------->
};

//<=============================--- Inline Definitions ---=============================>
//<------------------------------------------------------------------------------------>

//<=============================--- Pragma Un-Defines ---============================>
//<---------------------------------------------------------------------------------->
