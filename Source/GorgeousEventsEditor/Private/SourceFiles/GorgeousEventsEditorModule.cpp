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
#include "GorgeousEventsEditorModule.h"

void FGorgeousEventsEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FGorgeousEventsEditorModule has started!"));
}

void FGorgeousEventsEditorModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FGorgeousEventsEditorModule has shut down!"));
}

IMPLEMENT_MODULE(FGorgeousEventsEditorModule, GorgeousEventsEditor)