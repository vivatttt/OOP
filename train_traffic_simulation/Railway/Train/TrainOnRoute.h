#ifndef TRAIN_ON_ROUTE_H
#define TRAIN_ON_ROUTE_H

#include "../Route/Road.h"
#include "../../Trains/Train.h"
#include <vector>

template<typename TrainType, typename PointType>
class TrainOnRoute {
    public:
        TrainType train;
        float queued_time;
        
        std::vector<Road<PointType> > route;
        int route_length;
        int current_road_number;

        TrainOnRoute();
        TrainOnRoute(
            TrainType train_,
            std::vector<Road<PointType> > route_,
            float queued_time_
        );

        friend std::ostream& operator<<(std::ostream& os, const TrainOnRoute& t) {
            os << "Train: " << t.train << std::endl;
            os << "Route: ";
            for (auto & road : t.route){
                os << road << ", ";
            }
            os << std::endl;
            os << "Currend road: " << t.route[t.current_road_number] << std::endl;
            os << "Queued time: " << t.queued_time << std::endl;
            return os;
        }
};

template<typename TrainType, typename PointType>
TrainOnRoute<TrainType, PointType>::TrainOnRoute() :  
    queued_time(0.0), 
    current_road_number(0),
    route_length(0) {}

template<typename TrainType, typename PointType>
TrainOnRoute<TrainType, PointType>::TrainOnRoute(
    TrainType train_,
    std::vector<Road<PointType> > route_,
    float queued_time_
) : 
    train(train_), 
    queued_time(queued_time_), 
    route(route_), 
    current_road_number(0),
    route_length(route_.size()) {}

#endif