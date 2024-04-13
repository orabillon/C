#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "orn_graphics.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *orn_sdl_window;
SDL_Renderer *orn_sdl_renderer;

float orn_dt = 0;
Uint32 _frameStart = 0;

/**
 * Initialise la fenêtre et le renderer de la SDL2 avec les flags SDL_INIT_EVERYTHING / SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
 * Initialise également SDL_IMAGE et SDL_TTF
 * @param szTitle Titre de la fenetre
 * @param iWindowWidth Largeur de la fenetre
 * @param iWindowHeight Hauteur de la fenetre
 * @param iGameWidth Largeur de l'écran de jeu
 * @param iGameHeight Hauteur de l'écran de jeu
 * @param bFullScreen Active ou non le plein ecran
 * @return true en cas de succes sinon false en cas d'erreur
 */
bool orn_graphics_init(const char *szTitre, int iWindowWidth, int iWindowHeight, int iGameWidth, int iGameHeight, bool bFullScreen)
{
    Uint32 uFlagsWindos = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    Uint32 uFlagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    Uint32 uFlagsSdlImage = IMG_INIT_JPG | IMG_INIT_PNG;

    if (bFullScreen)
    {
        uFlagsWindos |= SDL_WINDOW_FULLSCREEN;
    }
    /*
        initialisation SDL
    */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL\n");
        return false;
    }

    /*
        création fenêtre
    */
    orn_sdl_window = SDL_CreateWindow(
        szTitre,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        iWindowWidth,
        iWindowHeight,
        uFlagsWindos);

    if (orn_sdl_window == NULL)
    {
        printf("Impossible de creer la fenetre : %s\n", SDL_GetError());
        return false;
    }

    /*
        création renderer
    */
    orn_sdl_renderer = SDL_CreateRenderer(orn_sdl_window, -1, uFlagsRenderer);
    if (orn_sdl_renderer == NULL)
    {
        printf("Impossible de creer le renderer : %s\n", SDL_GetError());
        return false;
    }
    else
    {
        /* Initialisation SDL IMAGE*/
        if (!(IMG_Init(uFlagsSdlImage) & uFlagsSdlImage))
        {
            printf("Impossible d'initialiser la librairie SDL_IMAGE : %s\n", IMG_GetError());
            return false;
        }
    }

    /* Initialisation SDL_TTF*/
    if (TTF_Init() == -1)
    {
        printf("Impossible d'initialiser la librairie SDL_TTF : %s\n", TTF_GetError());
        return false;
    }

    // Mise en place taille logique
    SDL_SetWindowMinimumSize(orn_sdl_window, iGameWidth, iGameHeight);
    SDL_RenderSetLogicalSize(orn_sdl_renderer, iGameWidth, iGameHeight);

    // Pixel Art
    SDL_RenderSetIntegerScale(orn_sdl_renderer, SDL_TRUE);

    // Permet d'activer le melange des couleur et l'alpha
    SDL_SetRenderDrawBlendMode(orn_sdl_renderer, SDL_BLENDMODE_BLEND);

    return true;
}

/**
 Détruit la fenêtre et le renderer et quitte proprement les extention et la SDL2
*/
void orn_graphics_close(void)
{
    SDL_DestroyRenderer(orn_sdl_renderer);
    SDL_DestroyWindow(orn_sdl_window);

    /* Fermeture SDL*/
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

// Game Loop
/**
 * Gère le SDL_PollEvent et le calcul du Delta Time, vide le renderer
 * @return 0 en cas d'evenement SDL_QUIT sinon 1
 */
int orn_graphics_beginDraw(void)
{

    /* Calcul du delta time */
    Uint32 now = SDL_GetTicks();
    orn_dt = (now - _frameStart) / 1000.0;
    _frameStart = now;

    /*Parcour des évenement SDL*/
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 0;
        }
    }

    /* Efface l'écran */
    SDL_RenderClear(orn_sdl_renderer);

    return 1;
}

/**
 * Execute le rendu final et limite le framrate
 */
void orn_graphics_endDraw(void)
{
    /* Affiche l'écran*/
    SDL_RenderPresent(orn_sdl_renderer);
    orn_keyboard_old();

    /* Limitation FPS*/
    int frameTime = SDL_GetTicks() - _frameStart;
    if (frameTime < (1000 / 60))
    {
        int delay = (1000 / 60) - frameTime;
        if (delay > 0)
        {
            SDL_Delay(delay);
        }
    }
}

/**
 * Dessine une texture a l'écran
 * @param image  Texture a dessiner
 * @param iX      Position x
 * @param iY      Position y
 */
