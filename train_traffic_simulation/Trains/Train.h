#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>

class BaseTrainParams {
    public:
        const int speed;
        BaseTrainParams(int speed_);
};

template<typename TrainParamsType>
class Train {
    public:
        int speed;
        std::string name;

        Train();
        Train(std::string name, int speed);
        virtual ~Train() = default;
        virtual TrainParamsType getParams() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Train& train) {
            os << "Train Name: " << train.name << ", Speed: " << train.speed;
            return os;
        }
};

template<typename TrainParamsType>
Train<TrainParamsType>::Train() : name(std::string()), speed(float()) {}

template<typename TrainParamsType>
Train<TrainParamsType>::Train(std::string name_, int speed_) : name(name_), speed(speed_) {}



BaseTrainParams::BaseTrainParams(int speed_) : speed(speed_) {}

#endif