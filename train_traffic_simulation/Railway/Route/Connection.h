#ifndef CONNECTION_H
#define CONNECTION_H


template<typename PointType>
class Connection {
    public: 
        PointType departure;
        PointType arrival;

        Connection(PointType departure_, PointType arrival_);
        bool operator==(const Connection& c) const;
};

template<typename PointType>
struct ConnectionHash {
    std::size_t operator()(const Connection<PointType>& connection) const {
        return (std::hash<std::string>()(connection.departure)) ^ (std::hash<std::string>()(connection.arrival));
    }
};

template<typename PointType>
Connection<PointType>::Connection(
    PointType departure_, 
    PointType arrival_
) : departure(departure_), arrival(arrival_) {}

template<typename PointType>
bool Connection<PointType>::operator==(const Connection& c) const{
    return departure == c.departure && arrival == c.arrival;
};

#endif