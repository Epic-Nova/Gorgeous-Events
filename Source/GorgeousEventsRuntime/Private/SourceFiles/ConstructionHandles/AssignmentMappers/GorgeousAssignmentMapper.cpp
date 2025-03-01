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
#include "ConstructionHandles/AssignmentMappers/GorgeousAssignmentMapper.h"
#include "Triggers/EventTrigger_A.h"

UObject* UGorgeousAssignmentMapper::SetObjectObjectSingleObjectVariable_Implementation(const FName OptionalVariableName, UObject*& NewValue)
{
	if (OptionalVariableName == TEXT("EventTrigger"))
	{
		TriggerReference = Cast<AEventTrigger_A>(NewValue);
	}
	return NewValue;
}

void UGorgeousAssignmentMapper::FlushAssignedVariables_Native(UGorgeousEvent* Event)
{
	Event->TriggerReference = TriggerReference;
	FlushAssignedVariables(Event);
}

void UGorgeousAssignmentMapper::FlushAssignedVariables_Implementation(UGorgeousEvent* Event)
{
	if (!Event->bIsDebuggingMode)
		return;
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of FlushAssignedVariables called, no action is performed!")),
		Event->EventLoggingKey.ToString());
}
