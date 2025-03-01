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

#include "EventTrigger_A.h"
#include "Components/BoxComponent.h"
#include "EventOverlapTrigger_A.generated.h"

UCLASS(Blueprintable, BlueprintType, DisplayName = "Event Overlap Trigger", Category = "Gorgeous Events")
class GORGEOUSEVENTSRUNTIME_API AEventOverlapTrigger_A : public AEventTrigger_A
{
	GENERATED_BODY()

public:
	AEventOverlapTrigger_A();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gorgeous Events")
	bool bCompleteEventOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gorgeous Events")
	TArray<TSubclassOf<AActor>> EligibleTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gorgeous Events")
	float CanTriggerEvery;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	float LastTriggerTime;
	bool bCanCallOverlapEnd;
};
