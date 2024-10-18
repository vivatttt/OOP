#include <iostream>
#include <unistd.h> // если у вас система Win32 поменять на <windows.h>, а sleep на Sleep

#include <assert.h>
#include "CarManager.h"

int main(){
    Coordinates new_coordinates;
    Coordinates start_position(0.0, 0.0);
    // прямолинейное движение без ускорения
    CarManager my_car_manager(10, 0.0, 0.0, 0.0, 0.0, start_position);
    sleep(2);
    new_coordinates = my_car_manager.getPosition();
    double eps = 0.1;
    assert(
        abs(new_coordinates.getX() - 20) < eps &&
        abs(new_coordinates.getY() - 0)< eps
    );
    // добавляем линейное ускорение
    my_car_manager.setAcceleration(5.0);
    sleep(2);
    new_coordinates = my_car_manager.getPosition();
    assert(
        abs(new_coordinates.getX() - 50) < eps &&
        abs(new_coordinates.getY() - 0)< eps
    );
    // добавляем угловое ускорение и убираем линейное для простоты проверки
    my_car_manager.setAngularAcceleration(5.0);
    my_car_manager.setAcceleration(0.0);
    sleep(2);
    new_coordinates = my_car_manager.getPosition();
    assert(
        abs(new_coordinates.getX() - 53.4) < eps &&
        abs(new_coordinates.getY() - 4.8)< eps
    );
    // проверяем абстрактную идентификацию
    std::string class_id = my_car_manager.identify();
    assert(class_id == "car-manager");

    std::cout << "All tests passed succesfully!\nМожно идти трогать траву 🌿" << std::endl;
}