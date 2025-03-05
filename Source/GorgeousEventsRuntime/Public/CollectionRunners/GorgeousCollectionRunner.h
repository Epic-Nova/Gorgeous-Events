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

#include "GorgeousCollectionRunner.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "Gorgeous Collection Runner", Category = "Gorgeous Events|Collection Runners", ClassGroup = "Gorgeous Events", Experimental, NotPlaceable, Transient,
	meta = (ToolTip = "The base class for all Gorgeous Collection runners."))
class UGorgeousCollectionRunner : public UObject
{
	GENERATED_BODY()

public:
	
};

//@TODO: A Event Collection runner holds a array of events and fires them of under different conditions eg Fire Event in index 1 when Event in index 0 has reached state X. this is useful for story games that have a chained scripted execution flow