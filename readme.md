# Proyecto ADA II

A continuación, se detalla la estructura del proyecto y las diferentes formas de ejecutarlo.

## Estructura del Proyecto

El proyecto se divide principalmente en los siguientes directorios:

- **`src/`**: Contiene toda la lógica del proyecto, incluyendo las clases (`Farm.h`, `Farm.cpp`, `TerminalUI.cpp`) y los diferentes algoritmos que dan solución al problema. Desde esta carpeta se ejecuta el punto de entrada principal en C++ (`main.cpp`).
- **`bin/`**: Carpeta donde se generará el programa ejecutable compilado.
- **`ui/`**: Contiene la interfaz de usuario implementada en Python (`main.py`), la cual interactúa con el ejecutable. Incluye la carpeta `Test` para entradas y `output` para resultados.
- **`input/`**: Carpeta usada para almacenar los casos de prueba cuando se utiliza la interfaz de terminal en C++.

## Requisitos Previos

- Se debe tener un compilador de C++ instalado.
- Si estás en **Windows**, puedes clonar o poner el proyecto en **WSL** (Windows Subsystem for Linux) para ejecutarlo sin complicaciones de permisos. 
- Si estás en macOS (**iOS/macOS**), puedes compilar el código de manera nativa utilizando Clang/GCC u otro compilador disponible, asegurándote de usar las herramientas de desarrollo.
- Se recomienda el uso de **Visual Studio Code (VSCode)**, con el cual puedes compilar y ejecutar todo el proyecto (el código C++) usando la tecla `F5` o `fn + F5`. Esto generará el ejecutable automáticamente en la carpeta `bin/`.

---

## Formas de Ejecutar el Proyecto

Existen dos formas principales de visualizar y ejecutar el proyecto, dando prioridad al uso de la interfaz en Python.

### 1. Interfaz Gráfica en Python (Recomendado)

Esta es la forma principal y más completa de probar los algoritmos con una interfaz visual.

- Para iniciar, debes ejecutar el archivo `main.py` que se encuentra en la carpeta **`ui/`**.
- Este script de Python se conectará y ejecutará automáticamente el programa `.cpp` compilado que ya viene preparado en la carpeta **`bin/`** (`bin/main`). De esta forma, no tendrás que compilar o ejecutar el archivo C++ por tu cuenta a menos que sea necesario actualizarlo.

**La interfaz consta de tres partes principales:**
1. **Gestión de Pruebas:** Permite elegir, ver y modificar el test o caso de prueba que se va a ejecutar. Las pruebas pueden seleccionarse directamente desde la carpeta `ui/Test/`.
2. **Selección de Algoritmo:** Permite elegir cuál de los algoritmos implementados deseas probar para ese caso de prueba.
3. **Salida:** Dispone de un botón de **"Calcular resultados"** que ejecuta el algoritmo seleccionado, y un botón de **"Limpiar resultados"** para limpiar todos los resultados en pantalla. 
   - Los resultados de tu prueba los podrás ver guardados dentro de la carpeta `ui/output/`.
   - El archivo generado tendrá como nombre el archivo de prueba seguido por el nombre del algoritmo implementado.

**Solución de problemas (Fallback):** Si al dar clic en calcular se presenta algún problema de acceso a la carpeta `bin/` o el binario no existe, deberás compilar y ejecutar primero el archivo `main.cpp` (ubicado en `src/`) como se explicó anteriormente usando `F5` o `fn + F5` en VSCode, para así generar un nuevo ejecutable en `bin/`.

### 2. Interfaz de Terminal en C++

La otra forma de correr el proyecto de manera más rápida y ligera es directamente desde el código C++, mediante una interfaz en la terminal que ya ha sido implementada (`TerminalUI.cpp`).

- Al ejecutar el ejecutable compilado desde la terminal (desde `src/main.cpp`), visualizarás un menú interactivo con diferentes opciones a elegir.
- Aquí podrás seleccionar rápidamente los casos de prueba ubicados en la carpeta **`input/`**.
- **Nota:** En este modo de ejecución rápida, no se generarán archivos de salida, pero es ideal para realizar una comprobación directa de resultados y rendimiento de los diferentes algoritmos.
