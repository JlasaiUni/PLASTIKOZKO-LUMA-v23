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

#define ETSAILA_IMAGE "./img/2etsaila.bmp"
#define MAX_TIROAK 100

JOKO_ELEMENTUA jokalaria;
ETSAILAK etsailak;
SARIAK sariak;

void OrdaModua(void)
{
    int ebentu = 0, irten = 0, bai = 0, kont = 0, i, bukaera = 0, pelotaId, j, back, backgroundZenbakia;
    int KontEtsailak, herena;
    char contadorTexto[50];
    char irudiak[20];

    ETSAILAK etsailak[120];
    TIROA tiroak[MAX_TIROAK] = {0};
    PowerUp DisparoKono;
    uint32_t hasierako_denbora = 0, pasatutako_denbora = 0; // hasierako denbora 32 bit eta bakarrik positiboak

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
    DisparoKono.aktibo = 0;

    jokalaria.pos.x = SCREEN_WIDTH / 2, jokalaria.pos.y = SCREEN_HEIGHT / 2; // jokalariaren ezaugarriak

    backgroundZenbakia = rand() % 4;

    snprintf(irudiak, sizeof(irudiak), "./img/back%d.bmp", backgroundZenbakia);
    back = irudiaKargatu(irudiak);

    irudiaMugitu(back, 0, 0);

    int etsailaImagenId[120];
    char denboraIdatzi[50];

    for (j = 0; j < 6; j++)
    {
        etsailaImagenId[j] = irudiaKargatu(ETSAILA_IMAGE);
    }

    // Inicializar pelotas con posiciones y colores diferentes
    EtsaiakSortu(&etsailak[0], 0, 200, etsailaImagenId[0]);
    EtsaiakSortu(&etsailak[1], 400, 0, etsailaImagenId[1]);
    EtsaiakSortu(&etsailak[2], 600, 200, etsailaImagenId[2]);
    EtsaiakSortu(&etsailak[3], 50, 400, etsailaImagenId[3]);
    EtsaiakSortu(&etsailak[4], 1000, 300, etsailaImagenId[4]);
    EtsaiakSortu(&etsailak[5], 200, 1000, etsailaImagenId[5]);

    KontEtsailak = 6;
    DisparoKono.posX = 100;
    DisparoKono.posY = 100;

    // hazierako imagenak kargatzeko
    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp");
    pelotaId = irudiaKargatu("./img/UrPelota.bmp");
    DisparoKono.id = irudiaKargatu("./img/TiroPowerup.bmp");
    irudiaMugitu(DisparoKono.id, DisparoKono.posX, DisparoKono.posY);
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
    irudiaMugitu(pelotaId, 1000, 1000);

    while (!irten) // galdu arte jokatu
    {
        herena = KontEtsailak / 3;
        SDL_Delay(5);
        ebentu = ebentuaJasoGertatuBada();
        pasatutako_denbora = denboraLortuMilisegundo(&hasierako_denbora);

        // Limpiar la pantalla
        pantailaGarbitu();
        irudiakMarraztu();

        // Mover el jugador
        JokalariMugimendu(&jokalaria.pos.y, &jokalaria.pos.x);
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);

        // puntuazioa idatzi
        sprintf(contadorTexto, "Puntuazioa: %d", kont);
        textuaIdatzi(10, 40, contadorTexto);
        // pasatutako denbora idatzi
        sprintf(denboraIdatzi, "Denbora: %d", pasatutako_denbora / 1000);
        textuaIdatzi(10, 80, denboraIdatzi);

        // etsaiak marraztu eta mugitu
        for (i = 0; i < herena; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }
        for (i = herena; i < herena * 2; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu2(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }
        for (i = herena * 2; i < KontEtsailak; i++)
        {
            EtsaiaMarraztu(&etsailak[i]);
            EtsaiakMugitu3(&etsailak[i], jokalaria.pos.x, jokalaria.pos.y);
        }
        // Soinua joaten da
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            Mix_PlayChannel(-1, soinuak[2], 0);
        }

        // tiroari deitu
        Disparoa(ebentu, tiroak, jokalaria.pos.x, jokalaria.pos.y);

        // disparo triplea powerup-a (no va)
        KolisioaPowerUp(tiroak, &DisparoKono, jokalaria.pos.x, jokalaria.pos.y);

        if ((pasatutako_denbora % 10000 == 0) && (KontEtsailak < 120)) // etsail berriak sortu 10 segunduro
        {
            for (j = KontEtsailak; j < KontEtsailak + 3; j++)
            {
                etsailaImagenId[j] = irudiaKargatu(ETSAILA_IMAGE);
                EtsaiakSortu(&etsailak[j], 50, 400, etsailaImagenId[j]);
                AldeaAukeratuEtsaila(&etsailak[j].x, &etsailak[j].y);
                EtsaiaMarraztu(&etsailak[j]);
            }

            KontEtsailak = KontEtsailak + 3;
        }

        /*
        if (pasatutako_denbora > 10000 && DisparoKono.activo == 0)
                {
                    irudiaMugitu(DisparoKono.id, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                }
                else
                {
                    irudiaMugitu(DisparoKono.id, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                }
        */

        // Kolisioak detektatu etsaila eta tiroan artean
        for (i = 0; i < KontEtsailak; i++)
        {
            for (j = 0; j < MAX_TIROAK; j++)
            {
                if (KolisioaTiroaEtsaila(etsailak[i].x, etsailak[i].y, tiroak[j].posX, tiroak[j].posY))
                {
                    AldeaAukeratuEtsaila(&etsailak[i].x, &etsailak[i].y);
                    Mix_PlayChannel(-1, soinuak[3], 0);
                    kont++;
                }
            }

            if (KolisioaJokalariaEtsaila(etsailak[i].x, etsailak[i].y, jokalaria.pos.x, jokalaria.pos.y))
            {
                irten = 1;
            }
        }

        if (ebentu == TECLA_RETURN) // return sakatu bada irten
        {
            irten = 1;
            Mix_HaltChannel(1);
        }
        pantailaBerriztu();
    }

    irudiaKendu(jokalaria.id);

    for (i = 0; i < KontEtsailak; i++)
    {
        irudiaKendu(etsailaImagenId[i]);
    }

    irudiaKendu(pelotaId);

    pantailaGarbitu();
    pantailaBerriztu();
    irudiaKendu(back);
    irudiaKendu(DisparoKono.id);

    Puntuazioa(kont, pasatutako_denbora);
    toggleMusic();
}

void Puntuazioa(int kont, int pasatutako_denbora)
{
    int egoera = 0, ebentu, fondo;
    char Punt[10];
    char Denb[10];

    arkatzKoloreaEzarri(0x00, 0x00, 0x00);
    fondo = irudiaKargatu("./img/PBL_puntuaziopantaila.bmp");
    sprintf(Punt, "%d puntu", kont);

    pasatutako_denbora = pasatutako_denbora / 1000;
    sprintf(Denb, "%d s", pasatutako_denbora);

    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiakMarraztu();

        irudiaMugitu(fondo, 0, 0);

        textuaIdatzibeltza(480, 210, Punt);
        textuaIdatzibeltza(480, 310, Denb);

        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}
