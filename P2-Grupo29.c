#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"
#include "alumno.h"

int main()
{
    int opcion = -1, check_resp = 0, resp = 0, exito;
    int LSO_alta_Max;
    LSO listaUsada;
    initLSO(&listaUsada);

    while (opcion != 0)
    {
        system("cls");
        printf("\n # # # # # # #   M E N U   # # # # # # #");
        printf("\n - - - - - - - - - - - - - - - - - - - - ");
        printf("\n  [1]   Comparar estructuras.");
        printf("\n  [2]   Mostrar LSO.");
        printf("\n  [3]   Mostrar LIBT.");
        printf("\n  [4]   Mostrar ABB.");
        printf("\n - - - - - - - - - - - - - - - - - - - - ");
        printf("\n  [0]  Salir.");
        printf("\n\n + Resp.: ");

        fflush(stdin);
        check_resp = scanf("%d", &opcion);
        while (opcion > 4 || opcion < 0 || check_resp != 1)
        {
            printf("\n\a # Respuesta invalida...");
            printf("\n\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &opcion);
        }
        switch (opcion)
        {
        case 2:
        {
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   # # # #\n");
            if (isEmpty(listaUsada))
            {
                printf("\n\a # No hay alumnos cargados en la base...");
            }
            else
            {
                mostrarEstructura(&listaUsada);
            }
            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
        }
        }
    }
    return 0;
}

int lectura_operaciones(LSO *listaLSO)
{
    FILE *fp;
    if ((fp = fopen("Operaciones-Alumnos.txt", "r")) == NULL)
        return 0;
    else
    {
        int cod_operador, aux;
        alumno x;
        while (!(feof(fp)))
        {
            fscanf(fp, "%d", &cod_operador);
            fscanf(fp, " %[^\n]", x.codigo);

            if (cod_operador == 1 || cod_operador == 2)
            {
                fscanf(fp, " %[^\n]", x.nombreCompleto);
                fscanf(fp, " %[^\n]", x.mail);
                fscanf(fp, "%d", x.nota);
                fscanf(fp, " %[^\n]", x.condicion);

                altaLSO(x, listaLSO, aux);
            }
            else if (cod_operador == 3)
            {
                evocarLSO(x.codigo, listaLSO);
            }
            else
            {
                // error cod no reconocido
            }
            cod_operador = 0;
        }
    }
    fclose(fp);
    return 1;
}