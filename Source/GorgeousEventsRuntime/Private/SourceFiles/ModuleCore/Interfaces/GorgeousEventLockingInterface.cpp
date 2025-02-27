﻿// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|         that has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
#include "Interfaces/GorgeousEventLockingInterface.h"

bool UGorgeousEventLockingInterface::LockEvent(UGorgeousEvent* EventToLock)
{
	return false;
}

bool UGorgeousEventLockingInterface::UnlockEvent(UGorgeousEvent* EventToUnlock)
{
	return false;
}

bool UGorgeousEventLockingInterface::IsEventLocked(UGorgeousEvent* EventToCheck)
{
	return false;
}
