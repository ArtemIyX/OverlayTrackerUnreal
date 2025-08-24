// Developed by Wellsaik

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "OverlayTrackerCanvasWidget.generated.h"

class UOverlayTrackerSubsystem;
class UOverlayTrackerObject;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class OVERLAYTRACKER_API UOverlayTrackerCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UOverlayTrackerCanvasWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(Transient)
	TObjectPtr<UOverlayTrackerSubsystem> OverlayTrackerSubsystem;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="OverlayTracker")
	void GetCameraLocRot(FVector& OutLoc, FRotator& OutRot) const;

public:
	UPROPERTY(meta=(BindWidget), EditAnywhere, BlueprintReadWrite)
	UCanvasPanel* MainCanvas;

	UFUNCTION(BlueprintCallable)
	bool ProjectToScreen(UOverlayTrackerObject* InTrackerObject, FVector2D& OutScreenPos);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddItem(const FString& InUid, UOverlayTrackerObject* InItem);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveItemByObject(UUserWidget* InItem);
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePosition(const FString& InUid, UOverlayTrackerObject* InTrackerObject, const FVector2D& InScreePos);
};