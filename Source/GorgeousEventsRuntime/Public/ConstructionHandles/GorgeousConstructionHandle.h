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
#include "GorgeousEvent.h"
//--------------=== Third Party & Miscellaneous Includes ===----------------->
#include "GorgeousConstructionHandle.generated.h"
//<-------------------------------------------------------------------------->

//<===========--- Forward Declarations ---===========>
//<-------------------------------------------------->

//<=================--- Delegates ---=================>

class UGorgeousAssignmentMapper;
// The delegate for the construction handle queued.
DECLARE_MULTICAST_DELEGATE(FGorgeousConstructionHandleQueued);

// The delegate for the construction handle started.
DECLARE_MULTICAST_DELEGATE_OneParam(FGorgeousConstructionHandleStarted, UGorgeousEvent*)

// The delegate for when the construction of the event is finished.
DECLARE_MULTICAST_DELEGATE(FGorgeousConstructionFinished)

// The delegate for the construction handle cleanup.
DECLARE_MULTICAST_DELEGATE(FGorgeousConstructionHandleCleanup);

//<--------------------------------------------------->

//<=====================--- Class Macro Definitions ---======================>
//<-------------------------------------------------------------------------->

/*============================--- Class Info ---============================>
<-----------------------------=== Quick Info ===---------------------------->
| Display Name: -
| Functional Name: -
| Parent Class: /Script/Engine.UObject
| Class Suffix: GCH
| Author: Nils Bergemann
<--------------------------------------------------------------------------->
<--------------------------=== Class Description ===------------------------>
| The Gorgeous Construction Handle class is responsible, for, to provide
| the overridable handle functions that are used by the child construction
| handles. It is responsible for handing over variables that are set by the
| object variable system during the construction of the event.
<--------------------------------------------------------------------------->
<==========================================================================*/
UCLASS(Blueprintable, BlueprintType, DisplayName = "Gorgeous Construction Handle", Category = "Gorgeous Events|Gorgeous Construction Handles", ClassGroup = "Gorgeous Events", Experimental, Transient,
	meta = (ToolTip = "The base class for all Gorgeous Construction Handles", ShortTooltip = "Gorgeous Construction Handle", ShowWorldContextPin))
class GORGEOUSEVENTSRUNTIME_API UGorgeousConstructionHandle : public UObject

{
	GENERATED_BODY()

	//<================--- Friend Classes ---================>
	//<------------------------------------------------------>
	
	//<============================--- Overrides ---============================>
public:

	UGorgeousConstructionHandle();
	
	// The equivalent to the OnConstruction function in the Unreal Engine.
	virtual void PostInitProperties() override;
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<============================--- Callbacks ---============================>
public:

	// This delegate can be called from anyone to queue the construction. The construction handle will then call the OnConstructionQueued_Internal and OnConstructionQueued function.
	FGorgeousConstructionHandleQueued OnConstructionQueuedDelegate;
	
	// This delegate can be called from anyone to start the construction. The construction handle will then call the OnConstructionStarted_Internal and OnConstructionStarted function.
	FGorgeousConstructionHandleStarted OnConstructionStartedDelegate;

	// This delegate is called from within this class to signalize that the construction is finished.
	FGorgeousConstructionFinished OnConstructionFinishedDelegate;

	// The delegate that is called when the construction is cleaned up. The construction handle will then call the OnConstructionCleanup_Internal and OnConstructionCleanup function.
	FGorgeousConstructionHandleCleanup OnConstructionCleanupDelegate;
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<=======================--- Blueprint Functions ---=======================>
public:

	// The event that is called when the construction is queued.
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Construction Queued", Category = "Gorgeous Events|Gorgeous Construction Handles")
	void OnConstructionQueued();
	
	// The event that is called when the construction is started.
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Construction Started", Category = "Gorgeous Events|Gorgeous Construction Handles")
	void OnConstructionStarted(UGorgeousEvent* Event);

	// The event that is called when the construction is cleaned up.
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Construction Cleanup", Category = "Gorgeous Events|Gorgeous Construction Handles")
	void OnConstructionCleanup();


	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Gorgeous Construction Handles")
	UGorgeousAssignmentMapper* GetAssigmentMapper();
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<====================--- UAT/UBT Exposed Variables ---====================>
public:

protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<============================--- C++ Only ---=============================>
public:

	//The event class that should be constructed by this construction handle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gorgeous Events|Gorgeous Construction Handles", meta = (ExposeOnSpawn = true))
	TSubclassOf<UGorgeousEvent> EventClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gorgeous Events|Gorgeous Construction Handles", meta = (ExposeOnSpawn = true))
	TSubclassOf<UGorgeousAssignmentMapper> CorrespondingAssigmentMapper;

	//The unique identifier associated with the constructing event
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gorgeous Events|Gorgeous Construction Handles", meta = ( ExposeOnSpawn = true))
	FGuid UniqueEventIdentifier;

protected:

	// The internal function that is called when the construction is queued.
	virtual void OnConstructionQueued_Internal();
	
	// The internal function that is called when the construction is started.
	virtual void OnConstructionStarted_Internal(UGorgeousEvent* Event);

	// The internal function that is called when the construction is cleaned up.
	virtual void OnConstructionCleanup_Internal();

private:

	//<------------------------------------------------------------------------->

	
	//<============================--- Variables ---============================>
public:
	
protected:

private:

	TObjectPtr<UGorgeousAssignmentMapper> AssigmentMapperReference;
	
	//<------------------------------------------------------------------------->
};

//<=============================--- Inline Definitions ---=============================>
//<------------------------------------------------------------------------------------>

//<=============================--- Pragma Un-Defines ---============================>
//<---------------------------------------------------------------------------------->