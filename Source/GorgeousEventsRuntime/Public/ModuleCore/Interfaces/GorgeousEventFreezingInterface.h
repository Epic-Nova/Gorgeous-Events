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
#include "GorgeousEventFreezingInterface.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventFreezingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Freezing")
	void FreezeEvent(UGorgeousEvent* EventToFreeze);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Freezing")
	void UnfreezeEvent(UGorgeousEvent* EventToUnfreeze);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Freezing")
	bool IsEventFrozen(UGorgeousEvent* EventToCheck);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Freezing")
	void FreezeAllEvents(bool bFreezeNewEvents, bool bFreezeNestedEvents);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Freezing")
	void UnfreezeAllEvents(bool bUnfreezeNewEvents, bool bUnfreezeNestedEvents);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Freezing")
	bool AreAllEventsFrozen(bool bCheckNewEvents, bool bCheckNestedEvents);
};