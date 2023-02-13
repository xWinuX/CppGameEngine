# Struktur

### Code

Der grösste Teil des Codes ist unter /vendor/GameEngine.

In /src befindet sich dann noch applikationsspezifischer Code der nicht unbedingt in die Engine gepasst hätte

### Build
Die Applikation wird unter dem /build Ordner gebuilded

### Dependencies
Im Ordner mit der Exe sollte sich der /res Ordner befinden und die DLL's im /dependencies Ordner (Dies sollte automatisch geschehen)

### Resourcen
Die ganzen Resourcen wie Shader und Texturen können unter /res gefunden werden.

### Third Party Code
Ausser dem GameEngine Ordner ist alles unter /vendor Third Party Code und wurde nicht von mir geschrieben.
Bei jedem Ordner hat es ein License file oder ähnliches.

# Applikation

### Steuerung

| Key    | Action             |
|--------|--------------------|
| WASD   | Bewegen            |
| LShift | Sprinten           |
| Space  | Springen           |
| Mouse  | Herum Schauen      |
| F      | Fullscreen Toggle  |
| Escape | Debug Menu Toggle  |
| P      | Physics Debug View |

# Credits

### Third Party Resourcen

Alles was hier nicht aufgelistet ist wurde selbst erstellt.

| Resource                                      | Source                                                                                    |
|-----------------------------------------------|-------------------------------------------------------------------------------------------|
| /res/fonts/Roboto-Regular                     | https://fonts.google.com/specimen/Roboto                                                  |
| /res/models/Suzanne.gltf                      | https://www.blender.org                                                                   |
| /res/textures/Skybox                          | https://assetstore.unity.com/packages/2d/textures-materials/sky/fantasy-skybox-free-18353 |
| /res/textures/(Crate.png, CrateNormalMap.png) | SAE                                                                                       |
| /res/texture/(Dirt.png, Sand.png, Grass.png)  | https://seamless-pixels.blogspot.com (Ja ich habe sie gekauft)                            |


### Tutorials used

- https://learnopengl.com
- https://www.youtube.com/@ThinMatrix/playlists
- https://www.youtube.com/@OGLDEV
- https://www.youtube.com/@VictorGordan/videos
- https://www.youtube.com/@TheCherno
