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
#pragma once

#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousEventVoidingContext.generated.h"

UCLASS()
class GORGEOUSEVENTSRUNTIME_API UGorgeousEventVoidingContext : public UObject
{
	GENERATED_BODY()

public:

	virtual void CheckVoidingNeed();

	void InvalidateVoiding(const bool bRegisterAgain) const;

	TObjectPtr<UGorgeousEvent> VoidedEvent;
};