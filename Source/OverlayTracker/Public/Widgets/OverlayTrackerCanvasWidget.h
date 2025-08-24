// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "OverlayTrackerCanvasWidget.generated.h"

class UOverlayTrackerSubsystem;
class UOverlayTrackerObject;

/**
 * @class UOverlayTrackerCanvasWidget
 * @brief A user widget for rendering and managing overlay tracker objects on a canvas in the game UI.
 * 
 * This class provides functionality for projecting 3D world positions of overlay tracker objects to 2D screen positions,
 * managing their addition and removal, and updating their positions on the canvas.
 */
UCLASS(Blueprintable, BlueprintType)
class OVERLAYTRACKER_API UOverlayTrackerCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief Constructor for the overlay tracker canvas widget.
	 * @param ObjectInitializer The object initializer for constructing the widget.
	 */
	UOverlayTrackerCanvasWidget(const FObjectInitializer& ObjectInitializer);

protected:
	/** @brief A reference to the overlay tracker subsystem for managing tracker objects. */
	UPROPERTY(Transient)
	TObjectPtr<UOverlayTrackerSubsystem> OverlayTrackerSubsystem;

protected:
	/**
	 * @brief Retrieves the camera's location and rotation.
	 * @param OutLoc The output vector for the camera's location.
	 * @param OutRot The output rotator for the camera's rotation.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTracker")
	void GetCameraLocRot(FVector& OutLoc, FRotator& OutRot) const;

public:
	/** @brief The main canvas panel for rendering overlay tracker objects. */
	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* MainCanvas;

	/**
	 * @brief Projects a tracker object's 3D world position to a 2D screen position.
	 * @param InTrackerObject The overlay tracker object to project.
	 * @param OutScreenPos The output 2D screen position.
	 * @return True if the projection was successful, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool ProjectToScreen(UOverlayTrackerObject* InTrackerObject, FVector2D& OutScreenPos);
	

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	
	/**
	 * @brief Adds an overlay tracker object to the canvas.
	 * @param InUid The unique identifier for the tracker object.
	 * @param InItem The overlay tracker object to add.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddItem(const FString& InUid, UOverlayTrackerObject* InItem);
	
	/**
	 * @brief Removes an overlay tracker object from the canvas by its widget.
	 * @param InItem The widget associated with the tracker object to remove.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveItemByObject(UUserWidget* InItem);
	
	/**
	 * @brief Updates the position of an overlay tracker object on the canvas.
	 * @param InUid The unique identifier of the tracker object.
	 * @param InTrackerObject The overlay tracker object to update.
	 * @param InScreePos The new 2D screen position for the object.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePosition(const FString& InUid, UOverlayTrackerObject* InTrackerObject, const FVector2D& InScreePos);
};