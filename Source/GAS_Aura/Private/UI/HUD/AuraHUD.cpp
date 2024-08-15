// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"

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

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
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
	OverlayWidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	
	
}
