#include <iostream>
#include <unistd.h> // если у вас система Win32 поменять на <windows.h>, а sleep на Sleep

#include <assert.h>
#include "manager/CarManager.h"

int main(){
    Coordinates start_position(0.0, 0.0), new_coords, certain_point_coords;
    CarManager my_car_manager(10, 0.0, 0.0, 0.0, 0.0, start_position);
    double eps = 0.01;
    // проверяем, что функции получения координат в лайве и в определенный момент
    // возвращают одинаковый результат
    // прямолинейное движение без ускорения
    sleep(2);
    new_coords = my_car_manager.getPosition();
    certain_point_coords = my_car_manager.getPositionAtCertainTime(2);
    assert(
        abs(new_coords.getX() - certain_point_coords.getX()) < eps &&
        abs(new_coords.getY() - certain_point_coords.getY()) < eps
    );
    std::cout << "At certain point & at live funcs result matches: without acceleration" << std::endl;
    // добавляем линейное ускорение
    my_car_manager.setAcceleration(5.0);
    sleep(3);
    new_coords = my_car_manager.getPosition();
    certain_point_coords = my_car_manager.getPositionAtCertainTime(5);

    assert(
        abs(new_coords.getX() - certain_point_coords.getX()) < eps &&
        abs(new_coords.getY() - certain_point_coords.getY()) < eps
    );
    std::cout << "At certain point & at live funcs result matches: +linear acceleration" << std::endl;
    // добавляем угловое ускорение
    my_car_manager.setAngularAcceleration(5.0);
    sleep(1);
    new_coords = my_car_manager.getPosition();
    certain_point_coords = my_car_manager.getPositionAtCertainTime(6);
    assert(
        abs(new_coords.getX() - certain_point_coords.getX()) < eps &&
        abs(new_coords.getY() - certain_point_coords.getY()) < eps
    );
    std::cout << "At certain point & at live funcs result matches: +angular acceleration" << std::endl;
    // убираем оба типа ускорения
    my_car_manager.setAcceleration(0.0);
    my_car_manager.setAngularAcceleration(0.0);
    sleep(1);
    new_coords = my_car_manager.getPosition();
    certain_point_coords = my_car_manager.getPositionAtCertainTime(7);
    assert(
        abs(new_coords.getX() - certain_point_coords.getX()) < eps &&
        abs(new_coords.getY() - certain_point_coords.getY()) < eps
    );
    std::cout << "At certain point & at live funcs result matches: -linear acceleration, -angular acceleration" << std::endl;
    // добавим новую машинку и проверим, что координаты считаются верно
    CarManager car_manager_check_process_coords(0.0, 0.0, 0.0, 0.0, 0.0, Coordinates(0.0, 0.0));
    // добавляем линейное ускорение
    car_manager_check_process_coords.setAcceleration(10.0);
    sleep(1);
    new_coords = car_manager_check_process_coords.getPosition();
    certain_point_coords = car_manager_check_process_coords.getPositionAtCertainTime(1);

    assert(
        abs(new_coords.getX() - 5.0) < eps &&
        abs(new_coords.getY() - 0.0) < eps &&
        abs(certain_point_coords.getX() - 5.0) < eps &&
        abs(certain_point_coords.getY() - 0.0) < eps
    );
    std::cout << "Check processing coordinates: +linear acceleration" << std::endl;
    // убираем линейное ускорние и добавляем угловое
    // имеем машинку, движующуюся с начальной скоростью v = 10 по окружности
    car_manager_check_process_coords.setAcceleration(0.0);
    car_manager_check_process_coords.setAngularAcceleration(10.0);
    sleep(1);
    new_coords = car_manager_check_process_coords.getPosition();
    certain_point_coords = car_manager_check_process_coords.getPositionAtCertainTime(2);
    assert(
        abs(new_coords.getX() - 6.83) < eps &&
        abs(new_coords.getY() - 2.60) < eps &&
        abs(certain_point_coords.getX() - 6.83) < eps &&
        abs(certain_point_coords.getY() - 2.60) < eps
    );
    std::cout << "Check processing coordinates: -linear acceleration, +angular acceleration" << std::endl;
    std::cout << "All tests passed succesfully!\nМожно идти трогать траву 🌿" << std::endl;
    return 0;
}