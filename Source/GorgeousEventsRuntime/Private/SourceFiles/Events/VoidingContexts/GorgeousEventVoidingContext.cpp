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

#include "VoidingContexts/GorgeousEventVoidingContext.h"

#include "Interfaces/GorgeousEventVoidingInterface.h"

void UGorgeousEventVoidingContext::CheckVoidingNeed()
{
	UGorgeousLoggingBlueprintFunctionLibrary::LogInformationMessage("Default implementation of CheckVoidingNeed called. Please override this!", "GT.Events.Voiding.Default_Implementation");
}

void UGorgeousEventVoidingContext::InvalidateVoiding(const bool bRegisterAgain) const
{
	UGorgeousEventVoidingInterface* VoidingInterface = UGorgeousEventVoidingInterface::GetEventVoidingInterface();
	VoidingInterface->UnvoidEvent(VoidedEvent, bRegisterAgain);
}
