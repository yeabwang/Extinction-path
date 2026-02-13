#include "Menu.h"

Menu::Menu(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height) {
    // Initialize background sprite
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 1598, 900, width, height, "");

    // Initialize buttons
    this->Buttons[0] = new Button(gRenderer, gWindow, "Data\\New\\start0.png", { 500, 400 }, { 422, 100 }); // 250
    this->Buttons[1] = new Button(gRenderer, gWindow, "Data\\New\\Option0.png", { 500, 510 }, { 422, 100 }); // 360
    this->Buttons[2] = new Button(gRenderer, gWindow, "Data\\New\\quit0.png", { 500, 620 }, { 422, 100 }); // 470

    this->e = e;
    Enable = false;
}

bool Menu::IsEnable() {
    return Enable;
}

void Menu::setEnabled(bool e) {
    Enable = e;
}

int Menu::getButtonPresed() {
    int ButtonCount = -1;

    if (Buttons[0]->IsClicked(e)) {
        ButtonCount = 0;
    } else if (Buttons[1]->IsClicked(e)) {
        ButtonCount = 1;
    } else if (Buttons[2]->IsClicked(e)) {
        ButtonCount = 2;
    }

    return ButtonCount;
}

void Menu::Render() {
    // Render background and buttons
    this->Background->render();
    this->Buttons[0]->Render();
    this->Buttons[1]->Render();
    this->Buttons[2]->Render();
}

Point Menu::getSize() {
    return Background->get_Size();
}

Menu::~Menu() {
    // Clean up dynamically allocated memory
    delete Background;
    for (int i = 0; i < 3; i++) {
        delete Buttons[i];
    }
}