#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumno.h"

#define max_LIBT_size 130

typedef struct
{
    alumno *lista;
    int li;
    int ls;
} LIBT;

void initLIBT(LIBT *listaLI)
{
    listaLI->lista = (alumno *)malloc(sizeof(alumno) * max_LIBT_size);
    listaLI->li = -1; // al pedo
    listaLI->ls = -1;
}

int isFullLIBT(LIBT listaLI)
{
    return (listaLI.ls == (max_LIBT_size - 1));
}

int isEmptyLIBT(LIBT listaLI)
{
    return (listaLI.ls == -1);
}

void localizarLIBT(char id[], LIBT listaLI, int *pos, int *exito) // 1 = Exito, 0 = No encontrado
{
    int comparar = -1, cur = listaLI.li;

    while ((cur <= listaLI.ls) && (comparar = strcmp(listaLI.lista[cur].codigo, id)) < 0)
    {
        cur++;
    }
    *pos = cur;
    *exito = (comparar == 0);
}

void localizarTrisecc(char id[], LIBT listaLI, int *pos, int *exito)
{
}

void altaLIBT(alumno x, LIBT *listaLI, int *exito)
{
    if (isEmptyLIBT(*listaLI))
    {
        listaLI->li = 0;
        listaLI->ls = 0;
        listaLI->lista[listaLI->li] = x;
        *exito = 1;
    }

    else
    {
        int pos;
        localizarLIBT(x.codigo, *listaLI, &pos, exito);

        if (*exito)
            *exito = 0;

        else
        {
            if (!isFullLIBT(*listaLI))
            {
                int aux = listaLI->ls;
                while (aux >= pos)
                {
                    listaLI->lista[aux + 1] = listaLI->lista[aux];
                    aux--;
                }
                listaLI->lista[pos] = x;
                listaLI->ls++;
                *exito = 1;
            }
            else
                *exito = -1;
        }
    }
}

void bajaLIBT(alumno x, LIBT *listaLI, int *exito)
{
    int pos = 0;
    localizarLIBT(x.codigo, *listaLI, &pos, exito);
    if (*exito == 1)
    {
        int aux = pos;
        while (aux < listaLI->ls)
        {
            listaLI->lista[aux] = listaLI->lista[aux + 1];
            aux++;
        }
        listaLI->ls--;
        *exito = 1;
    }
    else
        *exito = -1;
}

alumno *evocarLIBT(char codigo[], LIBT *listaLI, int *exito)
{
    int pos;
    localizarLIBT(codigo, *listaLI, &pos, exito);
    
    if (*exito)
        return &listaLI->lista[pos];
    else
        return NULL;
}

void mostrarEstructuraLIBT(LIBT listaLI)
{
    int cur = listaLI.li, aux = 0;
    while (cur <= listaLI.ls)
    {
        /*
        if (aux > 3)
        {
            printf("\n\n - Pulse para continuar...");
            fflush(stdin);
            getchar();
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   # # # #\n");
            aux = 0;
        }
            */
        aux++;
        mostrarDatos(listaLI.lista[cur]);
        cur++;
    }
    printf("\n\n # No hay mas alumnos para mostrar...");
}

#endif // LIBT_H_INCLUDED
