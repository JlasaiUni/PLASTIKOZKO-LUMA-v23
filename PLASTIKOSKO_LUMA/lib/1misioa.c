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
#define MAX_TIROAK 100

JOKO_ELEMENTUA jokalaria;
PUNTUA spawnPuntuak[6];
ETSAILAK etsailak;
SARIAK sariak;

// Lehenengo misioa hasieratzen da
EGOERA LehenengoMisioa(void)
{
    // Aldagaiak hasieratzen dira
    int ebentu = 0, irten = 0, bai = 0, puntuazioa = 0, i, j, bukaera = 0, back, pantailaKanpoan = 0;
    char contadorTexto[50];

    // Jokalariaren egoera hasieratzen da
    EGOERA egoera = JOLASTEN;

    // Etsailak hasieratzen dira
    ETSAILAK etsailak[6];

    // Tiroak hasieratzen dira
    TIROA tiroak[MAX_TIROAK] = {0};

    // Soinuak hasieratzen dira
    Mix_Chunk *soinuak[6] = {NULL};

    // Soinuen artxiboak definitzen dira
    const char *soinuenArtxiboak[5] = {"./sound/victory.wav", "./sound/loose.wav", "./sound/water-drop-clean-fx.wav",
                                       "./sound/clap-soft.wav", "./sound/8bit-video-game-music-289970.wav"};

    // Soinuak kargatzen dira
    soinuak[0] = Mix_LoadWAV(soinuenArtxiboak[0]); // irabazi
    soinuak[1] = Mix_LoadWAV(soinuenArtxiboak[1]); // galdu
    soinuak[2] = Mix_LoadWAV(soinuenArtxiboak[2]); // tiro
    soinuak[3] = Mix_LoadWAV(soinuenArtxiboak[3]); // etsaila jo
    soinuak[4] = Mix_LoadWAV(soinuenArtxiboak[4]); // jokoaren musika
    soinuak[5] = Mix_LoadWAV(soinuenArtxiboak[5]); // jokoaren musika

    Mix_PlayChannel(1, soinuak[4], -1);
    Mix_Volume(1, 100);

    // Jokalariaren posizioa hasieratzen da
    jokalaria.pos.x = SCREEN_WIDTH / 2;
    jokalaria.pos.y = SCREEN_HEIGHT / 2;

    // Atzera irudia kargatzen da
    back = irudiaKargatu("./img/back3.bmp");

    // Etsailen irudiak kargatzen dira
    int etsailaImagenId[6];
    for (i = 0; i < 6; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE);
    }

    // Puntuak sortzen dira
    SpawnPuntuakSortu(spawnPuntuak, 6);

    // Etsailak sortzen dira
    for (i = 0; i < 6; i++)
    {
        EtsaiakSortu(&etsailak[i], spawnPuntuak[i].x, spawnPuntuak[i].y, etsailaImagenId[i]);
    }

    // Jokalariaren irudia kargatzen da
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

    // Jokoa hasieratzen da
    while (puntuazioa < 5 && !irten)
    {
        // Ebentuak jaso eta pantaila garbitzen da
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();

        // Jokalariaren mugimendua kontrolatzen da
        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

        // Testua idazten da
        textuaIdatzi(10, 20, "Sakatu irudia");
        textuaIdatzi(10, 60, "Lortu 25 puntu");
        // puntuazioa
        sprintf(contadorTexto, "Puntuazioa: %d", puntuazioa);
        textuaIdatzi(10, 40, contadorTexto);

        // Pantaila berrizten da
        pantailaBerriztu();

        // Etsailak marrazten dira
        for (i = 0; i < 6; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }

        // Tiroa kontrolatzen da
        Disparoa(ebentu, tiroak, jokalaria.pos.x, jokalaria.pos.y);

        // Soinua joaten da
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            Mix_PlayChannel(-1, soinuak[2], 0);
        }

        // Kolisioak kontrolatzen dira
        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < MAX_TIROAK; j++)
            {
                if (KolisioaTiroaEtsaila(etsailak[i].x, etsailak[i].y, tiroak[j].posX, tiroak[j].posY))
                {
                    AldeaAukeratuEtsaila(&etsailak[i].x, &etsailak[i].y);
                    Mix_PlayChannel(-1, soinuak[3], 0);
                    puntuazioa++;
                }
            }

            if (KolisioaJokalariaEtsaila(etsailak[i].x, etsailak[i].y, jokalaria.pos.x, jokalaria.pos.y))
            {
                irten = 1;
            }
        }

        // Jokoa amaitzen da
        if (ebentu == TECLA_RETURN)
        {
            irten = 1;
            egoera = AMAIERA;
            Mix_HaltChannel(1);
        }
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

    // Irudiak kendu
    irudiaKendu(jokalaria.id);

    for (i = 0; i < 6; i++)
    {
        irudiaKendu(etsailaImagenId[i]);
    }

    // Atzera irudia kargatu
    back = irudiaKargatu("./img/back3.bmp");

    // Tarteko pantaila
    if (egoera == IRABAZI)
    {
        TartekoPantaila(&jokalaria.pos.x, &jokalaria.pos.y);
    }
    irudiaKendu(back);
    pantailaGarbitu();
    pantailaBerriztu();
    toggleMusic();
    Mix_FreeChunk(*soinuak);
    return egoera;
}

void LeenengonNibelaAsalpena(void)
{

    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/back3.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();
        textuaIdatzi(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, " Garaitu etsailak ");

        irudiaMugitu(fondo, 0, 0);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}
