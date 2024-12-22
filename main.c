#include <stdio.h>
#include <string.h>
#include "estructuraProducto.h"
#include "infoProductos.h"
#include "consultarProductos.h"
#include "validación.h"

struct Producto inventario[1000];
int numProductos = 0; // Contador de productos

int main() {
    int opcion;
    int continuar = 1;

    while (continuar) {
        // Mostrar menú principal
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

        //Leer y validar entrada del usuario
        if (scanf("%d", &opcion) != 1) {
            printf("\033[1;31mEntrada no válida, ingresa de nuevo . . .\033[0m\n");
            while (getchar() != '\n'); //Limpiar el buffer de entrada
            continue;
        }
        getchar(); // Limpiar el buffer

        //Selección de la opción del menú principal
        switch (opcion) {
            case 1:
                 // Llamar a la función para agregar un producto
                ingresarProducto(inventario, &numProductos);
                break;
            case 2:
                // Llamar a la función para buscar un producto
                buscarProducto(inventario, numProductos);
                break;
            case 3:
                // Llamar a la función para listar todos los productos
                imprimirTodosLosProductos(inventario, numProductos);
                break;    
            case 4:
                // Salir del sistema
                printf("\033[1;32mSistema cerrado . . .\033[0m\n");
                continuar = 0;
                break;
            case 5:
                // Llamar a la función para eliminar un producto
                eliminarProducto(inventario, &numProductos);
                break;
            case 6:
                // Llamar a la función para editar un producto
                editarProducto(inventario, numProductos);
                break;
            default:
                // Manejo de opciones inválidas
                printf("\033[1;31mOpción no válida, ingresa de nuevo . . .\033[0m\n");
        }
    }
    return 0;
}
