#include "entete.h"

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

 /*===========================================================================================================*/
void createPoint(SDL_Rect pos,SDL_Surface *ecran)
{
   SDL_Surface *unit = NULL;
   pos.x = pos.x -2;
   pos.y = pos.y -2;
   unit = SDL_CreateRGBSurface(SDL_HWSURFACE,5,5,32,0,0,0,0);
   SDL_BlitSurface(unit,NULL,ecran,&pos);
   SDL_Flip(ecran);
   SDL_FreeSurface(unit);
}
 /*===========================================================================================================*/
void createLine(SDL_Rect p1, SDL_Rect p2,SDL_Color col, SDL_Surface *ecran)
{
	SDL_Surface *unit = NULL;
	int lg =0;
	if (p1.x == p2.x){
         if (p1.y-p2.y >0){
         	  lg = p1.y -p2.y;
         	  SDL_Rect pos = p2;
		      unit = SDL_CreateRGBSurface(SDL_HWSURFACE,1,lg,32,0,0,0,0);
          SDL_FillRect(unit, NULL, SDL_MapRGB(unit->format, col.r, col.g,col.b));
		      SDL_BlitSurface(unit,NULL,ecran,&pos);
		   } else {
		   	  lg = p2.y -p1.y;
		   	  SDL_Rect pos = p1;
		      unit = SDL_CreateRGBSurface(SDL_HWSURFACE,1,lg,32,0,0,0,0);
          SDL_FillRect(unit, NULL, SDL_MapRGB(unit->format, col.r, col.g,col.b));
		      SDL_BlitSurface(unit,NULL,ecran,&pos);
		   }
	} else if (p1.y == p2.y){
		if (p1.x-p2.x >0){
         	  lg = p1.x -p2.x;
		      unit = SDL_CreateRGBSurface(SDL_HWSURFACE,lg,1,32,0,0,0,0);
          SDL_FillRect(unit, NULL, SDL_MapRGB(unit->format, col.r, col.g,col.b));
		      SDL_BlitSurface(unit,NULL,ecran,&p2);
		   } else {
		   	  lg = p2.x -p1.x;
		      unit = SDL_CreateRGBSurface(SDL_HWSURFACE,lg,1,32,0,0,0,0);
          SDL_FillRect(unit, NULL, SDL_MapRGB(unit->format, col.r, col.g,col.b));
		      SDL_BlitSurface(unit,NULL,ecran,&p1);
		   }
	}else {
		unit = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
    SDL_FillRect(unit, NULL, SDL_MapRGB(unit->format, col.r, col.g,col.b));
		int i =0;
        int lx = (p1.x-p2.x < 0)?p2.x-p1.x:p1.x-p2.x;
        int ly = (p1.y-p2.y < 0)?p2.y-p1.y:p1.y-p2.y;
        if(lx >ly){
        	float a = (p1.y-p2.y*1.00)/(p1.x-p2.x);
        	float b = p1.y - a*p1.x;
		   if(p1.x < p2.x) {
              SDL_Rect pos = p1;
              for (i=0; i<lx; i++){
            	 pos.x = pos.x+1;
            	 pos.y = a*pos.x +b;
            	 SDL_BlitSurface(unit,NULL,ecran,&pos);
               }
		    } else {
             SDL_Rect pos = p2;
             for (i=0; i<lx; i++){
            	 pos.x = pos.x+1;
            	 pos.y = a*pos.x +b;
            	 SDL_BlitSurface(unit,NULL,ecran,&pos);
                }
		    }
	  } else {
            float a = (p1.x-p2.x*1.00)/(p1.y-p2.y);
        	float b = p1.x - a*p1.y;
		   if(p1.y < p2.y) {
              SDL_Rect pos = p1;
              for (i=0; i<ly; i++){
            	 pos.y = pos.y+1;
            	 pos.x = a*pos.y +b;
            	 SDL_BlitSurface(unit,NULL,ecran,&pos);
               }
		    } else {
             SDL_Rect pos = p2;
             for (i=0; i<ly; i++){
            	 pos.y = pos.y+1;
            	 pos.x = a*pos.y +b;
            	 SDL_BlitSurface(unit,NULL,ecran,&pos);
                }
		    } 
	  }
	}

  SDL_Flip(ecran);
	SDL_FreeSurface(unit);
}

 /*=====================================================================================*/
