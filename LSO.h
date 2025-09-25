#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include "alumno.h"

#define max_LSO_size 130

typedef struct // LSO con tamaño conocido
{
    alumno vipd[max_LSO_size];
    int cur;
    int ultimoElem; // indice del ultimo elem guardado
} LSO;

void initLSO(LSO *lista)
{
    lista->cur = -1;
    lista->ultimoElem = -1;
}

int isFull(LSO lista)
{
    if (lista.ultimoElem == (max_LSO_size - 1))
        return 1;
    else
        return 0;
}

int isEmptyLSO(LSO lista)
{
    if (lista.ultimoElem == -1)
        return 1;
    else
        return 0;
}

int isOos(LSO lista)
{
    if (lista.cur > lista.ultimoElem)
        return 1;
    else
        return 0;
}

alumno peek(LSO lista)
{
    return lista.vipd[lista.cur];
}

void forward(LSO *lista)
{
    lista->cur++;
}

void resetCur(LSO *lista)
{
    lista->cur = 0;
}

void localizar(char id[], LSO *lista, int *pos, int *exito) // 1 = Exito, 0 = No encontrado
{
    int comparar = -1;

    lista->cur = 0;
    while (!isOos(*lista) && (comparar = strcmp(peek(*lista).codigo, id)) < 0)
    {
        lista->cur++; // deja el cur justo en la celda del 1er elem (>=) a x que encuentra
    }

    if (comparar == 0)
        *exito = 1;
    else
        *exito = 0;

    *pos = lista->cur;
}

void altaLSO(alumno x, LSO *lista, int *exito) // -1 = No espacio, 0 = Repetido, 1 = Exito
{
    int cambios = 0;
    int pos;
    if (isEmptyLSO(*lista))
    {
        lista->cur = 0;
        lista->vipd[0] = x;
        lista->ultimoElem = 0;
        *exito = 1;
    }

    else
    {
        localizar(x.codigo, lista, &pos, exito);
        if (*exito == 1)
        {
            *exito = 0;
        }
        else
        {
            if (!isFull(*lista))
            {
                int aux = lista->ultimoElem;
                while (aux >= pos)
                {
                    lista->vipd[aux + 1] = lista->vipd[aux];
                    aux--;
                    cambios++;
                }
                lista->vipd[pos] = x;
                lista->ultimoElem = (lista->ultimoElem) + 1;
                *exito = 1;
            }
            else
            {
                *exito = -1;
            }
        }
    }
}

void bajaLSO(alumno x, LSO *lista, int *exito) // -1 = No encontrado, 0 = Nupla distinta, 1 = Exito
{
    int pos;

    localizar(x.codigo, lista, &pos, exito);
    if (*exito == 1)
    {
        if (mismoAlumno(x, lista->vipd[pos]))
        {
            int aux = pos;
            while (aux < lista->ultimoElem)
            {
                lista->vipd[aux] = lista->vipd[aux + 1];
                aux++;
            }
            lista->ultimoElem = (lista->ultimoElem) - 1;
            *exito = 1;
        }
        else
            *exito = 0;
    }
    else
        *exito = -1;
}

int pertenece(char codigo[], LSO *lista)
{
    int exito = 0, pos;
    if (!isEmptyLSO(*lista))
    {
        localizar(codigo, lista, &pos, &exito);
    }
    return exito;
}

void modificar(char codigo[], LSO *lista, int *exito) // -1 = No encontrado, 0 = No confirmado, 1 = Modificado
{
    int pos;

    localizar(codigo, lista, &pos, exito);
    if (*exito == 1)
    {
        int check_resp = 0, resp = 0;
        alumno x;
        strcpy(x.codigo, peek(*lista).codigo);

        mostrarDatos(peek(*lista));
        printf("\n\n - Ingrese el nombre completo del alumno: ");
        scanf(" %[^\n]", x.nombreCompleto);

        printf("\n - Ingrese el correo del alumno: ");
        scanf("%s", x.mail);

        printf("\n - Ingrese la nota del alumno: ");
        check_resp = scanf("%d", &x.nota);
        while (x.nota < 0 || x.nota > 10 || check_resp != 1)
        {
            printf("\n\a # La nota ingresada no es valida (0 <= nota <= 10), por favor vuelva a intentar...");
            printf("\n - Ingrese el codigo del alumno: ");
            fflush(stdin);
            check_resp = scanf("%d", &x.nota);
        }

        printf("\n - Seleccione la condicion del alumno: ");
        printf("\n (1) Promociona, (2) Regular, (3) Libre, (4) Ausente");
        printf("\n + Resp: ");
        check_resp = scanf("%d", &resp);
        while (resp < 1 || resp > 4 || check_resp != 1)
        {
            printf("\n\a # Respuesta no valida, por favor vuelva a intentar...");
            printf("\n - Seleccione la condicion del alumno: ");
            printf("\n (1) Promociona, (2) Regular, (3) Libre, (4) Ausente");
            printf("\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &resp);
        }
        switch (resp)
        {
        case 1:
            strcpy(x.condicion, "Promociona");
            break;
        case 2:
            strcpy(x.condicion, "Regular");
            break;
        case 3:
            strcpy(x.condicion, "Libre");
            break;
        case 4:
            strcpy(x.condicion, "Ausente");
        }

        system("cls");
        printf("\n # # # #   M O D I F I C A R   A L U M N O S   # # # #\n");
        printf("\n - Antes: ");
        mostrarDatos(peek(*lista));
        printf("\n - Modificado: ");
        mostrarDatos(x);
        printf("\n - Desea efectuar las modificaciones? (1 = Si / 0 = No)");
        printf("\n + Resp: ");
        check_resp = scanf("%d", &resp);
        while (resp < 0 || resp > 1 || check_resp != 1)
        {
            printf("\n\a # Respuesta no valida.");
            printf("\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &resp);
        }
        *exito = resp;
        if (resp == 1)
        {
            strcpy(lista->vipd[pos].nombreCompleto, x.nombreCompleto);
            strcpy(lista->vipd[pos].mail, x.mail);
            lista->vipd[pos].nota = x.nota;
            strcpy(lista->vipd[pos].condicion, x.condicion);
        }
    }
    else
        *exito = -1;
}

alumno *evocarLSO(char codigo[], LSO *lista, int *exito)
{
    int pos;
    localizar(codigo, lista, &pos, exito);

    if (*exito == 1)
        return &lista->vipd[pos];

    else
        return NULL;
}

void mostrarEstructuraLSO(LSO lista)
{
    int aux = 0;

    lista.cur = 0;
    while (isOos(lista) != 1)
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
        mostrarDatos(peek(lista));
        lista.cur++;
    }
    printf("\n\n hay %d alumnos en LSO", lista.cur);
    printf("\n\n # No hay mas alumnos para mostrar...");
}
#endif // LSO_H_INCLUDED
