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
#define ETSAILA_IMAGE3 "./img/3etsaila.bmp"
#define MAX_TIROAK 100

ETSAILAK etsailak;
SARIAK sariak;
JOKO_ELEMENTUA jokalaria;
PUNTUA spawnPuntuak[6];

// LaugarrengoMisioa funtzioa: jokalariak medikamentua lortu behar du eta ahateari eman behar dio
EGOERA LaugarrengoMisioa(void)
{
    // Aldagaiak definitu
    int ebentu = 0, irten = 0, bai = 0, i, j, hasi = 0, laguna, medikamentua, dialogua, aurkituta = 0, amaiera = 0,
        back, pelotaId, MedicinarenPosx, MedicinarenPosy, denbora;

    // Jokalariaren egoera definitu
    EGOERA egoera = JOLASTEN;

    // Etsailak definitu
    ETSAILAK etsailak[6];

    // Tiroak definitu
    TIROA tiroak[MAX_TIROAK] = {0};

    // Denbora definitu
    uint32_t hasierako_denbora = 0, pasatutako_denbora = 0;

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

    // Jokalariaren hasierako posizioa definitu
    jokalaria.pos.x = 0, jokalaria.pos.y = SCREEN_HEIGHT / 2;

    // Medikamentuaren hasierako posizioa definitu
    MedicinarenPosx = rand() % (SCREEN_WIDTH - 32);
    MedicinarenPosy = rand() % (SCREEN_HEIGHT - 32);

    // Denbora definitu
    denbora = rand() % (100 - 20 + 1) + 20; // 20tik 100 ra hauzazko zenbaki bat

    // Imagenak kargatu
    back = irudiaKargatu("./img/back2.bmp");
    laguna = irudiaKargatu("./img/PATOENFERMO.bmp");
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    pelotaId = irudiaKargatu("./img/UrPelota.bmp");
    dialogua = irudiaKargatu("./img/dialogo.bmp");
    medikamentua = irudiaKargatu("./img/PBL-medkit.bmp");

    // Imagenak mugitu
    irudiaMugitu(medikamentua, 10000, 10000);
    irudiaMugitu(dialogua, 10000, 10000);
    irudiaMugitu(pelotaId, 10000, 10000);
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
    irudiaMugitu(laguna, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 60);

    // Jokoa hasi baino lehen
    while (hasi == 0)
    {
        // Ebentuak jaso
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();

        // Pantaila garbitu
        pantailaGarbitu();

        // Jokalariaren mugimendua
        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

        // Dialogoa marraztu
        irudiaMugitu(dialogua, 200, 120);
        textuaIdatzi(SCREEN_WIDTH / 2 + 70, SCREEN_HEIGHT / 2 + 100, "sakatu SPACE jolasa hasteko");

        // SPACE sakatu bada
        if (ebentu == TECLA_SPACE)
        {
            hasi = 1;
        }
        // RETURN sakatu bada
        if (ebentu == TECLA_RETURN)
        {
            hasi = 1;
            egoera = AMAIERA;
            Mix_HaltChannel(1);
        }

        // Pantaila berriztu
        irudiakMarraztu();
        pantailaBerriztu();
    }

    // Dialogoa kendu
    irudiaKendu(dialogua);

    // Etsailak sortu
    int etsailaImagenId[6];
    for (i = 0; i < 4; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE);
    }
    for (i = 4; i < 6; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE3);
    }

    // Spawn puntuak sortu
    SpawnPuntuakSortu(spawnPuntuak, 6);

    // Etsailak sortu
    for (i = 0; i < 6; i++)
    {
        EtsaiakSortu(&etsailak[i], spawnPuntuak[i].x, spawnPuntuak[i].y, etsailaImagenId[i]);
    }

    // Jokoa
    while (amaiera == 0 && !irten && egoera != AMAIERA)
    {
        // Ebentuak jaso
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();

        // Pantaila garbitu
        pantailaGarbitu();
        irudiakMarraztu();

        // Jokalariaren mugimendua
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);

        // Etsailak marraztu eta mugitu
        for (i = 0; i < 4; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }
        for (i = 4; i < 6; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu3(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }

        // Disparoa
        Disparoa(ebentu, tiroak, jokalaria.pos.x, jokalaria.pos.y);

        // SAGU_BOTOIA_EZKERRA sakatu bada
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            Mix_PlayChannel(-1, soinuak[2], 0);
        }

        // Kolisioak
        for (i = 0; i < 6; i++)
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

        // Medikamentua lortu
        luzeeraMedikamentuaJokaliriaETALaguna(MedicinarenPosx, MedicinarenPosy, jokalaria.pos.x, jokalaria.pos.y,
                                              &aurkituta, &amaiera, &medikamentua);

        // denbora batera medikamentua ateratzen da
        pasatutako_denbora = denboraLortu(&hasierako_denbora);

        // 15 segundo pasa ostean medikamentua pos random batera mugitu
        if ((pasatutako_denbora >= 15) && (aurkituta == 0))
        {
            irudiaMugitu(medikamentua, MedicinarenPosx, MedicinarenPosy);
        }

        // return sakatu bada irten
        if (ebentu == TECLA_RETURN)
        {
            irten = 1;
            egoera = AMAIERA;
            toggleMusic();
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

    // argazki guztiak kendu
    for (i = 0; i < 6; i++)
    {
        irudiaKendu(etsailaImagenId[i]);
    }

    irudiaKendu(jokalaria.id);
    irudiaKendu(laguna);
    irudiaKendu(medikamentua);
    pantailaGarbitu();
    pantailaBerriztu();

    back = irudiaKargatu("./img/back2.bmp");
    if (egoera == IRABAZI)
    {
        TartekoPantaila(&jokalaria.pos.x, &jokalaria.pos.y);
    }
    irudiaKendu(back);
    Mix_FreeChunk(*soinuak);
    return egoera;
}

void LaugarrenNibelaAzalpena()
{

    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/back2.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();
        textuaIdatzi(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 40, "Aguantatu medikamentua lortu harte ");
        textuaIdatzi(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 10, "gero heman ahateari ");

        irudiaMugitu(fondo, 0, 0);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}