void createAxeV(int pix, int min, int max,int nbstick, SDL_Surface *ecran)
{
	int i =0;
	int pas = pix/nbstick;
	char ch[10];
    TTF_Font *police =NULL;
	SDL_Color noir ={0,0,0};
	police = TTF_OpenFont("times.ttf",11);
    SDL_Surface *texte ;
    SDL_Surface *Axe =NULL;
    SDL_Surface *stick =NULL;
    float ps = (max - min)/(1.00*nbstick);

       SDL_Rect pos ={40,40};
       stick = SDL_CreateRGBSurface(SDL_HWSURFACE,8,1,32,0,0,0,0);
       Axe= SDL_CreateRGBSurface(SDL_HWSURFACE,1,pix,32,0,0,0,0);
       SDL_BlitSurface(Axe,NULL, ecran,&pos);
       for (i=0; i<= nbstick; i++){
       	pos.x =36;
    	pos.y = pix-(i*pas)+40;
        sprintf(ch, "%.1f",min+ (i*ps));
        texte = TTF_RenderText_Blended(police,ch, noir); 
    	SDL_BlitSurface(stick,NULL, ecran,&pos);
    	pos.x =10;
    	SDL_BlitSurface(texte,NULL, ecran,&pos);
      }
     TTF_CloseFont(police);
     SDL_Flip(ecran);
     SDL_FreeSurface(texte);
     SDL_FreeSurface(Axe);
     SDL_FreeSurface(stick);
}

 /*======================================================================================*/
void createAxeH(int pix,int py,int min, int max,int nbstick, SDL_Surface *ecran)
{
	int i =0;
	int pas = pix/nbstick;
	char ch[10];
  TTF_Font *police =NULL;
	SDL_Color noir ={0,0,0};
	police = TTF_OpenFont("times.ttf",11);
    SDL_Surface *texte ;
    SDL_Surface *Axe =NULL;
    SDL_Surface *stick =NULL;
    float ps = (max - min)/(1.00*nbstick);

       SDL_Rect pos ={40,py+40};
       stick = SDL_CreateRGBSurface(SDL_HWSURFACE,1,8,32,0,0,0,0);
       Axe= SDL_CreateRGBSurface(SDL_HWSURFACE,pix,1,32,0,0,0,0);
       SDL_BlitSurface(Axe,NULL, ecran,&pos);
       for (i=0; i<= nbstick; i++){
       	pos.x =40+(i*pas);
    	pos.y = py+36;
        sprintf(ch, "%.1f",min+ (i*ps));
        texte = TTF_RenderText_Blended(police,ch, noir); 
    	SDL_BlitSurface(stick,NULL, ecran,&pos);
    	pos.y =py+45; pos.x =pos.x-5;
    	SDL_BlitSurface(texte,NULL, ecran,&pos);
      }
     TTF_CloseFont(police);
     SDL_Flip(ecran);
     SDL_FreeSurface(texte);
     SDL_FreeSurface(Axe);
     SDL_FreeSurface(stick);
}
 /*======================================================================================================*/
int toPixelV(int val, int min, int max, int pmin, int pmax)
{   
	float aux, rep;
	rep  = 1.00*(pmin-pmax)/(max-min);
	aux = pmax + ((val-min)*rep);
	int res = (int)aux;

    return(res);
}
 /*======================================================================================================*/
int toPixelH(int val, int min, int max, int pmin, int pmax)
{
	float aux, rep;
	rep  = 1.00*(pmax-pmin)/(max-min);
	aux = pmin + ((val-min)*rep);
	int res = (int)aux;
    return(res);
}

 /*======================================================================================================*/
int maximum(int tab[], int taille)
{
	int i=0;
	int res = tab[i];
	for (i=1; i<taille; i++){
		if (tab[i]>res){
			res = tab[i];
		}
	}
   return (res);
}

 /*========================================================================================================*/
