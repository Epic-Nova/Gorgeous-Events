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
/*======================================================================================================================>
| --------------------------------------------------------------------------------------------------------------------- |
|								TO AVOID MISTAKES READ THIS BEFORE EDITING THIS FILE									|
| --------------------------------------------------------------------------------------------------------------------- |
|							ONLY INCLUDE CLASSES THAT ARE WITHIN THIS MODULE DEFINED                                    |
|		TO AVOID CIRCULAR DEPENDENCY ERRORS DO NOT USE THIS MINIMAL FILE IN THE "GorgeousEventsRuntime" MODULE          |
<======================================================================================================================*/
#pragma once

#include "GorgeousEventsRuntimeEnums.h"
#include "GorgeousEventsRuntimeGlobals.h"
#include "GorgeousEventsRuntimeLogging.h"
#include "GorgeousEventsRuntimeMacros.h"
#include "GorgeousEventsRuntimeStructures.h"

//Assignment Mappers Includes
#include "AssignmentMappers/GorgeousAssignmentMapper.h"

//Collection Runners Includes
#include "CollectionRunners/GorgeousCollectionRunner.h"

//Conditional Event Choosers Includes
#include "ConditionalEventChoosers/GorgeousConditionalEventChooser.h"

//Construction Handles Includes
#include "ConstructionHandles/GorgeousConstructionHandle.h"

//Event Includes
#include "Events/GorgeousEvent.h"
#include "Events/SubEvents/GorgeousSubEvent.h"
#include "Events/LinkEvents/GorgeousLinkEvent.h"
#include "Events/AsyncActions/GorgeousEventAsyncAction.h"

#include "Interfaces/GorgeousEventActionQueueInterface.h"
#include "Interfaces/GorgeousEventConstructionInterface.h"
#include "Interfaces/GorgeousEventFreezingInterface.h"
#include "Interfaces/GorgeousEventLockingInterface.h"
#include "Interfaces/GorgeousEventManagingInterface.h"
#include "Interfaces/GorgeousEventStatisticsInterface.h"
#include "Interfaces/GorgeousEventVoidingInterface.h"

