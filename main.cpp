#include <iostream>

#include <assert.h>
#include "CarManager.h"

int main(){
    Coordinates start_position(0.1, 0.2);
    CarManager my_car(5.1, 0.4, -3.1, 0.0, 60.0, start_position);
    float eps = 0.0001;
    // проверка конструктора инициализации и геттеров
    assert(
        abs(my_car.getVelocity() - 5.1) < eps && 
        abs(my_car.getAcceleration() - 0.4) < eps &&
        abs(my_car.getAngularVelocity() + 3.1) < eps &&
        abs(my_car.getAngularAcceleration() - 0.0) < eps &&
        abs(my_car.getAngle() - 60.0) < eps && 
        abs(my_car.getCoordinates().getX() - 0.1) < eps &&
        abs(my_car.getCoordinates().getY() - 0.2) < eps
    );

    my_car.setAcceleration(111.111);
    my_car.setAngularAcceleration(22.22);
    // проверка сеттеров
    assert(
        abs(my_car.getAcceleration() - 111.111) < eps &&
        abs(my_car.getAngularAcceleration() - 22.22) < eps 
    );

    CarManager my_car_copy = my_car;
    // проверка конструктора копирования
    assert(
        abs(my_car_copy.getVelocity() - 5.1) < eps && 
        abs(my_car_copy.getAcceleration() - 111.111 ) < eps &&
        abs(my_car_copy.getAngularVelocity() + 3.1 ) < eps &&
        abs(my_car_copy.getAngularAcceleration() - 22.22) < eps &&
        abs(my_car_copy.getAngle() - 60.0) < eps && 
        abs(my_car_copy.getCoordinates().getX() - 0.1) < eps &&
        abs(my_car_copy.getCoordinates().getY() - 0.2) < eps
    );

    CarManager empty_car;
    // проверка конструктора по умолчанию
    assert(
        abs(empty_car.getVelocity()) < eps && 
        abs(empty_car.getAcceleration()) < eps &&
        abs(empty_car.getAngularVelocity()) < eps&&
        abs(empty_car.getAngularAcceleration()) < eps &&
        abs(empty_car.getAngle()) < eps && 
        abs(empty_car.getCoordinates().getX()) < eps &&
        abs(empty_car.getCoordinates().getY()) < eps
    );

    std::cout << "All tests passed!!";
    return 0;
}