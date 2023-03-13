#ifndef CAR_H 
#define CAR_H
#include "main.hpp"
#include <cmath>

typedef struct{
    int r,g,b;
    bool braking;
    float x,y,rot,vel,theta;
}car;

class cars{
    private:
        int numCars;
    public:
        cars(int maxCars);
        car* createCar(int x, int y);
        void updateCar(car* target);
        void drawCar(SDL_Renderer* renderer, car* target);
        void drawCars(SDL_Renderer* renderer,car* target);
        void removeCar(car* target);
};

#endif
