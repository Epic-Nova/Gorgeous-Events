// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|      that is has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#pragma once

#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEventLockingInterface.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventLockingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Locking")
	bool LockEvent(UGorgeousEvent* EventToLock);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Locking")
	bool UnlockEvent(UGorgeousEvent* EventToUnlock);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Locking")
	bool IsEventLocked(UGorgeousEvent* EventToCheck);
};