void orn_graphics_draw(orn_Texture image, int iX, int iY)
{
    SDL_Rect recDestination = {iX, iY, image.iWidth, image.iHeight};
    SDL_SetTextureColorMod(image.sdl_texture, image.uRed, image.uGreen, image.uBlue);
    if (image.bTransparency)
    {
        SDL_SetTextureAlphaMod(image.sdl_texture, image.uAlpha);
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(image.bIsFlipH)
    {
        flip |= SDL_FLIP_HORIZONTAL;
    }
    if (image.bIsFlipV)
    {
        flip |= SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx(orn_sdl_renderer, image.sdl_texture, NULL, &recDestination,image.dAngle,NULL,flip);
}

/**
 * Dessine une portion d'une texture a l'écran
 * @param image         Texture a dessiner
 * @param rectSource    defini la portion de l'image a afficher
 * @param iX            Position x
 * @param iY            Position y
 */
void orn_graphics_drawQuad(orn_Texture image, orn_rect rectSource, int iX, int iY)
{
    SDL_Rect recDestination = {iX, iY, rectSource.w, rectSource.h};
    SDL_Rect recSource = {rectSource.x, rectSource.y, rectSource.w, rectSource.h};
    SDL_SetTextureColorMod(image.sdl_texture, image.uRed, image.uGreen, image.uBlue);
    if (image.bTransparency)
    {
        SDL_SetTextureAlphaMod(image.sdl_texture, image.uAlpha);
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(image.bIsFlipH)
    {
        flip |= SDL_FLIP_HORIZONTAL;
    }
    if (image.bIsFlipV)
    {
        flip |= SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx(orn_sdl_renderer, image.sdl_texture, &recSource, &recDestination,image.dAngle,NULL,flip);
}

/**
 * Prepare le dessin d'une portion de texture a l'écran
 * @param *tex          Texture pour le dessin
 * @param iQuadW        Largeur de la portion de la texture a afficher
 * @param iQuadH        Hauteur de la portion de la texture a afficher
 * @param iNumFrame     Numero de la portion de l'image a afficher
 * @param iX            Position x
 * @param iY            Position y
 */
void orn_graphics_drawQuad_game(orn_Texture *tex, int iQuadW, int iQuadH, int iNumFrame, int iX, int iY)
{

    int nbCol = tex->iWidth / iQuadW;
    int c = 0;
    int l = 0;

    l = (int)floor(iNumFrame / nbCol);
    c = iNumFrame - (l * nbCol);

    int xIm = c * iQuadW;
    int yIm = l * iQuadH;

    orn_rect rectSource = {xIm, yIm, iQuadW, iQuadH};

    orn_graphics_drawQuad(*tex, rectSource, iX, iY);
}

// images

/**
 * Charge une image en memoire
 * @param *path Chemin de l'image à charger
 * @return Retourne un pointeur sur la texture SDL Créée
 */
SDL_Texture *LoadTexture(const char *path)
{

    SDL_Texture *Texture = NULL;

    Texture = IMG_LoadTexture(orn_sdl_renderer, path);
    if (Texture == NULL)
    {
        printf("Impossible de creer la texture a partir de %s erreur : %s\n", path, IMG_GetError());
        return NULL;
    }

    return Texture;
}

/**
 * Créer une ORN_TEXTURE avec l'image demander par l'utilisateur
 * @param *path  Chemin de l'image à créer
 * @return Retourne un ORN_TEXTURE
 */
orn_Texture orn_graphics_newImage(const char *path)
{
    orn_Texture tex = {NULL, 0, 0, false, 255, 255, 255, 255, 0, false, false};

    tex.sdl_texture = LoadTexture(path);
    if (tex.sdl_texture == NULL)
    {
        printf("Impossible de charger la texture a partir de %s erreur : %s\n", path, IMG_GetError());
    }
    else
    {
        SDL_QueryTexture(tex.sdl_texture, NULL, NULL, &tex.iWidth, &tex.iHeight);
    }

    return tex;
}

/**
 * Libère la memoire occuper par la texture
 * @param image  texture a supprimer
 */
void orn_graphics_freeImage(orn_Texture image)
{
    if (image.sdl_texture != NULL)
    {
        SDL_DestroyTexture(image.sdl_texture);
        image.sdl_texture = NULL;
    }
}

/**
 * Modifie la couleur a appliquer sur une texture
 * @param *image  pointeur image source
 * @param uRed           0-255 - pourcentage de rouge de la couleur à appliquer
 * @param uGreen         0-255 - pourcentage de vert de la couleur à appliquer
 * @param uBlue          0-255 - pourcentage de bleu de la couleur à appliquer
 * @param uAlpha         0-255 - pourcentage de transparence pour la texture
 */
void orn_graphics_SetTextureColor(orn_Texture *image, Uint8 uRed, Uint8 uGreen, Uint8 uBlue, Uint8 uAlpha)
{
    image->uAlpha = uAlpha;
    image->uRed = uRed;
    image->uGreen = uGreen;
    image->uBlue = uBlue;
}

/**
 * Modifie la transparence d'une texture
 * @param *image  pointeur image source
 * @param bTransparency  true / false pour activer ou non la transparence
 * @param uAlpha         0-255 - pourcentage de transparence pour la texture
 */
void orn_graphics_SetTextureTransparency(orn_Texture *image, bool bTransparency, Uint8 uAlpha)
{
    image->bTransparency = bTransparency;
    image->uAlpha = uAlpha;
}

/**
 * Modifie l'angle de rotation de la texture
 * @param *image  pointeur image source
 * @param dAnggle angle de rotation de la texture
 */
void orn_graphics_setTextureAngle(orn_Texture *image, double dAngle)
{
    image->dAngle = dAngle;
}

/**
 * Modifie le flip de la texture 
 * @param *image  pointeur image source
 * @param bFlipV flip vertical
 * @param bFlipH flip horizontal
 */
void orn_graphics_setTextureFlip(orn_Texture *image, bool bFlipV, bool bFlipH)
{
    image->bIsFlipH = bFlipH;
    image->bIsFlipV = bFlipV;
}

// Primitive

/**
 * Modifie la couleur du dessin à l'ecran
 * @param uRed           0-255 - pourcentage de rouge de la couleur à appliquer
 * @param uGreen         0-255 - pourcentage de vert de la couleur à appliquer
 * @param uBlue          0-255 - pourcentage de bleu de la couleur à appliquer
 * @param uAlpha         0-255 - pourcentage de transparence pour la texture
 */
void orn_graphics_setColor(Uint8 uRed, Uint8 uGreen, Uint8 uBlue, Uint8 uAlpha)
{
    SDL_SetRenderDrawColor(orn_sdl_renderer, uRed, uGreen, uBlue, uAlpha);
}

/**
 * Dessine une ligne a l'écran
 * @param iX1         coordonnée x du premier point
 * @param iY1         coordonnée y du premier point
 * @param iX2         coordonnée x du second point
 * @param iY2         coordonnée x du second point
 */
void orn_graphics_line(int iX1, int iY1, int iX2, int iY2)
{
    SDL_RenderDrawLine(orn_sdl_renderer, iX1, iY1, iX2, iY2);
}

/**
 * Dessine un rectancle sur l'écran
 * @param *szMode    Type du remplissage (line / fill)
 * @param iX         Coordonnée x du point en haut a gauche
 * @param iY         Coordonnée y du point en haut a gauche
 * @param iWidth     Longeur du rectangle
 * @param iHeight    Hauteur du rectangle
 */
void orn_graphics_rectangle(const char *szMode, int iX, int iY, int iWidth, int iHeight)
{
    SDL_Rect rect;
    rect.h = iHeight;
    rect.w = iWidth;
    rect.x = iX;
    rect.y = iY;

    if (strcmp(szMode, "line") == 0)
    {
        SDL_RenderDrawRect(orn_sdl_renderer, &rect);
    }
    else if (strcmp(szMode, "fill") == 0)
    {
        SDL_RenderFillRect(orn_sdl_renderer, &rect);
    }
}

/**
 * Dessine un cercle sur l'écran
 * @param *szMode    Type du remplissage (line / fill)
 * @param iCentreX   Coordonnée x du point du centre
 * @param iCentreY   Coordonnée y du point du centre
 * @param iRadius    Rayon du cercle
 */
void orn_graphics_circle(const char *szMode, int iCentreX, int iCentreY, int iRadius)
{

    if (strcmp("line", szMode) == 0)
    {
        const int diameter = (iRadius * 2);

        int x = (iRadius - 1);
        int y = 0;
        int tx = 1;
        int ty = 1;
        int error = (tx - diameter);

        while (x >= y)
        {
            // Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + x, iCentreY - y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + x, iCentreY + y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - x, iCentreY - y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - x, iCentreY + y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + y, iCentreY - x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + y, iCentreY + x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - y, iCentreY - x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - y, iCentreY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
    if (strcmp("fill", szMode) == 0)
    {
        int offsetx, offsety, d;
        int status;

        offsetx = 0;
        offsety = iRadius;
        d = iRadius - 1;
        status = 0;

        while (offsety >= offsetx)
        {

            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsety, iCentreY + offsetx, iCentreX + offsety, iCentreY + offsetx);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsetx, iCentreY + offsety, iCentreX + offsetx, iCentreY + offsety);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsetx, iCentreY - offsety, iCentreX + offsetx, iCentreY - offsety);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsety, iCentreY - offsetx, iCentreX + offsety, iCentreY - offsetx);

            if (status < 0)
            {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx)
            {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (iRadius - offsety))
            {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else
            {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }
}
