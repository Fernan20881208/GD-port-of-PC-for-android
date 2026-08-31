# Compatibilidad técnica

## Base auditada

| Componente aportado para análisis | Resultado |
|---|---|
| Android `libcocos2dcpp.so` | ELF ARM64, símbolos de teclado y ratón disponibles |
| Android `libfmod.so` | ELF ARM64 |
| `GeometryDash.exe` | PE x86-64; sólo referencia de comportamiento |
| Geode de PC observado | 5.9.0 |
| Objetivo actual del SDK | Geometry Dash 2.2081 / Geode 5.10.1 |

Las copias analizadas no forman parte del repositorio ni del paquete `.geode`.

## Entrada

El launcher Android moderno de Geode ya traduce:

- `KeyEvent` de Android a `CCKeyboardDispatcher`.
- Teclas presionadas y soltadas, repetición y modificadores.
- Flechas, letras, números, numpad y F1-F12.
- Scroll horizontal/vertical a `CCMouseDispatcher`.
- Toque y clic de ratón a eventos táctiles de Cocos2d.
- Mandos y ejes analógicos.

Custom Keybinds convierte esas entradas en acciones equivalentes a PC dentro del juego y editor. Este mod no vuelve a inyectar las mismas teclas, evitando dobles pulsaciones.

## Límite actual del ratón

El launcher entrega clic y rueda, pero la ruta revisada no expone de forma completa `ACTION_HOVER_MOVE` ni captura relativa a mods nativos. Por eso el hover, el cursor continuo y el bloqueo del puntero están en la fase 3.

## Rendimiento

En Android, `CCApplication::setAnimationInterval` no controla de forma fiable el render de Geometry Dash. La frecuencia física de la pantalla y el limitador pertenecen al launcher. Esta versión sólo mide FPS/frametime y evita parches que puedan acelerar o ralentizar la física. La fase 2 integrará los controles compatibles del launcher.

