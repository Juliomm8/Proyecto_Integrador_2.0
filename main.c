#include <stdio.h>
#include <string.h>
#include "estructuraProducto.h" // Header que contiene la estructura de los producto en el inventario
#include "infoProductos.h"      // Header que tiene las funciones para agregar y listar productos
#include "consultarProductos.h" // Header que tiene las funciones para buscar, editar y eliminar productos
#include "validación.h"         // Header con funciones para validar entradas
#include "archivos.h"           // Header con funciones para guardar y cargar el inventario en un archivo

// Declaramos el inventario como un arreglo global de productos, para que sea mas facil de acceder desde cualquier parte del programa
struct Producto inventario[1000]; // El programa puede almacenar hasta 1000 productos
int numProductos = 0; // Variable que sirbe como contador para saber cuantos productos hay en el inventario

int main() {
    int opcion;           // Variable que sirve para saber la opción del usuario
    int continuar = 1;    // Variable que controla si el programa sigue ejecutándose

    // Carga el inventario desde el archivo 'inventario.txt' y si no encuentra el archivo, lo crea
    numProductos = cargarInventario("inventario.txt", inventario);

    // Inicia un while que muestra el menú principal hasta que el usuario elija la opcion de salir
    while (continuar) { 
        // Mendiante prints muestra el menú principal
        // Los '\033[1;3_' y son códigos de escape ANSI y estos códigos de colores ayudan a distinguir entre mensajes importantes, errores, advertencias, y opciones del programa.
        printf("\033[1;34m\n========================================\n");
        printf("          Inventario - \033[1;33mPharma+\033[0m\n");
        printf("\033[1;34m========================================\n");
        printf("\033[1;32m➕ Agregar un producto          [1]\n");
        printf("\033[1;36m🔍 Consultar un producto        [2]\n");
        printf("\033[1;35m📋 Ver lista de productos       [3]\n");
        printf("\033[1;31m❌ Salir                        [4]\n");
        printf("\033[1;33m🗑️  Eliminar un producto         [5]\n");
        printf("\033[1;34m✏️  Editar un producto           [6]\n");
        printf("\033[1;34m========================================\033[0m\n");
        printf("\033[1;37mSelecciona una opción [*]: \033[0m");

        /* 
        1. Cuando ingresa al if, se le pide al usuario que ingrese una opción, con la función `scanf.
        2.`scanf` retorna un valor si lo que ingreso el usuario esta correcto.
           - Si el usuario ingresa un número válido, `scanf` retorna 1.
           - Si la entrada no es válida (por ejemplo, letras o caracteres especiales), `scanf` retorna 0 o un valor negativo.
        3. `!= 1` verifica si `scanf` retorna un valor distinto de 1. Si es así, significa que la entrada no es válida.
        */

        if (scanf("%d", &opcion) != 1) {
            printf("\033[1;31mEntrada no válida, ingresa de nuevo . . .\033[0m\n");
            while (getchar() != '\n');
            /*
            `getchar` se usa aquí para limpiar el buffer de entrada.
            - Si el usuario ingresa algo inválido como carecteres, esos caracteres permanecen en el buffer de entrada.
            - El `while (getchar() != '\n')` este va continuar funcionando hasta encontrar un salto de línea (`\n`),
            asegurando que el próximo `scanf` reciba una entrada limpia.
            */
            continue;  
            // `continue` va hacer que se salte el if 
            //Hace que el programa a regresé al inicio del ciclo `while` principal.
