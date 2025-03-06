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
#include "Interfaces/GorgeousEventStatisticsInterface.h"

#include "GorgeousEvents_GIS.h"

UGorgeousEventStatisticsInterface* UGorgeousEventStatisticsInterface::GetEventStatisticsInterface()
{
	return Cast<UGorgeousEventStatisticsInterface>(UGorgeousEvents_GIS::StaticEventsGISInstance->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

void UGorgeousEventStatisticsInterface::AddEventToStatistics(UGorgeousEvent* EventToAdd)
{
}

void UGorgeousEventStatisticsInterface::RemoveEventFromStatistics(UGorgeousEvent* EventToRemove)
{
}

bool UGorgeousEventStatisticsInterface::IsEventInStatistics(UGorgeousEvent* EventToCheck)
{
	return false;
}

void UGorgeousEventStatisticsInterface::GatherCurrentEventHeapSnapshot()
{
}

void UGorgeousEventStatisticsInterface::StartEventHeapSnapshot(UGorgeousEvent* Event)
{
}

void UGorgeousEventStatisticsInterface::StopEventHeapSnapshot(UGorgeousEvent* Event)
{
}

void UGorgeousEventStatisticsInterface::SaveEventHeapSnapshot()
{
}

void UGorgeousEventStatisticsInterface::VisualizeEventHeapSnapshot()
{
}
