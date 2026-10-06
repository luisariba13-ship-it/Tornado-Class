#include <stdio.h>

int memory[100];

int accumulator = 0;
int instructionCounter = 0;
int instructionRegister = 0;
int operationCode = 0;
int operand = 0;


void cargar_programa()
{
    int posicion = 0;
    int valor = 0;

    printf("*** Bienvenido a Simpletron! ***\n");
    printf("*** Introduzca su programa una instruccion ***\n");
    printf("*** (o palabra de datos) a la vez en la linea ***\n");
    printf("*** de texto de entrada. Yo indicare el numero ***\n");
    printf("*** de posicion y una interrogacion (?). Usted ***\n");
    printf("*** tecleara entonces la palabra para esa ***\n");
    printf("*** posicion. Introduzca 9999 para dejar de ***\n");
    printf("*** introducir su programa. ***\n");

    while (posicion < 100)
    {
        printf("%02d ? ", posicion);
        scanf("%d", &valor);

        if (valor == 9999)
        {
            break;
        }

        if (valor >= -9999 && valor <= 9998)
        {
            memory[posicion] = valor;
            posicion++;
        }
        else
        {
            printf("Valor invalido\n");
            printf("Introduzca un valor entre -9999 y +9998\n");
        }
    }

    printf("\n");
    printf("Se termino de cargar el programa\n");
    printf("Comienza la ejecucion del programa\n");
    printf("\n");
}


void ejecutar_programa()
{
    int ejecutando = 1;
    int valor = 0;
    int resultado = 0;

    while (ejecutando == 1)
    {
        if (instructionCounter < 0 || instructionCounter > 99)
        {
            printf("Contador de instrucciones fuera de memoria\n");
            printf("La ejecucion de Simpletron termino anormalmente\n");

            ejecutando = 0;
        }
        else
        {
            instructionRegister = memory[instructionCounter];

            if (instructionRegister < 0)
            {
                printf("Instruccion invalida\n");
                printf("La ejecucion de Simpletron termino anormalmente\n");

                ejecutando = 0;
            }
            else
            {
                operationCode = instructionRegister / 100;
                operand = instructionRegister % 100;

                if (operationCode == 10)
                {
                    printf("? ");
                    scanf("%d", &valor);

                    if (valor >= -9999 && valor <= 9998)
                    {
                        memory[operand] = valor;
                        instructionCounter++;
                    }
                    else
                    {
                        printf("Valor fuera del rango permitido\n");
                        printf("La ejecucion de Simpletron termino anormalmente\n");

                        ejecutando = 0;
                    }
                }

                else if (operationCode == 11)
                {
                    printf("%d\n", memory[operand]);

                    instructionCounter++;
                }

                else if (operationCode == 20)
                {
                    accumulator = memory[operand];

                    instructionCounter++;
                }

                else if (operationCode == 21)
                {
                    memory[operand] = accumulator;

                    instructionCounter++;
                }

                else if (operationCode == 30)
                {
                    resultado = accumulator + memory[operand];

                    if (resultado > 9999 || resultado < -9999)
                    {
                        printf("Desbordamiento del acumulador\n");
                        printf("La ejecucion de Simpletron termino anormalmente\n");

                        ejecutando = 0;
                    }
                    else
                    {
                        accumulator = resultado;
                        instructionCounter++;
                    }
                }

                else if (operationCode == 31)
                {
                    resultado = accumulator - memory[operand];

                    if (resultado > 9999 || resultado < -9999)
                    {
                        printf("Desbordamiento del acumulador\n");
                        printf("La ejecucion de Simpletron termino anormalmente\n");

                        ejecutando = 0;
                    }
                    else
                    {
                        accumulator = resultado;
                        instructionCounter++;
                    }
                }

                else if (operationCode == 32)
                {
                    if (memory[operand] == 0)
                    {
                        printf("Intento de dividir entre cero\n");
                        printf("La ejecucion de Simpletron termino anormalmente\n");

                        ejecutando = 0;
                    }
                    else
                    {
                        resultado = accumulator / memory[operand];

                        if (resultado > 9999 || resultado < -9999)
                        {
                            printf("Desbordamiento del acumulador\n");
                            printf("La ejecucion de Simpletron termino anormalmente\n");

                            ejecutando = 0;
                        }
                        else
                        {
                            accumulator = resultado;
                            instructionCounter++;
                        }
                    }
                }

                else if (operationCode == 33)
                {
                    resultado = accumulator * memory[operand];

                    if (resultado > 9999 || resultado < -9999)
                    {
                        printf("Desbordamiento del acumulador\n");
                        printf("La ejecucion de Simpletron termino anormalmente\n");

                        ejecutando = 0;
                    }
                    else
                    {
                        accumulator = resultado;
                        instructionCounter++;
                    }
                }

                else if (operationCode == 40)
                {
                    instructionCounter = operand;
                }

                else if (operationCode == 41)
                {
                    if (accumulator < 0)
                    {
                        instructionCounter = operand;
                    }
                    else
                    {
                        instructionCounter++;
                    }
                }

                else if (operationCode == 42)
                {
                    if (accumulator == 0)
                    {
                        instructionCounter = operand;
                    }
                    else
                    {
                        instructionCounter++;
                    }
                }

                else if (operationCode == 43)
                {
                    printf("\n");
                    printf("Termino la ejecucion de Simpletron\n");

                    ejecutando = 0;
                }

                else
                {
                    printf("Codigo de operacion invalido\n");
                    printf("La ejecucion de Simpletron termino anormalmente\n");

                    ejecutando = 0;
                }
            }
        }
    }
}


void vaciado_memoria()
{
    int fila = 0;
    int columna = 0;
    int posicion = 0;

    printf("\n");
    printf("REGISTROS:\n");
    printf("accumulator:          %+05d\n", accumulator);
    printf("instructionCounter:   %02d\n", instructionCounter);
    printf("instructionRegister:  %+05d\n", instructionRegister);
    printf("operationCode:        %02d\n", operationCode);
    printf("operand:              %02d\n", operand);

    printf("\n");
    printf("MEMORIA\n");
    printf("\n");

    printf("       0      1      2      3      4      5      6      7      8      9\n");

    while (fila < 10)
    {
        printf("%d ", fila);

        columna = 0;

        while (columna < 10)
        {
            posicion = fila * 10 + columna;

            printf("%+05d ", memory[posicion]);

            columna++;
        }

        printf("\n");

        fila++;
    }
}


int main()
{
    int i = 0;

    while (i < 100)
    {
        memory[i] = 0;
        i++;
    }

    cargar_programa();

    ejecutar_programa();

    vaciado_memoria();

    return 0;
}