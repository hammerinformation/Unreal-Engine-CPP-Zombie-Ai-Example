#include "Zombie.h"

#include "BrainComponent.h"
#include "ZombieAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Extension.h"
#include "ZombieAIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FpsCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();
	ZombieAnimInstance = Cast<UZombieAnimInstance>(GetMesh()->GetAnimInstance());
	AIController = Cast<AZombieAIController>(GetController());
	Player = Cast<AFpsCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void AZombie::DecreaseHealth(const int Value)
{
	Healt -= Value;
	const auto CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;


	if (Hit && ZombieAnimInstance && Healt > 25)
	{
		ZombieAnimInstance->Montage_Play(Hit, 1.f);

		/// If Attacking

		FTimerHandle TimerHandle;
		StopMovement();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
		{			HIExtension::Print(FColor::Turquoise, "Lambda");

			HIExtension::Print(FColor::Red, GetCharacterMovement()->MaxWalkSpeed);
			GetCharacterMovement()->MaxWalkSpeed = 250.f;
			HIExtension::Print(FColor::Green, GetCharacterMovement()->MaxWalkSpeed);

		}), Hit->GetPlayLength(), false);
	}
	Check();
}



void AZombie::Die() const
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCapsuleComponent()->SetSimulatePhysics(true);
	if (Player)
	{
		
		GetMesh()->AddForce(Player->GetActorForwardVector() * 7000000 + FVector::UpVector * 500);
	}
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetMesh()->bPauseAnims = true;
	if (AIController)
		AIController->GetBrainComponent()->DestroyComponent();
}

void AZombie::Check()
{
	if (Healt <= 0)
	{
		Healt = 0;
		Die();
	}
	else if (Healt < 25)
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("Crawling", true);
	}
}


void AZombie::StartMovement(const float Speed) const
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AZombie::StopMovement() const
{
	GetCharacterMovement()->MaxWalkSpeed = 0;
}
