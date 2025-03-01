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

#include "CoreMinimal.h"
#include "GorgeousEvent.h"
#include "GameFramework/Actor.h"
#include "EventTrigger_A.generated.h"

UCLASS(Blueprintable, BlueprintType, DisplayName = "Event Trigger", Category = "Gorgeous Events")
class GORGEOUSEVENTSRUNTIME_API AEventTrigger_A : public AActor
{
	GENERATED_BODY()

public:
	AEventTrigger_A();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gorgeous Events")
	TSoftClassPtr<UGorgeousEvent> EventToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gorgeous Events")
	EGorgeousEventTriggerType_E TriggerType;

	UFUNCTION(BlueprintCallable, Category = "Gorgeous Events")
	void TriggerEvent();

protected:
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gorgeous Events")
	UGorgeousEvent* TriggeredEvent;

private:

	UFUNCTION()
	void OnEventConstructionQueued(UGorgeousConstructionHandle* ConstructionHandle);
};
