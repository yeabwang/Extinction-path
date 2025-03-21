#include "WinScreen.h"

WinScreen::WinScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height) {
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 1440, 900, width, height, "");

    this->e = e;
    Enable = false;
}

bool WinScreen::IsEnable() {
    return Enable;
}

void WinScreen::setEnabled(bool e) {
    Enable = e;
}

int WinScreen::getButtonPresed() {
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN) {
        return 1;
    }
    return 0;
}

void WinScreen::Render() {
    // Render background
    this->Background->render();
}

Point WinScreen::getSize() {
    return Background->get_Size();
}

WinScreen::~WinScreen() {
    // Clean up dynamically allocated memory
    delete Background;
}