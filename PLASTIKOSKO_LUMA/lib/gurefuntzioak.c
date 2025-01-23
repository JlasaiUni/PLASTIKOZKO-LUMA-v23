#define _CRT_SECURE_NO_WARNINGS
#include "./includeak/gurefuntzioak.h"
#include "./includeak/misioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

JOKO_ELEMENTUA jokalaria;
void jokoaAurkeztu(void)
{
    int ebentu = 0, kont = 0, i = 0, irudiakId[4];
    char irudiak[20];

    while (i <= 4)
    {
        irudiakId[i] = -1;
        i++;
    }

    pantailaBerriztu(); // irudi bat zartzen dan bakoitzian pantaila berriztu behar da
    snprintf(irudiak, sizeof(irudiak), "./img/Kaiola_%d.bmp", kont);
    irudiakId[kont] = irudiaKargatu(irudiak);

    irudiaMugitu(irudiakId[kont], 0, 0);
    irudiakMarraztu();

    pantailaBerriztu();

    do
    {

        ebentu = ebentuaJasoGertatuBada();

        if (ebentu == TECLA_SPACE)
        {
            irudiaKendu(irudiakId[kont]);

            kont++;

            snprintf(irudiak, sizeof(irudiak), "./img/Kaiola_%d.bmp", kont);
            irudiakId[kont] = irudiaKargatu(irudiak);
            irudiaMugitu(irudiakId[kont], 0, 0);
            irudiakMarraztu();

            pantailaBerriztu();
        }

    } while (kont < 5); // bost aldiz ezpazioa saktuta beste pantailara doia

    pantailaGarbitu();
}

void BUKAERA_GALDU()
{
    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/GAME-OVER.bmp");
    irudiaMugitu(fondo, 0, 0);
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();
        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

        if (ebentu == TECLA_RETURN)
        {
            egoera = 1;
        }
    }
    irudiaKendu(fondo);
}

void BUKAERA_IRABAZI()
{
    int ebentu = 0, kont = 0, i = 0, irudia2, irten = 0, idAldaketa;
    POSIZIOA Saguarenpos;
    pantailaGarbitu();
    irudia2 = irudiaKargatu("./img/lakua garbi 0.bmp");

    do
    {
        ebentu = ebentuaJasoGertatuBada();
        pantailaGarbitu();
        irudiaMugitu(irudia2, 0, 0);
        irudiakMarraztu();
        Saguarenpos = saguarenPosizioa();
        if (Saguarenpos.x > 109 && Saguarenpos.x < 269 && Saguarenpos.y > 360 && Saguarenpos.y < 590)
        {
            if (idAldaketa == 0)
            {
                idAldaketa = irudiaKargatu("./img/lakua garbi 1.bmp");
            }
            irudiaMugitu(idAldaketa, 0, 0);
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                irten = 1;
            }
        }
        else
        {
            if (idAldaketa != 0)
            {
                irudiaKendu(idAldaketa);
                idAldaketa = 0;
                irudia2 = irudiaKargatu("./img/lakua garbi 0.bmp");
            }
        }
        irudiaMugitu(irudia2, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

    } while (irten == 0); // bost aldiz ezpazioa saktuta beste pantailara doia

    pantailaGarbitu();
}

void TartekoPantaila(double *posx, double *posy)
{
    int bukaera = 0, ebentu;
    double posx2 = *posx, posy2 = *posy;

    jokalaria.id = irudiaKargatu("./img/ahate berria.bmp"); // jokalariaren irudia kargatu

    while (bukaera == 0)
    {
        SDL_Delay(5); // 5 milisegundu itxaron

        ebentu = ebentuaJasoGertatuBada(); // ebentua jaso

        // jokalariaren irudia mugitu
        JokalariMugimendu(&posy2, &posx2);
        irudiaMugitu(jokalaria.id, posx2, posy2);

        if ((posx2 >= SCREEN_WIDTH - 40) && (posy2 > 200) && (posy2 < 300)) // hurrengo pantailara pasatzeko baldintza
        {
            bukaera = 1;
        }

        irudiakMarraztu();
        pantailaBerriztu();
        pantailaGarbitu();
    }
    irudiaKendu(jokalaria.id);
}
void HasierakoPantaila(void)
{
    int running = 1;

    // Cargar imagen de fondo
    int backgroundId = irudiaKargatu("./img/PBL_laku_zikina.bmp");
    irudiaMugitu(backgroundId, 0, 0);

    while (running) //"space" tecla sakatzean pantaila bukatu
    {
        int ebentua = ebentuaJasoGertatuBada();

        if (ebentua == TECLA_SPACE)
        {
            running = 0;
        }

        pantailaGarbitu();
        irudiakMarraztu();
        pantailaBerriztu();
    }

    irudiaKendu(backgroundId);
}

