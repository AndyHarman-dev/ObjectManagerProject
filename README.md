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
The code is organized into four modules, each encapsulating distinct behaviors that can function independently rather than being embedded within a single module.

**ObjectManagerProjectModule** (Top-Level)
This is the highest-level module, designed to manage objects and handle user interactions. In this solution, it is responsible for:
- Processing input through the player controller
- Performing traces to detect objects in the world
- Managing object selection and detection logic

**InteractiveObjectModule** (Implementation Layer)
This lower-level implementation module contains three key classes that enable selection and movement functionality:
- `AInteractiveSceneObject`
- `UInteractiveObjectSelectionComponent`
- `UInteractiveObjectMovementComponent`

The components in this module are highly reusable. Importantly, they don't require implementation specifically with `AInteractiveSceneObject`—this class simply provides a ready-to-use implementation for interactive objects. These components can be attached to any actor to enable selection and movement capabilities.

**UIUtilitiesModule** (Utility Layer)
This smaller module currently exists to store a UMG wrapper for `SColorPicker`, but it can be extended to house additional UI utilities in the future.

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

## Known Limitations & Future Improvements

- ViewModels made in blueprints cannot call static functions, making the global access of singletons difficult.
- To maintain the list of objects spawned in the worlds, we have to spawn them through `InteractiveObjectSpawnSubsystem`, which limits us only to the use of the subsystem.

As for improvements:
- Instead of direct initialization of objects that can't call static functions with singletons, we could use a DI container pattern and initialize objects with the container where each could get a necessary service using an abstraction rather than a direct reference.
- Selection and movement components could be separated into different modules because movement logic can get pretty complex, requiring more boilerplate and utility classes.
- Player Controller ended up being an inflated object. It handles more than one responsibility. It could be separated into several composed objects for handling trace and selection logic.
