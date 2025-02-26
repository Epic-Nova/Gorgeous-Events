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
#include "GorgeousEventManagingInterface.generated.h"

class UGorgeousConstructionHandle;
class UGorgeousEvent;
class FOnEventLoaded;

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventManagingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing", meta = (CompactNodeTitle = "Gorgeous Event Management"))
	static UGorgeousEventManagingInterface* GetEventManagingInterface();
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	void LoadEvent(TSoftClassPtr<UGorgeousEvent> EventToLoad, const FOnEventLoaded& OnEventLoaded);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool RegisterEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& RegisteredEvent);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool UnregisterEvent(UGorgeousEvent* EventToUnregister);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool CancelEvent(UGorgeousEvent* EventToCancel);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool TriggerEvent(UGorgeousConstructionHandle* ConstructionHandle, UGorgeousEvent*& TriggeredEvent);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool CompleteEvent(UGorgeousEvent* EventToComplete);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing")
	bool IsEventOfClassRegistered(const TSubclassOf<UGorgeousEvent>& EventClassToCheck) const;

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool RemoveUnregisteredEvent(UGorgeousEvent* Event);
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool RemoveUnregisteredEvents();

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool RemoveUnregisteredEventsOfClass(TSubclassOf<UGorgeousEvent> EventClassToRemove);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	TArray<UGorgeousEvent*> GetRegisteredEvents() const;

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Managing")
	bool IsEventRegistered(UGorgeousEvent* EventToCheck) const;

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Managing")
	bool ValidateRegisteredEvents(bool bShouldRemoveInvalidEvents, bool bApplyValidationToInstancedVariable, bool& bAllRegisteredEventsValid, int32& NumInvalidEvents);

	virtual void LoadEventNative(TSoftClassPtr<UGorgeousEvent> EventToLoad, const FOnEventLoadedNative& OnEventLoaded);

private:

	static UGorgeousEventManagingInterface* SingletonInstance;

	TMap<TObjectPtr<UGorgeousEvent>, FTimerHandle> CurrentRegisteredEvents;
	
};