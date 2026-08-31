# GD PC Experience for Android

Mod de **Geode para Geometry Dash 2.2081 en Android ARM64** que acerca la experiencia de PC a Android sin intentar ejecutar el binario de Windows.

> Estado: **v0.1.0 / base funcional**. No es todavía una copia exacta de todas las funciones del `.exe`.

## Qué incluye ahora

- Panel **PC Experience** en el menú principal.
- Diagnóstico en vivo de teclado físico, ratón/táctil y rueda.
- Atajos completos de juego y editor mediante la dependencia oficial **Custom Keybinds**.
- Ocultado adaptativo de controles táctiles al detectar teclado, ratón o mando.
- Recuperación automática de los controles al volver a tocar la pantalla.
- HUD opcional de FPS reales y tiempo por fotograma durante juego y editor.
- Compilación reproducible para Android64 con GitHub Actions.

## Compatibilidad real

| Función de PC | Estado en Android | Implementación |
|---|---:|---|
| Teclado, modificadores, F1-F12 y numpad | Lista | Puente de entrada de Geode + Custom Keybinds |
| Clic principal y rueda | Lista | Eventos Android del launcher de Geode |
| Atajos del editor | Lista | Custom Keybinds |
| Interfaz sin botones táctiles | Lista | Modo adaptativo/estricto del mod |
| Contador FPS y frametime | Lista | HUD nativo del mod |
| Hover y posición continua del cursor | Pendiente | Requiere ampliar el puente de eventos del launcher |
| Captura relativa/bloqueo del cursor | Pendiente | Requiere soporte del launcher Android |
| Menú avanzado de vídeo estilo PC | Parcial | Se crearán equivalentes Android; no se copiarán llamadas Win32 |
| Ventana, borde y resolución de escritorio | No aplica | Android usa fullscreen, zoom y frecuencia de la pantalla |

## Requisitos

- Copia oficial de Geometry Dash para Android, versión **2.2081**.
- Geode **5.10.1 o posterior compatible**.
- Dispositivo **ARM64-v8a** para la versión actualmente validada.
- `geode.custom-keybinds` v2.2.2+ y `geode.node-ids` v1.23.3+; Geode pedirá instalarlos.

## Instalar

1. Descarga el artefacto `.geode` de la última ejecución correcta de **Build Android64**.
2. Abre Geode en Android e instala el archivo desde el selector de mods.
3. Reinicia Geometry Dash si Geode lo solicita.
4. Abre el botón de engranaje añadido al menú inferior para probar periféricos y ajustar el modo PC.

## Compilar

```sh
git clone https://github.com/Fernan20881208/GD-port-of-PC-for-android.git
cd GD-port-of-PC-for-android
export GEODE_SDK=/ruta/al/geode
cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build --config RelWithDebInfo
```

Para Android normalmente es más sencillo usar el workflow incluido, que configura NDK y SDK automáticamente.

## Arquitectura

Este proyecto usa el juego Android oficial como base. El `.exe` x86-64 de PC sirve únicamente como referencia de comportamiento e interfaz; no puede cargarse dentro del proceso ARM64 de Android. Las funciones se reconstruyen con hooks de Geode y equivalentes nativos de Android.

## Propiedad intelectual

El repositorio **no contiene** el juego, ejecutables, bibliotecas, texturas, música ni otros recursos de Geometry Dash. No subas `GeometryDash.exe`, APK, DLL, SO, ZIP/7z del juego ni su carpeta `Resources`.

Geometry Dash pertenece a RobTop Games. Geode y Custom Keybinds pertenecen a sus respectivos autores.

## Siguiente etapa

Consulta [docs/ROADMAP.md](docs/ROADMAP.md) y [docs/COMPATIBILITY.md](docs/COMPATIBILITY.md). Los reportes útiles deben incluir modelo del dispositivo, versión de Android, versión de Geode y tipo de teclado/ratón.

