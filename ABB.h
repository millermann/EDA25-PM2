#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "alumno.h"
#include "costo.h"

costoEstructura costoABB;

typedef struct nodo
{
    alumno vipd;
    struct nodo *hi;
    struct nodo *hd;
} nodo;

typedef struct
{
    nodo *raiz;
    // datos del arbol
} ABB;

nodo *peekRaizABB(ABB arbol)
{
    return arbol.raiz;
}

void initABB(ABB *arbol)
{
    arbol->raiz = NULL;
}

void localizarABB(char id[], ABB arbol, nodo **anterior, nodo **cur, int *exito)
{
    float consultas = 0;
    int comparar = -1;

    *anterior = NULL;
    *cur = arbol.raiz;
    *exito = 0;
    while (*cur != NULL)
    {
        comparar = strcmp(id, (**cur).vipd.codigo);
        consultas++;
        if (comparar == 0)
        {
            *exito = 1;
            break;
        }

        *anterior = *cur;
        if (comparar < 0)
            *cur = (**cur).hi;
        else
            *cur = (**cur).hd;
    }
    // si hay exito cur contiene la direccion del nodo

    // costes
    costoABB.consultasActuales = consultas;
}

void altaABB(alumno x, ABB *arbol, int *exito) // -1 = No espacio, 0 = Repetido, 1 = Exito
{
    nodo *anterior = NULL, *cur = NULL;

    localizarABB(x.codigo, *arbol, &anterior, &cur, exito);
    if (*exito == 1)
    {
        *exito = 0;
    }
    else
    {
        nodo *nuevo_nodo;
        if ((nuevo_nodo = (nodo *)malloc(sizeof(nodo))) != NULL)
        {
            float cambios = 0;

            nuevo_nodo->vipd = x;
            nuevo_nodo->hi = NULL;
            nuevo_nodo->hd = NULL;

            if (anterior == NULL)
            {
                arbol->raiz = nuevo_nodo;
            }
            else
            {
                if (strcmp(x.codigo, anterior->vipd.codigo) < 0)
                    anterior->hi = nuevo_nodo;
                else
                    anterior->hd = nuevo_nodo;
            }

            *exito = 1;
            // costos
            cambios += 0.5;
            if (cambios > costoABB.maxAlta)
                costoABB.maxAlta = cambios;
            costoABB.totalAltas += cambios;
            costoABB.cantAltasExito++;
        }
        else
            *exito = -1;
    }
}

void bajaABB(alumno x, ABB *arbol, int *exito) // -1 = No encontrado, 0 = La nupla no era igual, 1 = Exito
{
    nodo *anterior = NULL, *cur = NULL;
    localizarABB(x.codigo, *arbol, &anterior, &cur, exito);

    if (*exito == 1)
    {
        float cambios = 0;
        if (mismoAlumno(x, cur->vipd))
        {
            if (cur->hi == NULL || cur->hd == NULL)
            {
                if (cur->hi == NULL && cur->hd == NULL) // A - x tiene 0 hijos
                {
                    if (cur == arbol->raiz) // A1
                        arbol->raiz = NULL;
                    else
                    {
                        if (anterior->hi == cur) // A2
                            anterior->hi = NULL;
                        else
                            anterior->hd = NULL;
                    }
                }
                else // B - x tiene 1 hijo
                {
                    nodo *aux;
                    if (cur->hi != NULL)
                        aux = cur->hi;
                    else
                        aux = cur->hd;

                    if (cur == arbol->raiz) // B1
                        arbol->raiz = aux;
                    else
                    {
                        if (anterior->hi == cur) // B2
                            anterior->hi = aux;
                        else // B3
                            anterior->hd = aux;
                    }

                }
                free(cur);

                cambios = 0.5;
            }
            else // x tiene 2 hijos
            {
                nodo *anterior_aux = cur;
                nodo *aux = cur->hi;

                while (aux->hd != NULL)
                {
                    anterior_aux = aux;
                    aux = aux->hd;
                }

                cur->vipd = aux->vipd;
                cambios += 0.5;

                if (anterior_aux->hd == aux)
                    anterior_aux->hd = aux->hi;
                else
                    anterior_aux->hi = aux->hi;
                cambios += 0.5;

                free(aux);
            }
            *exito = 1;

            // costes
            if (cambios > costoABB.maxBaja)
                costoABB.maxBaja = cambios;
            costoABB.totalBajas += cambios;
            costoABB.cantBajasExito++;
        }
        else
            *exito = 0;
    }
    else
        *exito = -1;
}

alumno *evocarABB(char codigo[], ABB *arbol, int *exito)
{
    nodo *anterior = NULL, *cur = NULL;
    localizarABB(codigo, *arbol, &anterior, &cur, exito);

    if (*exito == 1)
    {
        if (costoABB.consultasActuales > costoABB.maxEvocExito)
            costoABB.maxEvocExito = costoABB.consultasActuales;
        costoABB.totalEvocExito += costoABB.consultasActuales;
        costoABB.cantEvocExito++;

        return &(*cur).vipd;
    }
    else
    {
        if (costoABB.consultasActuales > costoABB.maxEvocFrac)
            costoABB.maxEvocFrac = costoABB.consultasActuales;
        costoABB.totalEvocFrac += costoABB.consultasActuales;
        costoABB.cantEvocFrac++;

        return NULL;
    }
}

void barridoRestablecer(nodo *cur)
{
    if (cur != NULL)
    {
        barridoRestablecer(cur->hi);
        barridoRestablecer(cur->hd);
        free(cur);
    }
}

void restablecerABB(ABB *arbol)
{
    barridoRestablecer(arbol->raiz);
    arbol->raiz = NULL;
}

void barridoPreOrdenABB(nodo *cur, int *aux)
{
    if (cur != NULL)
    {
        if ((*aux) > 2)
        {
            printf("\n\n - Pulse para continuar...");
            fflush(stdin);
            getchar();
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   ( A B B )   # # # #\n");
            *aux = 0;
        }
        (*aux)++;
        mostrarDatos(cur->vipd);
        char codigo[cod_alumno_size];

        if (cur->hi == NULL)
            strcpy(codigo, "Ninguno");
        else
            strcpy(codigo, cur->hi->vipd.codigo);
        printf("\n     + Hijo Izquierdo: %s", codigo);

        if (cur->hd == NULL)
            strcpy(codigo, "Ninguno");
        else
            strcpy(codigo, cur->hd->vipd.codigo);
        printf("\n     + Hijo Derecho: %s", codigo);
        
        barridoPreOrdenABB(cur->hi, aux);
        barridoPreOrdenABB(cur->hd, aux);
    }
}

#endif // ABB_H_INCLUDED
