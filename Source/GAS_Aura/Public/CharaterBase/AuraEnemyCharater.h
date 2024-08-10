// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharaterBase/AuraCharaterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemyCharater.generated.h"

/**
 * 
 */
UCLASS()
class GAS_AURA_API AAuraEnemyCharater : public AAuraCharaterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemyCharater();
	virtual void HightlightActor() override;
	virtual void UnHightlightActor() override;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
