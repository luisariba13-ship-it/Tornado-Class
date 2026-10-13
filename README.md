
# Compilador Simple

Proyecto enfocado en el desarrollo de un compilador para el lenguaje **Simple**, utilizando programación en C y estructuras de datos básicas.

El proyecto se desarrolla de manera progresiva, incorporando nuevas funcionalidades y modificaciones.

---

## Descripción

El compilador Simple es un programa desarrollado en lenguaje C que permite leer instrucciones desde un archivo de texto, identificar comandos y generar instrucciones en lenguaje máquina SML.

El compilador utiliza una memoria de **100 posiciones**, una tabla de símbolos y diferentes funciones para procesar las instrucciones.

Entre sus principales funcionalidades se encuentran:

- Lectura de archivos de texto.
- Identificación de instrucciones.
- Manejo de variables y constantes.
- Construcción de una tabla de símbolos.
- Asignación de posiciones de memoria.
- Generación de instrucciones SML.
- Identificación de saltos pendientes.
- Generación automática de archivos.

---

## Primera pasada

La primera pasada consiste en leer las instrucciones del archivo `programa.simple` y generar las instrucciones SML correspondientes.

Durante este proceso se identifican los números de línea, variables y constantes, almacenando su información en una tabla de símbolos.

Entre sus principales funciones se encuentran:

- Lectura de instrucciones mediante `fgets()`.
- Separación de cadenas mediante `strtok()`.
- Identificación de comandos mediante `strcmp()`.
- Registro de símbolos utilizando `struct`.
- Búsqueda de variables y constantes.
- Asignación de ubicaciones en memoria.
- Almacenamiento de instrucciones en arreglos.
- Registro de saltos pendientes mediante `flags`.
- Escritura de instrucciones en un archivo SML.

---

## Segunda pasada

La segunda pasada consiste en revisar las instrucciones generadas durante la primera pasada para completar las referencias pendientes.

Entre sus principales funciones se encuentran:

- Recorrido del arreglo `flags`.
- Identificación de referencias pendientes.
- Búsqueda de símbolos en la tabla.
- Obtención de ubicaciones en memoria.
- Actualización de instrucciones SML.
- Generación del archivo final.

---

## Tercera etapa

La tercera etapa consiste en utilizar las instrucciones generadas por el compilador para su ejecución mediante el simulador Simpletron.

Entre sus principales funciones se encuentran:

- Lectura del archivo SML.
- Carga de instrucciones en memoria.
- Procesamiento de instrucciones.
- Manejo de registros.
- Ejecución de operaciones.
- Visualización de resultados.

---

## Estructuras de datos utilizadas

| Estructura | Función |
|---|---|
| `struct` | Representar símbolos |
| Arreglos | Almacenar instrucciones |
| Tabla de símbolos | Registrar variables y constantes |
| `flags` | Registrar referencias pendientes |
| Apuntadores | Manejar archivos y cadenas |
| Pilas | Procesar expresiones aritméticas |

---

## Lenguaje utilizado

**Lenguaje:**
- C

**Bibliotecas:**
- `stdio.h`
- `string.h`

**Conceptos de programación:**
- Variables.
- Funciones.
- Estructuras.
- Arreglos.
- Apuntadores.
- Ciclos.
- Condicionales.
- Manejo de archivos.
- Cadenas de caracteres.

**Estado:** En desarrollo

---

## Organización del proyecto

    Compilador-Simple/
    │
    ├── README.md
    ├── compilador.c
    ├── programa.simple
    ├── primera_pasada.sml
    └── programa.sml

---

## Compilación

Para compilar el programa utilizando GCC:

    gcc compilador.c -o compilador

Para ejecutarlo en Windows:

    .\compilador.exe

---

## Estado del proyecto

- **Primera pasada:** Desarrollada.
- **Segunda pasada:** Pendiente.
- **Tercera etapa:** Pendiente.

El proyecto continuará desarrollándose de manera progresiva, aplicando conocimientos de programación estructurada y estructuras de datos en lenguaje C.
