// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "OverlayTrackerObject.generated.h"

class UOverlayTrackerCanvasWidget;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(ShowWorldContextPin=true))
class OVERLAYTRACKER_API UOverlayTrackerObject : public UObject
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(Transient, BlueprintReadWrite)
	UUserWidget* CachedWidget;

	UPROPERTY(Transient, BlueprintReadWrite)
	FString CachedUID;
public:

	UFUNCTION(BlueprintCallable)
	void SetUID(const FString& InUid);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasWidget() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	bool ShouldBeVisible(float DistanceToCam) const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	UUserWidget* CreateTrackerWidget(APlayerController* InOwner);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="OverlayTrackerObject")
	UUserWidget* GetCachedWidget() const { return CachedWidget; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	FVector GetObjectWorldLocation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	FVector2D GetSize(float Distance);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="OverlayTrackerObject")
	FString GetUID() const { return CachedUID; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void Clear();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	float GetDistanceToCam() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifySelected();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyUnSelected();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyHovered();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTrackerObject")
	void NotifyUnHovered();
};