sudo apt install build-essential git

sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP # To make the static version.
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED # To make the dynamic shared version.
make PLATFORM=PLATFORM_WEB # To make web version.


sudo make install # Static version.
sudo make install RAYLIB_LIBTYPE=SHARED # Dynamic shared version.

#compile!
gcc -o out test.c -lraylib -lGL -lm -pthread -ldl;./out;


#sudo make uninstall
#sudo make uninstall RAYLIB_LIBTYPE=SHARED
