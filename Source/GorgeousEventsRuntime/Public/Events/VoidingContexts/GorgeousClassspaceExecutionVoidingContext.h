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
#include "GorgeousEventVoidingContext.h"
#include "GorgeousClassspaceExecutionVoidingContext.generated.h"

/**
 * Void the event with UGorgeousClassspaceExecutionVoidingContext as the reason for why this event got voided.
 * the context then should periodically check if the condition is not there anymore, when no dependencies exist anymore then we can safely delete this event with UnregisterEvent
 *
 * We do this because we don't want to lose the parent chain of the child, as the classspace execution system allowes specific events to share variables and context information as they were one single class, but they are still seperated
 */
UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousClassspaceExecutionVoidingContext : public UGorgeousEventVoidingContext
{
	GENERATED_BODY()

public:

	virtual void CheckVoidingNeed() override;
};