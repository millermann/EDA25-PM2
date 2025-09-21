#include <stdio.h>
#include <stdlib.h>

#include "ABB.h"
#include "LIBT.h"
#include "alumno.h"

#define nombreArchivo "test.txt"

int lectura_operaciones(LIBT *listaLI, ABB *arbolBB)
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

            if (cod_operador == 1 || cod_operador == 2)
            {
                fscanf(fp, " %[^\n]", x.nombreCompleto);
                fscanf(fp, " %[^\n]", x.mail);
                fscanf(fp, "%d", &x.nota);
                fscanf(fp, " %[^\n]", x.condicion);
                if (cod_operador == 1)
                {
                    altaLIBT(x, listaLI, &exito);
                    altaABB(x, arbolBB, &exito);
                    // altaLSO(x, listaLSO, aux);
                }

                else
                {
                    bajaLIBT(x, listaLI, &exito);
                }
            }
            else if (cod_operador == 3)
            {
                mostrarDatos(*evocarLIBT(x.codigo, listaLI, &exito));
                mostrarDatos(*evocarABB(x.codigo, arbolBB, &exito));            
                // evocarLSO(x.codigo, listaLSO);
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

int main()
{
    int aux;
    ABB arbol_usado;
    LIBT listaLI_usada;
    initABB(&arbol_usado);
    initLIBT(&listaLI_usada);
    lectura_operaciones(&listaLI_usada, &arbol_usado);
    printf("\n\n####################################################### Arboles");
    barridoPreOrdenABB(peekRaizABB(arbol_usado));
    printf("\n\n####################################################### LIBT");
    mostrarEstructuraLIBT(listaLI_usada);

    scanf("%d", &aux);
    return 0;
}
