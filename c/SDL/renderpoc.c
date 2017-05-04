#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

#define SCREEN_H        32*4
#define SCREEN_W        64*4
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
    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &ren);
    
    memset(screen, 0x00, SCREEN_W*SCREEN_H);

    while(1){
        
        screen[x + y * SCREEN_H] = 0;
        x++;
        if(x == SCREEN_W){
            x = 0;
            y++;
        }
        if(y == SCREEN_H)
            y = 0;
        screen[x + y * SCREEN_H] = 1;
        update_screen();
        SDL_Delay(200);
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

    int i, j;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    printf("SDL error(Clear): %s\n", SDL_GetError());

    for(j=0;j<SCREEN_H;j++){

        for(i=0;i<SCREEN_W;i++){

            if(screen[j*SCREEN_W+i] != 0){
                SDL_RenderDrawPoint(ren, i, j);
                printf("SDL error(DrawPoint): %s\n", SDL_GetError());
            }

        }
    }
    SDL_RenderPresent(ren);
    printf("SDL error(Present): %s\n", SDL_GetError());
}
