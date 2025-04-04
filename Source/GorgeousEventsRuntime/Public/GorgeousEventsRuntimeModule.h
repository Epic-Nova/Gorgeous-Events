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

//<=============================--- Pragmas ---==============================>
#pragma once
//<-------------------------------------------------------------------------->

/**
 * This module defines the runtime of the Gorgeous Events plugin.
 *
 * It's the most important module of the plugin, as it's responsible for loading the event runtime components and referenced third party libraries.
 *
 * @author Nils Bergemann
 */
 class FGorgeousEventsRuntimeModule final : public IGorgeousThingsModuleInterface
 {
 public:

 	/**
	 * The override function of the module interface that is called to load up this module.
	 */
 	virtual void StartupModule() override;

 	/**
	 * The override function of the module interface that is called to unload this module.
	 */
 	virtual void ShutdownModule() override;

 	/**
	 * Returns an array of names from other gorgeous plugins that this plugin depends on.
	 * This is used for the shop extension to download the full dependency chain of a gorgeous plugin.
	 * 
	 * @return All plugins that provide functionality that is used within this current module.
	 */
 	virtual TArray<FName> GetDependentPlugins() override;
 };