#include "./includeak/gurefuntzioak.h"
#include "./includeak/misioak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

void SariaMarraztu(SARIAK *sariak)
{
    irudiaMugitu(sariak->id, sariak->x, sariak->y);
}

void SariakIniziau(SARIAK *sariak, double x, double y, int idImagen)
{
    sariak->x = x;
    sariak->y = y;
    sariak->id = idImagen;
}
void JokalariakSariaArtu(int *kont2, double *sariakx, double *sariaky, double posx, double posy)
{
    double luzeeraSariaJokaliria;

    luzeeraSariaJokaliria = sqrt((*sariakx - posx) * (*sariakx - posx) + (*sariaky - posy) * (*sariaky - posy));

    if ((luzeeraSariaJokaliria <= 20) && (*kont2 < 4))
    {
        *kont2 = *kont2 + 1;
        *sariakx = 1000;
        *sariaky = 1000;
    }
}
void JokalariakBasuraDetektatu(int *kont2, int *kontBasura, double posx, double posy)
{
    double luzeeraBasuraJokaliria;
    luzeeraBasuraJokaliria = sqrt(((SCREEN_WIDTH - 100) - posx) * ((SCREEN_WIDTH - 100) - posx) +
                                  ((SCREEN_HEIGHT / 2) - posy) * ((SCREEN_HEIGHT / 2) - posy));

    if (luzeeraBasuraJokaliria < 20)
    {
        *kontBasura = *kontBasura + *kont2;
        *kont2 = 0;
    }
}