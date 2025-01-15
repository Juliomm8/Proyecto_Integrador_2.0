#ifndef VALIDACION_H
#define VALIDACION_H

#include <stdio.h>
#include <string.h>
#include "estructuraProducto.h"
#include "animacion.h"

int validarNombreProducto(char *cadena);
int validarCodigoProducto(char *codigo);
int validarCantidadProducto(int cantidad);
int esNombreUnico(char *nombre, struct Producto inventario[], int numProductos);
int esCodigoUnico(char *codigo, struct Producto inventario[], int numProductos);
void ingresarCodigoValido(char *codigo, size_t tam, struct Producto inventario[], int numProductos);

// Esta función valida que el nombre del producto ingresado sea válido.
// Un nombre válido solo puede contener:
// - Letras mayúsculas ('A' a 'Z')
// - Letras minúsculas ('a' a 'z')
// - Dígitos numéricos ('0' a '9')
// - Espacios (' ')
int validarNombreProducto(char *cadena) {
    
    // Itera a través de cada carácter de la cadena hasta llegar al carácter nulo ('\0'), que indica el final del texto.
    for (int i = 0; cadena[i] != '\0'; i++) {
        
        // Verifica si el carácter actual no es válido.
        // Se utiliza un condicional para comprobar que el carácter actual no pertenece
        // a ninguno de los rangos permitidos (letras mayúsculas, minúsculas, números o espacios).
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') || 
              (cadena[i] >= 'a' && cadena[i] <= 'z') || 
              (cadena[i] >= '0' && cadena[i] <= '9') || 
              cadena[i] == ' ')) {
            return 0; // Si el carácter no es válido, retornar 0 (falso).
        }
    }
    
    // Si se iteró toda la cadena sin encontrar caracteres inválidos, retornar 1 (verdadero).
    return 1;
}

// Esta función valida que el código del producto ingresado sea válido.
// Un código válido solo puede contener dígitos numéricos (del '0' al '9').
int validarCodigoProducto(char *codigo) {
    
    // Iterar a través de cada carácter de la cadena hasta llegar al carácter nulo ('\0'),
    // que indica el final del texto.
    for (int i = 0; codigo[i] != '\0'; i++) {
        
        // Verificar si el carácter actual no es un dígito numérico.
        // Se comprueba que el carácter no está en el rango de '0' a '9'.
        if (!(codigo[i] >= '0' && codigo[i] <= '9')) {
            
            // Si el carácter no es un número, retornar 0 (falso).
            return 0;
        }
    }
    return 1;
}

// Verifica que la cantidad de producto sea un valor positivo
int validarCantidadProducto(int cantidad) {
    return cantidad > 0;
}

int esNombreUnico(char *nombre, struct Producto inventario[], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            return 0; // No es único
        }
    }
    
    // Si se iteró toda la cadena sin encontrar caracteres no numéricos, retornar 1 (verdadero).
    return 1; 
}

// Esta función verifica si el código ingresado es único.
// Compara el código proporcionado con los códigos existentes en el inventario.
// Retorna 1 (verdadero) si el código es único, o 0 (falso) si ya existe.
int esCodigoUnico(char *codigo, struct Producto inventario[], int numProductos) {
     // Iterar a través de todos los productos almacenados en el inventario.
    for (int i = 0; i < numProductos; i++) {

        // Comparar el código actual del inventario con el código ingresado.
        // Se utiliza la función `strcmp` para comparar cadenas de texto.
        // Si ambas cadenas son iguales, `strcmp` retorna 0.
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            
            // Si se encuentra una coincidencia, retornar 0 (falso),
            // indicando que el código no es único.
            return 0;
        }
    }
    
    // Si no se encontró ninguna coincidencia en el inventario,
    // retornar 1 (verdadero), indicando que el código es único.
    return 1; 
}

// Esta función solicita al usuario que ingrese un código válido para un producto.
// El código ingresado debe cumplir dos condiciones:
// 1. Debe contener solo caracteres numéricos.
// 2. Debe ser único, es decir, no debe estar repetido en el inventario.
void ingresarCodigoValido(char *codigo, size_t tam, struct Producto inventario[], int numProductos) {
    int valido = 0; // Indicador para determinar si el código es válido
    
    do {
        printf("Ingresa el código del producto: ");
        fgets(codigo, tam, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';
        
        // Validar si el código es válido y único.
        if (strlen(codigo) == 0 || !validarCodigoProducto(codigo)) {
            // Caso 1: Si el código está vacío o contiene caracteres no válidos.
            printf("\033[1;31mEl código contiene caracteres no válidos o está vacío, ingresa de nuevo.\033[0m\n");
        } else if (!esCodigoUnico(codigo, inventario, numProductos)) {
            // Caso 2: Si el código ya existe en el inventario.
            printf("\033[1;31mEl código ya está en uso, ingresa otro.\033[0m\n");
        } else {
            // Si el código cumple todas las condiciones, se marca como válido.
            valido = 1;
        }
    } while (!valido); // Repetir el proceso mientras el código no sea válido.
}

#endif // VALIDACION_H