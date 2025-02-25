#define _CRT_SECURE_NO_WARNINGS
#include "./includeak/gurefuntzioak.h"
#include "./includeak/misioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

#define ETSAILA_IMAGE "./img/1etsaila.bmp"
#define ETSAILA_IMAGE3 "./img/3etsaila.bmp"
#define MAX_TIROAK 100

ETSAILAK etsailak;
JOKO_ELEMENTUA jokalaria;
PUNTUA spawnPuntuak[6];

EGOERA BosgarrengoMisioa(void)
{
    int ebentu = 0, irten = 0, bai = 0, i, kontjefe = 10, x = 600, pelotaId, bala, back, j, jefe, norabidea = 1;
    double disparoPosJefeX, disparoPosJefeY, disparoBaiJefe = 0, luzeeraPelotaJefe, LuzeeraDisparoJefeJokalaria,
                                             jefeposx = 400, jefeposy = 100;

    ETSAILAK etsailak[6];
    TIROA tiroak[MAX_TIROAK] = {0};
    EGOERA egoera = JOLASTEN;
    uint32_t AskenDisparua = 0, pasatutako_denbora, hasierako_denbora = 0;

    // Soinuak hasieratzen dira
    Mix_Chunk *soinuak[5] = {NULL};

    // Soinuen artxiboak definitzen dira
    const char *soinuenArtxiboak[5] = {"./sound/victory.wav", "./sound/loose.wav", "./sound/water-drop-clean-fx.wav",
                                       "./sound/clap-soft.wav", "./sound/8bit-video-game-music-289970.wav"};

    // Soinuak kargatzen dira
    soinuak[0] = Mix_LoadWAV(soinuenArtxiboak[0]); // irabazi
    soinuak[1] = Mix_LoadWAV(soinuenArtxiboak[1]); // galdu
    soinuak[2] = Mix_LoadWAV(soinuenArtxiboak[2]); // tiro
    soinuak[3] = Mix_LoadWAV(soinuenArtxiboak[3]); // etsaila jo
    soinuak[4] = Mix_LoadWAV(soinuenArtxiboak[4]); // jokoaren musika

    Mix_PlayChannel(1, soinuak[4], -1);
    Mix_Volume(1, 100);

    back = irudiaKargatu("./img/back1.bmp");
    jokalaria.pos.x = 0, jokalaria.pos.y = SCREEN_HEIGHT / 2; // jokalariaren esaugarriak

    int etsailaImagenId[4];
    for (i = 0; i < 2; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE);
    }
    for (i = 2; i < 4; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE3);
    }

    SpawnPuntuakSortu(spawnPuntuak, 4);

    for (i = 0; i < 4; i++)
    {
        EtsaiakSortu(&etsailak[i], spawnPuntuak[i].x, spawnPuntuak[i].y, etsailaImagenId[i]);
    }

    // hasierako imagenak kargatzeko
    jefe = irudiaKargatu("./img/cazador.bmp");
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    pelotaId = irudiaKargatu("./img/UrPelota.bmp");
    bala = irudiaKargatu("./img/bala.bmp");
    irudiaMugitu(pelotaId, 10000, 10000);
    irudiaMugitu(bala, 10000, 10000);
    irudiaMugitu(jefe, jefeposx, jefeposy);
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

    while (!irten && kontjefe != 0)
    {
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();

        pasatutako_denbora = denboraLortu(&hasierako_denbora);

        pantailaGarbitu();
        irudiakMarraztu();

        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

        // etsailak marraztu
        for (i = 0; i < 2; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }
        for (i = 2; i < 4; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu3(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }

        // DISPAROA DEITU
        Disparoa(ebentu, tiroak, jokalaria.pos.x, jokalaria.pos.y);

        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            Mix_PlayChannel(-1, soinuak[2], 0);
        }

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < MAX_TIROAK; j++)
            {
                if (KolisioaTiroaEtsaila(etsailak[i].x, etsailak[i].y, tiroak[j].posX, tiroak[j].posY))
                {
                    AldeaAukeratuEtsaila(&etsailak[i].x, &etsailak[i].y);
                    Mix_PlayChannel(-1, soinuak[3], 0);
                }
            }

            if (KolisioaJokalariaEtsaila(etsailak[i].x, etsailak[i].y, jokalaria.pos.x, jokalaria.pos.y))
            {
                irten = 1;
            }
        }

        if (pasatutako_denbora - AskenDisparua >= 1) // 2000 milisegundos = 2 segundos
        {

            TiroaJefe(&disparoPosJefeX, &disparoPosJefeY, &disparoBaiJefe, jefeposx, jefeposy);
            // Actualizamos el tiempo del último disparo
            AskenDisparua = pasatutako_denbora;
        }
        // Si el disparo está activo, lo movemos
        if (disparoBaiJefe == 1)
        {
            // Desplazamos el disparo en la dirección especificada (hacia la derecha)
            disparoPosJefeX = disparoPosJefeX - 1; // Mover hacia la derecha

            // Si el disparo sale de la pantalla (en el eje X), lo desactivamos
            if (disparoPosJefeX < 0)
            {
                disparoBaiJefe = 0;      // Desactivamos el disparo
                disparoPosJefeX = 10000; // Reseteamos la posición del disparo
                disparoPosJefeY = 10000; // Reseteamos la posición del disparo
            }
            else
            {
                // Si el disparo está dentro de la pantalla, lo dibujamos
                irudiaMugitu(bala, disparoPosJefeX, disparoPosJefeY);
            }
        }

        luzeeraPelotaJefe = sqrt((jefeposx - tiroak->posX + 550) * (jefeposx / 2 - tiroak->posX + 550) +
                                 (jefeposy - tiroak->posY + 150) * (jefeposy - tiroak->posY + 150));

        if (luzeeraPelotaJefe < 50)
        {
            kontjefe--;
            x = x - 50;
            tiroak->aktibo = 0;
            tiroak->posX = 10000;
            tiroak->posY = 10000;
        }
        // bizitza barra
        arkatzKoloreaEzarri(0xFF, 0x00, 0x00);

        for (i = 0; i < 6; i++)
        {
            zuzenaMarraztu(100, 20 + i, x, 20);
        }

        /*
        zuzenaMarraztu(100, 20, x, 20);
        zuzenaMarraztu(100, 21, x, 21);
        zuzenaMarraztu(100, 22, x, 22);
        zuzenaMarraztu(100, 23, x, 21);
        zuzenaMarraztu(100, 24, x, 22);
        */

        // pow = potentzia
        LuzeeraDisparoJefeJokalaria =
            sqrt(pow(disparoPosJefeX - jokalaria.pos.x - 15, 2) + pow(disparoPosJefeY - jokalaria.pos.y - 15, 2));

        // Si la distancia entre el disparo y el jugador es menor que la suma de los radios, colisión detectada
        if (LuzeeraDisparoJefeJokalaria < 32 / 2 + 15) // Radio del jugador (16px) + radio del disparo (5px)
        {
            irten = 1;
        }

        JefeFinalaMugitu(&jefeposy, 1, &norabidea);
        irudiaMugitu(jefe, jefeposx, jefeposy);

        if (ebentu == TECLA_RETURN)
        {
            irten = 1;
            egoera = AMAIERA;
            Mix_HaltChannel(1);
        }

        pantailaBerriztu(); // Refrescar la pantalla
    }

    // Jokoa amaitu da
    if ((irten == 0) && (egoera != AMAIERA))
    {
        egoera = IRABAZI;
        Mix_HaltChannel(1);
        Mix_PlayChannel(-1, soinuak[0], 0);
    }
    if ((irten == 1) && (egoera != AMAIERA))
    {
        egoera = GALDU;

        Mix_HaltChannel(1);
        Mix_PlayChannel(-1, soinuak[1], 0);
    }

    for (i = 0; i < 4; i++)
    {
        irudiaKendu(etsailaImagenId[i]);
    }
    irudiaKendu(jokalaria.id);
    irudiaKendu(jefe);
    irudiaKendu(bala);
    pantailaGarbitu();
    pantailaBerriztu();

    back = irudiaKargatu("./img/back1.bmp");
    if (egoera == IRABAZI)
    {
        TartekoPantaila(&jokalaria.pos.x, &jokalaria.pos.y);
    }
    irudiaKendu(back);
    Mix_FreeChunk(*soinuak);
    return egoera;
}

void BosgarrenNibelaAsalpena()
{

    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/back1.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();
        textuaIdatzi(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Etsai nagusia garaitu");

        irudiaMugitu(fondo, 0, 0);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}