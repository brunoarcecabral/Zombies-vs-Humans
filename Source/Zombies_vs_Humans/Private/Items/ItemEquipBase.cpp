// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemEquipBase.h"

#include "Components/SphereComponent.h"

// Sets default values
AItemEquipBase::AItemEquipBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(ItemMesh);
	SphereCollision->SetSphereRadius(200.0f);
}

// Called when the game starts or when spawned
void AItemEquipBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemEquipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemEquipBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor)return;
	
	if (OtherActor->Implements<UPlayerInterface>())
	{
		USkeletalMeshComponent* SkeletalMeshComponent = IPlayerInterface::Execute_GetSkeletalMesh(OtherActor);
		AttachToComponent(SkeletalMeshComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}

