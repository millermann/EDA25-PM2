#ifndef COSTO_H_INCLUDED
#define COSTO_H_INCLUDED

typedef struct
{
    float totalAltas;
    float totalBajas;
    float totalEvocExito; // sumatoria de todas las consult de cada evoc exit
    float totalEvocFrac;
    float maxAlta;
    float maxBaja;
    float maxEvocExito;
    float maxEvocFrac;
    float cantAltasExito;
    float cantBajasExito;
    float cantEvocExito;
    float cantEvocFrac;
    float consultasActuales;
} costoEstructura;

void initCostoEstructura(costoEstructura *costes)
{
    costes->totalAltas = 0;
    costes->totalBajas = 0;
    costes->totalEvocExito = 0;
    costes->totalEvocFrac = 0;
    costes->maxAlta = 0;
    costes->maxBaja = 0;
    costes->maxEvocExito = 0;
    costes->maxEvocFrac = 0;
    costes->cantAltasExito = 0;
    costes->cantBajasExito = 0;
    costes->cantEvocExito = 0;
    costes->cantEvocFrac = 0;
    costes->consultasActuales = 0;
}

void mostrarCostos(costoEstructura LSO, costoEstructura LIBT, costoEstructura ABB)
{
    printf("\n  %-20s|%8s|%8s|%8s\n", "Rutina", "LSO", "LIBT", "ABB");
    printf(" -------------------------------------------------\n");
    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Max. Alta",
           LSO.maxAlta, LIBT.maxAlta, ABB.maxAlta);

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Med. Alta",
           (LSO.totalAltas / LSO.cantAltasExito),
           (LIBT.totalAltas / LIBT.cantAltasExito),
           (ABB.totalAltas / ABB.cantAltasExito));

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Max. Baja",
           LSO.maxBaja, LIBT.maxBaja, ABB.maxBaja);

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Med. Baja",
           (LSO.totalBajas / LSO.cantBajasExito),
           (LIBT.totalBajas / LIBT.cantBajasExito),
           (ABB.totalBajas / ABB.cantBajasExito));

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Max. Evoc. Ex.",
           LSO.maxEvocExito, LIBT.maxEvocExito, ABB.maxEvocExito);

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Med. Evoc. Ex.",
           (LSO.totalEvocExito / LSO.cantEvocExito),
           (LIBT.totalEvocExito / LIBT.cantEvocExito),
           (ABB.totalEvocExito / ABB.cantEvocExito));

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Max. Evoc. No Ex.",
           LSO.maxEvocFrac, LIBT.maxEvocFrac, ABB.maxEvocFrac);

    printf("  %-20s|%8.2f|%8.2f|%8.2f\n", "Med. Evoc. No Ex.",
           (LSO.totalEvocFrac / LSO.cantEvocFrac),
           (LIBT.totalEvocFrac / LIBT.cantEvocFrac),
           (ABB.totalEvocFrac / ABB.cantEvocFrac));

}
#endif // COSTO_H_INCLUDED