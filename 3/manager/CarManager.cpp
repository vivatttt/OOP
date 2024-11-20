#include <iostream>
#include <chrono>
#include <iomanip>

#include "../coordinates/Coordinates.h"
#include "../manager/CarManager.h"
#include "../car/CarCondition.h"
#include "../params/CarParams.h"


CarManager::CarManager() :
    CarCondition(0.0, 0.0, 0.0, 0.0, 0.0, Coordinates(0, 0)) {}
CarManager::CarManager(
    double _velocity,
    double _acceleration,
    double _angular_velocity,
    double _angular_acceleration,
    double _angle,
    Coordinates _coordinates
) : CarCondition(
    _velocity,
    _acceleration,
    _angular_velocity,
    _angular_acceleration,
    _angle,
    _coordinates
) {}
CarParams CarManager::processCondition(double x, double y, double theta, double v, double omega, double delta_seconds, double a, double a_a){
    double t = 0.0;
    double dt = 0.001;
    while (t < delta_seconds) {
        v += a * dt;
        omega += a_a * dt;

        theta += omega * dt;

        x += v * cos(theta) * dt;
        y += v * sin(theta) * dt;

        t += dt;
    }
    return CarParams(Coordinates(x, y), theta, v, omega);
}
double CarManager::getDeltaSeconds(std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, std::chrono::time_point<std::chrono::steady_clock> prev_timestamp){
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(cur_timestamp - prev_timestamp);
    return elapsed.count();
}
CarParams CarManager::getUpdatedPosition(std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, std::chrono::time_point<std::chrono::steady_clock> prev_timestamp){
    double delta_seconds = getDeltaSeconds(cur_timestamp, prev_timestamp);

    double x = coordinates.getX();
    double y = coordinates.getY();
    double theta = angle;
    double v = velocity;
    double omega = angular_velocity;

    CarParams updated_condition = processCondition(x, y, theta, v, omega, delta_seconds, acceleration, angular_acceleration);
    return updated_condition;
}
void CarManager::updatePosition(std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, std::chrono::time_point<std::chrono::steady_clock> prev_timestamp){
    CarParams new_condition = getUpdatedPosition(cur_timestamp, prev_timestamp);
    
    coordinates = new_condition.coordinates;
    angle = new_condition.angle;
    velocity = new_condition.velocity;
    angular_velocity = new_condition.angular_velocity;
}
void CarManager::updateAcceleration(std::chrono::time_point<std::chrono::steady_clock> timestamp, double new_acceleration){
    std::chrono::time_point<std::chrono::steady_clock> prev_timestamp = getPrevCheckPointTimestamp();
    updatePosition(timestamp, prev_timestamp);
    acceleration = new_acceleration;
}
void CarManager::updateAngularAcceleration(std::chrono::time_point<std::chrono::steady_clock> timestamp, double new_angular_acceleration){
    std::chrono::time_point<std::chrono::steady_clock> prev_timestamp = getPrevCheckPointTimestamp();
    updatePosition(timestamp, prev_timestamp);
    angular_acceleration = new_angular_acceleration;
}
void CarManager::setAcceleration(double new_acceleration) {
    Command command(set_acceleration, new_acceleration);
    // сначала обновляем положение машинки
    executeCommand(command);
    // потом пишем команду в историю
    storeCommand(command);
}
void CarManager::setAngularAcceleration(double new_angular_acceleration) {
    Command command(set_angular_acceleration, new_angular_acceleration);
    // сначала обновляем положение машинки
    executeCommand(command);
    // потом пишем команду в историю
    storeCommand(command);
}
void CarManager::storeCommand(Command command){
    commandSequence.push_back(command);
}
std::chrono::time_point<std::chrono::steady_clock> CarManager::getPrevCheckPointTimestamp(){
    // если еще нет истории команд, то возвращаем время начала движения
    // иначе время, в которое была вызвана последняя в очереди команда
    if (commandSequence.size() == 0){
        return movement_start_time;
    }
    return commandSequence.back().timestamp;
}
void CarManager::executeCommand(Command cmd) {
    if (isCommandValid(cmd)){
        switch (cmd.command_type){
            case set_acceleration:
                updateAcceleration(cmd.timestamp, cmd.value);
                break;
            case set_angular_acceleration:
                updateAngularAcceleration(cmd.timestamp, cmd.value);
                break;
        }
    }
}
std::string CarManager::identify() const { 
    return "car-manager";
}
bool CarManager::isCommandValid(Command command){
    if (commandSequence.size() > 0){
        if (command.timestamp < commandSequence.back().timestamp) {
            std::cout << "Command is invalid. Skipping..." << std::endl;
            return false;
        }
    }
    return true;
}
Coordinates CarManager::getPosition(){
    // перед тем, как вернуть позицию, получаем ее обновленную версию для текущего момента времени
    auto cur_timestamp = std::chrono::steady_clock::now();
    auto prev_timestamp = (commandSequence.size() == 0) ? movement_start_time : commandSequence.back().timestamp;
    Coordinates cur_coordinates = getUpdatedPosition(cur_timestamp, prev_timestamp).coordinates;
    return cur_coordinates;
}
bool CarManager::isCheckPointValid(int checkpoint){
    return checkpoint < commandSequence.size() && checkpoint > 0;
}
void CarManager::printListOfCheckpoints(){
    int count = 0;
    std::cout << "Все чекпоинты:" << std::endl;
    std::cout << std::setw(6) << "count" << std::setw(16) << "command_type" <<  std::setw(20) << "value" << std::endl;
    for (Command& cmd : commandSequence) {
        std::cout << std::setw(6) << count << std::setw(16) << cmd.command_type << std::setprecision(4) << std::setw(20) << cmd.value << std::endl;
        count ++;
    }
    std::cout << std::endl;
}

