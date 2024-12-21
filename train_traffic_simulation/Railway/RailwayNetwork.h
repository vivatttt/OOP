#ifndef RAILWAY_NETWORK_H
#define RAILWAY_NETWORK_H

#include <iostream>
#include <unordered_map>
#include <set>
#include <deque>

#include "Train/MovingTrain.h"
#include "Route/Road.h"
#include "Route/Connection.h"
#include "Train/TrainOnRoute.h"
#include "Train/MovingTrain.h"
#include "../Trains/FreightTrain.h"
#include "../Utils/uuid.h"

enum RoadOccupation {
    OCCUPIED,
    FREE
};

template<typename TrainType, typename PointType>
class RailwayNetwork {
public:
    Road<PointType> buildRoad(PointType departure_point, PointType arrival_point, float length, bool both_directions);
    void createTrainOnRoute(TrainType train, std::vector<Road<PointType> > route);

    void showNetwork();
    void startSimulation();
    float processTravelTime(float length, float speed);

    void printQueuedTrains();
    void printMovingTrains();

    void clear();
    
private:
    // грамотно захэшировать объект MovingTrain не просто (в силу сложного наследования и полей-классов), а так же хранить класс как ключ не совсем верно
    // поэтому присвоим каждому движущемуся поезду уникальный идентификатор и складывать в множество будем их
    // а дополнительно создадим таблицу вида uuid: object
    std::set<std::string> movingTrainUUIDs;
    std::unordered_map<std::string, MovingTrain<TrainType, PointType> > movingTrains;
    std::unordered_map<PointType, std::deque<TrainOnRoute<TrainType, PointType> > > queuedTrains;
    std::unordered_map<PointType, std::set<PointType> > roads;
    std::unordered_map<Connection<PointType>, float, ConnectionHash<PointType> > road_length;
    std::unordered_map<Connection<PointType>, RoadOccupation, ConnectionHash<PointType> > road_occupation;

    void makeTrainMoving(TrainOnRoute<TrainType, PointType> train, float current_time);
    bool areConnected(PointType a, PointType b, bool check_both_directions);
    bool isArrivalPoint(MovingTrain<TrainType, PointType> train);
    
    void logTrainArrived(MovingTrain<TrainType, PointType> train);
    void logTrainArrivedToIntermediatePoint(MovingTrain<TrainType, PointType> train);
    void logTrainStartsMoving(MovingTrain<TrainType, PointType> train);
    void logTrainQueued(TrainOnRoute<TrainType, PointType> train);

    void storeNewMovingTrain(MovingTrain<TrainType, PointType> train);
    void destroyMovingTrain(std::string uuid);

    Connection<PointType> getConnectionByTrainOnRoute(TrainOnRoute<TrainType, PointType> train);
};

