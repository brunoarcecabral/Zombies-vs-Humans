#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h" // Tiene que estar sí o sí antes del generated
#include "InfectionPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerTeam : uint8
{
    Survivor UMETA(DisplayName = "Survivor"),
    Infected UMETA(DisplayName = "Infected")
};

UCLASS()
class ZOMBIES_VS_HUMANS_API AInfectionPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AInfectionPlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Team")
    EPlayerTeam GetTeam() const { return CurrentTeam; }

    void SetTeam(EPlayerTeam NewTeam);

    UFUNCTION(BlueprintImplementableEvent, Category = "Team")
    void BP_OnTeamChanged(EPlayerTeam NewTeam);

protected:
    UPROPERTY(ReplicatedUsing = OnRep_Team)
    EPlayerTeam CurrentTeam;

    UFUNCTION()
    void OnRep_Team();
};