#/usr/bin/env bash

rm ./bin/MonProg
rm ./bin/assets/images/*.*
rm ./bin/assets/fonts/*.*
rm ./bin/assets/sons/*.*

cp ./src/assets/images/*.* ./bin/assets/images/
cp ./src/assets/fonts/*.* ./bin/assets/fonts/
cp ./src/assets/sons/*.* ./bin/assets/sons/

gcc -Wall -Werror -pedantic -g src/main.c src/orn/orn.c src/orn/orn_graphics.c src/orn/orn_font.c src/orn/orn_keyboard.c src/orn/orn_sound.c src/orn/orn_lists.c src/orn/orn_animation.c src/game.c -o bin/MonProg  $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_mixer -lSDL2_image

if [ $? -eq 0 ]; then
    echo "Compilation OK"
    cd bin
    ./MonProg
else
    echo "Erreur de compilation"
fi
