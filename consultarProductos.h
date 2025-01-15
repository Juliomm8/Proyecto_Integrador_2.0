#ifndef CONSULTARPRODUCTOS_H
#define CONSULTARPRODUCTOS_H

#include "animacion.h"
#include "archivos.h"
#include "estructuraProducto.h"
#include "infoProductos.h"
#include "validación.h"
#include <stdio.h>
#include <string.h>

void buscarProducto(struct Producto inventario[], int numProductos);
void consultarProductoPorNombre(char *nombreBusqueda, struct Producto inventario[], int numProductos);
void consultarProductoPorCodigo(char *codigoBusqueda, struct Producto inventario[], int numProductos);
void eliminarProducto(struct Producto inventario[], int *numProductos);
void editarProducto(struct Producto inventario[], int numProductos);

void buscarProducto(struct Producto inventario[], int numProductos) {
  // Variable para almacenar el criterio de búsqueda elegido por el usuario
  int criterio = 0;
  // Variable para almacenar la entrada del usuario (nombre o código)
  char entrada[50];
  do {
    // Mostrar opciones al usuario para elegir el criterio de búsqueda
    printf("\nBuscar por:\n");
    printf(
        "\033[1;36mNombre [1]\n"); // Opción 1: Buscar por nombre (color cian)
    printf(
        "\033[1;36mCódigo [2]\n"); // Opción 2: Buscar por código (color cian)
    printf("\033[1;31mSalir [3]\033[0m\n"); // Opción 3: Salir de la función
                                            // (color rojo)
    // Leer la opción elegida por el usuario
    printf("\nSeleccione una opción: ");
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &criterio) != 1 || criterio < 1 || criterio > 3) {
      printf("\n\033[1;31m-----Opción no válida-----\033[0m\n");
      continue;
    }
    if (criterio == 1) { // Buscar por nombre
      printf("Ingrese el nombre del producto: ");
      // Leer el nombre ingresado por el usuario
      fgets(entrada, sizeof(entrada), stdin);
      // Eliminar el carácter de nueva línea ('\n') que `fgets` puede incluir al
      // final
      entrada[strcspn(entrada, "\n")] = '\0';
      // Llamar a la función que realiza la búsqueda por nombre
      consultarProductoPorNombre(entrada, inventario, numProductos);
    } else if (criterio == 2) { // Buscar por código
      // Solicitar al usuario el código del producto
      printf("Ingrese el código del producto: ");
      fgets(entrada, sizeof(entrada), stdin);
      // Eliminar el carácter de nueva línea ('\n') que `fgets` puede incluir al
      // final
      entrada[strcspn(entrada, "\n")] = '\0';
      // Llamar a la función que realiza la búsqueda por código
      consultarProductoPorCodigo(entrada, inventario, numProductos);
    } else if (criterio == 3) { // Salir de la función
      // Mensaje indicando que se regresa al menú principal
      printf("\n\033[1;32mVolviendo al menú principal\033[0m");
      animacionPuntos(); // Animar puntos después del mensaje
      printf("\n");
      return; // Termina la ejecución de la función
    }
  } while (1); // Repetir el menú hasta que el usuario elija salir
}

void consultarProductoPorNombre(char *nombreBusqueda,
                                struct Producto inventario[],
                                int numProductos) {
  int encontrado = 0; // Indicador para saber si el producto fue encontrado
  // El 'for' recorre todos los productos en el inventario
  for (int i = 0; i < numProductos; i++) {
    // Comparar el nombre del producto actual con el nombre buscado
    if (strcmp(inventario[i].nombre, nombreBusqueda) == 0) {
      // Si hay coincidencia, mostrar los detalles del producto
      printf("\033[1;32mProducto encontrado:\033[0m\n");
      printf("  Nombre: %s\n", inventario[i].nombre);
      printf("  Código: %s\n", inventario[i].codigo);
      printf("  Fabricante: %s\n", inventario[i].fabricante);
      printf("  Cantidad: %d\n", inventario[i].cantidad);
      printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio);
      printf("  Porcentaje de impuesto: %.2f%%\n", inventario[i].impuesto);
      printf("  P.V.P: %.2f\n", inventario[i].precio * (1 + inventario[i].impuesto / 100));
      printf("  Requiere prescripción: %s\n",
             inventario[i].requierePrescripcion ? "Sí" : "No");
      encontrado =
          1; // Cambia la variable a 1 para indicar que se encontró el producto
      break; // Salir del bucle porque el producto ya fue encontrado
    }
  }
  // Si no se encontró ningún producto con el nombre especificado, mostrar un
  // mensaje de error
  if (!encontrado) {
    printf(
        "\n\033[1;31mNo se encontró ningún producto con ese nombre\033[0m\n");
  }
}

