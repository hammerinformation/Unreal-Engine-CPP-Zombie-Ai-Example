#include "ZombieAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "FpsCharacter.h"
#include  "Extension.h"
#include "Zombie.h"

AZombieAIController::AZombieAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*PerceptionComp);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(
		this, &AZombieAIController::OnTargetPerceptionUpdated);
}

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AFpsCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	this->ReceiveMoveCompleted.AddDynamic(this, &AZombieAIController::OnMoveCompleted);
}


void AZombieAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			if (GetBlackboardComponent()->GetValueAsBool("PlayerSeen") == false)
			{
				GetBlackboardComponent()->SetValueAsBool("Investigate", true);
				GetBlackboardComponent()->SetValueAsVector("InvestigateLocation", Stimulus.StimulusLocation);
			}
		}
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			if (Actor == Player)
			{
				GetBlackboardComponent()->SetValueAsBool("Investigate", false);
				GetBlackboardComponent()->SetValueAsBool("PlayerSeen", true);
			}
		}
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool("PlayerSeen", false);
	}
}

void AZombieAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
	}
}


FRotator AZombieAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator();
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AZombieAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Player)
		GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Player->GetActorLocation());
}
