#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "LSO.h"
#include "LIBT.h"
#include "ABB.h"
#include "alumno.h"

#define nombreArchivo "Operaciones-Alumnos.txt"
/*
Grupo 29
Mariano Valentino Quiroga Puliti, Elias Ismael Videla

  Rutina              |     LSO|    LIBT|     ABB
 -------------------------------------------------
  Max. Alta           |   91.00|   46.00|    0.50
  Med. Alta           |   23.28|   12.01|    0.50
  Max. Baja           |   91.00|   46.00|    1.00
  Med. Baja           |   22.38|   11.69|    0.74
  Max. Evoc. Ex.      |  100.00|    7.00|   12.00
  Med. Evoc. Ex.      |   45.13|    5.53|    6.43
  Max. Evoc. No Ex.   |   71.00|    7.00|   11.00
  Med. Evoc. No Ex.   |   24.19|    5.13|    5.85

Promediando todos los costos obtenidos, el ABB es, por una amplia diferencia, 
la opcion mas eficiente respecto a los tipos de costo que evaluamos.
La LIBT ocupa el 2do lugar (siendo mas efieciente que ABB en las evocaciones) 
Por ultimo, la LSO es la que peor eficiencia posee de las 3.
*/


int strAMayus(char *str);
int lectura_operaciones(LSO *listaLSO, LIBT *listaLI, ABB *arbolBB);

int main()
{
    int opcion = -1, check_resp = 0;
    LSO listaLSO_usada;
    LIBT listaLI_usada;
    ABB arbol_usado;
    initLSO(&listaLSO_usada);
    initLIBT(&listaLI_usada);
    initABB(&arbol_usado);

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
        case 1:
        {
            system("cls");
            printf("\n # # # #   C O M P A R A R   E S T R U C T U R A S   # # # #\n");

            initLSO(&listaLSO_usada);
            restablecerLIBT(&listaLI_usada);
            restablecerABB(&arbol_usado);
            initCostoEstructura(&costoLSO);
            initCostoEstructura(&costoLIBT);
            initCostoEstructura(&costoABB);

            lectura_operaciones(&listaLSO_usada, &listaLI_usada, &arbol_usado);
            
            mostrarCostos(costoLSO, costoLIBT, costoABB);
            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }
        case 2:
        {
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   ( L S O )   # # # #\n");
            if (isEmptyLSO(listaLSO_usada))
                printf("\n\a # No hay alumnos cargados en la base...");
            else
                mostrarEstructuraLSO(listaLSO_usada);

            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }
        case 3:
        {
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   ( L I B T )   # # # #\n");
            if (isEmptyLIBT(listaLI_usada))
                printf("\n\a # No hay alumnos cargados en la base...");
            else
                mostrarEstructuraLIBT(listaLI_usada);

            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }
        case 4:
        {
            int aux = 0;
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   ( A B B )   # # # #\n");
            if (isEmptyLIBT(listaLI_usada))
                printf("\n\a # No hay alumnos cargados en la base...");
            else
            {
                barridoPreOrdenABB(peekRaizABB(arbol_usado), &aux);
            }
            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }
        }
    }
    return 0;
}

int strAMayus(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = toupper((unsigned char)str[i]);
        i++;
    }
    return 1;
}

int lectura_operaciones(LSO *listaLSO, LIBT *listaLI, ABB *arbolBB)
{
    FILE *fp;
    if ((fp = fopen(nombreArchivo, "r")) == NULL)
        return 0;
    else
    {
        int cod_operador, exito;
        alumno x;
        while (!(feof(fp)))
        {
            fscanf(fp, "%d", &cod_operador);
            fscanf(fp, " %[^\n]", x.codigo);
            strAMayus(x.codigo);

            if (cod_operador == 1 || cod_operador == 2)
            {
                fscanf(fp, " %[^\n]", x.nombreCompleto);
                fscanf(fp, " %[^\n]", x.mail);
                fscanf(fp, "%d", &x.nota);
                fscanf(fp, " %[^\n]", x.condicion);
                if (cod_operador == 1)
                {
                    altaLSO(x, listaLSO, &exito);
                    altaLIBT(x, listaLI, &exito);
                    altaABB(x, arbolBB, &exito);
                }

                else
                {
                    bajaLSO(x, listaLSO, &exito);
                    bajaLIBT(x, listaLI, &exito);
                    bajaABB(x, arbolBB, &exito);
                }
            }
            else if (cod_operador == 3)
            {
                evocarLSO(x.codigo, listaLSO, &exito);
                evocarLIBT(x.codigo, listaLI, &exito);
                evocarABB(x.codigo, arbolBB, &exito);
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
