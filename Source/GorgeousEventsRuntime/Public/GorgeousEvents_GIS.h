// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|			    Gorgeous Events - Events functionality provider				|
| ------------------------------------------------------------------------- |
|		  Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,			|
|			  administrated by Epic Nova. All rights reserved.				|
| ------------------------------------------------------------------------- |
|					Epic Nova is an independent entity,						|
|	    that has nothing in common with Epic Games in any capacity.			|
<==========================================================================*/

//<=============================--- Pragmas ---==============================>
#pragma once
//<-------------------------------------------------------------------------->

//<=============================--- Includes ---=============================>
//<-------------------------=== Module Includes ===-------------------------->
#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEvent.h"
#include "Interfaces/GorgeousEventActionsInterface.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "Interfaces/GorgeousEventFreezingInterface.h"
#include "Interfaces/GorgeousEventLockingInterface.h"
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "Interfaces/GorgeousEventStatisticsInterface.h"
#include "Interfaces/GorgeousEventVoidingInterface.h"
//--------------=== Third Party & Miscellaneous Includes ===----------------->
#include "GorgeousEvents_GIS.generated.h"
//<-------------------------------------------------------------------------->

//<===========--- Forward Declarations ---===========>
//<-------------------------------------------------->

//<=================--- Delegates ---=================>
//<--------------------------------------------------->

//<=====================--- Class Macro Definitions ---======================>
//<-------------------------------------------------------------------------->

/*============================--- Class Info ---============================>
<-----------------------------=== Quick Info ===---------------------------->
| Display Name: Gorgeous Events Game Instance Subsystem
| Functional Name: GorgeousEvents_GIS
| Parent Class: /Script/Engine.UGameInstanceSubsystem
| Class Suffix: GIS
| Author: Nils Bergemann
<--------------------------------------------------------------------------->
<--------------------------=== Class Description ===------------------------>
| The Gorgeous Events Game Instance Subsystem class is responsible, for,
| to provide callable functions as a wrapper that can be called and
| overwritten by setting the corresponding pointer to a function library.
<--------------------------------------------------------------------------->
<==========================================================================*/
UCLASS(BlueprintType, DisplayName = "Gorgeous Events", Category = "Gorgeous Events", ClassGroup = "Gorgeous Events", Experimental, Transient,
	meta = (ToolTip = "Game Instance Subsystem that provides callable functionalities through a coresponding function library.", ShortTooltip = "Gorgeous Events Game Instance Subsystem"))
class GORGEOUSEVENTSRUNTIME_API UGorgeousEvents_GIS : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	//<================--- Friend Classes ---================>
	//<------------------------------------------------------>
	
	//<============================--- Overrides ---============================>
public:

	//Override for when the subsystem is initialized.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static TObjectPtr<UGorgeousEvents_GIS> StaticEventsGISInstance;
	
protected:
	
private:

	UGorgeousEvents_GIS();
	
	//<------------------------------------------------------------------------->

	
	//<============================--- Callbacks ---============================>
public:
	
protected:
	
private:
	
	//<------------------------------------------------------------------------->

	
	//<=======================--- Blueprint Functions ---=======================>
public:
	/**
	 * Overrides the default event interface for a specific defined class you want.
	 * Note that when doing so that every current registered event will lose their outer and therefore will be invalid and garbage collected.
	 *
	 * 
	 * @param DefaultInterface The interface that is normaly in this place.
	 * @param OverrideInterface The interface that should replace the default one.
	 */
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events")
	void OverrideDefaultEventInterface(TSubclassOf<UGorgeousEventInterface> DefaultInterface, TSubclassOf<UGorgeousEventInterface> OverrideInterface);
	
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

	TObjectPtr<UGorgeousEventInterface> GetRegisteredEventsInterfaceForSubclass(const TSubclassOf<UGorgeousEventInterface>& InterfaceSubclassOf);

protected:

private:

	//Registers an event interface as instance for calling the function implementations for the events under the condition that the interface is listed as a default interface.
	void RegisterEventInterface(const TSubclassOf<UGorgeousEventInterface>& InterfaceToRegister, UGorgeousEventInterface* OldInterface);

	//<------------------------------------------------------------------------->

	
	//<============================--- Variables ---============================>
public:
	
protected:

private:

	//The interfaces that are used for calling the function implementations for the events.
	TMap<TSubclassOf<UGorgeousEventInterface>, TSubclassOf<UGorgeousEventInterface>> EventInterfaces;

	//The instances of the interfaces that are used for calling the function implementations for the events.
	TMap<TSubclassOf<UGorgeousEventInterface>, TObjectPtr<UGorgeousEventInterface>> EventInterfaceInstances;
	
	//<------------------------------------------------------------------------->
};

//<=============================--- Inline Definitions ---=============================>
//<------------------------------------------------------------------------------------>

//<=============================--- Pragma Un-Defines ---============================>
#undef DISPLAY_NAME
#undef CATEGORY_NAME
//<---------------------------------------------------------------------------------->