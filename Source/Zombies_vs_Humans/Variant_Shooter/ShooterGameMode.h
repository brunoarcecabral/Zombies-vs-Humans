// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class UShooterUI;

UCLASS(abstract)
class ZOMBIES_VS_HUMANS_API AShooterGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AShooterGameMode(); // Constructor para asignar el PlayerState

    // Llama el Character cuando su vida llega a 0
    void PlayerInfected(AController* VictimController, AController* AttackerController);

    virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Shooter")
    TSubclassOf<UShooterUI> ShooterUIClass;

    TObjectPtr<UShooterUI> ShooterUI;

    UPROPERTY(EditDefaultsOnly, Category = "Match", meta = (ClampMin = 10, Units = "s"))
    float MatchDuration = 300.0f; // 5 minutos de partida

    UPROPERTY(EditDefaultsOnly, Category = "Match", meta = (ClampMin = 5, Units = "s"))

    FTimerHandle MatchTimerHandle;
    

    virtual void BeginPlay() override;

    
    void CheckWinCondition();
    void OnMatchTimeUp();
    void UpdateScoresUI();
};