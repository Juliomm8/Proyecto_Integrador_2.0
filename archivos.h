#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuraProducto.h"
#include "animacion.h"

// Declaración de funciones
void guardarInventario(const char *inventarioArchivo, struct Producto inventario[], int numProductos);
int cargarInventario(const char *inventarioArchivo, struct Producto inventario[]);

/* 
Separamos 'archivos' en 2, por que?
- Separamos las declaraciones '.h'
- Separamos las definiciones '.c'

-Hicmos asi porque nos permite que otros archivos incluyan `archivos.h` y usen las funciones sin conocer sus
detalles internos. 
-También porque nos facilita en la reutilización del código, ya que el módulo de manejo de archivos puede adaptarse fácilmente a otros proyectos
-Escalabilidad: Al permitir cambios en la implementación `archivos.c` sin afectar al resto del programa.
*/

#endif // ARCHIVOS_H