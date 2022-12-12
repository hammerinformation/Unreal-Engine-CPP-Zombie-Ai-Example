#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "FpsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WeaponAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "Camera/PlayerCameraManager.h"
#include  "Kismet/GameplayStatics.h"
#include "Extension.h"
#include "Zombie.h"
#include "Perception/AISense_Hearing.h"


#define Private

UWeapon::UWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	FpsCharacter = Cast<AFpsCharacter>(GetOwner());
	WeaponMesh = FpsCharacter->GetWeaponMesh();
	InputComponent = FpsCharacter->InputComponent;
	InputComponent->BindAction("Fire", IE_Pressed, this, &UWeapon::StartFire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &UWeapon::Reload);
	WeaponAnimInstance = Cast<UWeaponAnimInstance>(WeaponMesh->GetAnimInstance());
}


void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

Private void UWeapon::StartFire()
{
	if (WeaponAnimInstance->IsAnyMontagePlaying() == false)
	{
		OnFire();
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("Bullet: %d"), Bullet));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("TotalBullet: %d"), TotalBullet));


	}


}
Private void UWeapon::OnFire()
{
	if (Bullet == 0)
	{
		return;
	}
	if (WeaponAnimInstance)
	{
		WeaponAnimInstance->Montage_Play(FireAnimMontage, 1);
		if(MuzzleFlash)
		{
			FTransform T;
			T.SetLocation(WeaponMesh->GetRelativeLocation());
			T.SetScale3D(FVector::OneVector);


			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, T, false);
		}
		
	}
	
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), FpsCharacter->GetActorLocation(), 1.0f, FpsCharacter, 0.0f);

	const APlayerCameraManager* const PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FHitResult OutHit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	UCameraComponent& Camera = *FpsCharacter->GetCamera();
	FVector ForwardVector = PlayerCameraManager->GetCameraLocation().ForwardVector.GetSafeNormal();
	ForwardVector = PlayerCameraManager->GetCameraRotation().Vector();
	FVector End = ((ForwardVector * 100000.f) + Start);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), OutHit.Location, 1.0f, FpsCharacter, 0.0f);

			AZombie* Zombie = Cast<AZombie>(OutHit.GetActor());
			if (Zombie)
			{
				int Value = FMath::RandRange(25, 100);
				if (Zombie->GetHealt()>0)
				Zombie->DecreaseHealth(Value);
			}
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

			DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5, 60, FColor::Red, false, 2.0f);
		}
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);

	Bullet -= 1;

}
Private void UWeapon::StopFire()
{

}

Private void UWeapon::Reload()
{
	if (TotalBullet != 0 && Bullet != 5 && WeaponAnimInstance->IsAnyMontagePlaying() == false)
	{
		if (WeaponAnimInstance)
		{
			WeaponAnimInstance->Montage_Play(ReloadAnimMontage, 1);
			TotalBullet -= (5 - Bullet);
			Bullet = 5;
		}
	}


}

