// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/AuraHUD.h"

UOverlayAuraWidgetController* AAuraHUD::GetOverlayAuraWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayAuraWidgetController==nullptr)
	{
		OverlayAuraWidgetController=NewObject<UOverlayAuraWidgetController>(this,OverlayAuraWidgetcontrollerClass);
		OverlayAuraWidgetController->SetWidgetControllerParams(WCParams);
		OverlayAuraWidgetController->BindCallbacksToDependencies();
	}
	return OverlayAuraWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayAuraWidgetcontrollerClass,TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayAuraWidgetController* OverlayWidgetController=GetOverlayAuraWidgetController(WidgetControllerParams);
	OverlayWidget->SetWigetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitiaValues();
	Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	
	
}
