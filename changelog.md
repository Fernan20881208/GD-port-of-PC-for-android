# v0.2.2

- El FPS objetivo ahora funciona como limite maximo estricto y no solo como una solicitud al loop de Android.
- Nuevo frame pacer monotónico en `CCDirector::drawScene` que impide renderizar antes del siguiente intervalo permitido.
- Reinicio seguro de la cadencia al cambiar el objetivo, desactivar Unlock FPS, activar VSync o volver de una pausa.
- Se conserva la separación entre render y tiempo real de gameplay introducida en v0.2.1.

# v0.2.1

- Corregido Unlock FPS para que aumentar los FPS no acelere la velocidad del juego.
- El render de Android puede seguir usando 120 / 144 / 240 / 360 FPS.
- La simulación de Geometry Dash usa `CCDirector::getActualDeltaTime()` como tiempo real independiente del intervalo de render.
- Protección contra deltas inválidos o picos grandes al reanudar la aplicación.

# v0.2.0

- Nuevo menú de gráficos estilo PC dentro de los ajustes del mod.
- Fullscreen Android documentado como modo nativo; Borderless y Windowed se marcan como no equivalentes en Android.
- Texture Quality: Auto / Low / Medium / High usando el escalado de contenido de Geometry Dash.
- Vertical Sync con intento real de control mediante `eglSwapInterval`.
- Smooth Fix durante juego y editor.
- Show FPS y frametime.
- Unlock FPS con objetivo personalizado de 30 a 360 FPS; VSync tiene prioridad cuando está activo.
- Estado gráfico visible desde el panel PC Experience.

# v0.1.0

- Panel PC Experience en el menú principal.
- Diagnóstico de teclado, ratón/táctil y rueda.
- Integración opcional con Custom Keybinds.
- Controles táctiles adaptativos y modo PC estricto.
- HUD opcional de FPS y frametime en juego/editor.
- Workflow reproducible para Android64.
