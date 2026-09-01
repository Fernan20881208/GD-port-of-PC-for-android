# v0.3.0

- Nombre público actualizado a **PC-FPS-MOD** sin cambiar el ID interno, para conservar la actualización de instalaciones existentes.
- Compatibilidad declarada con Geometry Dash 2.2081 en Android e iOS.
- Código Android específico aislado para permitir compilación iOS arm64.
- Nuevo workflow con builds independientes Android64 e iOS y paquete `.geode` universal combinado.
- GitHub Sponsors y Ko-fi añadidos a la configuración de financiación y al README.

# v0.2.2

- El FPS objetivo ahora funciona como limite maximo estricto y no solo como una solicitud al loop de Android.
- Nuevo frame pacer monotónico en `CCDirector::drawScene` que impide renderizar antes del siguiente intervalo permitido.
- Reinicio seguro de la cadencia al cambiar el objetivo, desactivar Unlock FPS, activar VSync o volver de una pausa.
- Se conserva la separación entre render y tiempo real de gameplay introducida en v0.2.1.

# v0.2.1

- Corregido Unlock FPS para que aumentar los FPS no acelere la velocidad del juego.
- El render puede seguir usando 120 / 144 / 240 / 360 FPS.
- La simulación de Geometry Dash usa `CCDirector::getActualDeltaTime()` como tiempo real independiente del intervalo de render.
- Protección contra deltas inválidos o picos grandes al reanudar la aplicación.

# v0.2.0

- Nuevo menú de gráficos estilo PC dentro de los ajustes del mod.
- Texture Quality: Auto / Low / Medium / High.
- Vertical Sync con intento real de control mediante `eglSwapInterval` en Android.
- Smooth Fix durante juego y editor.
- Show FPS y frametime.
- Unlock FPS con objetivo personalizado de 30 a 360 FPS.

# v0.1.0

- Panel PC Experience en el menú principal.
- Diagnóstico de teclado, ratón/táctil y rueda.
- Controles táctiles adaptativos y modo PC estricto.
- HUD opcional de FPS y frametime en juego/editor.
- Workflow reproducible para Android64.
