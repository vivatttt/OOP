#include "../params/CarParams.h"

CarParams::CarParams() :
    coordinates(Coordinates(0, 0)),
    angle(0.0),
    velocity(0.0),
    angular_velocity(0.0)
{}

CarParams::CarParams(
        Coordinates _coordinates,
        double _angle,
        double _velocity,
        double _angular_velocity   
    ) : 
    coordinates(_coordinates),
    angle(_angle), 
    velocity(_velocity), 
    angular_velocity(_angular_velocity)
{}