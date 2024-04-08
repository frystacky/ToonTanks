// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30.f, 12, FColor::Red, false, -1.f);

	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

	/*DrawDebugSphere(
		GetWorld(), 
		GetActorLocation() + FVector(0.f, 0.f, 200.f),
		100.f,
		12,
		FColor::Red,
		true,
		30.f);*/

}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

	FVector DeltaLocation = FVector::ZeroVector;

	// X = Value * DeltaTime * Speed
	DeltaLocation.X = (Value * UGameplayStatics::GetWorldDeltaSeconds(this) * speed);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	// Yaw = Value * DeltaTime * TurnRate
	DeltaRotation.Yaw = (Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate);
	AddActorLocalRotation(DeltaRotation, true);
}