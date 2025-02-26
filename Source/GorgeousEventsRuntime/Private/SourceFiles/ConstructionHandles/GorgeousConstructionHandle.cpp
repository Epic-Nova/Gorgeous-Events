// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|               Gorgeous Core - Core functionality provider                 |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|      that is has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "ConstructionHandles/GorgeousConstructionHandle.h"

void UGorgeousConstructionHandle::PostInitProperties()
{
	UObject::PostInitProperties();

	OnConstructionQueuedDelegate.AddLambda([this]()
	{
		OnConstructionQueued_Internal();
		OnConstructionQueued();
	});
	
	OnConstructionStartedDelegate.AddLambda([this](UGorgeousEvent* Event)
	{
		OnConstructionStarted_Internal(Event);
		OnConstructionStarted(Event);
	});

	OnConstructionCleanupDelegate.AddLambda([this]()
	{
		OnConstructionCleanup_Internal();
		OnConstructionCleanup();
	});
}

void UGorgeousConstructionHandle::OnConstructionQueued_Internal()
{
 // DO some preperations and the kick of the construction right away under the condition that the construction is allowed (Needed construction object variables must have been set first)
}

void UGorgeousConstructionHandle::OnConstructionStarted_Internal(UGorgeousEvent* Event)
{
	// Flush the assignment requests from the construction object variables to the constructing event
}

void UGorgeousConstructionHandle::OnConstructionCleanup_Internal()
{
	MarkAsGarbage();
}

void UGorgeousConstructionHandle::OnConstructionQueued_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage("Default implementation of OnConstructionQueued called. This should be overridden in the child class.",
		"GT.Events.Construction.Queue.DefaultQueued");
}

void UGorgeousConstructionHandle::OnConstructionStarted_Implementation(UGorgeousEvent* Event)
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage("Default implementation of OnConstructionStarted called. This should be overridden in the child class.",
		"GT.Events.Construction.Queue.DefaultStarted");
}

void UGorgeousConstructionHandle::OnConstructionCleanup_Implementation()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage("Default implementation of OnConstructionCleanup called. This should be overridden in the child class.",
		"GT.Events.Construction.Queue.DefaultCleanup");
}

