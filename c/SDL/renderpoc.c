#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

#define SCREEN_H        32
#define SCREEN_W        64
SDL_Window *window;
SDL_Renderer *ren;
SDL_Event event;


void update_screen();

unsigned char screen[SCREEN_W*SCREEN_H];
int main(){
    int x = 0, y = 0;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        printf("SDL Init error!\n");
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    window = SDL_CreateWindow("Chip-8",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_WINDOW_SHOWN); //Each screen pixel is 4 pixel wide
    ren = SDL_CreateRenderer(window, 1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL){
        printf("Unable to create renderer!\n");
    }
    
    memset(screen, 0x00, SCREEN_W*SCREEN_H);

    while(1){
        
        screen[x + y * SCREEN_H] = 0;
        x++;
        if(x = SCREEN_W){
            x = 0;
            y++;
        }
        if(y = SCREEN_H)
            y = 0;
        screen[x + y * SCREEN_H] = 1;
        update_screen();
        SDL_Delay(1000);
        while( (SDL_PollEvent(&event))){
            if(event.type == SDL_QUIT){
                SDL_Quit();
                return 0;
            }
        }
    }
    return 0;
}

void update_screen(){
    //Update the screen

    unsigned char i, j;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    printf("SDL error(Clear): %s\n", SDL_GetError());

    for(j=0;j<32;j++){
        for(i=0;i<64;i++){
            if(screen[j*64+i] != 0){
                SDL_RenderDrawPoint(ren, i, j);
    printf("SDL error(DrawPoint): %s\n", SDL_GetError());

            }
        }
    }
    SDL_RenderPresent(ren);
    printf("SDL error(Present): %s\n", SDL_GetError());
}
