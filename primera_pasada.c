#include <stdio.h>
#include <string.h>

#define TAM 100
#define MAXSIM 100
#define MAXTOK 100

struct Simbolo {
    int numero;
    char tipo;
    int posicion;
};

struct Simbolo tabla[MAXSIM];
int memoria[TAM], flags[TAM];
int total = 0, contador = 0, datos = 99, error = 0;
char separadores[] = {' ', '\t', '\r', 10, 0};

int convertir(char texto[]) {
    int i = 0, signo = 1, numero = 0;
    if (texto[0] == '-') { signo = -1; i++; }
    if (texto[i] == 0) { error = 1; return 0; }
    while (texto[i] != 0) {
        if (texto[i] < '0' || texto[i] > '9') { error = 1; return 0; }
        numero = numero * 10 + texto[i] - '0';
        i++;
    }
    return numero * signo;
}

int buscar(int numero, char tipo) {
    int i;
    for (i = 0; i < total; i++)
        if (tabla[i].numero == numero && tabla[i].tipo == tipo)
            return tabla[i].posicion;
    return -1;
}

void guardar(int numero, char tipo, int posicion) {
    if (total >= MAXSIM) { error = 1; return; }
    if (buscar(numero, tipo) != -1) { error = 1; return; }
    tabla[total].numero = numero;
    tabla[total].tipo = tipo;
    tabla[total].posicion = posicion;
    total++;
}

int reservar() {
    int posicion;
    if (datos <= contador) { error = 1; return 0; }
    posicion = datos;
    datos--;
    return posicion;
}

int ubicacion(char texto[]) {
    int numero, posicion;
    char tipo;
    if (strlen(texto) == 1 &&
        ((texto[0] >= 'a' && texto[0] <= 'z') ||
         (texto[0] >= 'A' && texto[0] <= 'Z'))) {
        numero = texto[0];
        tipo = 'V';
    } else {
        numero = convertir(texto);
        tipo = 'C';
        if (numero < -9999 || numero > 9999) error = 1;
    }
    if (error) return 0;
    posicion = buscar(numero, tipo);
    if (posicion != -1) return posicion;
    posicion = reservar();
    if (error) return 0;
    guardar(numero, tipo, posicion);
    if (tipo == 'C') memoria[posicion] = numero;
    return posicion;
}

void generar(int codigo, int posicion) {
    if (contador > datos || contador >= TAM || error) { error = 1; return; }
    memoria[contador] = codigo * 100 + posicion;
    contador++;
}

void salto(int codigo, int linea) {
    int posicion = buscar(linea, 'L');
    if (posicion == -1) {
        generar(codigo, 0);
        if (!error) flags[contador - 1] = linea;
    } else generar(codigo, posicion);
}

int prioridad(char operador) {
    if (operador == '*' || operador == '/') return 2;
    if (operador == '+' || operador == '-') return 1;
    return 0;
}

int esOperador(char texto[]) {
    return strlen(texto) == 1 &&
           (texto[0] == '+' || texto[0] == '-' ||
            texto[0] == '*' || texto[0] == '/');
}

void let(char destino[], char expresion[]) {
    char copia[300], salida[MAXTOK][30], operadores[MAXTOK];
    int pila[MAXTOK], ns = 0, no = 0, np = 0, i, a, b, resultado;
    int direccion = ubicacion(destino);
    char *parte;
    if (error) return;
    strcpy(copia, expresion);
    parte = strtok(copia, separadores);
    while (parte != NULL && !error) {
        if (ns >= MAXTOK - 1 || no >= MAXTOK - 1) { error = 1; break; }
        if (strcmp(parte, "(") == 0) operadores[no++] = '(';
        else if (strcmp(parte, ")") == 0) {
            while (no > 0 && operadores[no - 1] != '(') {
                salida[ns][0] = operadores[--no];
                salida[ns++][1] = 0;
            }
            if (no == 0) error = 1;
            else no--;
        } else if (esOperador(parte)) {
            while (no > 0 && operadores[no - 1] != '(' &&
                   prioridad(operadores[no - 1]) >= prioridad(parte[0])) {
                salida[ns][0] = operadores[--no];
                salida[ns++][1] = 0;
            }
            operadores[no++] = parte[0];
        } else {
            if (strlen(parte) >= 30) { error = 1; break; }
            strcpy(salida[ns++], parte);
        }
        parte = strtok(NULL, separadores);
    }
    while (no > 0 && !error) {
        if (operadores[no - 1] == '(') { error = 1; break; }
        salida[ns][0] = operadores[--no];
        salida[ns++][1] = 0;
    }
    for (i = 0; i < ns && !error; i++) {
        if (esOperador(salida[i])) {
            int codigo;
            if (np < 2) { error = 1; break; }
            b = pila[--np];
            a = pila[--np];
            codigo = 30;
            if (salida[i][0] == '-') codigo = 31;
            if (salida[i][0] == '/') codigo = 32;
            if (salida[i][0] == '*') codigo = 33;
            generar(20, a);
            generar(codigo, b);
            resultado = reservar();
            generar(21, resultado);
            pila[np++] = resultado;
        } else pila[np++] = ubicacion(salida[i]);
    }
    if (np != 1) error = 1;
    if (!error) {
        generar(20, pila[0]);
        generar(21, direccion);
    }
}

