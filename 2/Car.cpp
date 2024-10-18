#include <iostream>
#include <chrono>

#include "Coordinates.h"
#include "Car.h"

Car::Car() : 
    velocity(0.0),
    angular_velocity(0.0),
    angle(0.0),
    acceleration(0.0),
    angular_acceleration(0.0),
    coordinates(Coordinates(0, 0)) {}
Car::Car(
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
    coordinates(_coordinates),
    acceleration(_acceleration), 
    angular_acceleration(_angular_acceleration) {
    time_prev_check_point = std::chrono::steady_clock::now();
}
Car::Car(
    const Car &other
) {
    velocity = other.velocity;
    acceleration = other.acceleration;
    angular_velocity = other.angular_velocity;
    angular_acceleration = other.angular_acceleration;
    angle = other.angle;
    coordinates = other.coordinates;
}

double Car::getVelocity() {
    return velocity;
}
double Car::getAcceleration(){
    return acceleration;
}
double Car::getAngle(){
    return angle;
}
double Car::getAngularVelocity(){
    return angular_velocity;
}
double Car::getAngularAcceleration(){
    return angular_acceleration;
}

void Car::updateTime(){
    time_prev_check_point = std::chrono::steady_clock::now();
}
void Car::updatePosition(){
    std::chrono::time_point<std::chrono::steady_clock> time_now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(time_now - time_prev_check_point);
    double delta_seconds = elapsed.count();


    double x = coordinates.getX();
    double y = coordinates.getY();
    double theta = angle;
    double v = velocity;
    double omega = angular_velocity;
    double t = 0.0;
    double dt = 0.001;

    while (t < delta_seconds) {
        v += acceleration * dt;
        omega += angular_acceleration * dt;

        theta += omega * dt;

        x += v * cos(theta) * dt;
        y += v * sin(theta) * dt;

        t += dt;
    }

    Coordinates new_coordinates = Coordinates(x, y);
    coordinates = new_coordinates;
}
Coordinates Car::getPosition(){
    updatePosition();
    updateTime();
    return coordinates;
}