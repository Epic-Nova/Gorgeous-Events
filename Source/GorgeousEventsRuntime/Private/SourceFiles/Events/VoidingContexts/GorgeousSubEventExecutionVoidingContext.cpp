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

#include "VoidingContexts/GorgeousSubEventExecutionVoidingContext.h"
#include "GorgeousEvent.h"

void UGorgeousSubEventExecutionVoidingContext::CheckVoidingNeed()
{
	bool bAllSubEventsCompleted = false;
	for (const auto SubEvent : VoidedEvent->SubEvents)
	{
		if (VoidedEvent->IsSubEventFinished(SubEvent))
		{
			bAllSubEventsCompleted = true;
		}
		else
		{
			bAllSubEventsCompleted = false;
			break;
		}
	}

	if (bAllSubEventsCompleted)
	{
		InvalidateVoiding(false);
	}
}
