# Code

The majority of the code is located in /vendor/GameEngine.

In /src there is application-specific code that wouldn't necessarily fit into the engine.

## Build

The application is built in the /build folder.

## Dependencies

The /res folder should be located in the same directory as the executable, and the DLLs should be in the /dependencies folder (this should happen automatically).

## Resources

All resources such as shaders and textures can be found under /res.

## Third Party Code

Except for the GameEngine folder, everything under /vendor is third party code and was not written by me. Each folder has a license file or something similar.

# Application

## Controls

| Key    | Action             |
|--------|--------------------|
| WASD   | Move               |
| LShift | Sprint             |
| Space  | Jump               |
| Mouse  | Look around        |
| F      | Fullscreen toggle  |
| Escape | Debug menu toggle  |
| P      | Physics debug view |

## GUI

As described in the Controls section, pressing Escape opens a GUI with various functions.

### Material Properties

Most material values can be changed except for internal values such as matrices.

### Scene Hierarchy

All GameObjects are in a Scene Hierarchy similar to Unity, where you can also see which components are attached and change their values.

### Miscellaneous

Some tabs are empty because there are no exposed values.

To change the Directional Light position, you can adjust the X/Y Rotation value of the Directional Lights GameObject (similar to Unity).

The Root Transform can also be adjusted, but it breaks things pretty badly...

# Credits

## Third Party Resources

Everything not listed here was created by myself.

| Resource                                      | Source                                                                                    |
|-----------------------------------------------|-------------------------------------------------------------------------------------------|
| /res/fonts/Roboto-Regular                     | https://fonts.google.com/specimen/Roboto                                                  |
| /res/models/Suzanne.gltf                      | https://www.blender.org                                                                   |
| /res/textures/Skybox                          | https://assetstore.unity.com/packages/2d/textures-materials/sky/fantasy-skybox-free-18353 |
| /res/textures/(Crate.png, CrateNormalMap.png) | SAE                                                                                       |
| /res/texture/(Dirt.png, Sand.png, Grass.png)  | https://seamless-pixels.blogspot.com (Yes, I purchased them)                               |
| /res/audio/BackgroundMusic.mp3                | Pax Votum (a colleague of mine, also makes music for my projects)                          |

## Tutorials Used

- https://learnopengl.com
- https://www.youtube.com/@ThinMatrix
- https://www.youtube.com/@OGLDEV
- https://www.youtube.com/@VictorGordan
- https://www.youtube.com/@TheCherno
