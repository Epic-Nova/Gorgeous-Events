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
#include "GorgeousEventWithSubEvents.h"
#include "GorgeousSubEvent.h"
#include "ConstructionHandles/AssignmentMappers/GorgeousAssignmentMapper.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "Interfaces/GorgeousEventManagingInterface.h"

bool UGorgeousEventWithSubEvents::IsSubEventFinished(const UGorgeousSubEvent* SubEvent)
{
	return SubEvent->bIsEventFinished;
}

void UGorgeousEventWithSubEvents::ManuallyRegisterSubEvent(const TSoftClassPtr<UGorgeousSubEvent> EventToTrigger)
{
	UGorgeousEventConstructionInterface* ConstructionInterface = UGorgeousEventConstructionInterface::GetEventConstructionInterface();
	FOnEventConstructionQueued ConstructionQueued;
	ConstructionQueued.BindDynamic(this, &UGorgeousEventWithSubEvents::OnEventConstructionQueued);
	ConstructionInterface->QueueEventConstruction(EventToTrigger, FGuid::NewGuid(), ConstructionQueued);
}

void UGorgeousEventWithSubEvents::ContinuousEventProcessingLoop_Internal(const EGorgeousEventState_E CurrentLoopState,
                                                                         const float DeltaTime, const int64 CurrentProcessingLoopCount)
{
	Super::ContinuousEventProcessingLoop_Internal(CurrentLoopState, DeltaTime, CurrentProcessingLoopCount);

	for (const auto SubEvent : SubEvents)
	{
		if (SubEvent->RunOnParentState == CurrentLoopState)
		{
			if (!SubEvent->UniqueIdentifier.IsValid())
			{
				SubEvent->UniqueIdentifier = FGuid::NewGuid();
			}
			
			SubEvent->SetParent(this);
			SubEvent->CallingEvent = this;
			SubEvent->InvokeInstancedFunctionality(SubEvent->UniqueIdentifier);
		}
	}
}

void UGorgeousEventWithSubEvents::OnEventConstructionQueued(UGorgeousConstructionHandle* ConstructionHandle)
{
	ConstructionHandle->Parent = this;
	
	UObject* InCallingEvent = this;
	IGorgeousSingleObjectVariablesSetter_I::Execute_SetObjectObjectSingleObjectVariable(ConstructionHandle->GetAssigmentMapper(), "CallingEvent", InCallingEvent);
	AssignConstructionEventVariables(ConstructionHandle);
	
	UGorgeousEventManagingInterface* ManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();

	UGorgeousEvent* TriggeredEvent;
	ManagingInterface->TriggerEvent(ConstructionHandle, TriggeredEvent);

	SubEvents.Add(Cast<UGorgeousSubEvent>(TriggeredEvent));
}
