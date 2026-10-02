# cub3D - Proyecto de 42 School

Un motor de juego 3D con raycasting en C usando minilibx, inspirado en Wolfenstein 3D.

## Descripción General

Este proyecto implementa un renderizador 3D básico usando técnicas de raycasting. Lee un archivo de mapa, muestra una vista en primera persona de un entorno tipo laberinto y permite al jugador moverse usando controles de teclado. Forma parte del plan de estudios de 42 school y demuestra la comprensión de programación gráfica, matemáticas (algoritmo de raycasting) y manejo de eventos.

## Características

### Renderizado 3D
- Algoritmo de raycasting para perspectiva 3D
- Muros texturizados (4 texturas diferentes para cada dirección)
- Colores de suelo y techo configurables
- Movimiento y rotación suaves

### Controles del Jugador
- `W` - Mover adelante
- `A` - Mover atrás
- `S` - Desplazamiento lateral izquierdo
- `D` - Desplazamiento lateral derecho
- `←` - Rotar cámara a la izquierda
- `→` - Rotar cámara a la derecha
- `ESC` - Salir del juego
- Botón cerrar (X) - Salir del juego

### Análisis de Mapas
- Análisis de archivos de configuración (extensión .cub)
- Configuración de rutas de texturas
- Configuración de colores de suelo y techo (RGB)
- Validación de mapas (bordes cerrados, caracteres válidos, spawn del jugador)

## Estructura del Proyecto

```
cub3d/
├── src/                        # Archivos fuente
│   ├── main.c                 # Punto de entrada e inicialización
│   ├── map_reader.c           # Lectura de archivos de mapa
│   ├── map_validate.c         # Validación de mapas
│   ├── map_textures.c         # Carga de texturas
│   ├── map_utils.c            # Utilidades de mapa
│   ├── map_complete.c         # Completado/relleno de mapa
│   ├── exit.c                 # Limpieza y manejo de salida
│   └── draw_and_render/       # Subsistema de renderizado
│       ├── raycasting.c       # Algoritmo de raycasting
│       ├── rendering.c        # Bucle principal de renderizado
│       ├── draw.c             # Primitivas de dibujo
│       ├── player.c           # Movimiento del jugador y entrada
│       └── utils.c            # Utilidades de renderizado
├── inc/                        # Archivos de cabecera
│   └── cub3d.h                # Declaraciones principales
├── maps/                       # Archivos de mapa
│   ├── example.cub            # Mapa de ejemplo
│   ├── basic.cub              # Mapa de prueba básico
│   └── error*.cub             # Casos de prueba de errores
├── textures/                   # Archivos de texturas
│   ├── wall1.xpm              # Texturas de muros
│   ├── floor.xpm              # Textura de suelo
│   └── ...
├── obj/                        # Objetos compilados (generados)
├── .deps/                      # Dependencias (generadas)
├── Makefile                   # Configuración de compilación
└── cub3D                      # Ejecutable (generado)
```

## Dependencias

Este proyecto depende de:
- [libraryC](https://github.com/Davter17/MyLibrary.git) - Librería personalizada con libft, ft_printf y get_next_line
- [minilibx-linux](https://github.com/42Paris/minilibx-linux.git) - Librería gráfica simple

Ambas se clonan automáticamente durante la compilación.

## Compilación

### Compilación básica
```bash
make
```
Clona dependencias (si es necesario) y compila el juego.

### Compilación limpia
```bash
make re
```
Elimina todos los archivos compilados y recompila todo.

### Limpieza
```bash
make clean    # Elimina el directorio obj/
make fclean   # Elimina obj/, .deps/ y el binario cub3D
```

## Uso

```bash
./cub3D <archivo_mapa.cub>
```

### Formato del Archivo de Mapa

Los archivos de mapa deben tener la extensión `.cub` y contener:

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 100,150,180

1111111111
1000000001
1P00000001
1000000001
1111111111
```

#### Líneas de Configuración
- `NO` - Ruta de textura del muro norte
- `SO` - Ruta de textura del muro sur
- `WE` - Ruta de textura del muro oeste
- `EA` - Ruta de textura del muro este
- `F` - Color del suelo (formato RGB: R,G,B)
- `C` - Color del techo (formato RGB: R,G,B)

#### Caracteres del Mapa
- `1` - Muro
- `0` - Espacio vacío
- `N` - Spawn del jugador (mirando al Norte)
- `S` - Spawn del jugador (mirando al Sur)
- `W` - Spawn del jugador (mirando al Oeste)
- `E` - Spawn del jugador (mirando al Este)
- ` ` - Espacio vacío (fuera del mapa)

## Detalles de Implementación

### Algoritmo de Raycasting
- Algoritmo DDA (Digital Differential Analysis) para intersección rayo-muro
- Un rayo por columna vertical de la pantalla
- Corrección de perspectiva para alturas de muros
- Mapeo de texturas basado en posición de impacto

### Análisis de Mapas
- Análisis de cabecera para texturas y colores
- Validación de mapas (bordes cerrados, spawn único de jugador)
- Relleno de mapa para dimensiones consistentes
- Validación de espacios (deben estar rodeados por muros o espacios)

### Gestión de Memoria
- Asignación y liberación cuidadosa
- Sin fugas de memoria (verificado con Valgrind)
- Limpieza adecuada en errores y al salir
- Destrucción segura de imágenes y ventanas

## Calidad del Código

- Cumple con los estándares de norminette de 42 school
- Sin fugas de memoria (verificado con Valgrind)
- Maneja casos extremos y condiciones de error
- Separación limpia de responsabilidades
- Gestión adecuada de recursos

## Requisitos

- Compilador GCC
- Make
- Librerías de desarrollo X11 (`libx11-dev`, `libxext-dev`)
- Entorno tipo Unix (Linux, macOS o WSL)

## Autores

- **Mario Pico** (@Davter17)
- **Marta Cuesta** (@mcuesta-)

## Licencia

Este proyecto forma parte del plan de estudios de 42 school y sigue sus directrices académicas.
