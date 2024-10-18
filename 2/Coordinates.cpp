#include <iostream>
#include "Coordinates.h"

Coordinates::Coordinates() : x(0.0), y(0.0) {}
Coordinates::Coordinates(double _x, double _y) : x(_x), y(_y) {}
double Coordinates::getX(){
    return x;
}
double Coordinates::getY(){
    return y;
}