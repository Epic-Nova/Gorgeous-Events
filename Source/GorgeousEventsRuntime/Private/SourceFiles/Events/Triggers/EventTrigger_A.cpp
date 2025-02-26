// Epic Nova 2025


#include "Triggers/EventTrigger_A.h"


// Sets default values
AEventTrigger_A::AEventTrigger_A()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEventTrigger_A::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEventTrigger_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

