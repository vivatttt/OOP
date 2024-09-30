#include <iostream>
#include <chrono>

#include "Coordinates.h"
#include "CarManager.h"

CarManager::CarManager() : 
    velocity(0.0),
    acceleration(0.0),
    angular_velocity(0.0),
    angular_acceleration(0.0),
    angle(0.0) {}
CarManager::CarManager(
    double _velocity,
    double _acceleration,
    double _angular_velocity,
    double _angular_acceleration,
    double _angle,
    Coordinates _coordinates
) : 
    velocity(_velocity), 
    acceleration(_acceleration),
    angular_velocity(_angular_velocity), 
    angular_acceleration(_angular_acceleration),
    angle(_angle), coordinates(_coordinates) {
    time_prev_check_point = std::chrono::steady_clock::now();
}
CarManager::CarManager(
    const CarManager &other
) {
    velocity = other.velocity;
    acceleration = other.acceleration;
    angular_velocity = other.angular_velocity;
    angular_acceleration = other.angular_acceleration;
    angle = other.angle;
    coordinates = other.coordinates;
}

double CarManager::getVelocity() {
    return velocity;
}
double CarManager::getAcceleration(){
    return acceleration;
}
double CarManager::getAngle(){
    return angle;
}
double CarManager::getAngularVelocity(){
    return angular_velocity;
}
double CarManager::getAngularAcceleration(){
    return angular_acceleration;
}
Coordinates CarManager::getCoordinates(){
    return coordinates;
}
void CarManager::updateTime(){
    time_prev_check_point = std::chrono::steady_clock::now();
}
void CarManager::setAcceleration(double new_acceleration){
    acceleration = new_acceleration;
}
void CarManager::setAngularAcceleration(double new_angular_acceleration){
    angular_acceleration = new_angular_acceleration;
}