void condicion(char izquierda[], char operador[], char derecha[], int linea) {
    int a = ubicacion(izquierda), b = ubicacion(derecha);
    if (error) return;
    if (strcmp(operador, ">") == 0 || strcmp(operador, "<=") == 0) {
        generar(20, b);
        generar(31, a);
    } else {
        generar(20, a);
        generar(31, b);
    }
    if (strcmp(operador, "==") == 0) salto(42, linea);
    else if (strcmp(operador, "<") == 0 || strcmp(operador, ">") == 0)
        salto(41, linea);
    else if (strcmp(operador, "<=") == 0 || strcmp(operador, ">=") == 0) {
        salto(41, linea);
        salto(42, linea);
    } else if (strcmp(operador, "!=") == 0) {
        generar(42, contador + 2);
        salto(40, linea);
    } else error = 1;
}

void crearArchivo() {
    FILE *archivo = fopen("programa.simple", "r");
    if (archivo != NULL) { fclose(archivo); return; }
    archivo = fopen("programa.simple", "w");
    if (archivo == NULL) { error = 1; return; }
    fprintf(archivo, "10 rem Programa de prueba%c", 10);
    fprintf(archivo, "20 input x%c", 10);
    fprintf(archivo, "30 let y = x + 1%c", 10);
    fprintf(archivo, "40 if y > x goto 60%c", 10);
    fprintf(archivo, "50 goto 70%c", 10);
    fprintf(archivo, "60 print y%c", 10);
    fprintf(archivo, "70 end%c", 10);
    fclose(archivo);
}

void primeraPasada() {
    FILE *archivo = fopen("programa.simple", "r");
    char linea[300], expresion[300], destino[30];
    char izq[30], op[10], der[30];
    char *parte, *comando;
    int numero, posicion, anterior = -1;
    if (archivo == NULL) { error = 1; return; }
    while (fgets(linea, sizeof(linea), archivo) != NULL && !error) {
        parte = strtok(linea, separadores);
        if (parte == NULL) continue;
        numero = convertir(parte);
        if (error || numero <= anterior) { error = 1; break; }
        anterior = numero;
        guardar(numero, 'L', contador);
        comando = strtok(NULL, separadores);
        if (comando == NULL) { error = 1; break; }
        if (strcmp(comando, "rem") == 0) continue;
        if (strcmp(comando, "input") == 0 || strcmp(comando, "print") == 0) {
            parte = strtok(NULL, separadores);
            if (parte == NULL) { error = 1; break; }
            posicion = ubicacion(parte);
            if (strcmp(comando, "input") == 0) generar(10, posicion);
            else generar(11, posicion);
        } else if (strcmp(comando, "goto") == 0) {
            parte = strtok(NULL, separadores);
            if (parte == NULL) { error = 1; break; }
            numero = convertir(parte);
            if (!error) salto(40, numero);
        } else if (strcmp(comando, "end") == 0) generar(43, 0);
        else if (strcmp(comando, "let") == 0) {
            parte = strtok(NULL, separadores);
            if (parte == NULL || strlen(parte) >= 30) { error = 1; break; }
            strcpy(destino, parte);
            parte = strtok(NULL, separadores);
            if (parte == NULL || strcmp(parte, "=") != 0) { error = 1; break; }
            expresion[0] = 0;
            parte = strtok(NULL, separadores);
            while (parte != NULL) {
                if (strlen(expresion) + strlen(parte) + 2 >= 300) { error = 1; break; }
                strcat(expresion, parte);
                strcat(expresion, " ");
                parte = strtok(NULL, separadores);
            }
            if (expresion[0] == 0) error = 1;
            if (!error) let(destino, expresion);
        } else if (strcmp(comando, "if") == 0) {
            parte = strtok(NULL, separadores);
            if (parte == NULL || strlen(parte) >= 30) { error = 1; break; }
            strcpy(izq, parte);
            parte = strtok(NULL, separadores);
            if (parte == NULL || strlen(parte) >= 10) { error = 1; break; }
            strcpy(op, parte);
            parte = strtok(NULL, separadores);
            if (parte == NULL || strlen(parte) >= 30) { error = 1; break; }
            strcpy(der, parte);
            parte = strtok(NULL, separadores);
            if (parte == NULL || strcmp(parte, "goto") != 0) { error = 1; break; }
            parte = strtok(NULL, separadores);
            if (parte == NULL) { error = 1; break; }
            numero = convertir(parte);
            if (!error) condicion(izq, op, der, numero);
        } else error = 1;
    }
    fclose(archivo);
}

void mostrar() {
    int i;
    puts("INSTRUCCIONES SML");
    for (i = 0; i < contador; i++) {
        printf("%02d %+05d", i, memoria[i]);
        if (flags[i] != -1) printf(" Pendiente: %d", flags[i]);
        putchar(10);
    }
    puts("TABLA DE SIMBOLOS");
    for (i = 0; i < total; i++) {
        if (tabla[i].tipo == 'V')
            printf("%c %c %02d%c", tabla[i].numero, tabla[i].tipo, tabla[i].posicion, 10);
        else
            printf("%d %c %02d%c", tabla[i].numero, tabla[i].tipo, tabla[i].posicion, 10);
    }
}

void generarArchivo() {
    FILE *archivo = fopen("primera_pasada.sml", "w");
    int i;
    if (archivo == NULL) { puts("No se pudo crear el archivo SML"); return; }
    for (i = 0; i < contador; i++) fprintf(archivo, "%+05d%c", memoria[i], 10);
    fclose(archivo);
    puts("Archivo primera_pasada.sml generado");
}

int main() {
    int i;
    for (i = 0; i < TAM; i++) flags[i] = -1;
    crearArchivo();
    if (!error) primeraPasada();
    if (error) { puts("Error en el programa Simple o memoria llena"); return 1; }
    mostrar();
    generarArchivo();
    return 0;
}
