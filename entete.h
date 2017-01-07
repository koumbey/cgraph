#ifndef _ENTETE_H
#define _ENTETE_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

void pause();

void createPoint(SDL_Rect pos,SDL_Surface *ecran);

void createLine(SDL_Rect p1, SDL_Rect p2,SDL_Color col, SDL_Surface *ecran);

void createAxeV(int pix, int min, int max,int nbstick, SDL_Surface *ecran);

void createAxeH(int pix,int py,int min, int max,int nbstick, SDL_Surface *ecran);

int toPixelV(int val, int min, int max, int pmin, int pmax);

int toPixelH(int val, int min, int max, int pmin, int pmax);

int maximum(int tab[], int taille);

int minimum(int tab[], int taille);

void discretiser(int tab[], int taille,int pas,int* newtab, char *labels[]);

void ploty(int tab[], int taille,SDL_Color col, char *ylabel, char *legend); 

void plotxy(int tabx[], int taby[],int taille, SDL_Color col, char *labels[]);

void nuage_point(int tabx[], int taby[],int taille, char* labels[]);

void barplot(int tab[], int taille, SDL_Color col,char* ylabel, char* legend);

void barplot2(int tab[], char *label[], int taille,SDL_Color col, char* ylabel, char *legend);

#endif
