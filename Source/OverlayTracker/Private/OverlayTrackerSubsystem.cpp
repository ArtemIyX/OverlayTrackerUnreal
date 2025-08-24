// Developed by Wellsaik


#include "OverlayTrackerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Objects/OverlayTrackerObject.h"
#include "Widgets/OverlayTrackerCanvasWidget.h"


void UOverlayTrackerSubsystem::Deinitialize()
{
	ClearMap();
	Super::Deinitialize();
}

void UOverlayTrackerSubsystem::CacheCanvasWidget(class UOverlayTrackerCanvasWidget* InCanvasWidget)
{
	SavedCanvasWidget = InCanvasWidget;
}

void UOverlayTrackerSubsystem::AddObject(const FString& InUID, UOverlayTrackerObject* ObjectToAdd)
{
	check(ObjectToAdd != nullptr);
	ObjectToAdd->SetUID(InUID);
	SavedWidgetObjects.Add(InUID, ObjectToAdd);

	if (SavedCanvasWidget && ObjectToAdd)
	{
		RefreshWidget(SavedCanvasWidget.Get(),
			TTuple<FString, UOverlayTrackerObject*>(InUID, ObjectToAdd));
	}
}

void UOverlayTrackerSubsystem::RemoveObject(const FString& InUID)
{
	if (SavedWidgetObjects.Contains(InUID))
	{
		UOverlayTrackerObject* object = SavedWidgetObjects[InUID];
		if (IsValid(object))
		{
			// Clear widget
			object->Clear();
			object->ConditionalBeginDestroy();
			SavedWidgetObjects[InUID] = nullptr;
		}

		SavedWidgetObjects.Remove(InUID);
	}
}

UOverlayTrackerObject* UOverlayTrackerSubsystem::GetObject(const FString& InUID)
{
	UOverlayTrackerObject** itemPtr = SavedWidgetObjects.Find(InUID);
	if (itemPtr == nullptr)
	{
		return nullptr;
	}
	UOverlayTrackerObject* item = *itemPtr;
	return item;
}

void UOverlayTrackerSubsystem::ClearMap()
{
	for (const TTuple<FString, UOverlayTrackerObject*>& el : SavedWidgetObjects)
	{
		if (IsValid(el.Value))
		{
			el.Value->Clear();
			el.Value->ConditionalBeginDestroy();
		}
	}
	SavedWidgetObjects.Empty();
}


void UOverlayTrackerSubsystem::UpdatePositions(
	UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget)
{
	if (!OverlayTrackerCanvasWidget)
	{
		return;
	}
	for (const TTuple<FString, UOverlayTrackerObject*>& el : SavedWidgetObjects)
	{
		if (!IsValid(el.Value))
		{
			continue;
		}


		if (RefreshWidget(SavedCanvasWidget, el))
		{
			FVector2D projectedPos;
			if (SavedCanvasWidget->ProjectToScreen(el.Value, projectedPos))
			{
				OverlayTrackerCanvasWidget->UpdatePosition(el.Key, el.Value, projectedPos);
			}
		}
	}
}

void UOverlayTrackerSubsystem::SelectObject(const FString& InUid)
{
	if (SavedWidgetObjects.Contains(InUid))
	{
		UOverlayTrackerObject* object = SavedWidgetObjects[InUid];
		object->NotifySelected();
	}
}

void UOverlayTrackerSubsystem::UnSelectObject(const FString& InUid)
{
	if (SavedWidgetObjects.Contains(InUid))
	{
		UOverlayTrackerObject* object = SavedWidgetObjects[InUid];
		object->NotifyUnSelected();
	}
}

void UOverlayTrackerSubsystem::HoverObject(const FString& InUid)
{
	if (SavedWidgetObjects.Contains(InUid))
	{
		UOverlayTrackerObject* object = SavedWidgetObjects[InUid];
		object->NotifyHovered();
	}
}

void UOverlayTrackerSubsystem::UnHoverObject(const FString& InUid)
{
	if (SavedWidgetObjects.Contains(InUid))
	{
		UOverlayTrackerObject* object = SavedWidgetObjects[InUid];
		object->NotifyUnHovered();
	}
}

bool UOverlayTrackerSubsystem::RefreshWidget(
	UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget,
	const TTuple<FString, UOverlayTrackerObject*>& InTrackerTuple)
{
	UOverlayTrackerObject* trackerObject = InTrackerTuple.Value;
	FString uid = InTrackerTuple.Key;
	if (!IsValid(trackerObject))
	{
		return false;
	}
	float distanceToCam = trackerObject->GetDistanceToCam();
	bool bShouldBeVisible = trackerObject->ShouldBeVisible(distanceToCam);
	bool bHasWidget = trackerObject->HasWidget();
	APlayerController* pc = OverlayTrackerCanvasWidget->GetOwningPlayer();
	if (!IsValid(pc))
	{
		return false;
	}

	UUserWidget* widget = trackerObject->GetCachedWidget();

	// Check projection only
	if (bShouldBeVisible && bHasWidget)
	{
		FVector2D pos;

		// Clear if not projected
		if (SavedCanvasWidget && widget)
		{
			if (!SavedCanvasWidget->ProjectToScreen(trackerObject, pos))
			{
				SavedCanvasWidget->RemoveItemByObject(widget);
				trackerObject->Clear();
				return false; // Widget is removed from screen
			}
		}
	}
	// If it should be visible but does not have widget
	else if (bShouldBeVisible && !bHasWidget)
	{
		if (SavedCanvasWidget)
		{
			FVector2D pos;
			// Add if projected
			if (SavedCanvasWidget->ProjectToScreen(trackerObject, pos))
			{
				SavedCanvasWidget->AddItem(uid, trackerObject);
				return true; // Widget is added to screen
			}
		}
	}
	// Should not be visible -> Clear
	else if (!bShouldBeVisible && bHasWidget)
	{
		if (SavedCanvasWidget && widget)
		{
			SavedCanvasWidget->RemoveItemByObject(widget);
			trackerObject->Clear();
			return false; // Widget is removed from screen
		}
	}

	return trackerObject->HasWidget();
}


UOverlayTrackerSubsystem* UOverlayTrackerSubsystem::GetOverlayTrackerSubsystem(UObject* WorldContextObject)
{
	auto world = WorldContextObject->GetWorld();
	checkf(world != nullptr, TEXT("%hs Failed to get world"), __FUNCTION__);

	return world->GetSubsystem<UOverlayTrackerSubsystem>();
}

void UOverlayTrackerSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SavedCanvasWidget)
		return;

	UpdatePositions(SavedCanvasWidget);
}

TStatId UOverlayTrackerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UOverlayTrackerSubsystem, STATGROUP_Tickables);
}