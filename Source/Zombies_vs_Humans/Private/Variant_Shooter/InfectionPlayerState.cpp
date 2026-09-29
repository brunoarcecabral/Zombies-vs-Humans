// IMPORTANTE: Si esta primera línea te tira error de "No such file", 
// cambiala simplemente por #include "InfectionPlayerState.h"
#include "Variant_Shooter/InfectionPlayerState.h" 
#include "Net/UnrealNetwork.h"

AInfectionPlayerState::AInfectionPlayerState()
{
    CurrentTeam = EPlayerTeam::Survivor;
}

void AInfectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Acá estaba el error. Sin el guion bajo.
    DOREPLIFETIME(AInfectionPlayerState, CurrentTeam);
}
void AInfectionPlayerState::SetTeam(EPlayerTeam NewTeam)
{
    if (HasAuthority())
    {
        CurrentTeam = NewTeam;
        OnRep_Team();
    }
}

void AInfectionPlayerState::OnRep_Team()
{
    BP_OnTeamChanged(CurrentTeam);
}