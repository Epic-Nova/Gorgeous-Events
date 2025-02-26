// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|      that is has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "Interfaces/GorgeousEventFreezingInterface.h"

void UGorgeousEventFreezingInterface::FreezeEvent(UGorgeousEvent* EventToFreeze)
{
}

void UGorgeousEventFreezingInterface::UnfreezeEvent(UGorgeousEvent* EventToUnfreeze)
{
}

bool UGorgeousEventFreezingInterface::IsEventFrozen(UGorgeousEvent* EventToCheck)
{
	return false;
}

void UGorgeousEventFreezingInterface::FreezeAllEvents(bool bFreezeNewEvents, bool bFreezeNestedEvents)
{
}

void UGorgeousEventFreezingInterface::UnfreezeAllEvents(bool bUnfreezeNewEvents, bool bUnfreezeNestedEvents)
{
}

bool UGorgeousEventFreezingInterface::AreAllEventsFrozen(bool bCheckNewEvents, bool bCheckNestedEvents)
{
	return false;
}
