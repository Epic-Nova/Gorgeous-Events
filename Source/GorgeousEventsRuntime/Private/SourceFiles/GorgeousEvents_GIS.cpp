﻿// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|         that has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "GorgeousEvents_GIS.h"
TObjectPtr<UGorgeousEvents_GIS> UGorgeousEvents_GIS::StaticEventsGISInstance = nullptr;

void UGorgeousEvents_GIS::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	for (TPair InterfacePair : EventInterfaces)
	{
		RegisterEventInterface(InterfacePair.Key, nullptr);
	}

	StaticEventsGISInstance = this;
}

UGorgeousEvents_GIS::UGorgeousEvents_GIS()
{
	//Default Event Interfaces
	EventInterfaces = TMap<TSubclassOf<UGorgeousEventInterface>, TSubclassOf<UGorgeousEventInterface>>
	{
		{UGorgeousEventActionsInterface::StaticClass(), UGorgeousEventActionsInterface::StaticClass()},
		{UGorgeousEventConstructionInterface::StaticClass(), UGorgeousEventConstructionInterface::StaticClass()},
		{UGorgeousEventFreezingInterface::StaticClass(), UGorgeousEventFreezingInterface::StaticClass()},
		{UGorgeousEventLockingInterface::StaticClass(), UGorgeousEventLockingInterface::StaticClass()},
		{UGorgeousEventManagingInterface::StaticClass(), UGorgeousEventManagingInterface::StaticClass()},
		{UGorgeousEventStatisticsInterface::StaticClass(), UGorgeousEventStatisticsInterface::StaticClass()},
		{UGorgeousEventVoidingInterface::StaticClass(), UGorgeousEventVoidingInterface::StaticClass()}
	};
}

void UGorgeousEvents_GIS::OverrideDefaultEventInterface(const TSubclassOf<UGorgeousEventInterface> DefaultInterface,
                                                        const TSubclassOf<UGorgeousEventInterface> OverrideInterface)
{
	if (!DefaultInterface || !OverrideInterface)
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogFatalMessage("Check if DefaultInterface or OverrideInterface is valid!", "GT.Events.GIS.Interface.Not_Valid");
		return;
	}
	
	bool bFound = false;
	for (const auto& Pair : EventInterfaces)
	{
		if (Pair.Key == DefaultInterface || DefaultInterface->IsChildOf(Pair.Key))
		{
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("The default interface %s (or a parent of it) is not registered in the event interfaces map."), *DefaultInterface->GetName()),
			"GT.Events.GIS.Interface.Not_Registered");
	}
	else
	{
		EventInterfaces[DefaultInterface] = OverrideInterface;
		
		EventInterfaceInstances.Remove(DefaultInterface);
		RegisterEventInterface(DefaultInterface, EventInterfaceInstances[DefaultInterface]);
	}
}

TObjectPtr<UGorgeousEventInterface> UGorgeousEvents_GIS::GetRegisteredEventsInterfaceForSubclass(
	const TSubclassOf<UGorgeousEventInterface>& InterfaceSubclassOf)
{
	for (const auto& Pair : EventInterfaceInstances)
	{
		if (Pair.Key == InterfaceSubclassOf || InterfaceSubclassOf->IsChildOf(Pair.Key))
		{
			return Pair.Value;
		}
	}
	
	return nullptr;
}

void UGorgeousEvents_GIS::RegisterEventInterface(const TSubclassOf<UGorgeousEventInterface>& InterfaceToRegister, UGorgeousEventInterface* OldInterface)
{
	for (const auto& Pair : EventInterfaceInstances)
	{
		if (InterfaceToRegister->IsChildOf(Pair.Key))
		{
			UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("The interface %s or a child class is already registered in the event interface instances map."), *InterfaceToRegister->GetName()),
				"GT.Events.GIS.Interface.Already_Registered");
			return;
		}
	}

	if (!EventInterfaces.Contains(InterfaceToRegister))
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("The interface %s is not registered in the event interfaces map."), *InterfaceToRegister->GetName()),
			"GT.Events.GIS.Interface.Not_Registered");
	}
	else
	{
		UGorgeousEventInterface* NewInterface = NewObject<UGorgeousEventInterface>(this, InterfaceToRegister);
		EventInterfaceInstances.Add(InterfaceToRegister, NewInterface);


		if (!OldInterface)
			return;
		
		/**
		 * Functionality to update the failsafe reference or the outer when either one of the crutial managing interfaces changes
		 **/
		if (NewInterface->IsA<UGorgeousEventManagingInterface>())
		{
			for (const UGorgeousEventManagingInterface* ManagingInterface = Cast<UGorgeousEventManagingInterface>(OldInterface); const auto Event : ManagingInterface->GetRegisteredEvents())
			{
				Event->SetCachedOwner(NewInterface);
			}
		}
		else if (NewInterface->IsA<UGorgeousEventConstructionInterface>())
		{
			for (const UGorgeousEventManagingInterface* ManagingInterface = Cast<UGorgeousEventManagingInterface>(OldInterface); const auto Event : ManagingInterface->GetRegisteredEvents())
			{
				Event->Rename(*Event->GetName(), NewInterface);
			}
		}

		OldInterface->MarkAsGarbage();
	}
	
}