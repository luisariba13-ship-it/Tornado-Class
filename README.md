# Un compilador de Simple

Proyecto académico desarrollado para la materia de **Programación Avanzada** de la **Universidad Popular Autónoma del Estado de Puebla (UPAEP)**.

Este proyecto está enfocado en el desarrollo de un compilador para el lenguaje **Simple**, el cual permite traducir instrucciones a lenguaje máquina **SML (Simpletron Machine Language)** para su posterior ejecución en el simulador Simpletron.

El proyecto se desarrolla de manera progresiva, incorporando nuevas características y modificaciones conforme avanzan las actividades de la materia.

---

## Información del proyecto

- **Proyecto:** Un compilador de Simple
- **Nombre:** Compilador Simple
- **Universidad:** Universidad Popular Autónoma del Estado de Puebla (UPAEP)
- **Carrera:** Ingeniería de Software
- **Materia:** Programación Avanzada
- **Periodo:** Otoño 2026
- **Tipo de proyecto:** Académico

---

## Descripción

El compilador Simple es un programa que permite leer instrucciones escritas en el lenguaje Simple y traducirlas a instrucciones SML, utilizando una memoria de **100 posiciones**.

El proceso de compilación se desarrolla mediante dos pasadas principales y una tercera etapa de ejecución en el simulador Simpletron.

Entre sus principales funcionalidades se encuentran:

- Lectura de archivos con instrucciones Simple.
- Identificación de comandos y variables.
- Construcción de una tabla de símbolos.
- Asignación de posiciones de memoria.
- Generación de instrucciones SML.
- Manejo de constantes y variables.
- Identificación de saltos pendientes.
- Resolución de referencias mediante una segunda pasada.
- Generación de archivos con instrucciones SML.

---

## Primera pasada

La primera pasada consiste en leer el programa escrito en Simple, identificar sus instrucciones y generar el código SML inicial.

Durante este proceso se construye una tabla de símbolos que almacena los números de línea, variables y constantes utilizados en el programa.

Entre sus principales funciones se encuentran:

- Lectura del archivo `programa.simple`.
- Separación de instrucciones mediante `strtok()`.
- Identificación de los comandos del lenguaje Simple.
- Registro de variables, constantes y números de línea.
- Asignación de ubicaciones en memoria.
- Generación de instrucciones SML.
- Registro de saltos pendientes mediante el arreglo `flags`.
- Generación del archivo `primera_pasada.sml`.

### Tabla de símbolos

La tabla de símbolos almacena la información de los elementos utilizados durante la compilación.

| Campo | Descripción |
|---|---|
| `symbol` | Símbolo encontrado |
| `type` | Tipo de símbolo |
| `location` | Ubicación en memoria |

Los símbolos se clasifican en:

- **L:** Número de línea.
- **V:** Variable.
- **C:** Constante.

Las instrucciones SML se almacenan desde la posición `00`, mientras que las variables y constantes se almacenan desde la posición `99` hacia atrás.

---

## Segunda pasada

La segunda pasada se encarga de resolver las referencias pendientes generadas durante la primera pasada.

Estas referencias aparecen cuando una instrucción realiza un salto hacia una línea que todavía no había sido procesada.

Entre sus principales funciones se encuentran:

- Recorrido del arreglo `flags`.
- Identificación de saltos pendientes.
- Búsqueda de números de línea en la tabla de símbolos.
- Obtención de ubicaciones en memoria.
- Modificación de instrucciones SML.
- Generación del archivo `programa.sml`.

Por ejemplo, una instrucción pendiente:

`+4000`

Puede convertirse en:

`+4004`

Cuando se identifica que la línea de destino corresponde a la posición `04` de memoria.

---

## Tercera etapa: Ejecución en Simpletron

La tercera etapa consiste en ejecutar las instrucciones SML generadas por el compilador mediante el simulador Simpletron.

Esta etapa permite comprobar el funcionamiento del programa compilado.

Entre sus principales funciones se encuentran:

- Lectura del archivo `programa.sml`.
- Carga de instrucciones en memoria.
- Inicialización de registros.
- Ejecución de instrucciones SML.
- Lectura y escritura de datos.
- Operaciones aritméticas.
- Saltos condicionales e incondicionales.
- Visualización de resultados.

---

## Instrucciones del lenguaje Simple

El compilador utiliza diferentes comandos para representar las operaciones de un programa.

| Comando | Descripción |
|---|---|
| `rem` | Comentario |
| `input` | Lectura de datos |
| `print` | Escritura de datos |
| `let` | Asignación de valores |
| `goto` | Salto incondicional |
| `if/goto` | Salto condicional |
| `end` | Finalización del programa |

---

## Códigos de operación

El compilador genera instrucciones SML utilizando los siguientes códigos de operación:

| Código | Operación |
|---|---|
| `10` | READ |
| `11` | WRITE |
| `20` | LOAD |
| `21` | STORE |
| `30` | ADD |
| `31` | SUBTRACT |
| `32` | DIVIDE |
| `33` | MULTIPLY |
| `40` | BRANCH |
| `41` | BRANCHNEG |
| `42` | BRANCHZERO |
| `43` | HALT |

---

## Lenguaje utilizado

**Lenguaje:**
- C

**Bibliotecas:**
- `stdio.h`
- `string.h`

**Estructuras de datos:**
- Arreglos.
- Estructuras (`struct`).
- Apuntadores.
- Pilas.

**Estado:** En desarrollo

---

## Organización del proyecto

```text
Compilador-Simple/
│
├── README.md
│
├── compilador.c
│
├── programa.simple
│
├── primera_pasada.sml
│
└── programa.sml
```

---

## Estado del proyecto

- **Primera pasada:** Desarrollada.
- **Segunda pasada:** Pendiente de implementación.
- **Tercera etapa:** Pendiente de integración con Simpletron.

El proyecto continuará desarrollándose de manera progresiva, incorporando nuevas funcionalidades hasta completar el proceso de compilación y ejecución de instrucciones SML.
