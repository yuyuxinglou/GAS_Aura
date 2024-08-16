// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h" //增强子系统的头文件
#include "EnhancedInputComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// UEnhancedInputLocalPlayerSubsystem;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	bShowMouseCursor=true;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//不锁定鼠标
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	// AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	// AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		// if (IsValid(ThisActor))
		// {
		// 	TargetingStatus = ThisActor->Implements<UEnemyInterface>() ? ETargetingStatus::TargetingEnemy : ETargetingStatus::TargetingNonEnemy;
		// }
		// else
		// {
		// 	TargetingStatus = ETargetingStatus::NotTargeting;
		// }
		// bAutoRunning = false;
		bTargeting=ThisActor  ? true:false;
	}
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	// if (TargetingStatus != ETargetingStatus::TargetingEnemy && !bShiftKeyDown)
	// {
	// 	const APawn* ControlledPawn = GetPawn();
	// 	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	// 	{
	// 		if (IsValid(ThisActor) && ThisActor->Implements<UHighlightInterface>())
	// 		{
	// 			IHighlightInterface::Execute_SetMoveToLocation(ThisActor, CachedDestination);
	// 		}
	// 		else if (GetASC() && !GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	// 		{
	// 			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickNiagaraSystem, CachedDestination);
	// 		}
	// 		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
	// 		{
	// 			Spline->ClearSplinePoints();
	// 			for (const FVector& PointLoc : NavPath->PathPoints)
	// 			{
	// 				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
	// 			}
	// 			if (NavPath->PathPoints.Num() > 0)
	// 			{
	// 				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
	// 				bAutoRunning = true;
	// 			}
	// 		}
	// 	}
	// 	FollowTime = 0.f;
	// 	TargetingStatus = ETargetingStatus::NotTargeting;
	// }
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	

	if(bTargeting)
	{
		if(GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	
	// if (TargetingStatus == ETargetingStatus::TargetingEnemy || bShiftKeyDown)
	// {
	// 	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	// }
	// else
	// {
	// 	FollowTime += GetWorld()->GetDeltaSeconds();
	// 	if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;
	//
	// 	if (APawn* ControlledPawn = GetPawn())
	// 	{
	// 		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	// 		ControlledPawn->AddMovementInput(WorldDirection);
	// 	}
	// }
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RigntDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn=GetPawn<APawn>())
	{ 
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RigntDirection,InputAxisVector.X);
		
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	if(LastActor!=ThisActor)
	{
		if(LastActor) LastActor->UnHightlightActor();
		if(ThisActor) ThisActor->HightlightActor();
	}
	
}
