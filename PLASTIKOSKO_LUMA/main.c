#include "main.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "lib/includeak/gurefuntzioak.h"
#include "lib/includeak/misioak.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

int main(int argc, char *str[])
{
    // SDL liburutegia hasieratzen
    if (sgHasieratu() == -1)
    {
        // Errorea gertatzen bada, mezua inprimatzen
        fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    // Jokoaren egoerak definitzen
    EGOERA lehen_egoera = JOLASTEN, bigarren_egoera = JOLASTEN, hirugarren_egoera = JOLASTEN,
           laugarren_egoera = JOLASTEN, bosgarren_egoera = JOLASTEN;

    // Jokoaren aukerak definitzen
    int aukera = 0;

    // Testua eta audioa hasieratzen
    textuaGaitu();
    audioInit();

    // Hasierako pantaila erakusten
    HasierakoPantaila();

    // Jokoaren ziklo nagusia
    while (aukera != 3)
    {
        // Jokoaren aukera hautatzen
        aukera = ModuaAukeratu();

        // Jokoaren kontrolak definitzen
        if (aukera != 3)
        {
            Kontrolak();
        }

        // Jokoaren modua hautatzen
        if (aukera == 2)
        {
            OrdaModua();
        }
        if (aukera == 1)
        {
            // Jokoaren egoerak berriro definitzen
            lehen_egoera = JOLASTEN, bigarren_egoera = JOLASTEN, hirugarren_egoera = JOLASTEN,
            laugarren_egoera = JOLASTEN, bosgarren_egoera = JOLASTEN;

            // Kursorra ezkutatzen
            SDL_ShowCursor(0);

            // Hasierako mezua erakusten
            hasierakoMensajea();

            // Jokoa aurkezten
            jokoaAurkeztu();

            // Kursorra berriro erakusten
            SDL_ShowCursor(1);

            // Kursorra aldatzen
            SDL_Cursor *cursor;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
            SDL_SetCursor(cursor);

            // Lehenengo misioa hasieratzen
            LeenengonNibelaAsalpena();

            // Lehenengo misioa jolasten
            while (lehen_egoera == JOLASTEN || lehen_egoera == GALDU)
            {
                lehen_egoera = LehenengoMisioa();

                // Jokoaren amaiera gertatzen bada
                if (lehen_egoera == GALDU)
                {
                    BUKAERA_GALDU();
                }
            }

            // Bigarrengo misioa hasieratzen
            if (lehen_egoera != AMAIERA)
            {
                BigarrenNibelaAsalpena();

                // Bigarrengo misioa jolasten
                while (bigarren_egoera == JOLASTEN || bigarren_egoera == GALDU)
                {
                    bigarren_egoera = BigarrengoMisioa();

                    // Jokoaren amaiera gertatzen bada
                    if (bigarren_egoera == GALDU)
                    {
                        BUKAERA_GALDU();
                    }
                }

                // Hirugarrengo misioa hasieratzen
                if (bigarren_egoera != AMAIERA)
                {
                    HirugarrenNibelaAsalpena();

                    // Hirugarrengo misioa jolasten
                    while (hirugarren_egoera == JOLASTEN || hirugarren_egoera == GALDU)
                    {
                        hirugarren_egoera = HirugarrengoMisioa();

                        // Jokoaren amaiera gertatzen bada
                        if (hirugarren_egoera == GALDU)
                        {
                            BUKAERA_GALDU();
                        }
                    }

                    // Laugarrengo misioa hasieratzen
                    if (hirugarren_egoera != AMAIERA)
                    {
                        LaugarrenNibelaAzalpena();

                        // Laugarrengo misioa jolasten
                        while (laugarren_egoera == JOLASTEN || laugarren_egoera == GALDU)
                        {
                            laugarren_egoera = LaugarrengoMisioa();

                            // Jokoaren amaiera gertatzen bada
                            if (laugarren_egoera == GALDU)
                            {
                                BUKAERA_GALDU();
                            }
                        }

                        // Bosgarrengo misioa hasieratzen
                        if (laugarren_egoera != AMAIERA)
                        {
                            BosgarrenNibelaAsalpena();

                            // Bosgarrengo misioa jolasten
                            while (bosgarren_egoera == JOLASTEN || bosgarren_egoera == GALDU)
                            {
                                bosgarren_egoera = BosgarrengoMisioa();

                                // Jokoaren amaiera gertatzen bada
                                if (bosgarren_egoera == GALDU)
                                {
                                    BUKAERA_GALDU();
                                }
                            }

                            // Jokoaren amaiera erakusten
                            bukaerakoMensajea();
                            BUKAERA_IRABAZI();
                        }
                    }
                }
            }
        }
    }

    // Audioa itxi
    audioTerminate();

    // SDL liburutegia itxi
    sgItxi();

    return 0;
}