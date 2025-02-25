#define _CRT_SECURE_NO_WARNINGS
#include "./includeak/gurefuntzioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

uint32_t denboraLortu(uint32_t *hasierako_denbora)
{
    // Inicializar el tiempo inicial si es la primera llamada
    if (*hasierako_denbora == 0)
    {
        *hasierako_denbora = SDL_GetTicks();
    }

    // Calcular y devolver el tiempo transcurrido en segundos
    return ((SDL_GetTicks() - *hasierako_denbora) / 1000);
}
uint32_t denboraLortuMilisegundo(uint32_t *hasierako_denbora)
{
    // Inicializar el tiempo inicial si es la primera llamada
    if (*hasierako_denbora == 0)
    {
        *hasierako_denbora = SDL_GetTicks();
    }

    // Calcular y devolver el tiempo transcurrido en segundos
    return (SDL_GetTicks() - *hasierako_denbora);
}