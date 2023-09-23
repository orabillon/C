#include "orn.h"
#include "orn_keyboard.h"

void orn_init(void)
{
    _orn_keyboard_init();
}

void orn_close()
{
    _orn_keyboard_close();
}