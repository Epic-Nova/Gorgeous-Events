// Epic Nova 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventTrigger_A.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API AEventTrigger_A : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEventTrigger_A();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
