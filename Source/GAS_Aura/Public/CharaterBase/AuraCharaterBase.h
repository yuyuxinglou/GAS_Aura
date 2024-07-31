// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharaterBase.generated.h"

UCLASS(Abstract)
class GAS_AURA_API AAuraCharaterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAuraCharaterBase();

protected:
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
