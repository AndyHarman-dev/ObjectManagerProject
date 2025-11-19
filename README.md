# Interactive Object Manager

An Unreal Engine project for managing interactive objects with selection, movement, spawning, and UI utilities.

## Getting Started

### Prerequisites
- Unreal Engine
- Visual Studio or compatible IDE

### Installation
1. Clone the repository
2. Open project in Unreal Engine
3. Compile modules
4. Launch editor

## Architecture Overview

### Module: GameSettings

**Purpose:** Manages persistent data storage through INI file serialization.

#### Components

- **`UObjectManagerSettings`**
  - Service that provides direct methods for loading and saving data to .ini configuration files


### Module: InteractiveObject

**Purpose:** Implements the core interaction system for object manipulation within the scene.

#### Features
- Object selection and detection
- Transform-based object movement (activated by click-and-hold gesture)
- Runtime object spawning capabilities

#### Components

- **`UInteractiveObjectSelectionComponent`** - Manages the selection state and detection of interactive objects

- **`UInteractiveObjectMovementComponent`** - Controls object movement with configurable interpolation speed settings

- **`UInteractiveObjectSpawnSubsystem`** - Handles dynamic instantiation of interactive objects and broadcasts spawn-related events

- **`AInteractiveSceneObject`** - Main interactive object actor that integrates the selection and movement components


### Module: ObjectManagerProject

**Purpose:** Contains the primary business logic layer that orchestrates game systems and coordinates inter-module communication.

#### Components

- **`AObjectManagementPlayerController`**
  - Processes input and handles raycasting operations on click events
  - Implements camera look-at functionality for enhanced user experience
  - Coordinates object selection through component delegation


### Module: UIUtilities

**Purpose:** Provides reusable UI utility components and widgets.

#### Components

- **UMG Color Picker Wrapper**
  - UMG-based wrapper implementation around Unreal Engine's native `SColorPicker` slate widget

## UI Overview

The user interface is organized into several distinct components, each serving a specific function within the application.

### Main Viewport

The main viewport provides the primary view of the scene and contains all interactive UI elements. The complete interface layout is shown below:

<img width="826" height="424" alt="image" src="https://github.com/user-attachments/assets/ad3fb683-c25e-4618-9e27-3fc112c47614" />

### Outliner Panel

The Outliner displays a list of all interactive objects currently present in the scene. Selecting an object from this list will center the camera on that object.

<img width="232" height="111" alt="image" src="https://github.com/user-attachments/assets/b59063f8-f83d-40ca-84ae-971cd9315a41" />

### Details Panel

The Details panel allows you to modify properties of the currently selected object, including color and scale. This panel is only visible when an object is actively selected.

<img width="718" height="403" alt="image" src="https://github.com/user-attachments/assets/aea16e2e-7362-4d85-aea3-631b2af26764" />

### Spawn/Removal Panel

Located in the bottom-left corner, this panel contains controls for adding and removing objects from the scene.

<img width="381" height="152" alt="image" src="https://github.com/user-attachments/assets/6dc6f6ec-5ccb-4e4a-94ba-65615932b549" />

When spawning a new object, you can select the desired object type. If no type is selected, the system uses the default type specified in Settings.

<img width="425" height="179" alt="image" src="https://github.com/user-attachments/assets/add25bc5-45f2-45de-a15e-bdf7c8b65315" />

### Settings Menu

Access the Settings menu by clicking the button located in the top-left corner of the viewport. This opens the settings configuration screen:

<img width="823" height="400" alt="image" src="https://github.com/user-attachments/assets/f972b0ef-f00f-416d-a777-095e2fe9519a" />

The Settings menu allows you to configure default values for newly spawned objects. These values are automatically saved to configuration files and persist across sessions.

<img width="302" height="197" alt="image" src="https://github.com/user-attachments/assets/3185016f-8a33-475c-a828-5cd8147e90a6" />




## Architecture

```
GameSettings <- ObjectManagerProject -> InteractiveObject
                      ↓
                 UIUtilities
```
