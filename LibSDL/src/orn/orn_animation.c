#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "orn_graphics.h"
#include "orn_animation.h"

orn_animation *orn_animation_createAnimation(orn_Texture *tex, char *typeAnimation, int iWidth, int iHeight, int iFirst, int *tabListeImage, int iTailleTaubleau, float fSpeed, bool bRepeat)
{

    orn_animation *anim = malloc(sizeof(struct orn_animation));

    if (anim == NULL)
    {
        fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
        exit(EXIT_FAILURE);
    };

    anim->iHeight = iHeight;
    anim->iWidth = iWidth;
    anim->bRepeat = bRepeat;
    anim->fSpeed = fSpeed;
    anim->texture = tex;
    anim->typeAnimation = typeAnimation;
    anim->bFinish = false;
    anim->tabListeImage = tabListeImage;
    anim->iTailleTaubleau = iTailleTaubleau;
    anim->current_frame = tabListeImage[0];

    return anim;
}

void orn_animation_freeAnimation(orn_animation *animation)
{
    free(animation);
    animation = NULL;
}

void orn_animation_updateAnimation(orn_animation *animation);
void orn_animation_drawAnimation(orn_animation *animation, int iX, int iY);