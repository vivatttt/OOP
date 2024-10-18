#ifndef CAR_H
#define CAR_H

#include <chrono>
#include "Coordinates.h"

class Car {
    private:
        double velocity;             
        double angular_velocity;     
        double angle;                
        Coordinates coordinates; 
        std::chrono::time_point<std::chrono::steady_clock> time_prev_check_point;
        void updatePosition(); 
    protected:
        double acceleration;
        double angular_acceleration;
    public:
        Car();
        Car(
            double start_velocity,
            double start_acceleration,
            double start_angular_velocity,
            double start_angular_acceleration,
            double start_angle,
            Coordinates start_coordinates
        );
        Car(const Car &other);

        double getVelocity();
        double getAcceleration();
        double getAngularVelocity();
        double getAngularAcceleration();
        double getAngle();
        Coordinates getPosition();

        void updateTime();
        virtual std::string identify() const = 0;
};

#endif 