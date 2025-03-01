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

#include "VoidingContexts/GorgeousUniqueClassspaceExecutionVoidingContext.h"
#include "GorgeousEvent.h"
#include "Interfaces/GorgeousEventManagingInterface.h"

void UGorgeousUniqueClassspaceExecutionVoidingContext::CheckVoidingNeed()
{
	if (VoidedEvent->GetClassspaceChildren().Num() == 0)
	{
		const FGuid EventIdentifier = VoidedEvent->UniqueIdentifier;
		
		InvalidateVoiding(false);

		UGorgeousLoggingBlueprintFunctionLibrary::LogSuccessMessage(FString::Printf(TEXT("Voided event with identifier: %s got resolved and garbage collected due to the children completed their execution!"),
			*EventIdentifier.ToString()), "GT.Events.Voiding.Resolved");
	}
}
