#ifndef INFOPRODUCTOS_H
#define INFOPRODUCTOS_H

#include "estructuraProducto.h"
#include "validación.h"
#include <stdio.h>
#include <string.h>

// Función para guardar el inventario en un archivo
void ingresarProducto(struct Producto inventario[], int *numProductos) {
  // Verificar si el inventario ya está lleno (máximo 1000 productos)
  if (*numProductos >= 1000) {
    // Si el inventario está lleno, imprime un mensaje de error en color rojo
    printf("\033[1;31mNo se pueden agregar más productos [Inventario "
           "lleno]\033[0m\n");
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
    fgets(inventario[*numProductos].nombre,
          sizeof(inventario[*numProductos].nombre), stdin);

    // Eliminar el carácter de nueva línea ('\n') que `fgets` puede incluir al final
    inventario[*numProductos]
        .nombre[strcspn(inventario[*numProductos].nombre, "\n")] = '\0';

     // Valida si el nombre ingresado es único en el inventario
     // Si es así, se guarda en el campo `nombre` del producto actual.
    if (!esNombreUnico(inventario[*numProductos].nombre, inventario,
                       *numProductos)) {
      // Si el nombre ya existe, muestra un mensaje de error en color rojo
      printf("\033[1;31mEl nombre del producto ya existe, ingresa otro "
             "nombre.\033[0m\n");
    } else {
      nombreValido = 1;
    }
  } while (!nombreValido);

  // Ingreso del fabricante
  printf("Ingresa el nombre del fabricante: ");
  fgets(inventario[*numProductos].fabricante,
        sizeof(inventario[*numProductos].fabricante), stdin);
  inventario[*numProductos]
      .fabricante[strcspn(inventario[*numProductos].fabricante, "\n")] = '\0';

  // Ingreso del código del producto
  int codigoValido = 0;
  do {
    ingresarCodigoValido(inventario[*numProductos].codigo,
                         sizeof(inventario[*numProductos].codigo), inventario,
                         *numProductos);
    if (!esCodigoUnico(inventario[*numProductos].codigo, inventario,
                       *numProductos)) {
      printf("\033[1;31mEl código ya está en uso, ingresa otro.\033[0m\n");
    } else {
      codigoValido = 1;
    }
  } while (!codigoValido);

  // Ingreso de la cantidad de unidades
  do {
    printf("Cantidad de unidades: ");
    scanf("%d", &inventario[*numProductos].cantidad);
    getchar(); // Limpiar el buffer
    if (!validarCantidadProducto(inventario[*numProductos].cantidad)) {
      printf("\033[1;31mCantidad no válida, ingresa de nuevo.\033[0m\n");
    }
  } while (!validarCantidadProducto(inventario[*numProductos].cantidad));

  // Ingreso del precio sin impuestos
  do {
    printf("Precio del producto (sin impuestos): ");
    scanf("%f", &inventario[*numProductos].precio);
    getchar(); // Limpiar el buffer
    if (inventario[*numProductos].precio <= 0) {
      printf("\033[1;31mEl precio debe ser mayor que 0, ingresa de "
             "nuevo.\033[0m\n");
    }
  } while (inventario[*numProductos].precio <= 0);

  // Ingreso del porcentaje de impuestos
  do {
    printf("Porcentaje del impuesto para este producto: ");
    scanf("%f", &inventario[*numProductos].impuesto);
    getchar(); // Limpiar el buffer
    if (inventario[*numProductos].impuesto < 0) {
      printf("\033[1;31mEl impuesto no puede ser negativo, ingresa de "
             "nuevo.\033[0m\n");
    }
  } while (inventario[*numProductos].impuesto < 0);

  // Ingreso de si requiere prescripción médica
  do {
    printf("\033[1;31m-----¿Requiere prescripción médica?-----\033[0m\n");
    printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
    scanf("%d", &inventario[*numProductos].requierePrescripcion);
    getchar(); // Limpiar el buffer
    if (inventario[*numProductos].requierePrescripcion != 0 &&
        inventario[*numProductos].requierePrescripcion != 1) {
      printf("\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para "
             "No.\033[0m\n");
    }
  } while (inventario[*numProductos].requierePrescripcion != 0 &&
           inventario[*numProductos].requierePrescripcion != 1);

  // Incrementar el contador de productos
  (*numProductos)++;
  printf("\033[1;32m-----Producto agregado con éxito :)-----\033[0m\n");
}

void imprimirTodosLosProductos(struct Producto inventario[], int numProductos) {
  // Validar si el inventario está vacío
  if (numProductos == 0) {
    printf("\033[1;31m-----No hay productos en el inventario-----\033[0m\n");
    return;
  }

  // Imprimir información de cada producto
  printf("\033[1;34m\nLista de productos:\033[0m\n");
  for (int i = 0; i < numProductos; i++) {
    float precioConImpuestos =
        inventario[i].precio * (1 + inventario[i].impuesto / 100);
    printf("\033[1;33mProducto %d:\033[0m\n", i + 1);
    printf("  Nombre: %s\n", inventario[i].nombre);
    printf("  Código: %s\n", inventario[i].codigo);
    printf("  Fabricante: %s\n", inventario[i].fabricante);
    printf("  Unidades: %d\n", inventario[i].cantidad);
    printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio);
    printf("  Impuesto: %.2f%%\n", inventario[i].impuesto);
    printf("  P.V.P: %.2f\n", precioConImpuestos);
    printf("  Requiere prescripción: %s\n", inventario[i].requierePrescripcion
                                                ? "\033[1;31mSí\033[0m"
                                                : "\033[1;32mNo\033[0m");
    printf("\033[1;34m----------------------------------------\033[0m\n");
  }
}

#endif // INFOPRODUCTOS_H
