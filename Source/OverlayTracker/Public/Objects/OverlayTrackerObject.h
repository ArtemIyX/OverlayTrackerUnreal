// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "OverlayTrackerObject.generated.h"

class UOverlayTrackerCanvasWidget;
/**
 * @class UOverlayTrackerObject
 * @brief Logic provider for a single overlay element
 * 
 * This class acts as the data & logic provider for a single overlay element that
 * can be rendered on top of the 3-D world (e.g. name plates, markers, health
 * bars, etc.).
 */
UCLASS(Blueprintable, BlueprintType, meta=(ShowWorldContextPin=true))
class OVERLAYTRACKER_API UOverlayTrackerObject : public UObject
{
	GENERATED_BODY()

public:

protected:
	/** Cached widget instance */
	UPROPERTY(Transient, BlueprintReadWrite)
	UUserWidget* CachedWidget;

	/** Cached unique identifier for this tracker */
	UPROPERTY(Transient, BlueprintReadWrite)
	FString CachedUID;

public:
	/**
	 * @brief Assigns a new UID to this tracker.
	 * @param InUid The identifier to store in CachedUID.
	 */
	UFUNCTION(BlueprintCallable)
	void SetUID(const FString& InUid);

	/**
	 * @brief Checks whether a widget has already been created and cached.
	 * @return true if CachedWidget is non-null, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasWidget() const;

	/**
	 * @brief Determines whether the overlay should be rendered.
	 * @param DistanceToCam Distance from the owning camera to the object.
	 * @return true when the widget should be visible; false to hide.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	bool ShouldBeVisible(float DistanceToCam) const;

	/**
	 * @brief Creates (or re-creates) the actual UUserWidget instance.
	 * @param InOwner PlayerController that will own the widget.
	 * @return A valid UUserWidget pointer or nullptr on failure.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	UUserWidget* CreateTrackerWidget(APlayerController* InOwner);

	/**
	 * @brief Returns the cached widget without attempting to create one.
	 * @return CachedWidget (may be nullptr).
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="OverlayTrackerObject")
	UUserWidget* GetCachedWidget() const { return CachedWidget; }

	/**
	 * @brief Supplies the world-space position used for screen projection.
	 * @return FVector in world coordinates.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	FVector GetObjectWorldLocation();

	/**
	 * @brief Computes the desired on-screen dimensions for this tracker.
	 * @param Distance Distance from the camera to the object (units).
	 * @return 2-D size (in screen pixels) for the widget.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	FVector2D GetSize(float Distance);

	/**
	 * @brief Retrieves the currently assigned UID.
	 * @return CachedUID string.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="OverlayTrackerObject")
	FString GetUID() const { return CachedUID; }

	/**
	 * @brief Releases the cached widget and performs any additional cleanup.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void Clear();

	/**
	 * @brief Returns the camera-to-object distance (cm).
	 * @return Distance in centimeters.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	float GetDistanceToCam() const;

	/**
	 * @brief Called when the user has selected this tracker.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifySelected();

	/**
	 * @brief Called when the user has deselected this tracker.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyUnSelected();

	/**
	 * @brief Called when the mouse cursor starts hovering over the tracker.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyHovered();

	/**
	 * @brief Called when the mouse cursor stops hovering over the tracker.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyUnHovered();
};
