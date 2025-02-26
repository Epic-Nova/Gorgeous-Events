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

#include "CoreMinimal.h"

/**
 * @brief Enum that defines the state of the event that is being processed.
 * @author Nils Bergemann
 * @since Beginning
 */
UENUM(BlueprintType, DisplayName = "Event State", meta = (ShortTooltip = "The state of the event that is being processed."))
enum class EGorgeousEventState_E : uint8
{
	Event_State_Invalid = 0 UMETA(DisplayName = "Invalid", ToolTip = "The event is in an invalid state."),
	Event_State_Triggered = 1 UMETA(DisplayName = "Triggered", ToolTip = "The event has been triggered and is ready to be initialized."),
	Event_State_Initialized = 2 UMETA(DisplayName = "Initialized", ToolTip = "The event is initialized and ready to be processed."),
	Event_State_Started = 3 UMETA(DisplayName = "Started", ToolTip = "The event has been started and is currently running."),
	Event_State_Processing = 4 UMETA(DisplayName = "Processing", ToolTip = "The event is currently being processed."),
	Event_State_Finished = 5 UMETA(DisplayName = "Finished", ToolTip = "The event has been processed and is finished."),
	Event_State_Canceled = 6 UMETA(DisplayName = "Canceled", ToolTip = "The event has been canceled and is not processed."),
	Event_State_Voided = 7 UMETA(DisplayName = "Voided", ToolTip = "The event has been voided and is not processed."),
	Event_State_Max = 8 UMETA(Hidden)
};

UENUM(BlueprintType, DisplayName = "Trigger Type", meta = (ShortTooltip = "Under what condition should the event be triggered"))
enum class EGorgeousEventTriggerType_E : uint8
{
	Event_Trigger_Manual = 0 UMETA(DisplayName = "Manual", ToolTip = "The event is triggered manually."),
	Event_Trigger_WorldObjectOverlap = 1 UMETA(DisplayName = "World Object Overlap", ToolTip = "The event is triggered after an overlap with another object."),
	Event_Trigger_AfterInteraction = 2 UMETA(DisplayName = "After Interaction", ToolTip = "The event is triggered ater an interaction."),
	Event_Trigger_Max = 3 UMETA(Hidden)
};