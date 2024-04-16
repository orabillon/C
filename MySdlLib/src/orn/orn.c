#include "orn.h"
#include "orn_keyboard.h"
#include "orn_pad.h"
#include "orn_sound.h"

void orn_init(void)
{
    _orn_keyboard_init();
    _orn_pad_init();
    orn_sound_init();
}

void orn_close()
{
    _orn_keyboard_close();
    _orn_pad_close();
    orn_sound_close();
}