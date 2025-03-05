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

#include "Triggers/EventTrigger_A.h"

#include "ConstructionHandles/AssignmentMappers/GorgeousAssignmentMapper.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "Interfaces/GorgeousEventManagingInterface.h"


AEventTrigger_A::AEventTrigger_A(): TriggerType(EGorgeousEventTriggerType_E::Event_Trigger_Manual),
                                    TriggeredEvent(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEventTrigger_A::TriggerEvent()
{
	UGorgeousEventConstructionInterface* ConstructionInterface = UGorgeousEventConstructionInterface::GetEventConstructionInterface();
	FOnEventConstructionQueued ConstructionQueued;
	ConstructionQueued.BindDynamic(this, &AEventTrigger_A::OnEventConstructionQueued);
	ConstructionInterface->QueueEventConstruction(EventToTrigger, FGuid::NewGuid(), ConstructionQueued);
}

void AEventTrigger_A::AssignConstructionEventVariables_Implementation(UGorgeousConstructionHandle* ConstructionHandle)
{
	if (!ConstructionHandle->EventClass.GetDefaultObject()->bIsDebuggingMode)
		return;
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of AssignConstructionEventVariables called, no action is performed!")),
		ConstructionHandle->EventClass.GetDefaultObject()->EventLoggingKey.ToString());
}

void AEventTrigger_A::OnEventConstructionQueued(UGorgeousConstructionHandle* ConstructionHandle)
{
	UObject* TriggerReference = this;
	IGorgeousSingleObjectVariablesSetter_I::Execute_SetObjectObjectSingleObjectVariable(ConstructionHandle->GetAssigmentMapper(), "EventInstigator", TriggerReference);
	AssignConstructionEventVariables(ConstructionHandle);
	
	if (ConstructionHandle->EventClass.GetDefaultObject()->TriggerType == TriggerType)
	{
		UGorgeousEventManagingInterface* ManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
		ManagingInterface->TriggerEvent(ConstructionHandle, TriggeredEvent);
	}
	else
	{
		UGorgeousLoggingBlueprintFunctionLibrary::LogErrorMessage(FString::Printf(TEXT("The event with the identifier: %s could not be triggered because the Trigger type does not match with the one in the event!"),
			*ConstructionHandle->UniqueEventIdentifier.ToString()), "GT.Events.Trigger.Invalid_Type_Match");

		UGorgeousEventConstructionInterface* ConstructionInterface = UGorgeousEventConstructionInterface::GetEventConstructionInterface();
		ConstructionInterface->CancelEventConstruction(ConstructionHandle);
	}
}

