# OverlayTracker ‑ Unreal Engine 5 Plugin

**Author:** Wellsaik  
**Engine Version:** 5.6+ (backward-compatible with 5.0+)  
**License:** MIT (feel free to change)

## What it does

`OverlayTracker` lets you pin **2-D UI widgets** to **3-D world locations** without touching engine internals.  
Perfect for nameplates, health bars, quest markers, enemy tags, etc.

---

## Quick Start

### 1. Install

#### Via Git submodule (recommended)

```bash
cd YourProject
git submodule add https://github.com/Wellsaik/OverlayTracker Plugins/OverlayTracker
```

#### Via ZIP download
1. Download the repo as ZIP.
2. Extract to YourProject/Plugins/OverlayTracker.

### 2. Enable in .uproject
Open YourProject.uproject and add:
```json
"Plugins": [
  {
    "Name": "OverlayTracker",
    "Enabled": true
  }
]
```
Regenerate project files and compile.

## Classes at a Glance

| Class | Purpose |
|-------| -------- |
| UOverlayTrackerSubsystem        |	Global manager that keeps track of every 3-D → 2-D object.
| UOverlayTrackerCanvasWidget     |	Blueprint-ready widget that actually draws the 2-D overlays.
| UOverlayTrackerObject           | Data/logic provider for a single overlay (you subclass this).

## Typical Setup
1. **Create your own Canvas Widget**
  - Make a new UserWidget derived from UOverlayTrackerCanvasWidget.
  - Design the layout in UMG (optional: create BindWidget UCanvasPanel* MainCanvas).
2. **Spawn & register the widget**
    Do this once, e.g. in your AHUD subclass or somewhere safe:
    ```cpp
    void AMyHUD::BeginPlay()
    {
        Super::BeginPlay();
    
        MyOverlayCanvas = CreateWidget<UOverlayTrackerCanvasWidget>(GetOwningPlayerController(), MyCanvasWidgetClass);
        MyOverlayCanvas->AddToViewport();
    
        // Register with the subsystem
        GetWorld()->GetSubsystem<UOverlayTrackerSubsystem>()->CacheCanvasWidget(MyOverlayCanvas);
    }
    ```
3. **Create your Tracker Object**
   Create a Blueprint subclass of UOverlayTrackerObject and implement the required overrides:
   | Override |	Description |
   | ----------- |	----------- | 
   |CreateTrackerWidget()|	Return the actual UMG widget that appears on screen. Save it into CachedWidget.
   | GetObjectWorldLocation()|	Return the live 3-D world location to project.
   |ShouldBeVisible(float Distance)|	Return false to hide (e.g. too far, dead, etc.).
   |GetSize(float Distance)|	Return desired screen size in pixels (allows distance scaling).
   |GetDistanceToCam()|	Return distance in cm; override if default trace isn’t enough.

Example minimal C++ override:
```cpp
UUserWidget* UMyTrackerObj::CreateTrackerWidget_Implementation(APlayerController* InOwner)
{
    CachedWidget = CreateWidget<UUserWidget>(InOwner, MyWidgetClass);
    return CachedWidget;
}

FVector UMyTrackerObj::GetObjectWorldLocation_Implementation()
{
    return TrackedActor ? TrackedActor->GetActorLocation() : FVector::ZeroVector;
}
```

4. **Add / Remove objects at runtime**
   ```cpp
    auto Subsystem = GetWorld()->GetSubsystem<UOverlayTrackerSubsystem>();
    
    // Show
    Subsystem->AddObject("Enemy_42", NewObject<UMyTrackerObj>(...));
    
    // Hide
    Subsystem->RemoveObject("Enemy_42");
   ```cpp

## Support
Open an issue on GitHub
