#include "main.hpp"
#include "car.hpp"
#include <cmath>

SDL_Point collision_check(SDL_Point * ray ,SDL_Point * wall,int linecount){
    float maxT=FLT_MAX;
    SDL_Point out = {-1,-1};
    for(int i = 0;i<linecount;i++){

        float denominator = (ray[0].x-ray[1].x)*(wall[i].y-wall[i+1].y)-(ray[0].y-ray[1].y)*(wall[i].x-wall[i+1].x);
        if (denominator == 0){
            continue;
        }
        float t = ((ray[0].x-wall[i].x)*(wall[i].y-wall[i+1].y)-(ray[0].y-wall[i].y)*(wall[i].x-wall[i+1].x))/denominator;
        if (0>t||t>maxT){
            continue;
        }
         float u = ((ray[0].x-wall[i].x)*(ray[0].y-ray[1].y)-(ray[0].y-wall[i].y)*(ray[0].x-ray[1].x))/denominator;
        if(u<0||u>1){
            continue;
        }
        maxT=t;
        out.x=ray[0].x+t*(ray[1].x-ray[0].x);
        out.y=ray[0].y+t*(ray[1].y-ray[0].y);
    }
    return out;
}
int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
            SDL_GetError();
    }

    int width = 1200;
    int height = 800;

    SDL_Window* window=nullptr;
    window = SDL_CreateWindow("A1 Rally", 20,20,width,height,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer=nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_Point ray [] = {
        {1,2},
        {3,4}
    };
    SDL_Point wall[] = {
        {100,100},
        {200,300}
    };
    SDL_Point racetrack [] = {
        {0.10*width,0.10*height},
        {0.90*width,0.10*height},
        {0.90*width,0.90*height},
        {0.60*width,0.90*height},
        {0.60*width,0.70*height},
        {0.50*width,0.70*height},
        {0.50*width,0.90*height},
        {0.10*width,0.90*height},
        {0.10*width,0.10*height}
    };
    cars myCars(10);
    car* playerCar;
    playerCar = myCars.createCar(width/2,height/2);
    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case (SDL_QUIT):
                    gameIsRunning= false;
                    break;
                case (SDL_MOUSEBUTTONDOWN):
                    car* newCar;
                    newCar = myCars.createCar(event.button.x,event.button.y);
                    break;
                case (SDL_KEYDOWN):
                    if(event.key.keysym.sym == SDLK_0){
                        gameIsRunning = false;
                    }
                    break;
                default:
                    // std::cout << "some unknown case: " << event.type<<"\n";
                    break;
            }
        }
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_RIGHT]){
            if(state[SDL_SCANCODE_LEFT]){
                playerCar->rot=0;
            }
            playerCar->rot-=.002;
        }else if(state[SDL_SCANCODE_LEFT]){
            playerCar->rot+=.002;
        }else{
            playerCar->rot=0;
            // playerCar->rot=playerCar->rot>.002?playerCar->rot-.002:playerCar->rot<-.002?playerCar->rot+.002:0;
        }
        if(state[SDL_SCANCODE_UP]){
            playerCar->vel+=.3;
        }else if(state[SDL_SCANCODE_DOWN]){
            if (playerCar->vel >.1){
                playerCar->braking=true;
            }
            if(playerCar->braking){
                playerCar->vel=playerCar->vel*.8;
            }else{
                playerCar->vel-=.1;
            }
        }else{
            if (playerCar->vel<.1){
                playerCar->braking=false;
            }
            playerCar->vel=playerCar->vel>1?playerCar->vel*.98:playerCar->vel<-1?playerCar->vel*.9:0;
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        myCars.updateCar(playerCar);
        ray[0].x=playerCar->x;
        ray[0].y=playerCar->y;
        ray[1].x=playerCar->x+10000*sin(playerCar->theta);
        ray[1].y=playerCar->y-10000*cos(playerCar->theta);
        myCars.drawCars(renderer,playerCar);
        SDL_RenderDrawLines(renderer,racetrack,9);
        SDL_RenderDrawLines(renderer,wall,2);
        ray[1]=(collision_check(ray,racetrack,9));
        if(ray[1].x>=0){
            SDL_RenderDrawLines(renderer,ray,2);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