int ModuaAukeratu(void)
{
    // aldagaiak deklaratu
    int egoera = 0, ebentu, fondo, aukera = 0, idAldaketa;
    POSIZIOA Saguarenpos;

    fondo = irudiaKargatu("./img/PBL_aukeraketapantaila_dana_itzalita.bmp"); // fondo irudia kargatu

    do
    {
        ebentu = ebentuaJasoGertatuBada(); // ebentua jaso
        pantailaGarbitu();
        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        Saguarenpos = saguarenPosizioa(); // saguaren posizioa gorde

        // sagua 1 kuboaren gainean dagoenean
        if (Saguarenpos.x > 102 && Saguarenpos.x < 260 && Saguarenpos.y > 200 && Saguarenpos.y < 420)
        {
            if (idAldaketa == 0) // irudia ez bada aldatu...
            {
                // kartela piztuta irudia kargatu
                idAldaketa = irudiaKargatu("./img/PBL_aukeraketapantaila_jolastu_piztuta.bmp");
            }
            irudiaMugitu(idAldaketa, 0, 0);

            if (ebentu == SAGU_BOTOIA_EZKERRA) // saguaren botoia ezkerrera klik egitean misioak modua aukeratu
            {
                egoera = 1;
                aukera = 1;
            }
        }

        // sagua 2 kuboaren gainean dagoenean
        else if ((Saguarenpos.x > 333 && Saguarenpos.x < 480 && Saguarenpos.y > 200 && Saguarenpos.y < 420))
        {
            if (idAldaketa == 0) // irudia ez bada aldatu...
            {
                idAldaketa = irudiaKargatu("./img/PBL_aukeraketapantaila_iraupena_piztuta.bmp"); // irudi berria kargatu
            }
            irudiaMugitu(idAldaketa, 0, 0);

            if (ebentu == SAGU_BOTOIA_EZKERRA) // saguaren botoia ezkerrera klik egitean erronka modua aukeratu
            {
                egoera = 1;
                aukera = 2;
            }
        }
        // sagua 3 kuboaren gainean dagoenean
        else if ((Saguarenpos.x > 550 && Saguarenpos.x < 700 && Saguarenpos.y > 200 && Saguarenpos.y < 420))
        {
            if (idAldaketa == 0) // irudia ez bada aldatu...
            {
                idAldaketa = irudiaKargatu("./img/PBL_aukeraketapantaila_irten_piztuta.bmp"); // irudi berria kargatu
            }
            irudiaMugitu(idAldaketa, 0, 0);

            if (ebentu == SAGU_BOTOIA_EZKERRA) // saguaren botoia ezkerrera klik egitean irten
            {
                egoera = 1;
                aukera = 3;
            }
        }

        else
        {
            if (idAldaketa != 0) // irudia aldatu bada...
            {
                irudiaKendu(idAldaketa);
                idAldaketa = 0;
                fondo = irudiaKargatu("./img/PBL_aukeraketapantaila_dana_itzalita.bmp");
            }
        }
        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

    } while (egoera == 0);
    irudiaKendu(fondo);
    return aukera;
}

void hasierakoMensajea()
{
    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/historia1.bmp");

    while (egoera == 0) // "space" tekla eman arte
    {
        ebentu = ebentuaJasoGertatuBada(); // ebentua jaso

        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}

void bukaerakoMensajea()
{
    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/historia2.bmp");

    while (egoera == 0) // "space" tekla eman arte
    {
        ebentu = ebentuaJasoGertatuBada(); // ebentua jaso

        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}

void Kontrolak()
{

    int egoera = 0, ebentu, fondo;
    fondo = irudiaKargatu("./img/PBL_kontrolak.bmp");
    while (egoera == 0)
    {
        ebentu = ebentuaJasoGertatuBada();

        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        pantailaBerriztu();

        if (ebentu == TECLA_SPACE)
        {
            egoera = 1;
        }
    }

    irudiaKendu(fondo);
}

void SpawnPuntuakSortu(PUNTUA *points, int numPoints)
{
    // aldagaia deklaratu
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    double angle, radius = hypot(SCREEN_WIDTH, SCREEN_HEIGHT) / 2 - 50;

    for (int i = 0; i < numPoints; i++) // sortu "numPoints" puntu zirkuloan
    {
        angle = (2 * M_PI / numPoints) * i;
        points[i].x = centerX + (int)(radius * cos(angle));
        points[i].y = centerY + (int)(radius * sin(angle));
    }
}