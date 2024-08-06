// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWigetController(UObject* InWidgetController)
{
	WidgetController=InWidgetController;
	WidgetControllerSet();
}
