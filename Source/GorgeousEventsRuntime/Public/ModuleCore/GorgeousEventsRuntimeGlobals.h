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

#include "GorgeousCoreMinimalShared.h"
#include "GorgeousEventsRuntimeGlobals.generated.h"

class UGorgeousEvent;

//<=================--- Delegates ---=================>
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnEventLoaded, TSubclassOf<UGorgeousEvent>, LoadedEvent);
DECLARE_DELEGATE_OneParam(FOnEventLoadedNative, TSubclassOf<UGorgeousEvent>);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnEventConstructionQueued, UGorgeousConstructionHandle*, QueuedConstructionHandle);
//<--------------------------------------------------->

UCLASS(Blueprintable)
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventInterface : public UGorgeousInterface
{
	GENERATED_BODY()
};