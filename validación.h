#ifndef VALIDACION_H
#define VALIDACION_H

#include <stdio.h>
#include <string.h>
#include "estructuraProducto.h"


int validarNombreProducto(char *cadena);
int validarCodigoProducto(char *codigo);
int validarCantidadProducto(int cantidad);
int esNombreUnico(char *nombre, struct Producto inventario[], int numProductos);
int esCodigoUnico(char *codigo, struct Producto inventario[], int numProductos);
void ingresarCodigoValido(char *codigo, size_t tam, struct Producto inventario[], int numProductos);

// Valida que el nombre del producto solo contenga caracteres alfabéticos, numéricos y espacios
int validarNombreProducto(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        // Verifica si el carácter actual no es válido
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') || 
              (cadena[i] >= 'a' && cadena[i] <= 'z') || 
              (cadena[i] >= '0' && cadena[i] <= '9') || 
              cadena[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}

// Valida que el código del producto solo contenga dígitos numéricos
int validarCodigoProducto(char *codigo) {
    for (int i = 0; codigo[i] != '\0'; i++) {
        if (!(codigo[i] >= '0' && codigo[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

// Verifica que la cantidad de producto sea un valor positivo
int validarCantidadProducto(int cantidad) {
    return cantidad > 0;
}

// Comprueba si el nombre del producto es único comparándolo con los nombres existentes
int esNombreUnico(char *nombre, struct Producto inventario[], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            return 0; // No es único
        }
    }
    return 1; // Es único
}

// Comprueba si el código del producto es único comparándolo con los códigos existentes
int esCodigoUnico(char *codigo, struct Producto inventario[], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            return 0; // No es único
        }
    }
    return 1; // Es único
}

// Solicita al usuario que ingrese un código válido
void ingresarCodigoValido(char *codigo, size_t tam, struct Producto inventario[], int numProductos) {
    int valido = 0; // Indicador para determinar si el código es válido
    do {
        printf("Ingresa el código del producto: ");
        fgets(codigo, tam, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        // Validar si el código está vacío o contiene caracteres no válidos
            if (strlen(codigo) == 0 || !validarCodigoProducto(codigo)) {
                printf("\033[1;31mEl código contiene caracteres no válidos o está vacío, ingresa de nuevo.\033[0m\n");
            } else if (!esCodigoUnico(codigo, inventario, numProductos)) {
                printf("\033[1;31mEl código ya está en uso, ingresa otro.\033[0m\n");
            } else {
                valido = 1; // El código es válido y único
            }
        } while (!valido);
}

#endif // VALIDACION_H
