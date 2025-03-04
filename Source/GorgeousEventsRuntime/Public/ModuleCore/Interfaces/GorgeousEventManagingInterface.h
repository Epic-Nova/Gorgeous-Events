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

#include "GorgeousEvent.h"
#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEventManagingInterface.generated.h"

class UGorgeousConstructionHandle;
class UGorgeousEvent;
class FOnEventLoaded;

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventManagingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

	friend class UGorgeousEvent;
	
public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing", meta = (CompactNodeTitle = "Gorgeous Event Management"))
	static UGorgeousEventManagingInterface* GetEventManagingInterface();
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual void LoadEvent(TSoftClassPtr<UGorgeousEvent> EventToLoad, const FOnEventLoaded& OnEventLoaded);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool RegisterEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& RegisteredEvent);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual void ReregisterEvent(UGorgeousEvent* Event);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool UnregisterEvent(UGorgeousEvent* EventToUnregister);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool CancelEvent(UGorgeousEvent* EventToCancel);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool TriggerEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& TriggeredEvent);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool CompleteEvent(UGorgeousEvent* EventToComplete);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing")
	virtual bool IsEventOfClassRegistered(const TSubclassOf<UGorgeousEvent>& EventClassToCheck, bool bIncludeSubclassCheck = false) const;

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual bool RemoveUnregisteredEvent(UGorgeousEvent* Event);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	virtual TArray<UGorgeousEvent*> GetRegisteredEvents() const;

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing")
	virtual bool IsEventRegistered(UGorgeousEvent* EventToCheck) const;

	virtual void LoadEventNative(TSoftClassPtr<UGorgeousEvent> EventToLoad, const FOnEventLoadedNative& OnEventLoaded);

private:

	FTimerHandle SetupProcessingLoopForEvent(UGorgeousEvent* Event) const;

	static UGorgeousEventManagingInterface* SingletonInstance;

	TMap<TObjectPtr<UGorgeousEvent>, FTimerHandle> CurrentRegisteredEvents;

	bool RegisterEvent_Internal(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& RegisteredEvent, UGorgeousEvent* AlreadyInstancedEvent = nullptr);
	
};