// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OverlayTrackerSubsystem.generated.h"

class UCanvasPanel;
class UOverlayTrackerObject;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class OVERLAYTRACKER_API UOverlayTrackerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FString, UOverlayTrackerObject*> SavedWidgetObjects;

	UPROPERTY()
	TObjectPtr<class UOverlayTrackerCanvasWidget> SavedCanvasWidget;

protected:
	/**
	 * Creates a widget if necessary and deletes it if it needs to be hidden
	 * @return Returns true if widget is visible and valid
	 */
	bool RefreshWidget(class UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget, const TTuple<FString,
		UOverlayTrackerObject*>& InTrackerTuple);

public:
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem", meta=(WorldContext="WorldContextObject"))
	static UOverlayTrackerSubsystem* GetOverlayTrackerSubsystem(UObject* WorldContextObject);

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void CacheCanvasWidget(class UOverlayTrackerCanvasWidget* InCanvasWidget);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void AddObject(const FString& InUID, UOverlayTrackerObject* ObjectToAdd);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void RemoveObject(const FString& InUID);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	UOverlayTrackerObject* GetObject(const FString& InUID);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void ClearMap();

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UpdatePositions(class UOverlayTrackerCanvasWidget* OverlayTrackerCanvasWidget);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void SelectObject(const FString& InUid);
	
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UnSelectObject(const FString& InUid);

	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void HoverObject(const FString& InUid);
	
	UFUNCTION(BlueprintCallable, Category="OverlayTrackerSubsystem")
	void UnHoverObject(const FString& InUid);

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;


};