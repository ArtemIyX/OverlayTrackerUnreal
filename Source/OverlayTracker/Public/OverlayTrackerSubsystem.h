// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OverlayTrackerSubsystem.generated.h"

class UCanvasPanel;
class UOverlayTrackerObject;

/**
 * @class UOverlayTrackerSubsystem
 * @brief A subsystem for managing overlay tracker objects and their associated canvas widget in a game world.
 * 
 * This class handles the lifecycle of overlay tracker objects, including adding, removing, and updating their positions.
 * It also manages interactions such as selection and hovering of objects, and maintains a reference to a canvas widget for rendering.
 */
UCLASS(Blueprintable, BlueprintType)
class OVERLAYTRACKER_API UOverlayTrackerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	/** @brief A map storing overlay tracker objects, keyed by their unique identifiers. */
	UPROPERTY()
	TMap<FString, UOverlayTrackerObject*> SavedWidgetObjects;

	/** @brief A reference to the canvas widget used for rendering overlay tracker objects. */
	UPROPERTY()
	TObjectPtr<class UOverlayTrackerCanvasWidget> SavedCanvasWidget;

protected:
	/**
	 * @brief Refreshes the specified canvas widget, creating or deleting it as needed.
	 * @param OverlayTrackerCanvasWidget The canvas widget to refresh.
	 * @param InTrackerTuple A tuple containing the unique ID and associated overlay tracker object.
	 * @return True if the widget is visible and valid, false otherwise.
	 */
	bool RefreshWidget(class UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget, const TTuple<FString, UOverlayTrackerObject*>& InTrackerTuple);

public:
	/**
	 * @brief Retrieves the overlay tracker subsystem for the specified world context.
	 * @param WorldContextObject The object providing the world context.
	 * @return A pointer to the overlay tracker subsystem instance.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem", meta=(WorldContext="WorldContextObject"))
	static UOverlayTrackerSubsystem* GetOverlayTrackerSubsystem(UObject* WorldContextObject);

	/**
	 * @brief Deinitializes the subsystem, cleaning up resources.
	 */
	virtual void Deinitialize() override;

	/**
	 * @brief Caches the specified canvas widget for rendering overlay tracker objects.
	 * @param InCanvasWidget The canvas widget to cache.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void CacheCanvasWidget(class UOverlayTrackerCanvasWidget* InCanvasWidget);

	/**
	 * @brief Adds an overlay tracker object to the subsystem with the specified unique ID.
	 * @param InUID The unique identifier for the object.
	 * @param ObjectToAdd The overlay tracker object to add.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void AddObject(const FString& InUID, UOverlayTrackerObject* ObjectToAdd);

	/**
	 * @brief Removes an overlay tracker object with the specified unique ID.
	 * @param InUID The unique identifier of the object to remove.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void RemoveObject(const FString& InUID);

	/**
	 * @brief Retrieves an overlay tracker object by its unique ID.
	 * @param InUID The unique identifier of the object.
	 * @return A pointer to the overlay tracker object, or nullptr if not found.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	UOverlayTrackerObject* GetObject(const FString& InUID);

	/**
	 * @brief Clears all overlay tracker objects from the subsystem.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void ClearMap();

	/**
	 * @brief Updates the positions of all overlay tracker objects on the specified canvas widget.
	 * @param OverlayTrackerCanvasWidget The canvas widget used for rendering.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UpdatePositions(class UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget);

	/**
	 * @brief Selects an overlay tracker object by its unique ID.
	 * @param InUid The unique identifier of the object to select.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void SelectObject(const FString& InUid);

	/**
	 * @brief Deselects an overlay tracker object by its unique ID.
	 * @param InUid The unique identifier of the object to deselect.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UnSelectObject(const FString& InUid);

	/**
	 * @brief Sets an overlay tracker object as hovered by its unique ID.
	 * @param InUid The unique identifier of the object to hover.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void HoverObject(const FString& InUid);

	/**
	 * @brief Removes hover state from an overlay tracker object by its unique ID.
	 * @param InUid The unique identifier of the object to unhover.
	 */
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UnHoverObject(const FString& InUid);


	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
};