#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "orn_graphics.h"
#include "orn_animation.h"
#include "orn_param.h"

orn_animation *orn_animation_createAnimation(orn_Texture *tex, char *typeAnimation, int iWidth, int iHeight, int tabListeImage[], int iTailleTaubleau, float fSpeed, bool bRepeat, bool bEnCour)
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
    anim ->bAnimationEnCour = bEnCour;
    anim->iTailleTaubleau = iTailleTaubleau;
    anim->current_frame = 0;
    anim->bFinish = false;

    for (int i= 0; i<iTailleTaubleau; i++)
    {
        anim->tabListeImage[i]= tabListeImage[i];
    }

    return anim;
}

void orn_animation_freeAnimation(orn_animation *animation)
{
    free(animation);
    animation = NULL;
}

void orn_animation_updateAnimation(orn_animation *animation)
{
    if (animation->bAnimationEnCour)
    {
        if (animation->current_frame <= animation->iTailleTaubleau)
        {
            animation->current_frame += animation->fSpeed;

            if (animation->current_frame >= animation->iTailleTaubleau)
            {
                if (animation->bRepeat == true)
                {   
                    animation->current_frame = 0;
                }
                else
                {
                    animation->current_frame = animation->iTailleTaubleau - 1;
                    animation->bFinish = true;
                }
            }
        }
        else
        {
            if (animation->bRepeat == true)
            {
                animation->current_frame = 0;
            }
            else
            {
                animation->current_frame = animation->iTailleTaubleau - 1;
                animation->bFinish = true;
            }
        

        }
    }
}



void orn_animation_drawAnimation(orn_animation *animation, int iX, int iY)
{
    orn_graphics_drawQuad_game(animation->texture, animation->iWidth, animation->iHeight, animation->tabListeImage[((int)(animation->current_frame))], iX, iY);
}

void orn_animation_startAnimation(orn_animation *animation)
{
    animation ->bAnimationEnCour = true;
}

void orn_animation_stopAnimation(orn_animation *animation)
{
    animation ->bAnimationEnCour = false;
}