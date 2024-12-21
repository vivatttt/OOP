#ifndef MOVING_TRAIN_H
#define MOVING_TRAIN_H

#include "TrainOnRoute.h"

template<typename TrainType, typename PointType>
class MovingTrain {
    public:
        float start_time;
        float finish_time;
        
        TrainOnRoute<TrainType, PointType> object;

        bool operator==(const MovingTrain& m_t) const;
        bool operator<(const MovingTrain<TrainType, PointType>& m_t) const;

        MovingTrain();
        MovingTrain(float start_time, float finish_time, TrainOnRoute<TrainType, PointType> object);

        friend std::ostream& operator<<(std::ostream& os, const MovingTrain& t) {
            os << t.object << std::endl;
            os << "Start time: " << t.start_time << std::endl;
            os << "Finish time: " << t.finish_time << std::endl;
            return os;
        }
};

template<typename TrainType, typename PointType>
MovingTrain<TrainType, PointType>::MovingTrain(
    float start_time_, 
    float finish_time_,
    TrainOnRoute<TrainType, PointType> object_
) : start_time(start_time_), finish_time(finish_time_), object(object_) {}

template<typename TrainType, typename PointType>
MovingTrain<TrainType, PointType>::MovingTrain() : start_time(0.0), finish_time(0.0) {}


template<typename TrainType, typename PointType>
bool MovingTrain<TrainType, PointType>::operator==(const MovingTrain<TrainType, PointType>& m_t) const{
    float eps = 0.001;
    return abs(finish_time - m_t.finish_time) < eps && abs(finish_time - m_t.start_time) < eps;
};

template<typename TrainType, typename PointType>
bool MovingTrain<TrainType, PointType>::operator<(const MovingTrain<TrainType, PointType>& m_t) const {
    return start_time < m_t.start_time; 
};

template<typename TrainType, typename PointType>
struct MovingTrainHash {
    std::size_t operator()(const MovingTrain<TrainType, PointType>& m_t) const {
        return (std::hash<float>()(m_t.start_time)) ^ (std::hash<float>()(m_t.finish_time));
    }
};


#endif