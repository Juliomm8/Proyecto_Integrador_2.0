# Pharma+ Inventory Management System

Pharma+ es un sistema modular desarrollado en C que facilita la gestión eficiente del inventario de productos farmacéuticos. Este proyecto es parte de un trabajo integrador para **Programación I**, Universidad de las Américas**.

## Características Principales

- **Gestión de Productos:**
  - Ingreso, edición, eliminación y consulta de productos.
  - Listado completo de los productos registrados.

- **Validaciones:**
  - Nombres únicos para productos y fabricantes.
  - Códigos de productos únicos y compuestos solo por números.
  - Precios y cantidades positivas.
  - Control de requisitos de prescripción médica.

- **Cálculo de Precios:**
  - Determinación de precio final (P.V.P.) considerando impuestos personalizados por producto.

- **Modularidad:**
  - División en tres módulos principales:
    - `infoProductos.h`: Gestión del inventario.
    - `consultarProductos.h`: Consulta y manejo de productos.
    - `validación.h`: Validación de entradas del usuario.

## Estructura del Código

- **`main.c`:** Control principal del flujo del programa.
- **`infoProductos.h`:** Módulo para ingresar, listar y manipular productos.
- **`consultarProductos.h`:** Módulo para buscar, editar y eliminar productos.
- **`validación.h`:** Módulo de validaciones.

## Funcionalidades Implementadas

1. **Agregar Producto**
2. **Editar Producto**
3. **Eliminar Producto**
4. **Consultar Producto (por nombre o código)**
5. **Listar Todos los Productos**

## Cambios Planeados

- **Uso de Structs:** Implementación de una estructura `struct` para manejar los datos de los productos de forma más organizada. Esta estructura se definirá en un nuevo archivo de cabecera.
- **Manejo de Archivos:** Implementación de funcionalidades para persistencia de datos en archivos. Estas operaciones serán gestionadas en un nuevo archivo de cabecera que incluirá funciones para leer y escribir los datos del inventario.


## Colaboradores

- Eduardo Granja
- Julio Mera
- Jeremy Tomaselly
