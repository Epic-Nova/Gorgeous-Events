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
#include "GorgeousEventActionQueueInterface.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventActionQueueInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Action Queue")
	virtual void MoveEventToActionQueue(UGorgeousEvent* EventToMove);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Action Queue")
	virtual void TryResolveEventState(UGorgeousEvent* EventToResolve);
};