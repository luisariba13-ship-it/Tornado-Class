#include <stdio.h>

#define TAM 100

struct Simbolo {
    int numero;
    char tipo;
    int posicion;
};

struct Simbolo tabla[TAM];
int memoria[TAM], flags[TAM];
int contador = 0, total = 0, error = 0;

int buscar(int numero, char tipo) {
    int i;
    for (i = 0; i < total; i++) {
        if (tabla[i].numero == numero && tabla[i].tipo == tipo)
            return tabla[i].posicion;
    }
    return -1;
}

void leerEstado() {
    FILE *archivo = fopen("estado_pasada.txt", "r");
    int i, tipo;
    if (archivo == NULL) {
        puts("Ejecuta primero primera_pasada.c");
        error = 1;
        return;
    }
    if (fscanf(archivo, "%d %d", &contador, &total) != 2 ||
        contador < 0 || contador > TAM || total < 0 || total > TAM) {
        error = 1;
    }
    for (i = 0; i < TAM && !error; i++) {
        if (fscanf(archivo, "%d %d", &memoria[i], &flags[i]) != 2)
            error = 1;
    }
    for (i = 0; i < total && !error; i++) {
        if (fscanf(archivo, "%d %d %d",
                   &tabla[i].numero, &tipo, &tabla[i].posicion) != 3)
            error = 1;
        else
            tabla[i].tipo = (char)tipo;
    }
    fclose(archivo);
    if (error) puts("Error al leer estado_pasada.txt");
}

void segundaPasada() {
    int i, linea, posicion, operacion;
    for (i = 0; i < contador; i++) {
        if (flags[i] != -1) {
            linea = flags[i];
            posicion = buscar(linea, 'L');
            operacion = memoria[i] / 100;
            if (posicion == -1 || operacion < 40 || operacion > 42) {
                printf("Error en salto de la linea %d%c", linea, 10);
                error = 1;
            } else {
                memoria[i] = operacion * 100 + posicion;
                flags[i] = -1;
            }
        }
    }
}

void generarArchivo() {
    FILE *archivo = fopen("programa.sml", "w");
    int i;
    if (archivo == NULL) {
        puts("No se pudo crear programa.sml");
        error = 1;
        return;
    }
    for (i = 0; i < TAM; i++)
        fprintf(archivo, "%+05d%c", memoria[i], 10);
    fclose(archivo);
    puts("Archivo programa.sml generado");
}

int main() {
    leerEstado();
    if (error) return 1;
    segundaPasada();
    if (error) return 1;
    generarArchivo();
    return error ? 1 : 0;
}
