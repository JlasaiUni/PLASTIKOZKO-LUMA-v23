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

#define ETSAILA_IMAGE "./img/1etsaila.bmp"
#define ETSAILA_IMAGE2 "./img/2etsaila.bmp"
#define ETSAILA_IMAGE3 "./img/3etsaila.bmp"

ETSAILAK etsailak;
JOKO_ELEMENTUA jokalaria;
PUNTUA spawnPuntuak[10];

// Hirugarrengo misioa: jokalariak 30 segundo egin behar ditu hil gabe
EGOERA HirugarrengoMisioa(void)
{
    // Jokalariaren eta etsailen hasierako posizioak eta egoerak
    int ebentu = 0, irten = 0, i, back, bomba;
    double BombaPosx, BombaPosy, luzeeraBombaJokalaria, posx = 0, posy = SCREEN_HEIGHT / 2;
    char denboraIdatzi[50];

    // Denboraren kontrola
    uint32_t hasierako_denbora = 0, pasatutako_denbora = 0;
    EGOERA egoera = JOLASTEN;
    ETSAILAK etsailak[10];

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

    // Atzeko planoaren irudia kargatu
    back = irudiaKargatu("./img/back0.bmp");

    // Bombaren hasierako posizioa
    BombaPosx = rand() % (SCREEN_WIDTH - 32);
    BombaPosy = rand() % (SCREEN_HEIGHT - 32);

    // Etsailen irudiak kargatu
    int etsailaImagenId[10];
    etsailaImagenId[0] = irudiaKargatu(ETSAILA_IMAGE);
    etsailaImagenId[1] = irudiaKargatu(ETSAILA_IMAGE);
    etsailaImagenId[2] = irudiaKargatu(ETSAILA_IMAGE);
    etsailaImagenId[3] = irudiaKargatu(ETSAILA_IMAGE);
    etsailaImagenId[4] = irudiaKargatu(ETSAILA_IMAGE);
    etsailaImagenId[5] = irudiaKargatu(ETSAILA_IMAGE2);
    etsailaImagenId[6] = irudiaKargatu(ETSAILA_IMAGE2);
    etsailaImagenId[7] = irudiaKargatu(ETSAILA_IMAGE2);
    etsailaImagenId[8] = irudiaKargatu(ETSAILA_IMAGE3);
    etsailaImagenId[9] = irudiaKargatu(ETSAILA_IMAGE3);

    // Etsailen spawn puntuak sortu
    SpawnPuntuakSortu(spawnPuntuak, 10);

    // Etsailak sortu
    for (i = 0; i < 10; i++)
    {
        EtsaiakSortu(&etsailak[i], spawnPuntuak[i].x, spawnPuntuak[i].y, etsailaImagenId[i]);
    }

    // Jokalariaren eta bonbaren irudia kargatu
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    bomba = irudiaKargatu("./img/bomba.bmp");
    irudiaMugitu(jokalaria.id, posx, posy);
    irudiaMugitu(bomba, 10000, 10000);

    // Jokoa hasi
    while (!irten && pasatutako_denbora < 30)
    {
        // 5ms itxaron
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();

        // Denboraren kontrola
        pasatutako_denbora = denboraLortu(&hasierako_denbora);

        // Pantaila garbitu eta irudiak marraztu
        pantailaGarbitu();
        irudiakMarraztu();

        // Jokalaria mugitu
        irudiaMugitu(jokalaria.id, posx, posy);
        JokalariMugimendu(&posy, &posx);

        // Denboraren kontadoria
        sprintf(denboraIdatzi, "Denbora: %d", pasatutako_denbora);
        textuaIdatzi(10, 140, denboraIdatzi);

        for (i = 0; i < 5; i++) // Etsailak marraztu eta mugitu, mugimendu normalarekin
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu(&etsailak[i], posx, posy, 0.3);
        }
        for (i = 5; i < 8; i++) // Etsailak marraztu eta mugitu, mugimendu oszilakorrarekin (cos eta sin)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu2(&etsailak[i], posx, posy, 0.3);
        }
        for (i = 8; i < 10; i++) // Etsailak marraztu eta mugitu, mugimendu oszilakorrarekin (cos)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu3(&etsailak[i], posx, posy, 0.3);
        }

        for (i = 0; i < 10; i++) // Jokalariaren eta etsail guztien kolisioa detektatu
        {
            if (KolisioaJokalariaEtsaila(etsailak[i].x, etsailak[i].y, posx, posy))
            {
                irten = 1;
            }
        }

        if (pasatutako_denbora > 10) // 10 segundu pasu badira
        {
            irudiaMugitu(bomba, BombaPosx, BombaPosy); // Bomba mugitu pos random batera

            luzeeraBombaJokalaria =
                sqrt((BombaPosx - posx + 50) * (BombaPosx - posx + 50) +
                     (BombaPosy - posy + 50) * (BombaPosy - posy + 50)); // Jokalariaren eta bombaren arteko distantzia

            if (luzeeraBombaJokalaria <= 20) // ikutzen badaude
            {
                BombaPosx = 1000;
                BombaPosy = 1000;
                for (i = 0; i < 10; i++)
                {
                    AldeaAukeratuEtsaila(&etsailak[i].x, &etsailak[i].y); // etsailak hasierako posizioetara mugitu
                }
            }
        }

        if (ebentu == TECLA_RETURN) // return ematerakoan irten = 1
        {
            irten = 1;
            egoera = AMAIERA;
            Mix_HaltChannel(1);
        }
        pantailaBerriztu();
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
    for (i = 0; i < 10; i++) // Etsailak argazkiak kendu
    {
        irudiaKendu(etsailaImagenId[i]);
    }

    irudiaKendu(jokalaria.id); // jokalariaren argazkia kendu
    irudiaKendu(bomba);

    pantailaGarbitu();
    pantailaBerriztu();

    if (egoera == IRABAZI) // Tarteko pantaila
    {
        TartekoPantaila(&posx, &posy);
    }

    // Irudiak kendu
    irudiaKendu(back);
    Mix_FreeChunk(*soinuak);
    return egoera;
}
void HirugarrenNibelaAsalpena()
{
    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/back0.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();
        textuaIdatzi(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Aguantatu 30s hil barik ");

        irudiaMugitu(fondo, 0, 0);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}