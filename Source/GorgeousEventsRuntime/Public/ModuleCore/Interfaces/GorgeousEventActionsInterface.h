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
#pragma once

#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEventActionsInterface.generated.h"

class UGorgeousEventAction;

UCLASS()
class UGorgeousEventActionsInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Actions", meta = (CompactNodeTitle = "Event Actions"))
	static UGorgeousEventActionsInterface* GetEventActionsInterface();

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Actions")
	UGorgeousEventAction* GetActionInstance(const UGorgeousEvent* Event, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Actions")
	bool ExecuteAction(UGorgeousEvent* Event, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Actions")
	void CompleteAction(UGorgeousEvent* Event, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Actions")
	bool RequestSkip(UGorgeousEvent* Event, FName ActionName);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Actions")
	bool IsActionRunning(const UGorgeousEvent* Event, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Actions")
	bool DoesActionExist(UGorgeousEvent* Event, FName ActionName);

};
