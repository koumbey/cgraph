#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "entete.h"

 

/*======================================================================================================*/
int main(int argc, char *argv[])
{
	int taby[]={25,15,20,10,4,5,10,9,9,16,25};
    char *tabx[]= {"toto","titi","truc","machin","chose","tata","ton","son","muche","mou","enfin"};
    SDL_Init(SDL_INIT_VIDEO); /* Démarrage de la SDL (ici : chargement du système vidéo)*/
    TTF_Init();
    
    SDL_Color col ={255,0,0};
    /*char *labels[] = {"x", "y", "y=x^2"};*/
    barplot2(taby,tabx,11,col,"x^2","courbe x^2");
    TTF_Quit();

    SDL_Quit(); /* Arrêt de la SDL (libération de la mémoire).*/

 

    return 0;

}


