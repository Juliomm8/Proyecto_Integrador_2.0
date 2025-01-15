#ifndef INFOPRODUCTOS_H // Verifica si la macro INFOPRODUCTOS_H no está definida

//define la macro
#define INFOPRODUCTOS_H

#include "estructuraProducto.h"
#include "validación.h"
#include "animacion.h"
#include <stdio.h>
#include <string.h>

// Función para guardar el inventario en un archivo
void ingresarProducto(struct Producto inventario[], int *numProductos) {
  int valido = 0; // Indicador para determinar si el código es válido
  
  // Preguntar al usuario si quiere continuar con el ingreso de productos, o si no regresar al menu principal
  // Implementamos esto por si acaso el usuario eligió mal la opción
  do {
    
    char buffer[50];
    
    printf("\n\033[1;31m-----¿Seguro desea continuar?-----\033[0m\n");
    printf("\033[1;32mSí [1]\033[0m  \033[1;31mNo [0]\033[0m : ");
    fgets(buffer, sizeof(buffer), stdin);

    // Eliminar el salto de línea del final del buffer
    // "sscaanf" sirve para leer datos formateados de una cadena de caracteres (string) y asignarlos a variables específicas, siguiendo un formato definido, es como scanf, pero opera en cadenas en lugar de leer desde la entrada estándar (teclado).
    if (sscanf(buffer, "%d", &valido) != 1 || (valido != 0 && valido != 1)) {
      printf("\n\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para No.\033[0m\n");
    } else if (valido == 0) {
      printf("\n\033[1;32mVolviendo al menú principal\033[0m");
      animacionPuntos(); // Animar puntos después del mensaje
      return;
    }
  } while (valido != 1);

  // Verificar si el inventario ya está lleno (máximo 1000 productos)
  if (*numProductos >= 1000) {
    
    // Si el inventario está lleno, imprime un mensaje de error en color rojo
    printf("\033[1;31mNo se pueden agregar más productos [Inventario lleno]\033[0m\n");
    return; // Termina la ejecución de la función, ya que no se puede agregar más productos
  }
  
  // Si el inventario no está lleno, continúa con el proceso para agregar un nuevo producto
  printf("\n\033[1;32m-----Ingreso de un nuevo producto-----\033[0m\n");
  
  // Ingreso del nombre del producto
  int nombreValido = 0; // Variable para controlar si el nombre ingresado es válido
  do {
    
    // Lee la entrada del usuario (nombre del producto) y la guarda en el campo `nombre` del producto actual.
    // `fgets` asegura que no se lean más caracteres de los permitidos en el tamaño de `nombre`.
    printf("Ingresa el nombre del producto: ");
    fgets(inventario[*numProductos].nombre, sizeof(inventario[*numProductos].nombre), stdin);
    
    // Eliminar el carácter de nueva línea ('\n') que `fgets` puede incluir al final
    inventario[*numProductos].nombre[strcspn(inventario[*numProductos].nombre, "\n")] = '\0';
     
    // Valida si el nombre ingresado es único en el inventario
    // Si es así, se guarda en el campo `nombre` del producto actual.
    if (!esNombreUnico(inventario[*numProductos].nombre, inventario, *numProductos)) {
      
      // Si el nombre ya existe, muestra un mensaje de error en color rojo
      printf("\033[1;31mEl nombre del producto ya existe, ingresa otro nombre.\033[0m\n");
    } else {
      nombreValido = 1; // Si el nombre es válido y único, marca como válido para salir del ciclo
    }
  } while (!nombreValido); // Repetir mientras el nombre ingresado no sea válido

  // Ingreso del fabricante
  printf("Ingresa el nombre del fabricante: ");
  fgets(inventario[*numProductos].fabricante, sizeof(inventario[*numProductos].fabricante), stdin);
  inventario[*numProductos].fabricante[strcspn(inventario[*numProductos].fabricante, "\n")] = '\0';

  // Ingreso del código del producto
  int codigoValido = 0; // Variable para controlar si el código ingresado es válido
  do {
    
    // Solicita al usuario que ingrese un código válido
    ingresarCodigoValido(inventario[*numProductos].codigo, sizeof(inventario[*numProductos].codigo), inventario, *numProductos);
    
    // Verifica si el código ingresado ya existe en el inventario
    if (!esCodigoUnico(inventario[*numProductos].codigo, inventario, *numProductos)) {
      printf("\033[1;31mEl código ya está en uso, ingresa otro.\033[0m\n");
    } else {
      
      // Si el código es válido y único, marca como válido para salir del ciclo
      codigoValido = 1;
    }
  } while (!codigoValido); // Repetir mientras el código ingresado no sea válido

  // Ingreso de la cantidad de unidades
  do {
    
    char buffer[50];
    
    printf("Cantidad de unidades: "); // Solicita al usuario que ingrese la cantidad
    fgets(buffer, sizeof(buffer), stdin); // Lee la cantidad ingresada
    
    if (sscanf(buffer, "%d", &inventario[*numProductos].cantidad) != 1 || inventario[*numProductos].cantidad < 0) {
      printf("\033[1;31mCantidad no válida, ingresa de nuevo.\033[0m\n");
      continue;
    }
    break;
  } while (1);

  // Ingreso del precio sin impuestos
  do {
    
    char buffer[50];
    
    printf("Precio del producto (sin impuestos): "); // Solicitar al usuario que ingrese el precio
    fgets(buffer, sizeof(buffer), stdin);
    
    if (sscanf(buffer, "%f", &inventario[*numProductos].precio) != 1 || inventario[*numProductos].precio <= 0) {
      printf("\033[1;31mEl precio debe ser mayor que 0, ingresa de nuevo.\033[0m\n");
      continue;
    }
    break;
  } while (1);

  // Ingreso del porcentaje de impuestos
  do {
    
    char buffer[50];
    
    printf("Porcentaje del impuesto para este producto: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    if (sscanf(buffer, "%f", &inventario[*numProductos].impuesto) != 1 || inventario[*numProductos].impuesto < 0) {
      printf("\033[1;31mEl impuesto no puede ser negativo, ingresa de nuevo.\033[0m\n");
      continue;
    }
    break;
  } while (1);

  // Ingreso de si requiere prescripción médica
  do {
    
    char buffer[50];
    
    printf("\033[1;31m-----¿Requiere prescripción médica?-----\033[0m\n");
    printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
    fgets(buffer, sizeof(buffer), stdin);
    
    if (sscanf(buffer, "%d", &inventario[*numProductos].requierePrescripcion) != 1 || (inventario[*numProductos].requierePrescripcion != 0 && inventario[*numProductos].requierePrescripcion != 1)) {
      printf("\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para No.\033[0m\n");
      continue;
    }
    
    break;
  } while (1);

  // Incrementar el contador de productos
  (*numProductos)++; // Aumentar el número total de productos en el inventario
  printf("\033[1;32m-----Producto agregado con éxito :)-----\033[0m\n");
}

