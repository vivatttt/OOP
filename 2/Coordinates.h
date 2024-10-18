#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates {
    private:
        double x, y;
    public:
        Coordinates();
        Coordinates(double _x, double _y);
        double getX();
        double getY();        
};

#endif