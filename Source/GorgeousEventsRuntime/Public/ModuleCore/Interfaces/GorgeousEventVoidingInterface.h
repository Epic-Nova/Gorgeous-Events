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
#include "GorgeousEventVoidingInterface.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventVoidingInterface : public UGorgeousEventInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Voiding")
	void VoidEvent(UGorgeousEvent* EventToVoid);

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events|Voiding")
	void UnvoidEvent(UGorgeousEvent* EventToUnvoid);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Voiding")
	bool IsEventVoided(UGorgeousEvent* EventToCheck);

	UFUNCTION(BlueprintPure, Category = "Gorgeous Events|Voiding")
	bool IsVoidable(UGorgeousEvent* EventToCheck);
};