#ifndef IMAGEN_H
#define IMAGEN_H

#define MAX_IMG 100

int irudiaKargatu(char *fileName);
void irudiaMugitu(int numImg, double x, double y);
void irudiakMarraztu(void);
void irudiaKendu(int id);

typedef struct Img
{
    int id;
    SDL_Surface *imagen;
    SDL_Texture *texture;
    SDL_Rect dest;

} IMG;

extern IMG irudiak[MAX_IMG];
extern int irudiKop;
extern int id;

#endif
