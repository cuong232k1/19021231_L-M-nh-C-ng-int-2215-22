
#include <iostream>
#include <SDL.h>
#include"painter.h"
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<SDL_image.h>
#include<cstring>
using namespace std;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;


Painter::Painter(   SDL_Window* window, SDL_Renderer* renderer_)
    : renderer(renderer_)
{
	int width, height;
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);
    setPosition(10/2, 10/2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLACK_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;

}

void Painter::setAngle(float angle)
{
    this->angle = angle;

    - float (angle/360)*360;
}
void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(
        renderer, color.r, color.g, color.b, 0);
}

void Painter::clearWithBgColor(SDL_Color bgColor)
{
  SDL_SetRenderDrawColor(
     renderer, bgColor.r, bgColor.g, bgColor.b, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(
     renderer, color.r, color.g, color.b, 0);
}

void Painter::moveForward(float length)
{
    float prevX = x, prevY = y;
    jumpForward(length);
    SDL_RenderDrawLine(renderer, (int)prevX, (int)prevY, (int)x, (int)y);
}

void Painter::jumpForward(float length)
{
    float rad = (angle / 180) * M_PI;
    x += cos(rad) * length;
    y -= sin(rad) * length;
}
void Painter::setRandomColor()
{
   Uint8 r = rand() % 256;
   Uint8 g = rand() % 256;
   Uint8 b = rand() % 256;
   SDL_Color color = { r, g, b };
   setColor(color);
}

SDL_Texture* Painter::loadTexture( string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface =IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );

        return newTexture;
    }
}
bool Painter::createImage( SDL_Texture* texture)
{
    if( texture == NULL ) return false;
    SDL_RenderCopy( renderer, texture,NULL,NULL);
    return true;
}
