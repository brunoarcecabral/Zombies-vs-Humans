// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilidades/UtilidadesMultijugador.h"

#include "WorldPartition/HLOD/HLODActor.h"

void UUtilidadesMultijugador::MostrarRol(AActor* Actor, bool& Aut)
{
	if (Actor->HasAuthority())
	{
		bool Aut = true;
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Yellow, TEXT("Tiene Autoridad"));
			
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Green, TEXT("No Tiene Autoridad"));
		bool Aut = false;
	}
	
	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("No Tiene Rol"));
		break;
	case ROLE_SimulatedProxy:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("SimulatedProxy"));
		break;
	case ROLE_AutonomousProxy:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("AutonomousProxy"));
		break;
	case ROLE_Authority:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("Authority Proxy"));
		break;
	case ROLE_MAX:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("No Rol"));
		break;
	}
}