Coordinates CarManager::getPositionAtCertainTime(double seconds){
    double x = start_coordinates.getX();
    double y = start_coordinates.getY();
    double theta = start_angle;
    double v = start_velocity;
    double omega = start_angular_velocity;
    double delta_seconds;
    double a = start_acceleration;
    double a_a = start_angular_acceleration;
    std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, prev_timestamp;
    CarParams new_condition;
    // начало алгоритмической задачки 😭 😭 😭
    int checkpoint_ind = 0;
    int deq_len = commandSequence.size();
    double sum_seconds_since_start = 0;
    while (checkpoint_ind <= deq_len){
        if (checkpoint_ind == deq_len){
            delta_seconds = seconds - sum_seconds_since_start;
            new_condition = processCondition(x, y, theta, v, omega, delta_seconds, a, a_a);
        }else{
            cur_timestamp = commandSequence[checkpoint_ind].timestamp;
            prev_timestamp = (checkpoint_ind == 0) ? movement_start_time : commandSequence[checkpoint_ind - 1].timestamp;
            delta_seconds = getDeltaSeconds(cur_timestamp, prev_timestamp);
            new_condition = processCondition(x, y, theta, v, omega, delta_seconds, a, a_a);
            sum_seconds_since_start += delta_seconds;
            
            // обновляем параметры из команды на чекпоинте
            switch (commandSequence[checkpoint_ind].command_type)
            {
            case set_acceleration:
                a = commandSequence[checkpoint_ind].value;
                break;
            case set_angular_acceleration:
                a_a = commandSequence[checkpoint_ind].value;
                break;
            }
        }
        x = new_condition.coordinates.getX();
        y = new_condition.coordinates.getY();
        theta = new_condition.angle;
        v = new_condition.velocity;
        omega = new_condition.angular_velocity;
        checkpoint_ind ++;
    }
    // конец алгоритмической задачки 🥹🥹
    return Coordinates(x, y);   
}