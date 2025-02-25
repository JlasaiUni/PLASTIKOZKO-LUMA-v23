#include "./includeak/gurefuntzioak.h"
#include "./includeak/misioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "main.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>
#define MAX_DISPAROS 100

void JokalariMugimendu(double *JokalariaPosy, double *jokalariaPosx)
{
    double abiadura = 2;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL); // teklak detektatzeko

    // jokalaria fletzekin mugitu
    if (keystate[SDL_SCANCODE_W])
    {
        *JokalariaPosy -= abiadura;

        if (keystate[SDL_SCANCODE_A])
        {
            *jokalariaPosx += abiadura * 0.4;
            *JokalariaPosy += abiadura * 0.4;
        }
        if (keystate[SDL_SCANCODE_D])
        {
            *jokalariaPosx -= abiadura * 0.4;
            *JokalariaPosy += abiadura * 0.4;
        }
    }

    if (keystate[SDL_SCANCODE_S])
    {
        *JokalariaPosy += abiadura;

        if (keystate[SDL_SCANCODE_A])
        {
            *jokalariaPosx += abiadura * 0.4;
            *JokalariaPosy -= abiadura * 0.4;
        }
        if (keystate[SDL_SCANCODE_D])
        {
            *jokalariaPosx -= abiadura * 0.4;
            *JokalariaPosy -= abiadura * 0.4;
        }
    }

    if (keystate[SDL_SCANCODE_A])
    {
        *jokalariaPosx -= abiadura;
    }

    if (keystate[SDL_SCANCODE_D])
    {
        *jokalariaPosx += abiadura;
    }

    // ez ateratzeko pantailatik
    if (*jokalariaPosx < 0)
    {
        *jokalariaPosx = 0;
    }
    if (*jokalariaPosx + 32 > SCREEN_WIDTH)
    {
        *jokalariaPosx = SCREEN_WIDTH - 32;
    }
    if (*JokalariaPosy < 0)
    {
        *JokalariaPosy = 0;
    }
    if (*JokalariaPosy + 32 > SCREEN_HEIGHT)
    {
        *JokalariaPosy = SCREEN_HEIGHT - 32;
    }
}

