// Copyright Epic Games, Inc. All Rights Reserved.

#include "Zombies_vs_HumansCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interfaces/PlayerInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Zombies_vs_Humans.h"


AZombies_vs_HumansCharacter::AZombies_vs_HumansCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AZombies_vs_HumansCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AZombies_vs_HumansCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AZombies_vs_HumansCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AZombies_vs_HumansCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AZombies_vs_HumansCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AZombies_vs_HumansCharacter::LookInput);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AZombies_vs_HumansCharacter::HacerLineTrace);
	
	}
	
	else
	{
		UE_LOG(LogZombies_vs_Humans, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

USkeletalMeshComponent* AZombies_vs_HumansCharacter::GetSkeletalMesh_Implementation()
{
	return GetMesh() ;
}

void AZombies_vs_HumansCharacter::RecibirDano(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
				  AController* InstigatedBy, AActor* DamageCauser)
{
	Vida = FMath::Clamp(Vida - Damage);
}


void AZombies_vs_HumansCharacter::HacerLineTrace()
{
	FVector Inicio = FirstPersonCameraComponent->GetComponentLocation();
	FRotator Rotacion;
	GetActorEyesViewPoint(Inicio, Rotacion);
	
	FVector Fin = Inicio + FirstPersonCameraComponent->GetForwardVector() * 1000.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // para que no se golpee a sí mismo

	bool bGolpeo = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Inicio,
		Fin,
		ECC_Pawn,
		Params
	);

	// Debug: dibuja la línea (verde si golpea, rojo si no)
	DrawDebugLine(GetWorld(), Inicio, bGolpeo ? Hit.ImpactPoint : Fin,
				  bGolpeo ? FColor::Green : FColor::Red, false, 0.f, 0, 1.f);

	if (bGolpeo)
	{
		AActor* ActorGolpeado = Hit.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Golpeé: %s"), *ActorGolpeado->GetName());
		
		AActor* ActorGolpeado->RecibirDano();
	}
}

void AZombies_vs_HumansCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AZombies_vs_HumansCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AZombies_vs_HumansCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AZombies_vs_HumansCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AZombies_vs_HumansCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AZombies_vs_HumansCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

