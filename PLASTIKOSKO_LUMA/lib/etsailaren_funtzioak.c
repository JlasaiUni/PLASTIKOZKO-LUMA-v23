#define _CRT_SECURE_NO_WARNINGS
#include "./includeak/gurefuntzioak.h"
#include "./includeak/misioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

void AldeaAukeratuEtsaila(double *x, double *y)
{
    int aldea = rand() % 4; // 0tik 3ra

    switch (aldea)
    {
    case 0:
        *x = 0;
        *y = rand() % (SCREEN_HEIGHT - 32);
        break;
    case 1:
        *x = rand() % (SCREEN_WIDTH - 32);
        *y = 0;
        break;
    case 2:
        *x = rand() % (SCREEN_WIDTH - 32);
        *y = SCREEN_HEIGHT - 32;
        break;
    case 3:
        *x = SCREEN_WIDTH - 32;
        *y = rand() % (SCREEN_HEIGHT - 32);
        break;
    }
}

void EtsaiakSortu(ETSAILAK *etsaila, double x, double y, int idImagen)
{
    etsaila->x = x;
    etsaila->y = y;
    etsaila->dx = 0.0;
    etsaila->dy = 0.0;
    etsaila->id = idImagen;
}

void EtsaiakMugitu(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy, double abiadura)
{
    double dx, dy, Luzeera;

    dx = JokalariaPosX - etsaila->x;
    dy = JokalariaPosy - etsaila->y;

    Luzeera = sqrt(dx * dx + dy * dy);

    dx /= Luzeera;
    dy /= Luzeera;

    etsaila->x += dx * abiadura;
    etsaila->y += dy * abiadura;
}

void EtsaiaMarraztu(ETSAILAK *etsaila)
{
    irudiaMugitu(etsaila->id, etsaila->x, etsaila->y);
}
void EtsaiakMugitu2(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy, double abiadura)
{
    double dx, dy, Luzeera;
    double oszilatu;

    oszilatu = SDL_GetTicks();
    oszilatu = oszilatu * 2 * M_PI / 1000;

    dx = JokalariaPosX - etsaila->x;
    dy = JokalariaPosy - etsaila->y;

    // bektora nahi dozun bezala deitu

    Luzeera = sqrt(dx * dx + dy * dy);

    // bektore unitario atera
    dx /= Luzeera;
    dy /= Luzeera;

    etsaila->x += dx * abiadura + cos(oszilatu);
    etsaila->y += dy * abiadura + sin(oszilatu);
}
void EtsaiakMugitu3(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy, double abiadura)
{
    double dx, dy, Luzeera;
    double oszilatu;

    oszilatu = SDL_GetTicks();
    oszilatu = oszilatu * 2 * M_PI / 10000;

    dx = JokalariaPosX - etsaila->x;
    dy = JokalariaPosy - etsaila->y;

    // bektora nahi dozun bezala deitu

    Luzeera = sqrt(dx * dx + dy * dy);

    // bektore unitario atera
    dx /= Luzeera;
    dy /= Luzeera;

    etsaila->x += dx * abiadura + cos(oszilatu);
    etsaila->y += dy * abiadura;
}

void PelotaMarraztu(ETSAILAK *pelota)
{
    arkatzKoloreaEzarri(0xFF, 0x00, 0x00);
    // zirkuluaMarraztu(pelota->x, pelota->y, 10);
}

void JefeFinalaMugitu(double *JefePosY, double abiadura, int *norabidea)
{
    // Movimiento en Y
    *JefePosY += abiadura * (*norabidea);

    // Cambiar dirección si toca los límites
    if ((*JefePosY <= 0 - 200) || (*JefePosY >= SCREEN_HEIGHT - 100))
    {
        *norabidea = -(*norabidea); // Cambia la dirección de movimiento
    }
}

void TiroaJefe(double *disparoPosJefeX, double *disparoPosJefeY, double *disparoBaiJefe, double jefeposx,
               double jefeposy)
{
    // Solo activamos el disparo si no está activo
    if (*disparoBaiJefe == 0)
    {
        *disparoPosJefeX = jefeposx + 20;
        *disparoPosJefeY = jefeposy + 120; // Inicializamos la posición del disparo en la del jugador

        *disparoBaiJefe = 1; // Activa el disparo
    }
}
int KolisioaTiroaEtsaila(double EtsailaX, double EtsailaY, double PelotaX, double PelotaY)
{
    int Kolisioa = 0;
    double luzeeraPelotaEtsaila;

    luzeeraPelotaEtsaila =
        sqrt((EtsailaX - PelotaX) * (EtsailaX - PelotaX) + (EtsailaY - PelotaY) * (EtsailaY - PelotaY));

    if (luzeeraPelotaEtsaila <= 20)
    {
        Kolisioa = 1;
    }

    return Kolisioa;
}