#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <chrono>
#include "Coordinates.h"

class CarManager {
    private:
        double velocity;           
        double acceleration;       
        double angular_velocity;     
        double angular_acceleration;
        double angle;                
        Coordinates coordinates; 
        std::chrono::time_point<std::chrono::steady_clock> time_prev_check_point; 
    public:
        CarManager();
        CarManager(
            double start_velocity,
            double start_acceleration,
            double start_angular_velocity,
            double start_angular_acceleration,
            double start_angle,
            Coordinates start_coordinates
        );
        CarManager(const CarManager &other);

        double getVelocity();
        double getAcceleration();
        double getAngularVelocity();
        double getAngularAcceleration();
        double getAngle();
        Coordinates getCoordinates();

        void updateTime();
        void setAcceleration(double new_acceleration);
        void setAngularAcceleration(double new_angular_acceleration);
        
};

#endif 