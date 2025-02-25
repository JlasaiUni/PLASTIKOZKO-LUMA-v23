#ifndef OURTYPES_H
#define OURTYPES_H

#include "ebentoak.h"

typedef enum
{
    JOLASTEN,
    GALDU,
    IRABAZI,
    AMAIERA,

} EGOERA;

typedef enum
{
    HASIERA,
    MISIOAK,
    ORDA,
    IRTEN,

} JOLAS_AUKERAK;

typedef enum
{
    IRUDIA,
    MARGOA,
    TESTUA

} MOTA;

typedef struct
{
    POSIZIOA pos;
    int id;
    MOTA mota;

} JOKO_ELEMENTUA;

/*typedef struct
{
   int idIrudi;
   int text;
   int jokalaria;

} GURE_GAUZAK; */

typedef struct
{
    double x, y;
    double dx, dy;
    int id;

} ETSAILAK;

typedef struct
{
    double posX, posY;
    double dx, dy;
    int aktibo;
    int id;
    int tipo; // 0 normala, 1 konoa
} TIROA;

typedef struct
{
    double x, y;
    int id;

} SARIAK;

typedef struct
{
    double x, y;

} PUNTUA;

typedef struct
{
    double posX, posY;
    int aktibo;
    int id;
} PowerUp;

#endif