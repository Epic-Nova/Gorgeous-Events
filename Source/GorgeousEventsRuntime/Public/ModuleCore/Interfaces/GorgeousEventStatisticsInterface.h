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
#include "GorgeousEventStatisticsInterface.generated.h"

//@TODO: Basically a unreal insights & gc implementation
UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventStatisticsInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Statistics", meta = (CompactNodeTitle = "Event Statistics"))
	static UGorgeousEventStatisticsInterface* GetEventStatisticsInterface();
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void AddEventToStatistics(UGorgeousEvent* EventToAdd);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void RemoveEventFromStatistics(UGorgeousEvent* EventToRemove);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Statistics")
	virtual bool IsEventInStatistics(UGorgeousEvent* EventToCheck);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void GatherCurrentEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void StartEventHeapSnapshot(UGorgeousEvent* Event);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void StopEventHeapSnapshot(UGorgeousEvent* Event);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void SaveEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	virtual void VisualizeEventHeapSnapshot();
};