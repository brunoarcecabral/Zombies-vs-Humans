// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces\PlayerInterface.h"
#include "ItemEquipBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ZOMBIES_VS_HUMANS_API AItemEquipBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemEquipBase();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereCollision;
	
	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = true))
	FName SocketName = "";
};
