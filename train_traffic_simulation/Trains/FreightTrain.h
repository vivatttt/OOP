#ifndef FREIGHTTRAIN_H
#define FREIGHTTRAIN_H

#include "../Trains/Train.h"
#include <string>

class FreightTrainParams : public BaseTrainParams {
    public:
        float load_capacity;
        FreightTrainParams(int speed_, float load_capacity_);
};

class FreightTrain : public Train<FreightTrainParams> {
    public:
        FreightTrain();
        FreightTrain( std::string name, int speed, float load_capacity);

        FreightTrainParams getParams() const override;
        
    private:
        float load_capacity;
};

FreightTrain::FreightTrain() : Train(), load_capacity(0.0) {}

FreightTrain::FreightTrain(
    std::string name_,
    int speed_, 
    float load_capacity_
) : Train(name_, speed_), load_capacity(load_capacity_) {}

FreightTrainParams::FreightTrainParams(
    int speed_, 
    float load_capacity_
) : BaseTrainParams(speed_), load_capacity(load_capacity_) {}

FreightTrainParams FreightTrain::getParams() const {
    return FreightTrainParams(
        speed, 
        load_capacity
    );
};


#endif