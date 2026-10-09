// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilidadesMultijugador.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_VS_HUMANS_API UUtilidadesMultijugador : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = Utilidades)
	static void MostrarRol(AActor* actor, bool& Aut);
};
