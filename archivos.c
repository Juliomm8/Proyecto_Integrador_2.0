#include "archivos.h" 

// Funcion que sirve para guardar inventario en el archivo 'inventario.txt'
void guardarInventario(const char *inventarioArchivo, struct Producto inventario[], int numProductos) {

    // Abre el archivo en modo de escritura ("w")
    FILE *archivo = fopen(inventarioArchivo, "w"); 

    // El 'if' verifica si el archivo se pudo abrir, si no se pudo abrir, se muestra un mensaje de error
    if (!archivo) {  // Si fopen devuelve NULL, significa que no pudo abrir el archivo
        perror("Error al abrir el archivo para guardar");
        return; // Termina la función
    }

     // El for recorre hasta el numero de productos y luego escribe en el archivo
    for (int i = 0; i < numProductos; i++) {
        // Escribir cada producto como una línea en el archivo
        // Los campos están separados por el carácter '|'
        fprintf(archivo, "%s|%s|%s|%d|%.2f|%.2f|%d\n",
                inventario[i].nombre,               // Nombre del producto
                inventario[i].codigo,               // Código único del producto
                inventario[i].fabricante,           // Nombre del fabricante
                inventario[i].cantidad,             // Cantidad disponible en el inventario
                inventario[i].precio,               // Precio sin impuestos
                inventario[i].impuesto,             // Porcentaje de impuesto
                inventario[i].requierePrescripcion);// Si requiere receta médica (1 para sí, 0 para no)
    }

    // Cierra el archivo después de escribir todos los productos
    fclose(archivo);
    // Muestra un mensaje indicando que el inventario se guardó con éxito
    printf("\033[1;32mInventario guardado exitosamente en %s.\033[0m\n", inventarioArchivo);
}

// Carga el inventario desde el archivo llamado 'inventario.txt'
int cargarInventario(const char *inventarioArchivo, struct Producto inventario[]) {
    // Abre el archivo en modo de lectura "r"
    FILE *archivo = fopen(inventarioArchivo, "r"); 

    // Verificar si el archivo se pudo abrir
    if (!archivo) { // Si fopen devuelve NULL, significa que no pudo abrir el archivo
        // perror imprime el mensaje "No se encontró un archivo..." junto con el error
        perror("No se encontró un archivo de inventario existente. Se creará uno nuevo.");
        return 0;  // Si el archivo no existe o no se puede abrir, retorna 0 
    }

    int numProductos = 0; // Inicializar el contador de productos cargados

    // Lee el archivo línea por línea, separando los campos por el carácter '|'
    // fscanf devuelve el número de elementos leídos con éxito (esperamos leer 7 campos por línea)
    while (fscanf(archivo, "%50[^|]|%20[^|]|%50[^|]|%d|%f|%f|%d\n",
                  inventario[numProductos].nombre,
                  inventario[numProductos].codigo,
                  inventario[numProductos].fabricante,
                  &inventario[numProductos].cantidad,
                  &inventario[numProductos].precio,
                  &inventario[numProductos].impuesto,
                  &inventario[numProductos].requierePrescripcion) == 7) {
        // Verifica que fscanf haya leído exactamente 7 campos de una línea
        numProductos++; // Incrementa el contador de productos cargados
    }

    // Cierra el archivo después de leer todo el contenido
    fclose(archivo);
    // Imprime un mensaje indicando que el inventario se cargó con éxito
    printf("\033[1;32mInventario cargado exitosamente desde %s.\033[0m\n", inventarioArchivo);

    return numProductos; // Retornar la cantidad de productos cargados
}
