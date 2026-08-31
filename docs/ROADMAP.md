# Hoja de ruta

## Fase 1 — Base e entrada

- [x] Auditar binarios Android y PC sin redistribuirlos.
- [x] Confirmar objetivo GD 2.2081 y Android ARM64.
- [x] Reutilizar el puente oficial de teclado, clic y rueda de Geode.
- [x] Integrar Custom Keybinds para juego y editor.
- [x] Añadir diagnóstico de periféricos y HUD de rendimiento.
- [x] Ocultar/mostrar controles táctiles según el dispositivo usado.

## Fase 2 — Interfaz de PC con equivalentes Android

- [ ] Recrear `VideoOptionsLayer` para Android.
- [ ] Página de pantalla: fullscreen, zoom, relación de aspecto y frecuencia disponible.
- [ ] Página de rendimiento: límite de FPS del launcher, perfil equilibrado y perfil de baja latencia.
- [ ] Explicar claramente opciones Win32 que no tienen equivalente.
- [ ] Añadir indicadores de reinicio requerido.

## Fase 3 — Ratón completo

- [ ] Recibir movimiento/hover del puntero sin convertirlo en toque.
- [ ] Cursor visual consistente en menús y editor.
- [ ] Botón derecho, central y botones laterales.
- [ ] Arrastre y selección del editor con semántica de escritorio.
- [ ] Captura relativa opcional para movimientos continuos.

Esta fase puede requerir un cambio coordinado en el launcher Android de Geode. El mod nativo por sí solo no puede recibir eventos que la vista Java/Kotlin nunca envía.

## Fase 4 — Paridad y estabilidad

- [ ] Matriz de pruebas con Android 10-16 y varios fabricantes.
- [ ] Validar teclado USB, Bluetooth, docks y ratones con rueda horizontal.
- [ ] Medir latencia y estabilidad térmica sin cambiar la velocidad de la física.
- [ ] Compatibilidad Android32 si existe una biblioteca oficial del juego para esa ABI.
- [ ] Releases firmadas y guía de diagnóstico.

## Definición de “paridad”

La meta es reproducir el **resultado útil** de PC. No se copiarán APIs exclusivas de Windows cuando Android ya tenga un mecanismo distinto. Por ejemplo, “resolución de ventana” se traduce a zoom/área visible, mientras que la frecuencia y el límite de FPS se coordinan con el launcher.

