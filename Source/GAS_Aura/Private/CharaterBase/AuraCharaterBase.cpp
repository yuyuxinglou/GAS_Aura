// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaterBase/AuraCharaterBase.h"


AAuraCharaterBase::AAuraCharaterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AAuraCharaterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


