#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <chrono>
#include <deque>

#include "../coordinates/Coordinates.h"
#include "../car/CarCondition.h"
#include "../command/Command.h"
#include "../params/CarParams.h"

class CarManager : public CarCondition { 
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
        Coordinates getPosition();
        Coordinates getPositionAtCertainTime(double seconds);
        std::string identify() const override; 
        void printListOfCheckpoints();
    private:
        std::deque<Command> commandSequence;
        void updateAcceleration(std::chrono::time_point<std::chrono::steady_clock> timestamp, double new_angular_acceleration);
        void updateAngularAcceleration(std::chrono::time_point<std::chrono::steady_clock> timestamp, double new_angular_acceleration);
        std::chrono::time_point<std::chrono::steady_clock> getPrevCheckPointTimestamp();
        void storeCommand(Command command);
        void executeCommand(Command cmd);
        void updateTime();
        void updatePosition(std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, std::chrono::time_point<std::chrono::steady_clock> prev_timestamp);
        CarParams getUpdatedPosition(std::chrono::time_point<std::chrono::steady_clock> cur_timstamp, std::chrono::time_point<std::chrono::steady_clock> prev_timstamp);
        bool isCommandValid(Command command);
        bool isCheckPointValid(int checkpoint);
        CarParams processCondition(double x, double y, double theta, double v, double omega, double delta_seconds, double a, double a_a);
        double getDeltaSeconds(std::chrono::time_point<std::chrono::steady_clock> cur_timestamp, std::chrono::time_point<std::chrono::steady_clock> prev_timestamp);
};
#endif