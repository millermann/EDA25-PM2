#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "alumno.h"

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
    int comparar = -1;

    *anterior = NULL;
    *cur = arbol.raiz;
    *exito = 0;
    while (*cur != NULL)
    {
        comparar = strcmp(id, (**cur).vipd.codigo);
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
        }
        else
            *exito = -1;
    }
}

void bajaABB(alumno x, ABB *arbol, int *exito)
{
    nodo *anterior = NULL, *cur = NULL;
    localizarABB(x.codigo, *arbol, &anterior, &cur, exito);

    if (*exito == 1)
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

            if (anterior_aux->hd == aux)
                anterior_aux->hd = aux->hi;
            else
                anterior_aux->hi = aux->hi;

            free(aux);
        }
        *exito = 1;
    }
    else
        *exito = -1;
}

alumno *evocarABB(char codigo[], ABB *arbol, int *exito)
{
    nodo *anterior = NULL, *cur = NULL;
    localizarABB(codigo, *arbol, &anterior, &cur, exito);

    if (*exito == 1)

        return &(*cur).vipd;
    else
        return NULL;
}

void barridoPreOrdenABB(nodo *cur)
{
    if (cur != NULL)
    {
        mostrarDatos(cur->vipd);
        barridoPreOrdenABB(cur->hi);
        barridoPreOrdenABB(cur->hd);
    }
}

#endif // ABB_H_INCLUDED
