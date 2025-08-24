// Developed by Wellsaik


#include "Objects/OverlayTrackerObject.h"


UUserWidget* UOverlayTrackerObject::CreateTrackerWidget_Implementation(APlayerController* InOwner)
{
	CachedWidget = CreateWidget<UUserWidget>(InOwner);
	return CachedWidget;
}


FVector UOverlayTrackerObject::GetObjectWorldLocation_Implementation()
{
	return FVector();
}

void UOverlayTrackerObject::Clear_Implementation()
{
	if (IsValid(CachedWidget))
	{
		CachedWidget->RemoveFromParent();
		CachedWidget->ConditionalBeginDestroy();
	}
	CachedWidget = nullptr;
}

FVector2D UOverlayTrackerObject::GetSize_Implementation(float Distance)
{
	return FVector2D(100, 100);
}


void UOverlayTrackerObject::SetUID(const FString& InUid)
{
	this->CachedUID = InUid;
}

bool UOverlayTrackerObject::HasWidget() const
{
	return CachedWidget != nullptr && IsValid(CachedWidget);
}

void UOverlayTrackerObject::NotifyUnHovered_Implementation()
{
	
}

void UOverlayTrackerObject::NotifyHovered_Implementation()
{
	
}

void UOverlayTrackerObject::NotifyUnSelected_Implementation()
{
	
}

void UOverlayTrackerObject::NotifySelected_Implementation()
{
	
}

float UOverlayTrackerObject::GetDistanceToCam_Implementation() const
{
	return 0.0f;
}

bool UOverlayTrackerObject::ShouldBeVisible_Implementation(float DistanceToCam) const
{
	return true;
}