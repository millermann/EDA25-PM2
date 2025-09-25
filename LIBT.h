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
    listaLI->li = -1;
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

void localizarLI(char id[], LIBT listaLI, int *pos, int *exito) // 1 = Exito, 0 = No encontrado
{
    int comparar = -1, cur = listaLI.li;

    while ((cur <= listaLI.ls) && (comparar = strcmp(listaLI.lista[cur].codigo, id)) < 0)
    {
        cur++;
    }
    *pos = cur;
    *exito = (comparar == 0);
}

void localizarTrisecc(char id[], LIBT listaLI, int *pos, int *exito) // 1 = Exito, 0 = No encontrado
{
    int li = listaLI.li, ls = listaLI.ls, mitad = 0, comparar = -1;
    *exito = 0;

    while (li <= ls)
    {
        mitad = (li + ls) / 2;

        comparar = strcmp(id, listaLI.lista[mitad].codigo);

        if (comparar == 0)
        {
            *exito = 1;
            break;
        }

        if (comparar < 0)
            ls = mitad - 1;
        else
            li = mitad + 1;
    }

    if (*exito)
        *pos = mitad;
    else
        *pos = li;
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
        localizarTrisecc(x.codigo, *listaLI, &pos, exito);

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

void bajaLIBT(alumno x, LIBT *listaLI, int *exito) // -1 = No encontrado, 0 = La nupla no era igual, 1 = Exito
{
    int pos = 0;
    localizarTrisecc(x.codigo, *listaLI, &pos, exito);
    if (*exito == 1)
    {
        if (mismoAlumno(x, listaLI->lista[pos]))
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
        else *exito = 0;
    }
    else
        *exito = -1;
}

alumno *evocarLIBT(char codigo[], LIBT *listaLI, int *exito)
{
    int pos;
    localizarTrisecc(codigo, *listaLI, &pos, exito);

    if (*exito)
        return &listaLI->lista[pos];
    else
        return NULL;
}

void restablecerLIBT(LIBT *listaLI)
{
    free(listaLI->lista);
    initLIBT(listaLI);
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
        aux++;
        */
        mostrarDatos(listaLI.lista[cur]);
        cur++;
    }
    printf("\n\n hay %d alumnos en LIBT", cur);
    printf("\n\n # No hay mas alumnos para mostrar...");
}

#endif // LIBT_H_INCLUDED
