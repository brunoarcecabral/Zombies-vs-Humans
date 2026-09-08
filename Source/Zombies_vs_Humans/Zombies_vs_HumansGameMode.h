// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Zombies_vs_HumansGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class AZombies_vs_HumansGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZombies_vs_HumansGameMode();
};