void Disparoa(int ebentu, TIROA tiroak[MAX_DISPAROS], double posx, double posy)
{
    double luzeera, disparoVelocidad = 3;
    int i, j = -1;
    POSIZIOA pos;

    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
        pos = saguarenPosizioa();

        for (i = 0; i < MAX_DISPAROS; i++)
        {
            if (!tiroak[i].aktibo)
            {
                tiroak[i].posX = posx;
                tiroak[i].posY = posy;

                // TIROA normal
                if (tiroak[i].tipo == 0)
                {
                    tiroak[i].dx = pos.x - posx;
                    tiroak[i].dy = pos.y - posy;

                    luzeera = sqrt(tiroak[i].dx * tiroak[i].dx + tiroak[i].dy * tiroak[i].dy);
                    tiroak[i].dx /= luzeera;
                    tiroak[i].dy /= luzeera;

                    tiroak[i].aktibo = 1;
                    tiroak[i].id = irudiaKargatu("./img/UrPelota.bmp");
                    break;
                }
                // TIROA en cono ( tiroak)
                else if (tiroak[i].tipo == 1)
                {
                    if (i + j >= 0 && i + j < MAX_DISPAROS)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            if (i + j < MAX_DISPAROS)
                            {
                                tiroak[i + j].posX = posx;
                                tiroak[i + j].posY = posy;

                                double angle = atan2(pos.y - posy, pos.x - posx) + j * M_PI / 18;
                                tiroak[i + j].dx = cos(angle);
                                tiroak[i + j].dy = sin(angle);

                                tiroak[i + j].aktibo = 1;
                                tiroak[i + j].id = irudiaKargatu("./img/UrPelota.bmp");
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_DISPAROS; i++)
    {
        if (tiroak[i].aktibo)
        {
            tiroak[i].posX += tiroak[i].dx * disparoVelocidad;
            tiroak[i].posY += tiroak[i].dy * disparoVelocidad;

            if (tiroak[i].posX < 0 || tiroak[i].posX > SCREEN_WIDTH || tiroak[i].posY < 0 ||
                tiroak[i].posY > SCREEN_HEIGHT)
            {
                tiroak[i].aktibo = 0;
                irudiaKendu(tiroak[i].id);
            }
            else
            {
                irudiaMugitu(tiroak[i].id, tiroak[i].posX, tiroak[i].posY);
            }
        }
    }
}

void KolisioaPowerUp(TIROA tiroak[MAX_DISPAROS], PowerUp *powerUp, double jokalariaX, double jokalariaY)
{
    if ((((powerUp->posX + 5) > jokalariaX) && ((powerUp->posX - 5) < jokalariaX + 16)) &&
        (((powerUp->posY + 5) > jokalariaY) && ((powerUp->posY - 5) < jokalariaY + 16)))
    {
        powerUp->aktibo = 0;

        for (int i = 0; i < MAX_DISPAROS; i++)
        {
            tiroak[i].tipo = 1; // Cambia todos los tiroak al tipo de cono
        }
    }
}

/*
void Disparoa(int ebentu, TIROA tiroak[MAX_DISPAROS], double posx, double posy)
{
    double luzeera, disparoVelocidad = 3;
    POSIZIOA pos;

    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
        pos = saguarenPosizioa();

        // Encontrar un disparo inaktibo para usar
        for (int i = 0; i < MAX_DISPAROS; i++)
        {
            if (!tiroak[i].aktibo)
            {
                tiroak[i].posX = posx;
                tiroak[i].posY = posy;
                tiroak[i].dx = pos.x - posx;
                tiroak[i].dy = pos.y - posy;

                luzeera = sqrt(tiroak[i].dx * tiroak[i].dx + tiroak[i].dy * tiroak[i].dy);
                tiroak[i].dx /= luzeera;
                tiroak[i].dy /= luzeera;

                tiroak[i].aktibo = 1;
                tiroak[i].id = irudiaKargatu("./img/UrPelota.bmp");
                break;
            }
        }
    }

    // Movimiento y dibujado de cada disparo
    for (int i = 0; i < MAX_DISPAROS; i++)
    {
        if (tiroak[i].aktibo)
        {
            tiroak[i].posX += tiroak[i].dx * disparoVelocidad;
            tiroak[i].posY += tiroak[i].dy * disparoVelocidad;

            // Pueeds definir un rango de desactivación adecuado
            if (tiroak[i].posX < -50 || tiroak[i].posX > SCREEN_WIDTH + 50 || tiroak[i].posY < -50 ||
                tiroak[i].posY > SCREEN_HEIGHT + 50)
            {
                tiroak[i].aktibo = 0;
                irudiaKendu(tiroak[i].id);
            }
            else
            {
                irudiaMugitu(tiroak[i].id, tiroak[i].posX, tiroak[i].posY);
            }
        }
    }
}

*/

int KolisioaJokalariaEtsaila(double EtsailaX, double EtsailaY, double jokalariaX, double jokalariaY)
{
    int Kolisioa = 0;

    if ((((EtsailaX + 5) > jokalariaX) && ((EtsailaX - 5) < jokalariaX + 16)) &&
        (((EtsailaY + 5) > jokalariaY) && ((EtsailaY - 5) < jokalariaY + 16)))
    {
        Kolisioa = 1;
    }

    return Kolisioa;
}

void luzeeraMedikamentuaJokaliriaETALaguna(double MedicinarenPosx, double MedicinarenPosy, double posx, double posy,
                                           int *aurkituta, int *amaiera, int *medikamentua)
{
    double luzeeraMedikamentuaJokaliria, luzeeraLagunaJokaliria, kont = 0;
    luzeeraMedikamentuaJokaliria =
        sqrt((MedicinarenPosx - posx) * (MedicinarenPosx - posx) + (MedicinarenPosy - posy) * (MedicinarenPosy - posy));

    if (luzeeraMedikamentuaJokaliria <= 20 && kont == 0)
    {
        kont = 1;
        irudiaMugitu(*medikamentua, 10000, 10000);
        *aurkituta = 1;
    }

    if (*aurkituta == 1)
    {
        luzeeraLagunaJokaliria = sqrt((SCREEN_WIDTH / 2 - posx) * (SCREEN_WIDTH / 2 - posx) +
                                      (SCREEN_HEIGHT / 2 - posy) * (SCREEN_HEIGHT / 2 - posy));

        if (luzeeraLagunaJokaliria < 20)
        {
            *amaiera = 1;
        }
    }
}