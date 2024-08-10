// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharaterBase/AuraCharaterBase.h"
#include "AuraCharater.generated.h"

/**
 * 
 */
UCLASS()
class GAS_AURA_API AAuraCharater : public AAuraCharaterBase
{
	GENERATED_BODY()
public:
	AAuraCharater();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	virtual void InitAbilityActorInfo() override;
};
