// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_PlayAnimMontage.h"

#include "AIController.h"
#include "ZombieAnimInstance.h"
#include "Zombie.h"
#include "TimerManager.h"

UTask_PlayAnimMontage::UTask_PlayAnimMontage()
{
	NodeName = "Task Play AnimMontage";
	bCreateNodeInstance = true;
}


EBTNodeResult::Type UTask_PlayAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AnimInstance && AnimMontage)
	{
		AnimInstance->Montage_Play(AnimMontage);
		FinishTaskWithTime(AnimMontage->GetPlayLength(), OwnerComp);
		
	}
	
	return EBTNodeResult::InProgress;
}

void UTask_PlayAnimMontage::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	const AZombie* const Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	AnimInstance = Cast<UZombieAnimInstance>(Zombie->GetMesh()->GetAnimInstance());
}

void UTask_PlayAnimMontage::FinishTaskWithTime(const float& Time, UBehaviorTreeComponent& OwnerComp) const
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}),Time , false);
}