template<typename TrainType, typename PointType>
Road<PointType> RailwayNetwork<TrainType, PointType>::buildRoad(PointType departure_point, PointType arrival_point, float length, bool both_directions) {
    roads[departure_point].insert(arrival_point);
    road_occupation[Connection<PointType>(departure_point, arrival_point)] = FREE;

    if (both_directions) {
        roads[arrival_point].insert(departure_point);
        road_occupation[Connection<PointType>(arrival_point, departure_point)] = FREE;
    }

    road_length[Connection<PointType>(departure_point, arrival_point)] = length;
    return Road<PointType>(departure_point, arrival_point, length);
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::showNetwork() {
    std::cout << "---------------" << std::endl << "Roads - Graph View: " << std::endl << "---------------" << std::endl;

    for (auto& road : roads){
        PointType departure = road.first;
        std::set<PointType> arrivals = road.second;
        std::cout << departure << ": [ ";
        for (auto& arrival : arrivals){
            std::cout << arrival << " ";
        }
        std::cout << "]" << std::endl;
    }

    std::cout << "---------------" << std::endl << "Roads - Detailed View: " << std::endl << "---------------" << std::endl;
    for (auto& road_obj : road_length){
        Connection<PointType> connection = road_obj.first;
        float length = road_obj.second;
        std::string line = " ---> ";
        if (areConnected(connection.arrival, connection.departure, true)){
            line = " <---> ";
        }
        std::cout << connection.departure << line << connection.arrival << ": " << length << " km" << std::endl;
    }
};

template<typename TrainType, typename PointType>
bool RailwayNetwork<TrainType, PointType>::areConnected(PointType a, PointType b, bool check_both_directions) {
    auto it = roads.find(a);
    if (it != roads.end()) {
        return it->second.find(b) != it->second.end() || (check_both_directions && it->second.find(a) != it->second.end());
    }
    return false;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::createTrainOnRoute(TrainType train, std::vector<Road<PointType> > route) {
    if (route.size() < 1) return;
    TrainOnRoute<TrainType, PointType> queued_train = TrainOnRoute<TrainType, PointType>(train, route, 0.0);
    PointType start_point = route[0].departure_point;
    queuedTrains[start_point].push_back(queued_train);
};

template<typename TrainType, typename PointType>
float RailwayNetwork<TrainType, PointType>::processTravelTime(float length, float speed) {
    return (length / speed) * 60;
};

template<typename TrainType, typename PointType>
Connection<PointType> RailwayNetwork<TrainType, PointType>::getConnectionByTrainOnRoute(TrainOnRoute<TrainType, PointType> train) {
    PointType departure = train.route[train.current_road_number].departure_point;
    PointType arrival = train.route[train.current_road_number].arrival_point;
    return Connection<PointType>(departure, arrival);
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::storeNewMovingTrain(MovingTrain<TrainType, PointType> train){
    std::string uuid = UUID::get_uuid();
    movingTrainUUIDs.insert(uuid);
    movingTrains[uuid] = train;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::destroyMovingTrain(std::string uuid){
    movingTrainUUIDs.erase(uuid);
    movingTrains.erase(uuid);
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::makeTrainMoving(TrainOnRoute<TrainType, PointType> train, float current_time) {
    Connection<PointType> connection = getConnectionByTrainOnRoute(train);

    if (road_occupation[connection] == FREE) {
        road_occupation[connection] = OCCUPIED;
        float length = road_length[connection];
        float speed = train.train.speed;
        float start_time = current_time;
        float finish_time = processTravelTime(length, speed) + start_time;
        MovingTrain<TrainType, PointType> moving_train(start_time, finish_time, train);

        storeNewMovingTrain(moving_train);
        logTrainStartsMoving(moving_train);

    } else {
        std::cout << "Error while moving train!" << std::endl;
    }
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::printQueuedTrains() {
    std::cout << "------Queued Trains------" << std::endl;
    for (auto& queued_object : queuedTrains) {
        std::cout << queued_object.first << ": " << std::endl;
        std::cout << "      ";
        for (auto t = queued_object.second.begin(); t != queued_object.second.end(); ++t) {
            std::cout << " [" << (*t).train.name << " " << (*t).queued_time << "],";
        }
        std::cout << std::endl;
    }
};


template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::printMovingTrains() {
    std::cout << "------Moving Trains------" << std::endl;
    for (auto& moving_train : movingTrains) {
        std::cout << moving_train.second << std::endl;
    }
};

template<typename TrainType, typename PointType>
bool RailwayNetwork<TrainType, PointType>::isArrivalPoint(MovingTrain<TrainType, PointType> train) {
    return train.object.current_road_number == train.object.route_length - 1;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::logTrainStartsMoving(MovingTrain<TrainType, PointType> train) {
    std::cout <<  train.start_time << ": " << train.object.train.name << " starts moving from " << train.object.route[train.object.current_road_number].departure_point << " to " << train.object.route[train.object.current_road_number].arrival_point << std::endl;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::logTrainArrived(MovingTrain<TrainType, PointType> train) {
    std::cout << train.finish_time << ": " << train.object.train.name << " has successfully arrived to " << train.object.route[train.object.current_road_number].arrival_point << "!!!" << std::endl;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::logTrainArrivedToIntermediatePoint(MovingTrain<TrainType, PointType> train) {
    std::cout << train.finish_time << ": " << train.object.train.name << " has arrived to intermediate point - " << train.object.route[train.object.current_road_number].arrival_point << std::endl;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::logTrainQueued(TrainOnRoute<TrainType, PointType> train) {
    std::cout << train.queued_time << ": " << train.train.name << " queued at " << train.route[train.current_road_number].departure_point << std::endl;
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::startSimulation() {
    bool is_selected;
    MovingTrain<TrainType, PointType> closest_arrival_time_train, moving_train;
    std::string closest_arrival_time_train_uuid;

    std::cout << "Simulation started" << std::endl;

    // Запускаем все возможные поезда из очереди
    for (auto& queued_object : queuedTrains) {
        PointType departure = queued_object.first;
        TrainOnRoute<TrainType, PointType> queued_train = queued_object.second.front();
        PointType arrival = queued_train.route[queued_train.current_road_number].arrival_point;
        Connection<PointType> expected_connection = Connection<PointType>(departure, arrival);

        if (road_occupation[expected_connection] == FREE) {
            makeTrainMoving(queued_train, 0.0);
            queued_object.second.pop_front();
        } else {
            std::cout << "Road from " << departure << " to " << arrival << " is occupied, train is waiting." << std::endl;
        }
    }
    
    // Основная логика
    while (!movingTrains.empty()) {
        is_selected = false;
        for (auto& moving_train_uuid : movingTrainUUIDs) {
            moving_train = movingTrains[moving_train_uuid];
            if (!is_selected) {
                closest_arrival_time_train = moving_train;
                closest_arrival_time_train_uuid = moving_train_uuid;
                is_selected = true;
            } else {
                if (moving_train.finish_time < closest_arrival_time_train.finish_time) {
                    closest_arrival_time_train = moving_train;
                    closest_arrival_time_train_uuid = moving_train_uuid;
                }
            }
        }

        if (isArrivalPoint(closest_arrival_time_train)) {
            // логируем прибытие в финальную точку
            logTrainArrived(closest_arrival_time_train);
        } else {
            // логируем прибытие в промежуточную точку
            logTrainArrivedToIntermediatePoint(closest_arrival_time_train);
            // ставим собственный указатель на следующую дорогу в маршруте
            TrainOnRoute<TrainType, PointType> train = closest_arrival_time_train.object;
            train.queued_time = closest_arrival_time_train.finish_time;
            train.current_road_number++;
            Connection<PointType> new_connection = getConnectionByTrainOnRoute(train);
            // смотрим, свободна ли следующая дорога
            // если да, то едем по ней
            // иначе становимся в очередь
            if (road_occupation[new_connection] == FREE) {
                makeTrainMoving(train, train.queued_time);
            } else {
                queuedTrains[new_connection.departure].push_back(train);
                logTrainQueued(train);
            }
        }
        destroyMovingTrain(closest_arrival_time_train_uuid);
        // помечаем дорогу как свободную
        Connection<PointType> connection = getConnectionByTrainOnRoute(closest_arrival_time_train.object);
        road_occupation[connection] = FREE;
        // проверяем, есть ли очередь на эту дорогу
        // если да, то пускаем первый поезд из очереди
        if (!queuedTrains[connection.departure].empty()) {
            makeTrainMoving(queuedTrains[connection.departure].front(), closest_arrival_time_train.finish_time);
            queuedTrains[connection.departure].pop_front();
        }
    }   
};

template<typename TrainType, typename PointType>
void RailwayNetwork<TrainType, PointType>::clear() {
    movingTrainUUIDs.clear();
    movingTrains.clear();
    queuedTrains.clear();
    roads.clear();
    road_length.clear();
    road_occupation.clear();
};

#endif
