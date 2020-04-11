#ifndef painter_H
#define painter_H
#endif // painter_H
#include<iostream>
#include<SDL.h>
#include<cmath>
#include<cstring>
using namespace std;
    class Painter
{
  float x;
  float y;
  float angle;
  SDL_Color color;
  SDL_Renderer* renderer;
  public:
    int _x=0;
    int _y=0;
    int _w=0;
    int _h=0;
    Painter(SDL_Window* window,
            SDL_Renderer* renderer);
    void setPosition(float x, float y);
    float getX() const { return x; }
    float getY() const { return y; }

    void setAngle(float angle);
    float getAngle() const { return angle; }

    void setColor(SDL_Color color);
    SDL_Color getColor() const
        { return color; }

    SDL_Renderer* getRenderer() const
        { return renderer; }

  void clearWithBgColor(SDL_Color color);
  void moveForward(float length);

  void jumpForward(float length);
  void moveBackward(float length) { moveForward(-length); }
  void jumpBackward(float length) { jumpForward(-length); }
  void turnLeft(float angle) { setAngle(this->angle + angle); }
  void turnRight(float angle) { turnLeft(-angle); }
  void setRandomColor();
                SDL_Texture* loadTexture( string path);
  bool createImage( SDL_Texture* texture);

  void do_hoa_player1();
  void dk_x_right();
  void dk_x_left();
  void dk_y_up();
  void dk_y_down();
};