void consultarProductoPorCodigo(char *codigoBusqueda, struct Producto inventario[], int numProductos) {
  int encontrado = 0; // Variable para indicar si se encontró el producto
  // Recorre todos los productos en el inventario
  for (int i = 0; i < numProductos; i++) {
    // Compara el código del producto actual con el código buscado
    if (strcmp(inventario[i].codigo, codigoBusqueda) == 0) { // Comparar códigos
      printf("\033[1;32mProducto encontrado:\033[0m\n");

      // Imprimir información del producto (similar a la función anterior)
      printf("  Nombre: %s\n", inventario[i].nombre);
      printf("  Código: %s\n", inventario[i].codigo);
      printf("  Fabricante: %s\n", inventario[i].fabricante);
      printf("  Cantidad: %d\n", inventario[i].cantidad);
      printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio);
      printf("  Porcentaje de impuesto: %.2f%%\n", inventario[i].impuesto);
      printf("  P.V.P: %.2f\n",
             inventario[i].precio * (1 + inventario[i].impuesto / 100));
      printf("  Requiere prescripción: %s\n", inventario[i].requierePrescripcion ? "\033[1;31mSi\033[0m" : "\033[1;32mNo\033[0m"); // El operador condicional (?:) evalúa el valor de `inventario[i].requierePrescripcion`:
      // - Si es verdadero, muestra "Si" en rojo, indicando que se requiere prescripción.
      // - Si es falso, muestra "No" en verde, indicando que no se requiere prescripción.
      encontrado = 1;
      break;
    }
  }

  if (!encontrado) { // Si no se encontró ningún producto con el código especificado
    printf("\n\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
  }
}

void eliminarProducto(struct Producto inventario[], int *numProductos) {
  char entrada[50];
  int valido = 0; // Indicador para determinar si el usuario confirma continuar
  // Preguntar al usuario si quiere continuar con la eliminación de productos
  do {
    char buffer[50];
    printf("\n\033[1;31m-----¿Seguro desea continuar?-----\033[0m\n");
    printf("\033[1;32mSí [1]\033[0m  \033[1;31mNo [0]\033[0m : ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &valido) != 1 || (valido != 0 && valido != 1)) {
      printf("\n\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para "
             "No.\033[0m\n");
    } else if (valido == 0) {
      printf("\n\033[1;32mVolviendo al menú principal\033[0m");
      animacionPuntos(); // Animar puntos después del mensaje
      printf("\n");
      return;
    }
  } while (valido != 1);

  // Solicitar al usuario el código del producto que desea eliminar
  do {
    printf("Ingrese el código del producto a eliminar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';           // Elimina el carácter de nueva línea ('\n')
    int encontrado = 0; // Indicador para saber si se encontró el producto
    // Recorre el inventario para buscar el producto con el código ingresado
    for (int i = 0; i < *numProductos; i++) {
      // Comparar el código del producto actual con el código ingresado
      if (strcmp(inventario[i].codigo, entrada) == 0) {
        // Desplazar los elementos siguientes para eliminar el producto
        for (int j = i; j < *numProductos - 1; j++) {
          inventario[j] = inventario[j + 1]; // Mover cada producto una posición hacia atrás
        }
        (*numProductos)--; // Reducir el contador de productos
        printf("\n\033[1;32m-----Producto eliminado con éxito-----\033[0m\n");
        printf("\n\033[1;32mVolviendo al menú principal\033[0m");
        animacionPuntos();
        return;
      }
    }

    // Si no se encontró el producto, mostrar mensaje de error
    printf("\033[1;31mNo se encontró ningún producto con ese código.\033[0m\n");
    // Preguntar al usuario si desea intentar de nuevo
    printf("\n\033[1;33m¿Desea intentar nuevamente?\033[0m\n");
    printf("\033[1;32mSí [1]\033[0m  \033[1;31mNo [0]\033[0m : ");
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &valido) != 1 || (valido != 0 && valido != 1)) {
      printf("\033[1;31mOpción no válida, volviendo al menú principal.\033[0m\n");
      return;
    }
    if (valido == 0) {
      printf("\n\033[1;32mVolviendo al menú principal\033[0m");
      animacionPuntos();
      return;
    }
  } while (1); // Continuar hasta que el usuario decida salir
}

