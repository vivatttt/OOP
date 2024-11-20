#ifndef CARCONDITION_H
#define CARCONDITION_H

#include <chrono>
#include "../coordinates/Coordinates.h"

class CarCondition {
    protected:
        double velocity;             
        double angular_velocity;     
        double angle;                
        double acceleration;
        double angular_acceleration;
        Coordinates coordinates; 

        double start_velocity;             
        double start_angular_velocity;     
        double start_angle;                
        double start_acceleration;
        double start_angular_acceleration;
        Coordinates start_coordinates; 

        std::chrono::time_point<std::chrono::steady_clock> movement_start_time;
    public:
        CarCondition();
        CarCondition(
            double start_velocity,
            double start_acceleration,
            double start_angular_velocity,
            double start_angular_acceleration,
            double start_angle,
            Coordinates start_coordinates
        );
        CarCondition(const CarCondition &other);

        double getVelocity();
        double getAcceleration();
        double getAngularVelocity();
        double getAngularAcceleration();
        double getAngle();

        virtual std::string identify() const = 0;
};


#endif 