#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <chrono>
#include "Coordinates.h"
#include "Car.h"

class CarManager : public Car { 
    public:
        CarManager();
        CarManager(
            double _velocity,
            double _acceleration,
            double _angular_velocity,
            double _angular_acceleration,
            double _angle,
            Coordinates _coordinates
        );
        void setAcceleration(double new_acceleration);
        void setAngularAcceleration(double new_angular_acceleration);
        std::string identify() const override;
};
#endif