void editarProducto(struct Producto inventario[], int numProductos) {
  char entrada[50];
  int valido = 0; // Indicador para determinar si el código es válido

  // Confirmar si el usuario desea continuar
  do {
    char buffer[50];
    printf("\n\033[1;31m-----¿Seguro desea continuar?-----\033[0m\n");
    printf("\033[1;32mSí [1]\033[0m  \033[1;31mNo [0]\033[0m : ");
    fgets(buffer, sizeof(buffer), stdin);

    // Validacion para que el usuario eliga una opcion
    // Si el usuario no elige 1 o 0, se le pide que elija de nuevo
    // Si el usuario elige 1, se continua con la funcion
    // Si el usuario elige 0, se regresa al menu principal
    if (sscanf(buffer, "%d", &valido) != 1 || (valido != 0 && valido != 1)) {
      printf("\n\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para "
             "No.\033[0m\n");
    } else if (valido == 0) {
      printf("\n\033[1;32mVolviendo al menú principal\033[0m");
      animacionPuntos();
      printf("\n");
      return;
    }
  } while (valido != 1);

  // Solicita el código del producto
  // Lee la entrada del usuario usando 'fgets' y almacenarla en `entrada`
  // Esto asegura que no se desborde el buffer y permite caracteres especiales.
  printf("\n\033[1;33mIngrese el código del producto a editar: \033[0m");
  fgets(entrada, sizeof(entrada), stdin);
  entrada[strcspn(entrada, "\n")] = '\0';

  // Ciclo para buscar el producto por código
  // Si se encuentra el producto, se muestra la información del producto y se
  // solicita al usuario que ingrese los nuevos datos
  for (int i = 0; i < numProductos; i++) {

    // Comparar el código ingresado (`entrada`) con el código
    // del producto actual (`inventario[i].codigo`).
    // Si `strcmp` retorna 0, significa que los códigos coinciden.
    if (strcmp(inventario[i].codigo, entrada) == 0) {
      printf("\n\033[1;32m-----Editando Producto-----\033[0m\n");
      int opcion = 0;

      // Inicia un bucle `do-while` para permitir al usuario editar los campos
      // del producto seleccionado.
      do {
        char buffer[50];
        printf("\n\033[1;33m¿Qué campo desea editar?\033[0m\n");
        printf("[1] Nombre (Actual: %s)\n", inventario[i].nombre);
        printf("[2] Fabricante (Actual: %s)\n", inventario[i].fabricante);
        printf("[3] Número de unidades (Actual: %d)\n", inventario[i].cantidad);
        printf("[4] Precio sin impuestos (Actual: %.2f)\n",
               inventario[i].precio);
        printf("[5] Porcentaje de impuesto (Actual: %.2f%%)\n",
               inventario[i].impuesto);
        printf("[6] Requiere prescripción médica (Actual: %s)\n",
               inventario[i].requierePrescripcion ? "Sí" : "No");
        printf("\n\033[1;31m[7] Salir\033[0m\n");

        printf("\n\033[1;33mSeleccione una opción: \033[0m");
        fgets(buffer, sizeof(buffer), stdin);

        // Intenta convertir la entrada del usuario (almacenada en `buffer`) a
        // un número entero. `sscanf` devuelve 1 si la conversión es exitosa.
        // También valida si el número está dentro del rango permitido (1 a 7).
        if (sscanf(buffer, "%d", &opcion) != 1 || opcion < 1 || opcion > 7) {
          printf("\033[1;31mOpción no válida, intente de nuevo.\033[0m\n");
          // `continue` fuerza la siguiente iteración del bucle, permitiendo al
          // usuario intentar nuevamente.
          continue;
        }
        switch (opcion) {
        case 1: // Editar nombre
          do {
            // Solicitar al usuario que ingrese un nuevo nombre para el producto
            printf("\nIngrese el nuevo nombre: ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0';

            // Validar que el nombre sea válido (contenga solo letras, números y
            // espacios)
            if (!validarNombreProducto(inventario[i].nombre)) {
              printf("\033[1;31mEl nombre no es válido. Solo se permiten "
                     "letras, números y espacios.\033[0m\n");
              // Volver al inicio del ciclo si el nombre no es válido
              continue;
            }
            int nombreExiste =
                0; // Indicador para verificar si el nombre ya existe
            // Verificar si el nombre ingresado ya existe en el inventario
            for (int j = 0; j < numProductos; j++) {
              // Ignorar el producto actual al verificar nombres duplicados
              if (j != i && strcmp(inventario[j].nombre, entrada) == 0) {
                // Si el nombre ya existe, mostrar un mensaje y marcarlo como no
                // único
                printf("\n\033[1;31mEl nombre ya existe, ingrese uno "
                       "diferente.\033[0m\n");
                nombreExiste = 1; // Indicar que el nombre ya está en uso
                break;            // Salir del ciclo de búsqueda
              }
            }
            // Si el nombre no existe en el inventario
            if (!nombreExiste) {
              // Copiar el nuevo nombre al campo correspondiente en el producto
              // actual
              strcpy(inventario[i].nombre, entrada);

              break; // Salir del ciclo `do-while` una vez que se ha actualizado
                     // el nombre
            }
          } while (1); // Repetir mientras el usuario no ingrese un nombre
                       // válido y único
          break;       // Salir del `case` una vez que el nombre ha sido editado

        case 2: // Editar fabricante
          do {
            printf("Ingrese el nuevo fabricante: ");
            fgets(inventario[i].fabricante, sizeof(inventario[i].fabricante),
                  stdin);
            // Eliminar el carácter de nueva línea `\n` que podría quedar en la
            // entrada.
            inventario[i].fabricante[strcspn(inventario[i].fabricante, "\n")] =
                '\0';
            // Validar que el nombre del fabricante sea válido.
            // Un nombre válido solo puede contener letras, números y espacios.
            if (!validarNombreProducto(inventario[i].fabricante)) {
              printf("\033[1;31mEl nombre del fabricante no es válido. Solo se "
                     "permiten letras, números y espacios.\033[0m\n");
            }
            // Repetir mientras el nombre ingresado no sea válido.
          } while (!validarNombreProducto(inventario[i].fabricante));

          // Salir del ciclo y confirmar que se ha actualizado el fabricante.
          break;

        case 3: // Editar número de unidades
          do {
            char buffer[50]; // Buffer temporal para almacenar la entrada del
                             // usuario como texto.
            printf("Ingrese el nuevo número de unidades: ");
            fgets(buffer, sizeof(buffer), stdin);

            // Validar que la entrada sea un número entero
            // `sscanf` intenta convertir el texto a un número entero y almacena
            // el resultado en `inventario[i].cantidad` `strchr(buffer, '.')`
            // verifica si hay un punto decimal en la entrada (para evitar
            // números flotantes)
            if (sscanf(buffer, "%d", &inventario[i].cantidad) != 1 ||
                strchr(buffer, '.')) {
              printf("\033[1;31mLa cantidad debe ser un número entero mayor o "
                     "igual a 0.\033[0m\n");
              continue; // Si la entrada no es válida, volver al inicio del
                        // ciclo
            }
            // Validar que la cantidad no sea negativa
            if (inventario[i].cantidad < 0) {
              printf("\033[1;31mLa cantidad no puede ser negativa.\033[0m\n");
              continue; // Si la cantidad es negativa, volver al inicio del
                        // ciclo
            }
            // Si todas las validaciones pasan, salir del ciclo
            break;
          } while (1); // Continuar repitiendo mientras la entrada no sea válida

          // Finalizar el case después de actualizar la cantidad
          break;

        case 4: // Editar precio sin impuestos
          do {
            char buffer[50]; // Buffer temporal para almacenar la entrada del
                             // usuario como texto.
            printf("Ingrese el nuevo precio sin impuestos: ");
            fgets(buffer, sizeof(buffer), stdin);
            // Validar que la entrada sea un número flotante y mayor que 0.
            // `sscanf` convierte el texto en `buffer` a un número flotante y lo
            // almacena en `inventario[i].precio`. La condición también verifica
            // que el precio sea mayor que 0.
            if (sscanf(buffer, "%f", &inventario[i].precio) != 1 ||
                inventario[i].precio <= 0) {
              // Si la conversión falla o el precio no es mayor que 0:
              // Mostrar un mensaje de error al usuario.
              printf("\033[1;31mEl precio debe ser un número mayor que "
                     "0.\033[0m\n");
              continue; // Volver al inicio del ciclo para solicitar la entrada
                        // nuevamente.
            }
            // Si todas las validaciones son exitosas, salir del ciclo.
            break;
          } while (1); // Repetir mientras la entrada no sea válida.

          // Finalizar el `case` después de actualizar el precio.
          break;

        case 5: // Editar porcentaje de impuesto
          do {
            char buffer[50]; // Buffer temporal para almacenar la entrada del
                             // usuario como texto.

            // Solicitar al usuario que ingrese el nuevo porcentaje de impuesto.
            printf("Ingrese el nuevo porcentaje de impuesto: ");
            fgets(buffer, sizeof(buffer),
                  stdin); // Leer la entrada del usuario.

            // Validar que la entrada sea un número flotante y mayor o igual a
            // 0. `sscanf` intenta convertir el texto del buffer en un número
            // flotante y lo almacena en `inventario[i].impuesto`. La condición
            // también verifica que el porcentaje de impuesto sea mayor o igual
            // a 0.
            if (sscanf(buffer, "%f", &inventario[i].impuesto) != 1 ||
                inventario[i].impuesto < 0) {
              // Si la conversión falla o el porcentaje es menor que 0:
              // Mostrar un mensaje de error al usuario.
              printf("\033[1;31mEl porcentaje de impuesto debe ser un número "
                     "mayor o igual a 0.\033[0m\n");
              continue; // Volver al inicio del ciclo para solicitar la entrada
                        // nuevamente.
            }

            // Si todas las validaciones son exitosas, salir del ciclo.
            break;
          } while (
              1); // Continuar repitiendo mientras la entrada no sea válida.

          // Finalizar el `case` después de actualizar el porcentaje de
          // impuesto.
          break;

          case 6: // Editar si requiere prescripción médica
          do {
              char buffer[50]; // Buffer temporal para almacenar la entrada del usuario como texto.

              // Solicitar al usuario que indique si el producto requiere prescripción médica.
              printf("\033[1;31m¿Requiere prescripción médica?\033[0m\n");
              printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
              fgets(buffer, sizeof(buffer), stdin); // Leer la entrada del usuario.

              // Validar que la entrada sea un número entero (1 o 0).
              // `sscanf` convierte el texto del buffer a un número entero y lo almacena en `inventario[i].requierePrescripcion`.
              // También verifica que el valor sea exactamente 0 o 1.
              if (sscanf(buffer, "%d", &inventario[i].requierePrescripcion) != 1 ||
                  (inventario[i].requierePrescripcion != 0 &&
                   inventario[i].requierePrescripcion != 1)) {
                  // Si la conversión falla o el valor no es 0 ni 1:
                  // Mostrar un mensaje de error al usuario.
                  printf("\033[1;31mOpción no válida. Ingresa 1 para Sí o 0 para No.\033[0m\n");
                  continue; // Volver al inicio del ciclo para solicitar la entrada nuevamente.
              }

              // Si todas las validaciones son exitosas, salir del ciclo.
              break;
          } while (1); // Continuar repitiendo mientras la entrada no sea válida.

          // Finalizar el `case` después de actualizar el valor de prescripción médica.
          break;


          case 7: // Salir de edición
          // Mostrar un mensaje indicando que se está regresando al menú principal
          printf("\n\033[1;32mVolviendo al menú principal\033[0m");
          animacionPuntos(); // Llamar a una función para animar puntos (visualización estética)
          printf("\n"); // Agregar un salto de línea después de la animación
          break; // Finalizar el case y salir del bucle


          default: // Opción no válida
          // Mostrar un mensaje en color rojo indicando que la opción ingresada no es válida
          printf("\033[1;31mOpción no válida, intente de nuevo.\033[0m\n");
          break; // Finalizar el case y permitir al usuario volver a intentar

        }
      } while (opcion != 7);

      printf("\033[1;32m-----Producto editado con éxito-----\033[0m\n");
      return;
    }
  }
  printf("\n\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
  printf("\n\033[1;32mVolviendo al menú principal\033[0m");
  animacionPuntos();
}

#endif // CONSULTARPRODUCTOS_H