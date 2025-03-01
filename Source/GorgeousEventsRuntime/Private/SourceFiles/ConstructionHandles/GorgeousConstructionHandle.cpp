// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|               Gorgeous Core - Core functionality provider                 |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|         that has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "ConstructionHandles/GorgeousConstructionHandle.h"

#include "ConstructionHandles/AssignmentMappers/GorgeousAssignmentMapper.h"

UGorgeousConstructionHandle::UGorgeousConstructionHandle(): CorrespondingAssigmentMapper(UGorgeousAssignmentMapper::StaticClass()) {}

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

UGorgeousAssignmentMapper* UGorgeousConstructionHandle::GetAssigmentMapper()
{
	return AssigmentMapperReference;
}

void UGorgeousConstructionHandle::OnConstructionQueued_Internal()
{
	AssigmentMapperReference = NewObject<UGorgeousAssignmentMapper>(this, CorrespondingAssigmentMapper);
}

void UGorgeousConstructionHandle::OnConstructionStarted_Internal(UGorgeousEvent* Event)
{
	AssigmentMapperReference->FlushAssignedVariables(Event);
}

void UGorgeousConstructionHandle::OnConstructionCleanup_Internal()
{
	AssigmentMapperReference->MarkAsGarbage();
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

