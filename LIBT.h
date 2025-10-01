#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumno.h"

#define max_LIBT_size 130

costoEstructura costoLIBT;

typedef struct
{
    alumno *lista[max_LIBT_size];
    int li;
    int cant;
} LIBT;

void initLIBT(LIBT *listaLI)
{
    listaLI->li = 0;
    listaLI->cant = 0;
}

int isFullLIBT(LIBT listaLI)
{
    return (listaLI.cant == max_LIBT_size);
}

int isEmptyLIBT(LIBT listaLI)
{
    return (listaLI.cant == 0);
}

void localizarTrisecc(char id[], LIBT listaLI, int *pos, int *exito) // 1 = Exito, 0 = No encontrado
{
    int li = listaLI.li, ls = listaLI.cant - 1, mitad = 0, comparar = -1;
    *exito = 0;

    costoLIBT.consultasActuales = 0;

    while (li <= ls)
    {
        mitad = (li + ls) / 2;

        comparar = strcmp(id, listaLI.lista[mitad]->codigo);
        costoLIBT.consultasActuales++;

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

void altaLIBT(alumno x, LIBT *listaLI, int *exito) // -1 = No hay espacio. 0 = Ya existe en la estruc. 1 = Exito
{
    alumno *alumnoNuevo = (alumno *)malloc(sizeof(alumno));

    int pos;
    localizarTrisecc(x.codigo, *listaLI, &pos, exito);

    if (*exito)
        *exito = 0;

    else
    {
        if (!isFullLIBT(*listaLI) && alumnoNuevo != NULL)
        {
            float cambios = 0;

            *alumnoNuevo = x;
            int aux = (listaLI->cant) - 1;
            while (aux >= pos)
            {
                listaLI->lista[aux + 1] = listaLI->lista[aux];
                aux--;
                cambios += 0.5;
            }
            listaLI->lista[pos] = alumnoNuevo;
            cambios += 0.5;
            listaLI->cant++;
            *exito = 1;

            // costes
            if (cambios > costoLIBT.maxAlta)
                costoLIBT.maxAlta = cambios;
            costoLIBT.totalAltas += cambios;
            costoLIBT.cantAltasExito++;
        }
        else
            *exito = -1;
    }
}

void bajaLIBT(alumno x, LIBT *listaLI, int *exito) // -1 = No encontrado, 0 = La nupla no era igual, 1 = Exito
{
    int pos = 0;
    localizarTrisecc(x.codigo, *listaLI, &pos, exito);
    if (*exito == 1)
    {
        if (mismoAlumno(x, *listaLI->lista[pos]))
        {
            float cambios = 0.5;

            free(listaLI->lista[pos]);
            int aux = pos;
            while (aux < (listaLI->cant) - 1)
            {
                listaLI->lista[aux] = listaLI->lista[aux + 1];
                aux++;
                cambios += 0.5;
            }
            listaLI->cant--;
            *exito = 1;

            // costes
            if (cambios > costoLIBT.maxBaja)
                costoLIBT.maxBaja = cambios;
            costoLIBT.totalBajas += cambios;
            costoLIBT.cantBajasExito++;
        }
        else
            *exito = 0;
    }
    else
        *exito = -1;
}

alumno *evocarLIBT(char codigo[], LIBT *listaLI, int *exito)
{
    int pos;
    localizarTrisecc(codigo, *listaLI, &pos, exito);

    if (*exito)
    {
        if (costoLIBT.consultasActuales > costoLIBT.maxEvocExito)
            costoLIBT.maxEvocExito = costoLIBT.consultasActuales;

        costoLIBT.totalEvocExito += costoLIBT.consultasActuales;
        costoLIBT.cantEvocExito++;

        return listaLI->lista[pos];
    }
    else
    {
        if (costoLIBT.consultasActuales > costoLIBT.maxEvocFrac)
            costoLIBT.maxEvocFrac = costoLIBT.consultasActuales;

        costoLIBT.totalEvocFrac += costoLIBT.consultasActuales;
        costoLIBT.cantEvocFrac++;

        return NULL;
    }
}

void restablecerLIBT(LIBT *listaLI)
{
    int pos = listaLI->li;
    while (pos < listaLI->cant)
    {
        free(listaLI->lista[pos]);
        pos++;
    }

    initLIBT(listaLI);
}

void mostrarEstructuraLIBT(LIBT listaLI)
{
    int cur = listaLI.li, aux = 0;
    while (cur < listaLI.cant)
    {
        if (aux > 3)
        {
            printf("\n\n - Pulse para continuar...");
            fflush(stdin);
            getchar();
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   ( L I B T )   # # # #\n");
            aux = 0;
        }
        aux++;
        
        mostrarDatos(*(listaLI.lista[cur]));
        cur++;
    }
    printf("\n\n # No hay mas alumnos para mostrar...");
}

#endif // LIBT_H_INCLUDED
