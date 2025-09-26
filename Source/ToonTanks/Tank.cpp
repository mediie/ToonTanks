// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"



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

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
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

	}
}

void ATank::Move(const FInputActionValue& Value)
{

	if (Controller) 
	{

		FVector2D InputValue = Value.Get<FVector2D>();
		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = InputValue.X * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		ATank::AddActorLocalOffset(DeltaLocation, true); //true to block if colliding

		UE_LOG(LogTemp, Warning, TEXT("x-Axis Value: %f"), InputValue.X); 
	}
}
void ATank::Turn(const FInputActionValue& Value)
{
		FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller)
	{	
		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = InputValue.X * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
		ATank::AddActorLocalRotation(DeltaRotation, true); //true to block if colliding

		UE_LOG(LogTemp, Warning, TEXT("Rotation x-Axis Value: %f"), InputValue.X);
	}
}