int minimum(int tab[], int taille)
{
	int i=0;
	int res = tab[i];
	for (i=1; i<taille; i++){
		if (tab[i]<res){
			res = tab[i];
		}
	}
   return (res);
}
/* =======================================================================================================*/
void discretiser(int tab[], int taille,int pas,int* newtab, char *labels[])
{
  int max = maximum(tab, taille);
  int min = minimum(tab, taille);
  int nb =(max - min)/pas;
  int k=0 , i=0;
  char ch[20];
  nb = (nb*pas == max- min)?nb:nb+1;
  newtab =(int*)malloc(nb*sizeof(int));
  for (i=0; i<taille; i++){
    newtab[i]=0;
  }
  for(i=0; i<taille; i++){
    k = (tab[i]-min)/pas;
    newtab[k]++;
  }
  for(i=0; i<nb; i++){
      sprintf(ch,"[%d,%d[",min+i*pas, min+(i+1)*pas);
      labels[i] =ch;
  }

}
/*=======================================================================================================*/
void ploty(int tab[], int taille, SDL_Color col, char *ylabel, char *legend)
{
    int px =700,py =560;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(px+80, py+80, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Figure 1", NULL);
    SDL_FillRect(ecran,NULL, SDL_MapRGB(ecran ->format,255,255,255));
	  int max = maximum(tab,taille);
	  int min = minimum(tab,taille);
	  createAxeH(px,py,1,taille,taille-1,ecran);
	  createAxeV(py, min, max,taille-1, ecran);
    TTF_Font *police =NULL;
    SDL_Color noir ={0,0,0};
    police = TTF_OpenFont("times.ttf",20);
    SDL_Surface *texte ;
	 int i=0; 
	SDL_Rect p1, p2;
	for(i=0; i<taille-1; i++){
		p1.x = toPixelH(i+1,1,taille,40,px+40);
		p2.x = toPixelH(i+2,1,taille,40,px+40);
		p1.y =toPixelV(tab[i],min,max,40,py+40);
		createPoint(p1,ecran);
		p2.y =toPixelV(tab[i+1],min,max,40,py+40);
		createLine(p1,p2,col ,ecran);
	}
  SDL_Rect pos ={20, 20};
  texte = TTF_RenderText_Blended(police,ylabel, noir); 
  SDL_BlitSurface(texte,NULL, ecran,&pos);
  SDL_Color fond ={0,255,0};
  texte = TTF_RenderText_Shaded(police,legend, noir,fond); 
  pos.x =px-(texte->w/2); pos.y =35;
  SDL_BlitSurface(texte,NULL, ecran, &pos);
	createPoint(p2,ecran);

  SDL_Flip(ecran);
  pause();
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(ecran);
}
 /*======================================================================================================*/
void plotxy(int tabx[], int taby[],int taille, SDL_Color col, char *labels[]) 
{
    int px =700,py =560;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(px+80, py+80, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Figure 1", NULL);
    SDL_FillRect(ecran,NULL, SDL_MapRGB(ecran ->format,255,255,255));
	int Max = maximum(tabx,taille);
	int mix = minimum(tabx,taille);
	int May = maximum(taby,taille);
	int miy = minimum(taby,taille);
	createAxeH(px,py,mix,Max,taille-1,ecran);
	createAxeV(py, miy, May,taille-1, ecran);
	int i=0; 
    TTF_Font *police =NULL;
    SDL_Color noir ={0,0,0};
    police = TTF_OpenFont("times.ttf",20);
    SDL_Surface *texte ;
	SDL_Rect p1, p2;
	for(i=0; i<taille-1; i++){
		p1.x = toPixelH(tabx[i],mix,Max,40,px+40);
		p2.x = toPixelH(tabx[i+1],mix,Max,40,px+40);
		p1.y =toPixelV(taby[i],miy,May,40,py+40);
		p2.y =toPixelV(taby[i+1],miy,May,40,py+40);
		createLine(p1,p2,col ,ecran);
	}

  SDL_Rect pos ={40, 15};
  texte = TTF_RenderText_Blended(police,labels[1], noir); 
  pos.x -= (texte->w/2);
  SDL_BlitSurface(texte,NULL, ecran,&pos);
  SDL_Color fond ={0,255,0};
  texte = TTF_RenderText_Shaded(police,labels[2], noir,fond); 
  pos.x =px-(texte->w/2); pos.y =35;
  SDL_BlitSurface(texte,NULL, ecran, &pos);
  texte = TTF_RenderText_Blended(police,labels[0], noir); 
  pos.x = px+60-(texte->w); pos.y =py+20;
  SDL_BlitSurface(texte,NULL, ecran, &pos);

  SDL_Flip(ecran);
  pause();
  TTF_CloseFont(police); 
  SDL_FreeSurface(texte); 
  SDL_FreeSurface(ecran);
}
 /*=======================================================================================================*/
void nuage_point(int tabx[], int taby[],int taille, char* labels[])
{
    int px =700,py =560;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(px+80, py+80, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Figure 1", NULL);
    SDL_FillRect(ecran,NULL, SDL_MapRGB(ecran ->format,255,255,255));
	  int Max = maximum(tabx,taille);
	  int mix = minimum(tabx,taille);
	  int May = maximum(taby,taille);
	  int miy = minimum(taby,taille);
	  createAxeH(px,py,mix,Max,taille-1,ecran);
	  createAxeV(py, miy, May,taille-1, ecran);
	  int i=0; 
    TTF_Font *police =NULL;
    SDL_Color noir ={0,0,0};
    police = TTF_OpenFont("times.ttf",20);
    SDL_Surface *texte ;
	  SDL_Rect p;
	 for(i=0; i<taille; i++){
		 p.x = toPixelH(tabx[i],mix,Max,40,px+40);
		 p.y =toPixelV(taby[i],miy,May,40,py+40);
		 createPoint(p,ecran);
	 }

  SDL_Rect pos ={40, 15};
  texte = TTF_RenderText_Blended(police,labels[1], noir); 
  pos.x -= (texte->w/2);
  SDL_BlitSurface(texte,NULL, ecran,&pos);
  SDL_Color fond ={0,255,0};
  texte = TTF_RenderText_Shaded(police,labels[2], noir,fond); 
  pos.x =px-(texte->w/2); pos.y =35;
  SDL_BlitSurface(texte,NULL, ecran, &pos);
  texte = TTF_RenderText_Blended(police,labels[0], noir); 
  pos.x = px+60-(texte->w); pos.y =py+20;
  SDL_BlitSurface(texte,NULL, ecran, &pos);

  SDL_Flip(ecran);
  pause();
  TTF_CloseFont(police); 
  SDL_FreeSurface(texte); 
  SDL_FreeSurface(ecran);
}
 /*======================================================================================================*/
void barplot(int tab[], int taille, SDL_Color col,char* ylabel, char* legend)
{
    int px =700,py =560;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(px+80, py+80, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Figure 1", NULL);
    SDL_FillRect(ecran,NULL, SDL_MapRGB(ecran ->format,255,255,255));
    SDL_Surface *bar = NULL;
    SDL_Surface *Ax = NULL;
    SDL_Surface *stick =NULL;
    SDL_Surface *texte = NULL;
    int i =0;
    char ch[10];
    TTF_Font *police =NULL;
	  SDL_Color noir ={0,0,0};
	  police = TTF_OpenFont("times.ttf",11);
    int max = maximum(tab,taille);
    createAxeV(py, 0, max, taille-1,ecran);
    Ax= SDL_CreateRGBSurface(SDL_HWSURFACE,580,1,32,0,0,0,0);
    stick = SDL_CreateRGBSurface(SDL_HWSURFACE,1,8,32,0,0,0,0);
    SDL_Rect posx ={40,py+40};
    SDL_BlitSurface(Ax, NULL, ecran, &posx);
    int larg = (py-10)/taille;
    int haut =0;
    int pas = px/taille;
    SDL_Rect pos;
    for (i=0; i<taille; i++)
    {
       sprintf(ch,"%2d",i+1);
       texte = TTF_RenderText_Blended(police,ch, noir); 
       haut = toPixelV(tab[i],0,max, 40,py+40);
       bar = SDL_CreateRGBSurface(SDL_HWSURFACE,larg,py-haut+40,32,0,0,0,0);
       SDL_FillRect(bar,NULL, SDL_MapRGB(bar->format, col.r,col.g,col.b));
       pos.x= 40+(larg/2) +i*pas; 
       pos.y =haut;
       SDL_BlitSurface(bar, NULL, ecran, &pos);
       pos.x = pos.x+(larg/2);
       pos.y = 40+py;
       SDL_BlitSurface(stick,NULL, ecran, &pos);
       pos.x = pos.x-5;  pos.y = pos.y+10;
       SDL_BlitSurface(texte,NULL, ecran, &pos);
    }
     police = TTF_OpenFont("times.ttf",20);
     pos.x =20; pos.y =20;
     texte = TTF_RenderText_Blended(police,ylabel, noir); 
    SDL_BlitSurface(texte,NULL, ecran,&pos);
    SDL_Color fond ={0,255,0};
    texte = TTF_RenderText_Shaded(police,legend, noir,fond); 
    pos.x =px-(texte->w/2); pos.y =35;
    SDL_BlitSurface(texte,NULL, ecran, &pos);
    SDL_Flip(ecran);

    pause();
    TTF_CloseFont(police);
    SDL_FreeSurface(bar);
    SDL_FreeSurface(Ax);
    SDL_FreeSurface(stick);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(ecran);
}
 /*======================================================================================================*/
void barplot2(int tab[], char *label[], int taille,SDL_Color col, char* ylabel, char *legend)
{
    int px =700,py =560;
    SDL_Surface *ecran =NULL;
    ecran = SDL_SetVideoMode(px+80, py+80, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Figure 1", NULL);
    SDL_FillRect(ecran,NULL, SDL_MapRGB(ecran ->format,255,255,255));
    SDL_Surface *bar = NULL;
    SDL_Surface *Ax = NULL;
    SDL_Surface *stick =NULL;
    SDL_Surface *texte = NULL;
    int i =0;
    TTF_Font *police =NULL;
	  SDL_Color noir ={0,0,0};
	  police = TTF_OpenFont("times.ttf",14);
    int max = maximum(tab,taille);
    createAxeV(py, 0, max, taille-1,ecran);
    Ax= SDL_CreateRGBSurface(SDL_HWSURFACE,580,1,32,0,0,0,0);
    stick = SDL_CreateRGBSurface(SDL_HWSURFACE,1,8,32,0,0,0,0);
    SDL_Rect posx ={40,py+40};
    SDL_BlitSurface(Ax, NULL, ecran, &posx);
    int larg = (py-10)/taille;
    int haut =0;
    int pas = px/taille;
    SDL_Rect pos;
    for (i=0; i<taille; i++)
    {
       
       texte = TTF_RenderText_Blended(police,label[i], noir); 
       haut = toPixelV(tab[i],0,max, 40,py+40);
       bar = SDL_CreateRGBSurface(SDL_HWSURFACE,larg,py-haut+40,32,0,0,0,0);
       SDL_FillRect(bar,NULL, SDL_MapRGB(bar->format, col.r,col.g,col.b));
       pos.x= 40+(larg/2) +i*pas; 
       pos.y =haut;
       SDL_BlitSurface(bar, NULL, ecran, &pos);
       pos.x = pos.x+(larg/2);
       pos.y = 40+py;
       SDL_BlitSurface(stick,NULL, ecran, &pos);
       pos.x = pos.x-5;  pos.y = pos.y+10;
       SDL_BlitSurface(texte,NULL, ecran, &pos);
    }
     police = TTF_OpenFont("times.ttf",20);
     pos.x =20; pos.y =20;
     texte = TTF_RenderText_Blended(police,ylabel, noir); 
    SDL_BlitSurface(texte,NULL, ecran,&pos);
    SDL_Color fond ={0,255,0};
    texte = TTF_RenderText_Shaded(police,legend, noir,fond); 
    pos.x =px-(texte->w/2); pos.y =35;
    SDL_BlitSurface(texte,NULL, ecran, &pos);
    SDL_Flip(ecran);

    pause();
    TTF_CloseFont(police);
    SDL_FreeSurface(bar);
    SDL_FreeSurface(Ax);
    SDL_FreeSurface(stick);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(ecran);
}