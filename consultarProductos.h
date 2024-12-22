#ifndef CONSULTARPRODUCTOS_H
#define CONSULTARPRODUCTOS_H

#include <stdio.h>
#include <string.h>
#include "estructuraProducto.h"

void buscarProducto(struct Producto inventario[], int numProductos);
void consultarProductoPorNombre(char *nombreBusqueda, struct Producto inventario[], int numProductos);
void consultarProductoPorCodigo(char *codigoBusqueda, struct Producto inventario[], int numProductos);
void eliminarProducto(struct Producto inventario[], int *numProductos);
void editarProducto(struct Producto inventario[], int numProductos);

void buscarProducto(struct Producto inventario[], int numProductos) {

    int criterio=0;

    char entrada[50];

    // Mostrar opciones al usuario
    printf("¿Desea buscar por:\n");
    printf("Nombre [1]\n");
    printf("Código [2]\n");
    printf("Seleccione una opción: ");
    scanf("%d", &criterio);
    getchar(); // Limpiar el buffer de entrada

    if (criterio == 1) { // Buscar por nombre
        printf("Ingrese el nombre del producto: ");

        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = '\0';

        consultarProductoPorNombre(entrada, inventario, numProductos);

    } else if (criterio == 2) { // Buscar por código
        printf("Ingrese el código del producto: ");

        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = '\0';

        consultarProductoPorCodigo(entrada, inventario, numProductos);

    } else {
        printf("\033[1;31m-----Opción no válida-----\033[0m\n");
    }
}

void consultarProductoPorNombre(char *nombreBusqueda, struct Producto inventario[], int numProductos) {
    int encontrado = 0; // Indicador para saber si el producto fue encontrado

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombreBusqueda) == 0) {
            
            printf("\033[1;32mProducto encontrado:\033[0m\n");
            
            printf("  Nombre: %s\n", inventario[i].nombre);
            
            printf("  Código: %s\n", inventario[i].codigo);
            
            printf("  Fabricante: %s\n", inventario[i].fabricante);
            
            printf("  Cantidad: %d\n", inventario[i].cantidad);
            
            printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio);
            
            printf("  Porcentaje de impuesto: %.2f%%\n", inventario[i].impuesto);
            
            printf("  P.V.P: %.2f\n", inventario[i].precio * (1 + inventario[i].impuesto / 100));
            
            printf("  Requiere prescripción: %s\n", inventario[i].requierePrescripcion ? "Sí" : "No");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\033[1;31mNo se encontró ningún producto con ese nombre\033[0m\n");
    }
}

void consultarProductoPorCodigo(char *codigoBusqueda, struct Producto inventario[], int numProductos) {
    int encontrado = 0;

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].codigo, codigoBusqueda) == 0) { // Comparar códigos
            printf("\033[1;32mProducto encontrado:\033[0m\n");

            // Imprimir información del producto (similar a la función anterior)
            printf("  Nombre: %s\n", inventario[i].nombre);

            printf("  Código: %s\n", inventario[i].codigo);

            printf("  Fabricante: %s\n", inventario[i].fabricante);

            printf("  Cantidad: %d\n", inventario[i].cantidad);

            printf("  Precio (sin impuestos): %.2f\n", inventario[i].precio);

            printf("  Porcentaje de impuesto: %.2f%%\n", inventario[i].impuesto);

            printf("  P.V.P: %.2f\n", inventario[i].precio * (1 + inventario[i].impuesto / 100));

            printf("  Requiere prescripción: %s\n", inventario[i].requierePrescripcion ? "\033[1;31mSi\033[0m" : "\033[1;32mNo\033[0m");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
    }
}

void eliminarProducto(struct Producto inventario[], int *numProductos) {
    char entrada[50];
    printf("Ingrese el código del producto a eliminar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(inventario[i].codigo, entrada) == 0) {
            // Desplazar los elementos siguientes para eliminar el producto
            for (int j = i; j < *numProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            (*numProductos)--; // Reducir el contador de productos

            printf("\033[1;32m-----Producto eliminado con éxito-----\033[0m\n");

            return;
        }
    }

    printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
}

void editarProducto(struct Producto inventario[], int numProductos) {
    char entrada[50];

    printf("Ingrese el código del producto a editar: ");

    fgets(entrada, sizeof(entrada), stdin);

    entrada[strcspn(entrada, "\n")] = '\0';

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].codigo, entrada) == 0) {

            printf("\033[1;32m-----Editando Producto-----\033[0m\n");

            // Solicitar nuevos datos del producto
            printf("Nuevo nombre para [%s]: ", inventario[i].nombre);
            fgets(inventario[i].nombre, sizeof(inventario[i].nombre), stdin);
            inventario[i].nombre[strcspn(inventario[i].nombre, "\n")] = '\0';

            printf("Nuevo fabricante para [%s]: ", inventario[i].fabricante);
            fgets(inventario[i].fabricante, sizeof(inventario[i].fabricante), stdin);
            inventario[i].fabricante[strcspn(inventario[i].fabricante, "\n")] = '\0';

            printf("Nuevo N° unidades para [%d]: ", inventario[i].cantidad);
            scanf("%d", &inventario[i].cantidad);
            getchar();

            printf("Nuevo precio (sin impuestos) para [%.2f]: ", inventario[i].precio);
            scanf("%f", &inventario[i].precio);
            getchar();

            printf("Nuevo Impuesto para [%.2f%%]: ", inventario[i].impuesto);
            scanf("%f", &inventario[i].impuesto);
            getchar();

            printf("\033[1;31m¿Requiere prescripción médica?\033[0m\n");
            printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
            scanf("%d", &inventario[i].requierePrescripcion);
            getchar();

            printf("\033[1;32m-----Producto editado con éxito-----\033[0m\n");
            return;
        }
    }

    printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
}

#endif // CONSULTARPRODUCTOS_H
