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
	virtual void QueueEventConstruction(TSoftClassPtr<UGorgeousEvent> EventToConstruct, FGuid UniqueEventIdentifierOverride, const FOnEventConstructionQueued& OnEventConstructionQueued);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction")
	virtual bool CancelEventConstruction(UGorgeousConstructionHandle* ConstructionToCancel);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction")
	virtual bool CancelEventConstructionByGuid(FGuid EventGuid);
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	virtual TArray<UGorgeousConstructionHandle*> GetEventConstructionQueue();
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	virtual bool IsEventInConstructionQueue(FGuid EventToCheck);
	
	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	virtual UGorgeousConstructionHandle* GetConstructionHandle(const UGorgeousEvent* EventToGetHandleFor);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Construction|Queue")
	virtual UGorgeousConstructionHandle* GetConstructionHandleByGuid(FGuid EventGuid);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	virtual bool RemoveConstructionHandleFromQueue(UGorgeousConstructionHandle* HandleToRemove, bool bDeleteHandle = false);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	virtual bool RemoveConstructionHandleFromQueueByGuid(FGuid EventGuid, bool bDeleteHandle = false);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Construction|Queue")
	virtual TArray<UGorgeousConstructionHandle*> ValidateConstructionQueue(bool bShouldRemoveInvalidHandles, bool bApplyValidationToInstancedVariable, bool& bAllQueuedHandlesValid, int32& NumInvalidEvents);
	
private:

	TMap<FGuid, TObjectPtr<UGorgeousConstructionHandle>> ConstructionQueue;

	static UGorgeousEventConstructionInterface* SingletonInstance;
};