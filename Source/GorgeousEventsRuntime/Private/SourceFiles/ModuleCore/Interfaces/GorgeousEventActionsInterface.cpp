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
#include "Interfaces/GorgeousEventActionsInterface.h"
#include "GorgeousEvents_GIS.h"
#include "GorgeousEventAction.h"

UGorgeousEventActionsInterface* UGorgeousEventActionsInterface::GetEventActionsInterface()
{
	return Cast<UGorgeousEventActionsInterface>(UGorgeousEvents_GIS::StaticEventsGISInstance->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

UGorgeousEventAction* UGorgeousEventActionsInterface::GetActionInstance(const UGorgeousEvent* Event, const FName ActionName)
{
	for (const auto Action : Event->GetActions())
	{
		if (Action->ActionName == ActionName)
		{
			return Action;
		}
	}
	return nullptr;
}

bool UGorgeousEventActionsInterface::ExecuteAction(UGorgeousEvent* Event, FName ActionName)
{
	if (!DoesActionExist(Event, ActionName))
		return false;

	const TObjectPtr<UGorgeousEventAction> Action = NewObject<UGorgeousEventAction>(Event, Event->Actions[ActionName], ActionName);
	Action->ActionName = ActionName;
	
	Event->RegisteredEventActions.Add(Action);

	Action->OnEventActionStartedDelegate.Broadcast();

	return true;
}

void UGorgeousEventActionsInterface::CompleteAction(UGorgeousEvent* Event, const FName ActionName)
{
	UGorgeousEventAction* Action = GetActionInstance(Event, ActionName);
	if (!Action)
		return;

	Action->OnEventActionCompletedDelegate.Broadcast();
	Action->MarkAsGarbage();

}

bool UGorgeousEventActionsInterface::RequestSkip(UGorgeousEvent* Event, const FName ActionName)
{
	UGorgeousEventAction* Action = GetActionInstance(Event, ActionName);
	if (!Action)
		return false;

	if (Action->SkipType == EGorgeousEventSkipType_E::Event_Skip_Skippable)
	{
		CompleteAction(Event, ActionName);
		return true;
	}
	if (Action->SkipType == EGorgeousEventSkipType_E::Event_Skip_Cond_Skippable && Action->IsEventActionSkippable())
	{
		CompleteAction(Event, ActionName);
		return true;
	}

	UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage(FString::Printf(TEXT("Skipping the event action: %s for event: %s is not allowed!"), *ActionName.ToString(),  *Event->UniqueIdentifier.ToString()),
		Event->EventLoggingKey.ToString(), 2.f);
	return false;
}

bool UGorgeousEventActionsInterface::IsActionRunning(const UGorgeousEvent* Event, const FName ActionName)
{
	if (!GetActionInstance(Event, ActionName))
		return false;
	return GetActionInstance(Event, ActionName)->bIsRunning;
}

bool UGorgeousEventActionsInterface::DoesActionExist(UGorgeousEvent* Event, const FName ActionName)
{
	return Event->Actions.Contains(ActionName);
}
