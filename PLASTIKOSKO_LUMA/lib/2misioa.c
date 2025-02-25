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
#define SARIA_IMAGE "./img/zaborra.bmp"
#define MAX_TIROAK 100

ETSAILAK etsailak;
SARIAK sariak;
JOKO_ELEMENTUA jokalaria;
PUNTUA spawnPuntuak[6];

// EGOERA BigarrengoMisioa funtzioa, jokoa martxan jartzen du
EGOERA BigarrengoMisioa(void)
{
    // Aldagaiak deklaratu
    int ebentu = 0, irten = 0, bai = 0, SariakKont = 0, kont2 = 0, i, basura, kontBasura = 0, pelotaId, back, Erlojua,
        ErlojuaAktibatuta = 0, j;
    char kontadoreaSariak[50], kontadoreaBasura[50];
    double relojPosx, relojPosy, LuzeeraErlojuaJokalaria;
    int sariarenImagenId[128];

    // EGOERA aldagaia hasieratu
    EGOERA egoera = JOLASTEN;

    // Etsailak, sariak eta tiroak hasieratu
    ETSAILAK etsailak[6];
    SARIAK sariak[128];
    TIROA tiroak[MAX_TIROAK] = {0};

    // Denbora hasieratu
    uint32_t hasierako_denbora = 0, pasatutako_denbora = 0, denbora_geldik;

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

    // Erlojua hasieratu
    relojPosx = rand() % (SCREEN_WIDTH - 32);
    relojPosy = rand() % (SCREEN_HEIGHT - 32);

    // Atzera botoia hasieratu
    back = irudiaKargatu("./img/back4.bmp");

    // Etsailen irudiak hasieratu
    int etsailaImagenId[6];
    for (i = 0; i < 4; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE);
    }
    for (i = 4; i < 6; i++)
    {
        etsailaImagenId[i] = irudiaKargatu(ETSAILA_IMAGE2);
    }

    // Spawn puntuak hasieratu
    SpawnPuntuakSortu(spawnPuntuak, 6);

    // Etsailak hasieratu
    for (i = 0; i < 6; i++)
    {
        EtsaiakSortu(&etsailak[i], spawnPuntuak[i].x, spawnPuntuak[i].y, etsailaImagenId[i]);
    }

    // Jokalaria hasieratu
    jokalaria.pos.x = 0, jokalaria.pos.y = SCREEN_HEIGHT / 2;

    // Irudiak hasieratu
    basura = irudiaKargatu("./img/basura.bmp");
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    Erlojua = irudiaKargatu("./img/reloj.bmp");

    // Pelota hasieratu
    pelotaId = irudiaKargatu("./img/UrPelota.bmp");

    // Irudiak mugitu
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
    irudiaMugitu(pelotaId, 1000, 1000);
    irudiaMugitu(basura, SCREEN_WIDTH - 100, SCREEN_HEIGHT / 2);
    irudiaMugitu(Erlojua, 1000, 1000);

    // Jokoa martxan jartzen duen while bukletan
    while (kontBasura < 16 && !irten)
    {
        // 5ms itxaron
        SDL_Delay(5);
        // Ebentuak jaso
        ebentu = ebentuaJasoGertatuBada();
        // Denbora kontatu
        pasatutako_denbora = denboraLortu(&hasierako_denbora);

        // Pantaila garbitu eta irudiak marraztu
        pantailaGarbitu();
        irudiakMarraztu();

        // Jokalariaren mugimendua kontrolatu
        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

        // Sarien kontadorea pantailaratu
        sprintf(kontadoreaSariak, "Hartutako zaborrak: %d", kont2);
        textuaIdatzi(10, 90, kontadoreaSariak);

        // Basuraren kontadorea pantailaratu
        sprintf(kontadoreaBasura, "Basuran dauden zaborrak: %d", kontBasura);
        textuaIdatzi(10, 120, kontadoreaBasura);

        // Etsaiak mugitu
        if (ErlojuaAktibatuta == 0)
        {
            for (i = 0; i < 4; i++)
            {
                EtsaiakMugitu(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
            }
            for (i = 4; i < 6; i++)
            {
                EtsaiakMugitu2(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
            }
        }

        // Etsailak marraztu
        for (i = 0; i < 6; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
        }

        // Disparoa deitu
        Disparoa(ebentu, tiroak, jokalaria.pos.x, jokalaria.pos.y);

        // Soinuak kontrolatu
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            Mix_PlayChannel(-1, soinuak[2], 0);
        }

        // Kolisioak detektatu
        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < MAX_TIROAK; j++)
            {
                if (KolisioaTiroaEtsaila(etsailak[i].x, etsailak[i].y, tiroak[j].posX, tiroak[j].posY))
                {
                    // Saria sortu
                    sariarenImagenId[SariakKont] = irudiaKargatu(SARIA_IMAGE);
                    SariakIniziau(&sariak[SariakKont], etsailak[i].x, etsailak[i].y, sariarenImagenId[SariakKont]);
                    SariakKont++;
                    Mix_PlayChannel(-1, soinuak[3], 0);
                    AldeaAukeratuEtsaila(&etsailak[i].x, &etsailak[i].y);
                }
            }

            // Jokalariaren eta etsailaren kolisioa detektatu
            if (KolisioaJokalariaEtsaila(etsailak[i].x, etsailak[i].y, jokalaria.pos.x, jokalaria.pos.y))
            {
                irten = 1;
            }
        }

        // Jokalariak saria artzeko
        for (i = 0; i < SariakKont; i++)
        {
            SariaMarraztu(&sariak[i]);
            JokalariakSariaArtu(&kont2, &sariak[i].x, &sariak[i].y, jokalaria.pos.x, jokalaria.pos.y);
        }

        // Basura eta jokalariaren kolisioa detektatu
        if (ebentu == TECLA_SPACE)
        {
            JokalariakBasuraDetektatu(&kont2, &kontBasura, jokalaria.pos.x, jokalaria.pos.y);
        }

        // Erlojua kontrolatu
        if (pasatutako_denbora > 10)
        {
            // Erlojua mugitu
            irudiaMugitu(Erlojua, relojPosx, relojPosy);

            // Erlojua jokalariarekin kolisioa detektatu
            LuzeeraErlojuaJokalaria = sqrt((relojPosx - jokalaria.pos.x) * (relojPosx - jokalaria.pos.x) +
                                           (relojPosy - jokalaria.pos.y) * (relojPosy - jokalaria.pos.y));
            if (LuzeeraErlojuaJokalaria <= 20)
            {
                relojPosx = 1000;
                relojPosy = 1000;
                ErlojuaAktibatuta = 1;
                denbora_geldik = pasatutako_denbora;
            }
        }
        // Jokalariaren eta erlojuaren kolisioa detektatu
        if (denbora_geldik + 10 == pasatutako_denbora)
        {
            ErlojuaAktibatuta = 0;
        }
        // Jokoa amaitu
        if (ebentu == TECLA_RETURN)
        {
            irten = 1;
            egoera = AMAIERA;
            Mix_HaltChannel(1);
        }

        pantailaBerriztu(); // Pantaila "actualizatu"
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

    pantailaGarbitu();
    pantailaBerriztu();

    for (i = 0; i < 6; i++) // Irudiak kendu
    {
        irudiaKendu(etsailaImagenId[i]);
    }
    for (i = 0; i < SariakKont; i++)
    {
        irudiaKendu(sariarenImagenId[i]);
    }
    irudiaKendu(pelotaId);
    irudiaKendu(basura);
    back = irudiaKargatu("./img/back4.bmp");

    if (egoera == IRABAZI) // Jokoa irabazi bada
    {
        TartekoPantaila(&jokalaria.pos.x, &jokalaria.pos.y);
    }
    irudiaKendu(back);
    Mix_FreeChunk(*soinuak);

    return egoera;
}

void BigarrenNibelaAsalpena()
{
    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/back4.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();
        textuaIdatzi(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 70, " Garaitutako etsailak basurak botako dute");
        textuaIdatzi(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 30, " Ahatearekin hartu eta basurara bota");
        textuaIdatzi(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, " Horretarako, basura gainean SPACE eman");

        irudiaMugitu(fondo, 0, 0);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}