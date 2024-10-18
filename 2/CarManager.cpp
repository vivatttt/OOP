#include <iostream>
#include <chrono>

#include "Coordinates.h"
#include "CarManager.h"

CarManager::CarManager() :
    Car(0.0, 0.0, 0.0, 0.0, 0.0, Coordinates(0, 0)) {}
CarManager::CarManager(
    double _velocity,
    double _acceleration,
    double _angular_velocity,
    double _angular_acceleration,
    double _angle,
    Coordinates _coordinates
) : Car(
    _velocity,
    _acceleration,
    _angular_velocity,
    _angular_acceleration,
    _angle,
    _coordinates
) {}

void CarManager::setAcceleration(double new_acceleration){
    acceleration = new_acceleration;
}
void CarManager::setAngularAcceleration(double new_angular_acceleration){
    angular_acceleration = new_angular_acceleration;
}
std::string CarManager::identify() const { 
    return "car-manager";
}
