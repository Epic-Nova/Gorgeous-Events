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
#include "Interfaces/GorgeousEventVoidingInterface.h"

#include "GorgeousEvents_GIS.h"

UGorgeousEventVoidingInterface* UGorgeousEventVoidingInterface::GetEventVoidingInterface()
{
	//@TODO: Probably problematic for Dedicated server scenarios
	UGorgeousEvents_GIS* Events_GIS = GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UGorgeousEvents_GIS>();
	return Cast<UGorgeousEventVoidingInterface>(Events_GIS->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

void UGorgeousEventVoidingInterface::VoidEvent(UGorgeousEvent* EventToVoid, TSubclassOf<UGorgeousEventVoidingContext> VoidingContext)
{
}

void UGorgeousEventVoidingInterface::UnvoidEvent(UGorgeousEvent* EventToUnvoid)
{
}

bool UGorgeousEventVoidingInterface::IsEventVoided(UGorgeousEvent* EventToCheck)
{
	return false;
}

bool UGorgeousEventVoidingInterface::IsVoidable(UGorgeousEvent* EventToCheck)
{
	return false;
}
