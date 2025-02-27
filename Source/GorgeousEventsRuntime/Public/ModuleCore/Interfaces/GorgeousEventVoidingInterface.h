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
#include "GorgeousEventVoidingInterface.generated.h"

class UGorgeousEventVoidingContext;

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventVoidingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Voiding", meta = (CompactNodeTitle = "Gorgeous Event Voiding"))
	static UGorgeousEventVoidingInterface* GetEventVoidingInterface();
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Voiding")
	virtual void VoidEvent(UGorgeousEvent* EventToVoid, TSubclassOf<UGorgeousEventVoidingContext> VoidingContext);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Voiding")
	virtual void UnvoidEvent(UGorgeousEvent* EventToUnvoid);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Voiding")
	virtual bool IsEventVoided(UGorgeousEvent* EventToCheck);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Voiding")
	virtual bool IsVoidable(UGorgeousEvent* EventToCheck);
};