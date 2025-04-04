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
#include "GorgeousEventsRuntimeModule.h"
#include "GameplayTagsManager.h"
#include "Interfaces/IPluginManager.h"

void FGorgeousEventsRuntimeModule::StartupModule()
{
	//@TODO: Use the Gorgeous Helper functions and do this in every gorgeous plugin.
	const TSharedPtr<IPlugin> ThisPlugin = IPluginManager::Get().FindPlugin(TEXT("GorgeousEvents"));
	check(ThisPlugin.IsValid());

	UGameplayTagsManager::Get().AddTagIniSearchPath(ThisPlugin->GetBaseDir() / TEXT("Config") / TEXT("Tags"));
}

void FGorgeousEventsRuntimeModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FGorgeousEventsRuntimeModule has shut down!"));
}

TArray<FName> FGorgeousEventsRuntimeModule::GetDependentPlugins()
{
	return TArray<FName>();
}

IMPLEMENT_MODULE(FGorgeousEventsRuntimeModule, GorgeousEventsRuntime)
