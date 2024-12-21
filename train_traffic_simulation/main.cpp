#include "Trains/PassengerTrain.h"
#include "Trains/ElectricTrain.h"
#include "Trains/FreightTrain.h"
#include "Railway/RailwayNetwork.h"
#include "Railway/Route/Road.h"
#include "Utils/uuid.h"

int main(){
    RailwayNetwork<FreightTrain, std::string> railway;
    
    std::cout << std::endl << "ON RAILWAY: " << std::endl<< std::endl;

    Road<std::string> DubnaMoscowRoad = railway.buildRoad("Dubna", "Moscow", 120.0, true);
    Road<std::string> MoscowNewYorkRoad = railway.buildRoad("Moscow", "NewYork", 1000.0, false);
    Road<std::string> MoscowCanberraRoad = railway.buildRoad("Moscow", "Canberra", 800.0, false);
    Road<std::string> CanberraWellingtonRoad = railway.buildRoad("Canberra", "Wellington", 400.0, false);
    Road<std::string> MoscowWeelingtonRoad = railway.buildRoad("Moscow", "Wellington", 1500.0, true); 
    Road<std::string> NewYorkCanberraRoad = railway.buildRoad("NewYork", "Canberra", 920.0, true);
    
    Road<std::string> MoscowBelgradeRoad = railway.buildRoad("Moscow", "Belgrade", 400.0, false);
    Road<std::string> BelgradeLondonRoad = railway.buildRoad("Belgrade", "London", 500.0, false);

    /*
        Симуляция с очередью в Канберре

                    📍Belgrade-----📍London
                        |
                        |🚂
        📍Dubna-------📍Moscow-------📍NewYork
          🚂         /     \           |  🚂
                    /       \         |
                   /     📍Canberra----
                  /          |
            📍Wellington------
    */

    std::vector<Road<std::string> > DubnaWellingtonRoute;
    DubnaWellingtonRoute.push_back(DubnaMoscowRoad); 
    DubnaWellingtonRoute.push_back(MoscowCanberraRoad);
    DubnaWellingtonRoute.push_back(CanberraWellingtonRoad);

    std::vector<Road<std::string> > NewYorkWellingtonRoute;
    NewYorkWellingtonRoute.push_back(NewYorkCanberraRoad);
    NewYorkWellingtonRoute.push_back(CanberraWellingtonRoad);
    
    std::vector<Road<std::string> > MoscowLondonRoute;
    MoscowLondonRoute.push_back(MoscowBelgradeRoad);
    MoscowLondonRoute.push_back(BelgradeLondonRoad);

    FreightTrain yandex_ft("Грузовой яндекс-поезд", 120, 2.2);
    railway.createTrainOnRoute(yandex_ft, DubnaWellingtonRoute);
    
    FreightTrain google_ft("Грузовой гугл-поезд", 120, 5.0);
    railway.createTrainOnRoute(google_ft, NewYorkWellingtonRoute);

    FreightTrain eastern_express("Восточный экспресс", 90, 400);
    railway.createTrainOnRoute(eastern_express, MoscowLondonRoute);

    railway.showNetwork();

    std::cout << "---------------" << std::endl << "Simulation: " << std::endl << "---------------" << std::endl;
    railway.startSimulation();
    railway.clear();

    /*
        Симуляция, где все поезда выезжают из одной точки

                   🚂 🚂 🚂
                    🌍Earth ------🌞Sun------🪐Teegarden B
                   /   \
                  /    🪐Mars
                 / 
              🪐Venus   
    */
    RailwayNetwork<ElectricTrain, std::string> star_railway;
    std::cout << std::endl << "ON STAR RAILWAY: " << std::endl<< std::endl;

    Road<std::string> EarthMarsRoad = star_railway.buildRoad("Earth", "Mars", 20000.0, false);
    Road<std::string> EarthVenusRoad = star_railway.buildRoad("Earth", "Venus", 30000.0, false);
    Road<std::string> EarthSunRoad = star_railway.buildRoad("Earth", "Sun", 120000.0, false);
    Road<std::string> SunTeegardenBRoad = star_railway.buildRoad("Sun", "TeegardenB", 1000000.0, false);

    std::vector<Road<std::string> > EarthMarsRoute;
    EarthMarsRoute.push_back(EarthMarsRoad); 

    std::vector<Road<std::string> > EarthVenusRoute;
    EarthVenusRoute.push_back(EarthVenusRoad); 

    std::vector<Road<std::string> > EarthTeegardenBRoute;
    EarthTeegardenBRoute.push_back(EarthSunRoad); 
    EarthTeegardenBRoute.push_back(SunTeegardenBRoad); 


    ElectricTrain mars_starship("Mars Starship", 1000, 2.2);
    star_railway.createTrainOnRoute(mars_starship, EarthMarsRoute);
    
    ElectricTrain venus_starship("Venus Starship", 2000, 5.0);
    star_railway.createTrainOnRoute(venus_starship, EarthVenusRoute);

    ElectricTrain exoplanet_starship("Exoplenet Starship", 2500, 400);
    star_railway.createTrainOnRoute(exoplanet_starship, EarthTeegardenBRoute);

    star_railway.showNetwork();

    std::cout << "---------------" << std::endl << "Simulation: " << std::endl << "---------------" << std::endl;
    star_railway.startSimulation();
    star_railway.clear();

    /*
        Симуляция без очередей с круговой дорогой
        Два поезда едут по кругу в противоположных направлениях
    */

    RailwayNetwork<PassengerTrain, std::string> mkad;
    std::cout << std::endl << "ON MKAD RAILWAY: " << std::endl<< std::endl;

    Road<std::string> Mkad_0_20 = mkad.buildRoad("0", "20", 20.0, true);
    Road<std::string> Mkad_20_70 = mkad.buildRoad("20", "70", 50.0, true);
    Road<std::string> Mkad_70_98 = mkad.buildRoad("70", "98", 28.0, true);
    Road<std::string> Mkad_98_0 = mkad.buildRoad("98", "0", 10.0, true);
    
    std::vector<Road<std::string> > ClockWise;
    ClockWise.push_back(Mkad_0_20);
    ClockWise.push_back(Mkad_20_70);
    ClockWise.push_back(Mkad_70_98);
    ClockWise.push_back(Mkad_98_0);

    std::vector<Road<std::string> > CounterClockWise;
    CounterClockWise.push_back(Mkad_98_0);
    CounterClockWise.push_back(Mkad_70_98);
    CounterClockWise.push_back(Mkad_20_70);
    CounterClockWise.push_back(Mkad_0_20);
    
    PassengerTrain clockwise_direction_train("Clockwise Direction Train", 120, 200);
    mkad.createTrainOnRoute(clockwise_direction_train, ClockWise);
    
    PassengerTrain counterclockwise_direction_train("Counterclockwise Direction Train", 110, 100);
    mkad.createTrainOnRoute(counterclockwise_direction_train, CounterClockWise);

    mkad.showNetwork();

    std::cout << "---------------" << std::endl << "Simulation: " << std::endl << "---------------" << std::endl;
    mkad.startSimulation();
    mkad.clear();


    return 0;
}