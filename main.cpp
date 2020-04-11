#include<iostream>
#include<SDL.h>
#include<cstring>
#include<SDL_image.h>
using namespace std;
SDL_Surface* load_image(string file_path){
    SDL_Surface *load_image=NULL;
    SDL_Surface *image_1=NULL;
    load_image=IMG_load(file_path.c_str());
    if (load_image==NULL){
        cout<<"not file"<<file_path;

    }
}
