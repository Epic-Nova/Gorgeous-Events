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
#pragma once

#include "IGorgeousThingsModuleInterface.h"

/**
 * This module defines the runtime of the GorgeousEvents plugin.
 *
 * It's the most important module of the plugin, as it's responsible for loading the event runtime components and referenced third party libraries.
 *
 * @author Nils Bergemann
 * @since Beginning
 * @version v0.1
 * @todo Finish the implementation of the event runtime module and the comments.
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
 	
 };