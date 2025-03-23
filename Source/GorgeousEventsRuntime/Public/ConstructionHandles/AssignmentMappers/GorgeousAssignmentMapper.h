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

#include "GorgeousEventsRuntimeMinimal.h"
#include "GorgeousAssignmentMapper.generated.h"

class AEventTrigger_A;

UCLASS(Blueprintable, BlueprintType)
class GORGEOUSEVENTSRUNTIME_API UGorgeousAssignmentMapper : public UObject,
	public IGorgeousSingleObjectVariablesSetter_I,
	public IGorgeousArrayObjectVariablesSetter_I,
	public IGorgeousMapObjectVariablesSetter_I,
	public IGorgeousSetObjectVariablesSetter_I
{
	GENERATED_BODY()

public:
	
	virtual UObject* SetObjectObjectSingleObjectVariable_Implementation(const FName OptionalVariableName, UObject*& NewValue) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Gorgeous Events|Gorgeous Assignment Mapper")
	void FlushAssignedVariables(UGorgeousEvent* Event);

	virtual void FlushAssignedVariables_Native(UGorgeousEvent* Event);

private:

	TObjectPtr<AEventTrigger_A> EventInstigator;
	TObjectPtr<UGorgeousEvent> CallingEvent;
};