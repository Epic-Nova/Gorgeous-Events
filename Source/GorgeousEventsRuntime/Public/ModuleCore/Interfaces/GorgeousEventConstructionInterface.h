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
#include "ConstructionHandles/GorgeousConstructionHandle.h"
#include "GorgeousEventConstructionInterface.generated.h"

class UGorgeousEvent;

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventConstructionInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction", meta = (CompactNodeTitle = "Gorgeous Event Construction"))
	static UGorgeousEventConstructionInterface* GetEventConstructionInterface();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction")
	void QueueEventConstruction(TSoftClassPtr<UGorgeousEvent> EventToConstruct, FGuid UniqueEventIdentifierOverride, const FOnEventConstructionQueued& OnEventConstructionQueued);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction")
	bool CancelEventConstruction(UGorgeousConstructionHandle* ConstructionToCancel);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction")
	bool CancelEventConstructionByGuid(FGuid EventGuid);
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	TArray<UGorgeousConstructionHandle*> GetEventConstructionQueue();
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	bool IsEventInConstructionQueue(FGuid EventToCheck);
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	UGorgeousConstructionHandle* GetConstructionHandle(const UGorgeousEvent* EventToGetHandleFor);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	UGorgeousConstructionHandle* GetConstructionHandleByGuid(FGuid EventGuid);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	bool RemoveConstructionHandleFromQueue(UGorgeousConstructionHandle* HandleToRemove);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	bool RemoveConstructionHandleFromQueueByGuid(FGuid EventGuid);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	TArray<UGorgeousConstructionHandle*> ValidateConstructionQueue(bool bShouldRemoveInvalidHandles, bool bApplyValidationToInstancedVariable, bool& bAllQueuedHandlesValid, int32& NumInvalidEvents);
	
private:

	TMap<FGuid, TObjectPtr<UGorgeousConstructionHandle>> ConstructionQueue;

	static UGorgeousEventConstructionInterface* SingletonInstance;
};