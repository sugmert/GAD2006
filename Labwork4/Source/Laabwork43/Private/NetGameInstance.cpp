// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameInstance.h"

void UNetGameInstance::Host(FString MapName, FSPlayerInfo Info)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("Hosting Game..."));
	PlayerInfo = Info;
	PlayerInfo.Ready = true;
	GWorld->ServerTravel(FString::Printf(TEXT("/Game/Maps/%s?listen"), *MapName));
}

void UNetGameInstance::Join(FString Adress, FSPlayerInfo Info)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green,
		FString::Printf(TEXT("JoiningGame at %s..."), *Adress));
	PlayerInfo = Info;
	PlayerInfo.Ready = true;
	GWorld->GetFirstPlayerController()->ClientTravel(Adress,
		ETravelType::TRAVEL_Absolute);
}
