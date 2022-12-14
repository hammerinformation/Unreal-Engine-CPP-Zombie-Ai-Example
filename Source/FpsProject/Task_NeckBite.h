// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_NeckBite.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class  UTask_NeckBite : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UTask_NeckBite();


public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
