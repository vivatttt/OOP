#ifndef ROAD_H
#define ROAD_H

template<typename PointType>
class Road {
    public:
        PointType departure_point;
        PointType arrival_point;
        float length;

        Road(PointType departure, PointType arrival, float length);

        friend std::ostream& operator<<(std::ostream& os, const Road& road) {
            os << road.departure_point << " ---> " << road.arrival_point;
            return os;
        }
};

template<typename PointType>
Road<PointType>::Road(
    PointType departure_point_, 
    PointType arrival_point_, 
    float length_
) : departure_point(departure_point_), arrival_point(arrival_point_), length(length_) {}

#endif