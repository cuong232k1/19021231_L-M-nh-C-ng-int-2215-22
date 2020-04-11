
#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<cstring>
#include"file.h"
#include"painter.h"
using namespace std;
const int SCREEN_WIDTH = 1480;
const int SCREEN_HEIGHT = 780;
const string WINDOW_TITLE = "game";//tieu đề
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    Painter painter(window,renderer);
    painter.do_hoa_player1();
    SDL_Texture *game_over;
    game_over=painter.loadTexture("game_over.png");
    painter.createImage(game_over);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(game_over);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
