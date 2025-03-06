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
#include "Interfaces/GorgeousEventVoidingInterface.h"
#include "GorgeousEvents_GIS.h"
#include "VoidingContexts/GorgeousEventVoidingContext.h"

UGorgeousEventVoidingInterface* UGorgeousEventVoidingInterface::GetEventVoidingInterface()
{
	return Cast<UGorgeousEventVoidingInterface>(UGorgeousEvents_GIS::StaticEventsGISInstance->GetRegisteredEventsInterfaceForSubclass(StaticClass()));
}

bool UGorgeousEventVoidingInterface::VoidEvent(UGorgeousEvent* EventToVoid, const TSubclassOf<UGorgeousEventVoidingContext> VoidingContext)
{
	if (VoidingContext && IsVoidable(EventToVoid))
	{
		UGorgeousEventVoidingContext* NewVoidingContext = NewObject<UGorgeousEventVoidingContext>(this, VoidingContext);
		NewVoidingContext->VoidedEvent = EventToVoid;
		
		FTimerHandle VoidingTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(VoidingTimerHandle, [NewVoidingContext]()
		{
			NewVoidingContext->CheckVoidingNeed();
		}, 5.f, true);

		const TPair<TObjectPtr<UGorgeousEventVoidingContext>, FTimerHandle> Pair(NewVoidingContext, VoidingTimerHandle);
		VoidedEvents.Add(EventToVoid, Pair);
		return true;
	}
	return false;
}

void UGorgeousEventVoidingInterface::UnvoidEvent(UGorgeousEvent* EventToUnvoid, const bool bRegisterAgain)
{
	if (VoidedEvents[EventToUnvoid].Key)
	{
		GetWorld()->GetTimerManager().ClearTimer(VoidedEvents[EventToUnvoid].Value);
		UGorgeousEventManagingInterface* ManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
		if (!bRegisterAgain)
		{
			ManagingInterface->UnregisterEvent(EventToUnvoid);
		}
		else
		{
			ManagingInterface->ReregisterEvent(EventToUnvoid);
			
			const EGorgeousEventState_E PreviousEventState = EventToUnvoid->EventState;
			EventToUnvoid->EventState = EGorgeousEventState_E::Event_State_Processing;
			EventToUnvoid->OnEventStateChangeDelegate.Broadcast(PreviousEventState, EventToUnvoid->EventState);
			EventToUnvoid->OnEventProcessingDelegate.Broadcast();
		}
		VoidedEvents[EventToUnvoid].Key->MarkAsGarbage();
		VoidedEvents.Remove(EventToUnvoid);
	}
}

bool UGorgeousEventVoidingInterface::IsEventVoided(UGorgeousEvent* EventToCheck)
{
	if (!EventToCheck || !VoidedEvents.Contains(EventToCheck))
		return false;
	return VoidedEvents[EventToCheck].Key != nullptr;
}

bool UGorgeousEventVoidingInterface::IsVoidable(UGorgeousEvent* EventToCheck)
{
	const UGorgeousEventManagingInterface* ManagingInterface = UGorgeousEventManagingInterface::GetEventManagingInterface();
	return ManagingInterface->IsEventRegistered(EventToCheck);
}
