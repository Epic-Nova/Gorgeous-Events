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
#include "GorgeousEventStatisticsInterface.generated.h"

//@TODO: Basically a unreal insights & gc implementation
UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventStatisticsInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void AddEventToStatistics(UGorgeousEvent* EventToAdd);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void RemoveEventFromStatistics(UGorgeousEvent* EventToRemove);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Statistics")
	bool IsEventInStatistics(UGorgeousEvent* EventToCheck);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void GeatherCurrentEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void StartEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void StopEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void SaveEventHeapSnapshot();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Statistics")
	void VisualizeEventHeapSnapshot();
};