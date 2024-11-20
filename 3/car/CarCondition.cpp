#include <iostream>
#include <chrono>

#include "../coordinates/Coordinates.h"
#include "../car/CarCondition.h"

CarCondition::CarCondition() : 
    velocity(0.0),
    angular_velocity(0.0),
    angle(0.0),
    acceleration(0.0),
    angular_acceleration(0.0),
    coordinates(Coordinates(0, 0)),

    start_velocity(0.0),
    start_angular_velocity(0.0),
    start_angle(0.0),
    start_acceleration(0.0),
    start_angular_acceleration(0.0),
    start_coordinates(Coordinates(0, 0))

    {
        movement_start_time = std::chrono::steady_clock::now();
    }
CarCondition::CarCondition(
    double _velocity,
    double _acceleration,
    double _angular_velocity,
    double _angular_acceleration,
    double _angle,
    Coordinates _coordinates
) : 
    velocity(_velocity), 
    angular_velocity(_angular_velocity),
    angle(_angle), 
    acceleration(_acceleration), 
    angular_acceleration(_angular_acceleration),
    coordinates(_coordinates),

    start_velocity(_velocity),
    start_angular_velocity(_angular_velocity),
    start_angle(_angle), 
    start_acceleration(_acceleration), 
    start_angular_acceleration(_angular_acceleration),
    start_coordinates(_coordinates)
    {
        movement_start_time = std::chrono::steady_clock::now();
    }
CarCondition::CarCondition(
    const CarCondition &other
) {
    velocity = other.velocity;
    acceleration = other.acceleration;
    angular_velocity = other.angular_velocity;
    angular_acceleration = other.angular_acceleration;
    angle = other.angle;
    coordinates = other.coordinates;
}

double CarCondition::getVelocity() {
    return velocity;
}
double CarCondition::getAcceleration(){
    return acceleration;
}
double CarCondition::getAngle(){
    return angle;
}
double CarCondition::getAngularVelocity(){
    return angular_velocity;
}
double CarCondition::getAngularAcceleration(){
    return angular_acceleration;
}