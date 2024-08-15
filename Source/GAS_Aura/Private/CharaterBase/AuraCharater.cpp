// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaterBase/AuraCharater.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

AAuraCharater::AAuraCharater()
{
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;
 
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false; 
}

void AAuraCharater::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharater::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// InitAbilityActorInfo();
}

int32 AAuraCharater::GetPlayerLevel()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
	
}

void AAuraCharater::InitAbilityActorInfo()
{
	AAuraPlayerState*  AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributSet=AuraPlayerState->GetAttributeSet();

	if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD*AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributSet);
		}
	}
	
	InitializeDefaultAttributes();
	
} 