void imprimirTodosLosProductos(struct Producto inventario[], int numProductos) {
  
  // Validar si el inventario está vacío
  if (numProductos == 0) {
    printf("\n\033[1;31m-----No hay productos en el inventario-----\033[0m\n");
    printf("\n\033[1;32mVolviendo al menú principal\033[0m");
    animacionPuntos();
    return;  // Termina la función, ya que no hay nada que mostrar
  }
  
  // Si hay productos, imprime un encabezado para la lista
  printf("\033[1;34m\nLista de productos:\033[0m\n");
  
  // Iterar sobre cada producto en el inventario
  for (int i = 0; i < numProductos; i++) {
    
    // Calcular el precio con impuestos (P.V.P - Precio de Venta al Público)
    float precioConImpuestos = inventario[i].precio * (1 + inventario[i].impuesto / 100);
    
    // Imprimir el encabezado de cada producto
    printf("\033[1;33mProducto %d:\033[0m\n", i + 1); // Muestra el número del producto
    
    // Imprimir los detalles del producto
    printf("  Nombre: %s\n", inventario[i].nombre);             // Nombre del producto
    printf("  Código: %s\n", inventario[i].codigo);             // Código único del producto
    printf("  Fabricante: %s\n", inventario[i].fabricante);     // Nombre del fabricante
    printf("  Unidades: %d\n", inventario[i].cantidad);         // Cantidad disponible en el inventario
    printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio); // Precio base sin impuestos
    printf("  Impuesto: %.2f%%\n", inventario[i].impuesto);     // Porcentaje de impuestos aplicado
    printf("  P.V.P: %.2f\n", precioConImpuestos);              // Precio final con impuestos incluidos
    
    // Indicar si el producto requiere prescripción médica
    printf("  Requiere prescripción: %s\n", inventario[i].requierePrescripcion ? "\033[1;31mSí\033[0m" : "\033[1;32mNo\033[0m");
    
    // Imprimir una línea divisoria para separar los productos
    printf("\033[1;34m----------------------------------------\033[0m\n");
    printf("\n\033[1;32mCargando\033[0m");
    animacionPuntos();
  }
  printf("\n\033[1;32mVolviendo al menú principal\033[0m");
  animacionPuntos();
}

#endif // INFOPRODUCTOS_H