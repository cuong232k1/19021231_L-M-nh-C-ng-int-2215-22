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
const int start_y=455;
const int start_x=0;
const int step_x=45;
const int step_y=50;
const int size_bot_w=93;
const int size_bot_h=56;
const int size_main_w=117;
const int size_main_h=167;
const int size_bullet_w=43;
const int size_bullet_h=33;
int so_luong_quai=3;
int step_bullet=0;
int health_goku=100;
int health_main=1000;
int point =0;
void Painter:: dk_x_right(){
    if (_x+size_main_w>SCREEN_WIDTH){
        _x-=step_x;
    }
}
void Painter::dk_x_left(){
    if (_x<0){
        _x+=step_x;
    }
}
void Painter::dk_y_up(){
    if (_y<0){
        _y+=step_y;
    }
}
void Painter::dk_y_down(){
    if (_y+size_main_h>SCREEN_HEIGHT){
        _y-=step_y;
    }
}
void Painter:: do_hoa_player1(){
    SDL_Texture *gameman=NULL;
    SDL_Texture* texture=NULL;
    texture =loadTexture("anh_ne.jpg");
    SDL_Rect sourceRect,desRect;// anh va vi tri cua nhan vat
    sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w =_w= size_main_w;//co anh rong
	sourceRect.h =_h= size_main_h;//co anh cao
	desRect.x = _x;
    desRect.y = _y;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_Event e;
	gameman=loadTexture("goku_bay.png");
    texture =loadTexture("anh_ne.jpg");
    createImage(texture);
    SDL_RenderPresent(renderer);

    //bot
    SDL_Texture *image_bot[so_luong_quai];
    IMG_Init(IMG_INIT_PNG);
    SDL_Rect sourceRect_bot[so_luong_quai],desRect_bot[so_luong_quai];
    for (int i=0;i<so_luong_quai;i++){
        image_bot[i]=loadTexture("plane.png");
        sourceRect_bot[i].x = 0;
        sourceRect_bot[i].y = 0;
        sourceRect_bot[i].w = size_bot_w;//co anh rong
        sourceRect_bot[i].h = size_bot_h;// co anh cao
        desRect_bot[i].x = SCREEN_WIDTH;
        desRect_bot[i].y = rand()%(SCREEN_HEIGHT-size_main_h*3/4);//tránh cho máy bay ngoài tầm bắn
        desRect_bot[i].w = sourceRect_bot[i].w ;
        desRect_bot[i].h = sourceRect_bot[i].h ;
    }
	//bom
	SDL_Texture *bom;
	bom=loadTexture("fire.png");
	SDL_Rect bom1,bom2;
	bom1.x=0;
	bom1.y=0;
	bom1.w=120;
	bom1.h=120;
	bom2.w=bom1.w;
	bom2.h=bom2.w;
	// bullet
	SDL_Texture *bullet=NULL;
    bullet=loadTexture("bullet.png");
	SDL_Rect bullet1,bullet2;
	bullet1.x=0;
	bullet1.y=0;
	bullet1.w=size_bullet_w;
	bullet1.h=size_bullet_h;
	bullet2.x=_x+_w+SCREEN_WIDTH+100;// để đạn ở ngoài màn hình bên phải
    bullet2.y=_y+_h/2;
	bullet2.w=bullet1.w;
	bullet2.h=bullet1.h;
      while(health_goku>0 && health_main>0&&point<100){
       // gameman=loadTexture("goku_bay.png");
        desRect.x = _x;
        desRect.y = _y;
        bullet2.x+=step_bullet;
        for (int i=0;i<so_luong_quai;i++){
            desRect_bot[i].x-=5;
        }
        createImage(texture);
        SDL_RenderCopy(renderer,gameman,&sourceRect,&desRect);
        for (int i=0;i<so_luong_quai;i++){
            SDL_RenderCopy(renderer,image_bot[i],&sourceRect_bot[i],&desRect_bot[i]);
            if(((bullet2.x+size_bullet_w>=desRect_bot[i].x) && (bullet2.x<=desRect_bot[i].x+size_bot_w ))
            &&((bullet2.y+size_bullet_h>=desRect_bot[i].y) && (bullet2.y<=desRect_bot[i].y+size_bot_h))) {// xử lí đạn bắn chúng
                bom2.x=desRect_bot[i].x;
                bom2.y=desRect_bot[i].y;
                SDL_RenderCopy(renderer,bom,&bom1,&bom2);
                desRect_bot[i].x = SCREEN_WIDTH;
                desRect_bot[i].y = rand()%(SCREEN_HEIGHT-size_main_h*3/4);
                step_bullet=0;
                bullet2.x=_x+_w+SCREEN_WIDTH+100;
                bullet2.y=_y+_h/2;
            }
            else if(desRect_bot[i].x<0){
                bom2.x=desRect_bot[i].x;
                bom2.y=desRect_bot[i].y;
                SDL_RenderCopy(renderer,bom,&bom1,&bom2);
                desRect_bot[i].x = SCREEN_WIDTH;
                desRect_bot[i].y = rand()%(SCREEN_HEIGHT-size_main_h*3/4);
                health_main-=50;
            }
            else if (((desRect.x+size_main_w>=desRect_bot[i].x) && (desRect.x<=desRect_bot[i].x+size_bot_w ))
            &&((desRect.y+size_main_h>=desRect_bot[i].y) && (desRect.y<=desRect_bot[i].y+size_bot_h))){
                bom2.x=desRect_bot[i].x;
                bom2.y=desRect_bot[i].y;
                SDL_RenderCopy(renderer,bom,&bom1,&bom2);
                desRect_bot[i].x = SCREEN_WIDTH;
                desRect_bot[i].y = rand()%(SCREEN_HEIGHT-size_main_h*3/4);
                health_goku-=10;
            }
            else {
                SDL_RenderCopy(renderer,image_bot[i],&sourceRect_bot[i],&desRect_bot[i]);
                SDL_RenderCopy(renderer,bullet,&bullet1,&bullet2);
          }
        }
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&e)==0){continue;}
        if (e.type==SDL_QUIT){break;}
        if (e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case (SDLK_ESCAPE):break;
                case (SDLK_LEFT):{ gameman=loadTexture("goku_dung.png");_x-=step_x;dk_x_left();break;}
                case (SDLK_RIGHT):{gameman=loadTexture("goku_dung.png");_x+=step_x;dk_x_right();break;}
                case (SDLK_UP):{gameman=loadTexture("goku_dung.png");_y-=step_y;dk_y_up();break;}
                case (SDLK_DOWN):{gameman=loadTexture("goku_dung.png");_y+=step_y;dk_y_down();break;}
                case (SDLK_0):{
                    if (bullet2.x>=SCREEN_WIDTH){//để đạn có thể đi hết đường đi
                        gameman=loadTexture("sayda.png");
                        SDL_RenderCopy(renderer,gameman,&sourceRect,&desRect);
                        bullet2.x=desRect.x+_w/2;
                        bullet2.y=desRect.y+_h/2-30;
                        step_bullet=80;
                    }
                    break;
                }
                default:break;
            }
        }
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(gameman);
}
