// Developed by Wellsaik


#include "Widgets/OverlayTrackerCanvasWidget.h"
#include "OverlayTrackerSubsystem.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Objects/OverlayTrackerObject.h"


UOverlayTrackerCanvasWidget::UOverlayTrackerCanvasWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MainCanvas(nullptr) {}

bool UOverlayTrackerCanvasWidget::ProjectToScreen(UOverlayTrackerObject* InTrackerObject, FVector2D& OutScreenPos)
{
	const FVector objLoc = InTrackerObject->GetObjectWorldLocation();
	FVector2D screenPos;
	bool bProjected = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(),
		objLoc, screenPos, false);

	OutScreenPos = screenPos;
	return bProjected;
}

void UOverlayTrackerCanvasWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UOverlayTrackerCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (auto pc = GetOwningPlayer())
	{
		if (auto world = pc->GetWorld())
		{
			if (auto subsystem = world->GetSubsystem<UOverlayTrackerSubsystem>())
			{
				OverlayTrackerSubsystem = subsystem;
				OverlayTrackerSubsystem->CacheCanvasWidget(this);
			}
		}
	}
}

void UOverlayTrackerCanvasWidget::RemoveItemByObject_Implementation(UUserWidget* InItem)
{
	if (MainCanvas->HasChild(InItem))
	{
		MainCanvas->RemoveChild(InItem);
	}
}

void UOverlayTrackerCanvasWidget::UpdatePosition_Implementation(const FString& InUid, UOverlayTrackerObject* InTrackerObject,
	const FVector2D& InScreePos)
{
	if (!InTrackerObject)
		return;
	if (!MainCanvas)
		return;
	UUserWidget* widget = InTrackerObject->GetCachedWidget();
	if (!widget)
		return;
	if (!MainCanvas->HasChild(widget))
		return;

	// Get canvas slot
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(widget);
	if (!slot)
		return;

	// Update alignment
	static FVector2D alignment = FVector2D(0.5f, 0.5f);
	if (slot->GetAlignment() != alignment)
	{
		slot->SetAlignment(alignment);
	}

	// Update position
	if (slot->GetPosition() != InScreePos)
	{
		slot->SetPosition(InScreePos);
	}

	// Retrieve camLoc
	FVector camLoc = FVector::ZeroVector;
	if (APlayerController* pc = GetOwningPlayer())
	{
		if (TObjectPtr<APlayerCameraManager> cam = pc->PlayerCameraManager)
		{
			camLoc = cam->GetCameraLocation();
		}
	}

	// Update size
	FVector2D size = InTrackerObject->GetSize(FVector::Distance(InTrackerObject->GetObjectWorldLocation(), camLoc));
	if (slot->GetSize() != size)
	{
		slot->SetSize(size);
	}
}


void UOverlayTrackerCanvasWidget::AddItem_Implementation(const FString& InUid, UOverlayTrackerObject* InItem)
{
	if (!IsValid(InItem))
	{
		return;
	}
	UUserWidget* widget = InItem->CreateTrackerWidget(GetOwningPlayer());
	widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UCanvasPanelSlot* slot = MainCanvas->AddChildToCanvas(widget);
	slot->SetAlignment(FVector2D(0.5f, 0.5f));
}

void UOverlayTrackerCanvasWidget::GetCameraLocRot_Implementation(FVector& OutLoc, FRotator& OutRot) const
{
	OutLoc = FVector::ZeroVector;
	OutRot = FRotator::ZeroRotator;
	if (APlayerController* pc = GetOwningPlayer())
	{
		pc->GetPlayerViewPoint(OutLoc, OutRot);
	}
}