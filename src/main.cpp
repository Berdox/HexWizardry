#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <iostream>
#include "../include/Platform.hpp"
#include "../include/HexEditor.hpp"


int main(int argc, char* argv[]) {
    Platform plat;
    
    plat.init_hexEditor();

    //HexEditor hex;

    //hex.loadFile("G:/code/c++/HexWizardry/resource/test.txt");
    //hex.displayHexData();

    return 0;
}
