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
#include "Triggers/EventOverlapTrigger_A.h"

#include "GameFramework/Character.h"
#include "Interfaces/GorgeousEventManagingInterface.h"

AEventOverlapTrigger_A::AEventOverlapTrigger_A(): EligibleTriggers(TArray<TSubclassOf<AActor>>({ACharacter::StaticClass()})), CanTriggerEvery(1.f)
{
	TriggerType = EGorgeousEventTriggerType_E::Event_Trigger_WorldObjectOverlap;
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	RootComponent = OverlapBox;
	
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapBox->SetCollisionObjectType(ECC_WorldStatic);
	OverlapBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	OverlapBox->SetLineThickness(5.f);
	OverlapBox->SetOverlayColor(FColor::Green);
}

void AEventOverlapTrigger_A::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AEventOverlapTrigger_A::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AEventOverlapTrigger_A::OnOverlapEnd);
}

void AEventOverlapTrigger_A::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OverlapBox)
	{
		OverlapBox->OnComponentBeginOverlap.RemoveDynamic(this, &AEventOverlapTrigger_A::OnOverlapBegin);
		OverlapBox->OnComponentEndOverlap.RemoveDynamic(this, &AEventOverlapTrigger_A::OnOverlapEnd);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AEventOverlapTrigger_A::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		bool bIsEligible = false;
		for (const auto& EligibleClass : EligibleTriggers)
		{
			if (OtherActor->GetClass()->IsChildOf(EligibleClass))
			{
				bIsEligible = true;
				break;
			}
		}

		if (bIsEligible)
		{
			bCanCallOverlapEnd = true;
			if (const float CurrentTime = GetWorld()->GetTimeSeconds(); CurrentTime - LastTriggerTime >= CanTriggerEvery)
			{
				TriggerEvent();
				LastTriggerTime = CurrentTime;
			}
			else
			{
				UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage(FString::Printf(TEXT("Overlap Begin: %s is eligible but trigger is on cooldown."), *OtherActor->GetName()), "GT.Events.Trigger.Cooldown");
			}
		}
		else
		{
			UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage(FString::Printf(TEXT("Overlap Begin: %s is not an eligible trigger."), *OtherActor->GetName()), "GT.Events.Trigger.Not_Eligible");
		}
	}
}

void AEventOverlapTrigger_A::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && bCompleteEventOnEndOverlap && TriggeredEvent && bCanCallOverlapEnd)
	{
		bool bIsEligible = false;
		for (const auto& EligibleClass : EligibleTriggers)
		{
			if (OtherActor->GetClass()->IsChildOf(EligibleClass))
			{
				bIsEligible = true;
				break;
			}
		}

		if (bIsEligible)
		{
			UGorgeousEventManagingInterface* EventManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
			EventManagingInterface->CompleteEvent(TriggeredEvent);
		}
		else
		{
			UGorgeousLoggingBlueprintFunctionLibrary::LogWarningMessage(FString::Printf(TEXT("Overlap End: %s is not an eligible completion trigger."), *OtherActor->GetName()), "GT.Events.Trigger.Not_Eligible");
		}
		bCanCallOverlapEnd = false;
	}
}
