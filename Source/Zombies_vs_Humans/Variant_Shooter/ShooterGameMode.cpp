// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameMode.h" // Ajustá el path si te tira error
#include "ShooterUI.h"
#include "Variant_Shooter/InfectionPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"

AShooterGameMode::AShooterGameMode()
{
    // Le decimos a Unreal que empiece a usar nuestro nuevo PlayerState
    PlayerStateClass = AInfectionPlayerState::StaticClass();
}

void AShooterGameMode::BeginPlay()
{
    Super::BeginPlay();

    ShooterUI = CreateWidget<UShooterUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ShooterUIClass);
    if (ShooterUI) ShooterUI->AddToViewport(0);

    // Arrancamos los relojes
    
    GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &AShooterGameMode::OnMatchTimeUp, MatchDuration, false);
}



void AShooterGameMode::PlayerInfected(AController* VictimController, AController* AttackerController)
{
    if (!VictimController) return;

    if (AInfectionPlayerState* PS = VictimController->GetPlayerState<AInfectionPlayerState>())
    {
        PS->SetTeam(EPlayerTeam::Infected);
        CheckWinCondition();
        UpdateScoresUI();
    }
}

void AShooterGameMode::CheckWinCondition()
{
    bool bSurvivorsRemaining = false;

    for (APlayerState* PS : GameState->PlayerArray)
    {
        if (AInfectionPlayerState* IPS = Cast<AInfectionPlayerState>(PS))
        {
            if (IPS->GetTeam() == EPlayerTeam::Survivor)
            {
                bSurvivorsRemaining = true;
                break;
            }
        }
    }

    if (!bSurvivorsRemaining)
    {
        UE_LOG(LogTemp, Warning, TEXT("INFERNO: Los infectados han ganado la partida."));
    }
}

void AShooterGameMode::OnMatchTimeUp()
{
    int32 SurvivorCount = 0;
    int32 InfectedCount = 0;

    for (APlayerState* PS : GameState->PlayerArray)
    {
        if (AInfectionPlayerState* IPS = Cast<AInfectionPlayerState>(PS))
        {
            if (IPS->GetTeam() == EPlayerTeam::Survivor)
            {
                SurvivorCount++;
            }
            else
            {
                InfectedCount++;
            }
        }
    }

    if (SurvivorCount > InfectedCount)
    {
        UE_LOG(LogTemp, Warning, TEXT("Sobrevivientes ganan por tiempo!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infectados ganan por tiempo!"));
    }
}

void AShooterGameMode::UpdateScoresUI()
{
    if (!ShooterUI || !GameState) return;

    int32 SurvivorCount = 0;
    int32 InfectedCount = 0;

    for (APlayerState* PS : GameState->PlayerArray)
    {
        if (AInfectionPlayerState* IPS = Cast<AInfectionPlayerState>(PS))
        {
            if (IPS->GetTeam() == EPlayerTeam::Survivor) SurvivorCount++;
            else InfectedCount++;
        }
    }

    // Aprovechamos tu UI existente: El equipo 0 muestra cantidad de Sobrevivientes, el 1 Infectados.
    ShooterUI->BP_UpdateScore(0, SurvivorCount);
    ShooterUI->BP_UpdateScore(1, InfectedCount);
}

void AShooterGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer); // Obligatorio llamar al padre primero

    if (AInfectionPlayerState* PS = NewPlayer->GetPlayerState<AInfectionPlayerState>())
    {
        int32 SurvivorCount = 0;
        int32 InfectedCount = 0;

        // Contamos los equipos actuales
        for (APlayerState* ExistingPS : GameState->PlayerArray)
        {
            if (ExistingPS != PS) // Ignoramos al jugador que está entrando ahora mismo
            {
                if (AInfectionPlayerState* IPS = Cast<AInfectionPlayerState>(ExistingPS))
                {
                    if (IPS->GetTeam() == EPlayerTeam::Survivor) SurvivorCount++;
                    else InfectedCount++;
                }
            }
        }

        // Lo asignamos al equipo que necesite jugadores
        if (SurvivorCount <= InfectedCount)
        {
            PS->SetTeam(EPlayerTeam::Survivor);
        }
        else
        {
            PS->SetTeam(EPlayerTeam::Infected);
        }
    }

    UpdateScoresUI();
}