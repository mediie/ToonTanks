// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/HitResult.h"




ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		
		RotateTurret(HitResult.ImpactPoint);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Green, false, -1.f);
	}
}

void  ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast to Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the move action
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATank::Move);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATank::Turn);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ATank::Fire);
	}
}

void ATank::Move(const FInputActionValue& Value)
{

		FVector2D InputValue = Value.Get<FVector2D>();
		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = InputValue.X * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		ATank::AddActorLocalOffset(DeltaLocation, true); //true to block if colliding


}
void ATank::Turn(const FInputActionValue& Value)
{
		FVector2D InputValue = Value.Get<FVector2D>();

		
		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = InputValue.X * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
		ATank::AddActorLocalRotation(DeltaRotation, true); //true to block if colliding
}
