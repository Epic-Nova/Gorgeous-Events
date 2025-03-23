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
#include "GorgeousEventAction.h"

#include "GorgeousEvent.h"
#include "Interfaces/GorgeousEventActionsInterface.h"


void UGorgeousEventAction::PostInitProperties()
{
	UObject::PostInitProperties();

	OnEventActionStartedDelegate.AddLambda([this]()
	{
		OnEventActionStarted_Internal();
		OnEventActionStarted();
	});

	OnEventActionCompletedDelegate.AddLambda([this]()
	{
		OnEventActionCompleted_Internal();
		OnEventActionCompleted();
	});

	OnEventActionTickDelegate.AddLambda([this](const float DeltaTime, const int64 CurrentProcessingLoopCount)
	{
		OnEventActionTick_Internal(DeltaTime, CurrentProcessingLoopCount);
		OnEventActionTick(DeltaTime, CurrentProcessingLoopCount);
	});
}

UGorgeousEventAction::UGorgeousEventAction(): SkipType(EGorgeousEventSkipType_E::Event_Skip_Skippable), EventReference(nullptr), bIsRunning(true)
{
}

UGorgeousEventAction::~UGorgeousEventAction() {}

bool UGorgeousEventAction::IsEventActionSkippable_Implementation()
{
	//@TODO
	return false;
}

void UGorgeousEventAction::CompleteAction() const
{
	UGorgeousEventActionsInterface* ActionsInterface = UGorgeousEventActionsInterface::GetEventActionsInterface();
	ActionsInterface->CompleteAction(EventReference, ActionName);
}

void UGorgeousEventAction::OnEventActionStarted_Internal()
{
	OnEventActionTickDelegateHandle = EventReference->ContinuousProcessingLoopDelegate.AddLambda([this](EGorgeousEventState_E EventState, const float DeltaTime, const int64 CurrentProcessingLoopCount)
	{
		OnEventActionTickDelegate.Broadcast(DeltaTime, CurrentProcessingLoopCount);
	});

	bIsRunning = true;
}

void UGorgeousEventAction::OnEventActionCompleted_Internal()
{
	bIsRunning = false;
	EventReference->ContinuousProcessingLoopDelegate.Remove(OnEventActionTickDelegateHandle);
	EventReference->RegisteredEventActions.Remove(this);
}

void UGorgeousEventAction::OnEventActionTick_Internal(float DeltaTime, int64 CurrentProcessingLoopCount)
{
}

void UGorgeousEventAction::OnEventActionStarted_Implementation()
{
	if (!EventReference->bIsDebuggingMode)
		return;
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventActionStarted for event with identifier: %s called, no action is performed!"), *EventReference->UniqueIdentifier.ToString()),
EventReference->EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEventAction::OnEventActionCompleted_Implementation()
{
	if (!EventReference->bIsDebuggingMode)
		return;
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventActionCompleted for event with identifier: %s called, no action is performed!"), *EventReference->UniqueIdentifier.ToString()),
EventReference->EventLoggingKey.ToString(), 2.f, false, true, this);
}

void UGorgeousEventAction::OnEventActionTick_Implementation(float DeltaTime, int64 CurrentProcessingLoopCount)
{
	if (!EventReference->bIsDebuggingMode)
		return;
	
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage(FString::Printf(TEXT("Default implementation of OnEventActionTick for event with identifier: %s called, no action is performed!"), *EventReference->UniqueIdentifier.ToString()),
EventReference->EventLoggingKey.ToString(), 2.f, false, true, this);
}
