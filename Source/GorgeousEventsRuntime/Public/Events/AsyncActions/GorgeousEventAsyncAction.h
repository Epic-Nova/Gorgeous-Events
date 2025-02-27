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
#include "GorgeousEventsRuntimeMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
//--------------=== Third Party & Miscellaneous Includes ===----------------->
#include "GorgeousEventAsyncAction.generated.h"
//<-------------------------------------------------------------------------->

//<===========--- Forward Declarations ---===========>
//<-------------------------------------------------->

//<=================--- Delegates ---=================>
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGorgeousEventCompleted, FString, EventResult);
//<--------------------------------------------------->

//<=====================--- Class Macro Definitions ---======================>
//<-------------------------------------------------------------------------->

/*============================--- Class Info ---============================>
<-----------------------------=== Quick Info ===---------------------------->
| Display Name: -
| Functional Name: -
| Parent Class: /Script/Engine.UBlueprintAsyncActionBase
| Class Suffix: -
| Author: Nils Bergemann
<--------------------------------------------------------------------------->
<--------------------------=== Class Description ===------------------------>
| Used for executing an event asynchronously. When using this node the
| opportunity of using the event construction handle system that assigns
| object variables at construction time is not possible anymore.
<--------------------------------------------------------------------------->
<---------------------------=== TODOs & Notes ===--------------------------->
@TODO: Make this class compatible with the construction handle system by implementing dynamic behavior where object variables can be added through an array. The construction handle is then handled by this class.
<--------------------------------------------------------------------------->
<==========================================================================*/
UCLASS(Blueprintable, BlueprintType, DisplayName = "Gorgeous Event Async Action", Category = "Gorgeous Events", ClassGroup = "Gorgeous Events",
	meta = (ToolTip = "Used for executing an event asynchronously. When using this node the opportunity of using the event construction handle system that assigns object variables at construction time is not possible anymore.", ShortTooltip = "Gorgeous Event Async Action"))
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	//<================--- Friend Classes ---================>
	//<------------------------------------------------------>
	
	//<============================--- Overrides ---============================>
public:

	// The activation function for the async action.
	virtual void Activate() override;
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<============================--- Callbacks ---============================>
public:
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<=======================--- Blueprint Functions ---=======================>
public:
	/**
	 * @brief Triggers a Gorgeous Event with the given name.
	 * @param EventName The name of the event to trigger.
	 * @return A new instance of the Gorgeous Event Async Action.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Gorgeous Events")
	static UGorgeousEventAsyncAction* TriggerGorgeousEvent(FString EventName);
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<====================--- UAT/UBT Exposed Variables ---====================>
public:
	
	UPROPERTY(BlueprintAssignable)
	FGorgeousEventCompleted OnCompleted;

protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<============================--- C++ Only ---=============================>
public:

protected:
	
private:

	//<------------------------------------------------------------------------->

	
	//<============================--- Variables ---============================>
public:
	
protected:

private:

	// The name of the event to trigger.
	FString EventName;
	
	//<------------------------------------------------------------------------->
};

//<=============================--- Inline Definitions ---=============================>
//<------------------------------------------------------------------------------------>

//<=============================--- Pragma Un-Defines ---============================>
//<---------------------------------------------------------------------------------->
