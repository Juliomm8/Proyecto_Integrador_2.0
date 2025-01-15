#include <stdio.h>
#include <unistd.h> // Para usleep (microsegundos)

// Función para mostrar animación de puntos
void animacionPuntos() {
    int duracion = 2000000; // Duración total de 2 segundos (en microsegundos)
    int intervalo = 300000; // Intervalo entre cada animación (300 ms)
    int tiempoTranscurrido = 0;

    while (tiempoTranscurrido < duracion) {
        printf("\033[1;32m."); // Muestra un punto al final del mensaje
        //se usa fflush para forzar la impresión inmediata de los puntos en las animaciones
        fflush(stdout);  // ayuda a forzar a mostrar el contenido en pantalla
        usleep(intervalo);
        //La función usleep en C se utiliza para pausar la ejecución de un programa durante un período de tiempo especificado en microsegundos (1 segundo = 1,000,000 microsegundos), es útil para introducir retrasos o animaciones en aplicaciones.

        printf("\033[1;32m."); // Añade el segundo punto
        fflush(stdout);
        usleep(intervalo);

        printf("\033[1;32m."); // Añade el tercer punto
        fflush(stdout);
        usleep(intervalo);

        printf("\b\b\b   \b\b\b"); // Borra los tres puntos y reinicia, se conoce como "backspace"
        fflush(stdout);

        tiempoTranscurrido += intervalo * 3; // Aumenta el tiempo transcurrido
    }

    printf("\033[1;32m..."); // Deja los tres puntos al final
    fflush(stdout);
    printf("\n"); // Nueva línea al final
}