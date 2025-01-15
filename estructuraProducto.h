#ifndef ESTRUCTURA_PRODUCTO_H
#define ESTRUCTURA_PRODUCTO_H

#include <stdio.h>
#include <string.h>

// Es la estructura que contiene los datos de un producto
struct Producto {
    char nombre[50];           // Nombre del producto
    char codigo[20];           // Código único del producto
    char fabricante[50];       // Nombre del fabricante
    int cantidad;              // Cantidad disponible en inventario
    float precio;              // Precio sin impuestos
    float impuesto;            // Porcentaje de impuesto aplicado
    int requierePrescripcion;  // 1 si requiere prescripción médica, 0 si no
};

#endif // ESTRUCTURA_PRODUCTO_H