#ifndef ELECTRICTRAIN_H
#define ELECTRICTRAIN_H

#include "../Trains/Train.h"
#include <string>

class ElectricTrainParams : public BaseTrainParams {
    public:
        int voltage;
        ElectricTrainParams(int speed_, int voltage_);
};

class ElectricTrain : public Train<ElectricTrainParams> {
    public:
        ElectricTrain();
        ElectricTrain(std::string name_, int speed_, int voltage_);

        ElectricTrainParams getParams() const override;
        
    private:
        int voltage;
};

ElectricTrain::ElectricTrain() : Train(), voltage(0) {}

ElectricTrain::ElectricTrain(
    std::string name_,
    int speed_, 
    int voltage_
) : Train(name_, speed_), voltage(voltage_) {}

ElectricTrainParams::ElectricTrainParams(
    int speed_, 
    int voltage_
) : BaseTrainParams(speed_), voltage(voltage_) {}

ElectricTrainParams ElectricTrain::getParams() const {
    return ElectricTrainParams(
        speed, 
        voltage
    );
};


#endif