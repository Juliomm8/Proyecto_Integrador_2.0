#include "animacion.h" // Header con funciones para animar la carga
#include "archivos.h" // Header con funciones para guardar y cargar el inventario en un archivo
#include "consultarProductos.h" // Header que tiene las funciones para buscar, editar y eliminar productos
#include "estructuraProducto.h" // Header que contiene la estructura de los producto en el inventario
#include "infoProductos.h" // Header que tiene las funciones para agregar y listar productos
#include "validación.h" // Header con funciones para validar entradas
#include <stdio.h>
#include <string.h>

// Declaramos el inventario como un arreglo global de productos, para que sea mas facil de acceder desde cualquier parte del programa
struct Producto inventario[1000]; // El programa puede almacenar hasta 1000 productos
int numProductos = 0; // Variable que sirbe como contador para saber cuantos productos hay en el inventario
int main() {
  int opcion;        // Variable que sirve para saber la opción del usuario
  int continuar = 1; // Variable que controla si el programa sigue ejecutándose

  // Carga el inventario desde el archivo 'inventario.txt' y si no encuentra el archivo, lo crea
  numProductos = cargarInventario("inventario.txt", inventario);

  // Inicia un while que muestra el menú principal hasta que el usuario elija la opcion de salir
  while (continuar) {
    // Mendiante prints muestra el menú principal
    // Los '\033[1;3_' y son códigos de escape ANSI y estos códigos de colores
    // ayudan a distinguir entre mensajes importantes, errores, advertencias, y
    // opciones del programa.
    printf("\033[1;34m\n========================================\n");
    printf("          Inventario - \033[1;33mPharma+\033[0m\n");
    printf("\033[1;34m========================================\n");
    printf("\033[1;32m➕ Agregar un producto          [1]\n");
    printf("\033[1;36m🔍 Consultar un producto        [2]\n");
    printf("\033[1;35m📋 Ver lista de productos       [3]\n");
    printf("\033[1;31m❌ Salir                        [4]\n");
    printf("\033[1;33m🗑️  Eliminar un producto         [5]\n");
    printf("\033[1;34m✏️  Editar un producto           [6]\n");
    // printf("\033[1;30m🧾 Crear Factura                [7]\n")
    printf("\033[1;34m========================================\033[0m\n");
    printf("\033[1;37mSelecciona una opción [*]: \033[0m");

    /*
    1. Cuando ingresa al if, se le pide al usuario que ingrese una opción, con
    la función `scanf. 2.scanf retorna un valor si lo que ingreso el usuario
    esta correcto.
       - Si el usuario ingresa un número válido, scanf retorna 1.
       - Si la entrada no es válida (por ejemplo, letras o caracteres
    especiales), scanf retorna 0 o un valor negativo.
    3. != 1 verifica si scanf retorna un valor distinto de 1. Si es así,
    significa que la entrada no es válida.
    */

    if (scanf("%d", &opcion) != 1) {
      printf("\n\033[1;31mEntrada no válida, ingresa de nuevo\033[0m\n");
      while (getchar() != '\n');
      /*
      getchar se usa aquí para limpiar el buffer de entrada.
      - Si el usuario ingresa algo inválido como carecteres, esos caracteres
      permanecen en el buffer de entrada.
      - El while (getchar() != '\n') este va continuar funcionando hasta
      encontrar un salto de línea (\n), asegurando que el próximo scanf reciba
      una entrada limpia.
      */
      continue;
      // continue va hacer que se salte el if
      // Hace que el programa a regresé al inicio del ciclo while principal.
    }
    getchar(); // Limpia el buffer tras leer el número que ingresó el usuario

    // Según la opción elegida por el usuario, se llama a la función
    // correspondiente
    switch (opcion) {
    case 1:
      // Llama a la función para agregar un producto
      ingresarProducto(inventario, &numProductos);
      // Guardar el inventario en el archivo después de agregar un producto
      guardarInventario("inventario.txt", inventario, numProductos);
      break;

    case 2:
      // Llama a la función para buscar productos
      buscarProducto(inventario, numProductos);
      break;

    case 3:
      // Llama a la función para listar todos los productos
      imprimirTodosLosProductos(inventario, numProductos);
      break;

    case 4:
      // Guarda el inventario antes de salir
      guardarInventario("inventario.txt", inventario, numProductos);

      // Imprime el mensaje y luego llama a la animación
      printf("\033[1;32mCerrando Sistema\033[0m");
      fflush(stdout); // Asegura que el mensaje se imprime antes de la animación
      animacionPuntos(); // Realiza la animación de puntos al lado del mensaje

      printf("\n"); // Nueva línea después de la animación
      printf("\033[1;32m============Sistema  Cerrado============\033[0m\n");
      continuar = 0;
      // Termina el ciclo porque el 'while' se ejecuta mientras 'continuar' sea
      // verdadero
      break;

    case 5:
      // Llama a la función para eliminar un producto
      eliminarProducto(inventario, &numProductos);
      // Guarda después de eliminar un producto
      guardarInventario("inventario.txt", inventario, numProductos);
      break;

    case 6:
      // Llama a la función para editar un producto
      editarProducto(inventario, numProductos);
      // Guarda después de editar
      guardarInventario("inventario.txt", inventario, numProductos);
      break;

    default:
      // Si la opción ingresada no está entre las válidas, se muestra un mensaje
      // de error y se vuelve a pedir una opción porque el while se ejecuta
      // mientras continuar sea verdadero
      printf("\n\033[1;31mOpción no válida, ingresa de nuevo\033[0m\n");
    }
  }
  return 0;
}