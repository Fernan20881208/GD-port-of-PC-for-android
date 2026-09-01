# PC-FPS-MOD

[![Build Android64 + iOS](https://github.com/Fernan20881208/PC-FPS-MOD/actions/workflows/build.yml/badge.svg)](https://github.com/Fernan20881208/PC-FPS-MOD/actions/workflows/build.yml)
[![GitHub Sponsors](https://img.shields.io/badge/GitHub-Sponsors-ea4aaa?logo=githubsponsors)](https://github.com/sponsors/Fernan20881208)
[![Ko-fi](https://img.shields.io/badge/Ko--fi-Apoyar-ff5e5b?logo=kofi&logoColor=white)](https://ko-fi.com/zaidnavarrosaucedo)

Mod de **Geode para Geometry Dash 2.2081** que acerca los controles y opciones gráficas de PC a Android e iOS, con control estricto de FPS sin acelerar la física del juego.

## Funciones actuales

- Menú gráfico inspirado en la versión de PC.
- Texture Quality: Auto, Low, Medium y High.
- VSync mediante EGL en Android y manejo compatible con CADisplayLink en iOS.
- Unlock FPS y límite personalizado de 30 a 360 FPS.
- Frame pacer monotónico para que el valor elegido sea un límite máximo real.
- Separación entre render y tiempo de juego para conservar la velocidad normal.
- Smooth Fix, contador de FPS y frametime.
- Soporte de teclado, ratón, rueda y controles táctiles adaptativos en Android.
- Interfaz y HUD de rendimiento compatibles con Android64 e iOS arm64.

## Builds

Cada ejecución correcta de GitHub Actions publica:

| Artefacto | Plataforma | Contenido |
|---|---|---|
| `PC-FPS-MOD-Android64` | Android ARM64-v8a | `.geode` con binario Android64 |
| `PC-FPS-MOD-iOS-arm64` | iPhone/iPad arm64 | `.geode` con binario iOS |
| `PC-FPS-MOD-Android64-iOS` | Universal | Un solo `.geode` con ambos binarios |

La build de iOS es un **mod `.geode`**, no una IPA ni una copia de Geometry Dash. Requiere una instalación de Geode compatible en iOS.

## Requisitos

- Copia oficial de Geometry Dash 2.2081 para la plataforma correspondiente.
- Geode 5.10.1 o una versión posterior compatible.
- `geode.node-ids` v1.23.3 o posterior.

## Instalación

1. Abre la última ejecución correcta de **Build PC-FPS-MOD**.
2. Descarga el artefacto de tu plataforma o el paquete universal.
3. Extrae el ZIP del artefacto y selecciona el archivo `.geode` desde Geode.
4. Reinicia Geometry Dash si Geode lo solicita.

## Compilación local

```sh
git clone https://github.com/Fernan20881208/PC-FPS-MOD.git
cd PC-FPS-MOD
export GEODE_SDK=/ruta/al/geode
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Para Android e iOS se recomienda el workflow incluido: configura el entorno correcto para Android NDK o Xcode y después combina ambos paquetes.

## Créditos y autoría

Este repositorio adapta y continúa trabajo previo; no se afirma que todo el concepto o código original pertenezca al mantenedor actual. Los cambios de esta versión, la adaptación móvil y el mantenimiento están publicados por **Fernan20881208**.

- Instagram: [@Zaid.nvr](https://www.instagram.com/zaid.nvr/)
- GitHub Sponsors: [Fernan20881208](https://github.com/sponsors/Fernan20881208)
- Ko-fi: [zaidnavarrosaucedo](https://ko-fi.com/zaidnavarrosaucedo)

Geometry Dash pertenece a RobTop Games. Geode y las dependencias usadas pertenecen a sus respectivos autores. El repositorio no incluye APK, IPA, EXE, bibliotecas, música, texturas ni otros recursos originales del juego.

## Soporte

Consulta [support.md](support.md) para enviar un reporte útil y [changelog.md](changelog.md) para revisar los cambios de cada versión.
