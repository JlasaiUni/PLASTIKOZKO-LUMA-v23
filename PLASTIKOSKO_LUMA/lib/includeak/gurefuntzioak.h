#ifndef GUREFUNTZIOAK_H
#define GUREFUNTZIOAK_H

#include "main.h"

// GURE FUNTZIOAK.c ----------------------------------------------------------------------------------------------------
void BUKAERA_IRABAZI(void);
void BUKAERA_GALDU(void);
void jokoaAurkeztu(void);
void TartekoPantaila(double *posx, double *posy);
void HasierakoPantaila(void);
JOLAS_AUKERAK ModuaAukeratu(void);
void hasierakoMensajea(void);
void bukaerakoMensajea(void);
void Kontrolak(void);
void SpawnPuntuakSortu(PUNTUA *points, int numPoints);

// ETSAILEN FUNTZIOAK.c ----------------------------------------------------------------------------------------------
void AldeaAukeratuEtsaila(double *x, double *y);
void EtsaiakSortu(ETSAILAK *etsaila, double x, double y, int idImagen);
void EtsaiaMarraztu(ETSAILAK *etsaila);
void JefeFinalaMugitu(double *JefePosY, double abiadura, int *norabidea);
void TiroaJefe(double *disparoPosJefeX, double *disparoPosJefeY, double *disparoBaiJefe, double jefeposx,
               double jefeposy);
void EtsaiakMugitu(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy);
void EtsaiakMugitu3(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy);
void EtsaiakMugitu2(ETSAILAK *etsaila, double JokalariaPosX, double JokalariaPosy);
int KolisioaTiroaEtsaila(double EtsailaX, double EtsailaY, double PelotaX, double PelotaY);

// JOKALARIAREN FUNTZIOAK.c -------------------------------------------------------------------------------------------
void JokalariMugimendu(double *JokalariaPosy, double *jokalariaPosx);
void Disparoa(int ebentu, TIROA tiroak[], double posx, double posy);
int KolisioaPowerUp(TIROA tiroak[], PowerUp *powerUp, double jokalariaX, double jokalariaY);
int KolisioaJokalariaEtsaila(double EtsailaX, double EtsailaY, double jokalariaX, double jokalariaY);
void luzeeraMedikamentuaJokaliriaETALaguna(double MedicinarenPosx, double MedicinarenPosy, double posx, double posy,
                                           int *aurkituta, int *amaiera, int *medikamentua);

// DENBORAREN FUNTZIOAK.c ---------------------------------------------------------------------------------------------
uint32_t denboraLortu(uint32_t *hasierako_denbora);
uint32_t denboraLortuMilisegundo(uint32_t *hasierako_denbora);

// SARIAREN FUNTZIOAK.c -----------------------------------------------------------------------------------------------
void SariaMarraztu(SARIAK *sariak);
void SariakIniziau(SARIAK *sariak, double x, double y, int idImagen);
void JokalariakBasuraDetektatu(int *kont2, int *kontBasura, double posx, double posy);
void JokalariakSariaArtu(int *kont2, double *sariakx, double *sariaky, double posx, double posy);

#endif