#include "car.hpp"

cars::cars(int maxCars){
    car carList[maxCars];
    numCars=0;
    std::cout<<"cars class init\n";
}

car* cars::createCar(int x,int y){
    car* newCar = new car;
    newCar->x=x;
    newCar->y=y;
    newCar->rot=0;
    newCar->r=255;
    newCar->g=255;
    newCar->b=255;
    numCars++;
    std::cout<<"number of cars is now: "<<numCars;
    return newCar;
}

void cars::removeCar(car* target){
    delete target;
}
void cars::updateCar(car* target){
    float maxrot=.02;
    float maxvel = 8;
    target->vel =  target->vel>maxvel ? maxvel : target->vel<-maxvel ? -maxvel : target->vel;
    target->rot =  target->rot>maxrot ? maxrot : target->rot<-maxrot ? -maxrot : target->rot;
    target->theta -= target->vel*target->rot;
    target->x += sin(target->theta)*target->vel;
    target->y -= cos(target->theta)*target->vel;
}
void cars::drawCar(SDL_Renderer* renderer,car* target){
    SDL_SetRenderDrawColor(renderer,target->r,target->g,target->b,255);
    int height = 16; //half length
    int width = 10; // half width
    int x = (int)target->x;
    int y = (int)target->y;

    SDL_Point points [5] = {
        {x+(width*cos(target->theta)-height*sin(target->theta)),y+(width*sin(target->theta)+height*cos(target->theta))},
        {x+(-width*cos(target->theta)-height*sin(target->theta)),y+(-width*sin(target->theta)+height*cos(target->theta))},
        {x+(-width*cos(target->theta)+height*sin(target->theta)),y+(-width*sin(target->theta)-height*cos(target->theta))},
        {x+(width*cos(target->theta)+height*sin(target->theta)),y+(width*sin(target->theta)-height*cos(target->theta))},
        {x+(width*cos(target->theta)-height*sin(target->theta)),y+(width*sin(target->theta)+height*cos(target->theta))}
    };

    SDL_RenderDrawLines(renderer,points,5);
}
void cars::drawCars(SDL_Renderer* renderer,car* target){
    for(int i = 0; i < numCars; i++){
        drawCar(renderer,&target[i]);
    }
}


