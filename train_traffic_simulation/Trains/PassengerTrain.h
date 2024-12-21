#ifndef PASSENGER_TRAIN_H
#define PASSENGER_TRAIN_H

#include "../Trains/Train.h"
#include <string>

class PassengerTrainParams : public BaseTrainParams {
    public:
        int capacity;
        PassengerTrainParams(int speed_, int capacity_);
};

class PassengerTrain : public Train<PassengerTrainParams> {
    public:
        PassengerTrain();
        PassengerTrain(std::string name, int speed, int capacity);

        PassengerTrainParams getParams() const override;
        
    private:
        int capacity;
};

PassengerTrain::PassengerTrain() : Train(), capacity(0) {}

PassengerTrain::PassengerTrain(
    std::string name_,
    int speed_, 
    int capacity_
) : Train(name_, speed_), capacity(capacity_) {}

PassengerTrainParams::PassengerTrainParams(
    int speed_, 
    int capacity_
) : BaseTrainParams(speed_), capacity(capacity_) {}

PassengerTrainParams PassengerTrain::getParams() const{
    return PassengerTrainParams(
        speed, 
        capacity
    );
};

#endif