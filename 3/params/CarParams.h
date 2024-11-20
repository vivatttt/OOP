#ifndef CARPARAMS_H
#define CARPARAMS_H

#include "../coordinates/Coordinates.h"

class CarParams {
    public:
        Coordinates coordinates;
        double angle;
        double velocity;             
        double angular_velocity;     
                        
        CarParams();
        CarParams(
            Coordinates _coordinates,
            double _angle,
            double _velocity,
            double _angular_velocity  
        );
};

#endif