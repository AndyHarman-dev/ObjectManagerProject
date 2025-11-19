# Interactive Object Manager

An Unreal Engine project for managing interactive objects with selection, movement, spawning, and UI utilities.

## Modules

### GameSettings
Contains default game configuration and parameters.

### InteractiveObject
Core interaction system providing:
- Object selection and detection
- Object movement (transform-based)
- Dynamic object spawning
- Component-based extensible behaviors

### ObjectManagerProject
Main business logic module that orchestrates game systems and coordinates between modules.

### UIUtilities
UI components and tools including:
- Unreal Color Picker widget

## Getting Started

### Prerequisites
- Unreal Engine
- Visual Studio or compatible IDE

### Installation
1. Clone the repository
2. Open project in Unreal Engine
3. Compile modules
4. Launch editor

## Architecture

```
GameSettings <- ObjectManagerProject -> InteractiveObject
                      ↓
                 UIUtilities
```
