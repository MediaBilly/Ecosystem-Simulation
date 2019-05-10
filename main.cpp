#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ecosystem.h"

int main() {
    int dim,lakeSize,hills,days,grasses,algaes,maples,oaks,pines,deers,rabbits,groundhogs,salmon,foxes,wolves,bears;
    unsigned int seed;
    std::string season;
    char detailedInfo;
    //Read dimension
    do {
        std::cout << "Dimension:(>=10)" << std::endl;
        std::cin >> dim;
    } while (dim < 10);
    //Read lake size
    do {
        std::cout << "Lake Size:" << std::endl;
        std::cin >> lakeSize;
    } while (lakeSize <= 0);
    //Read hills amount
    do {
        std::cout << "Hills:" << std::endl;
        std::cin >> hills;
    } while (hills <= 0);
    //Read starting season
    do {
        std::cout << "Starting Season:(Winter,Spring,Summer,Autumn)" << std::endl;
        std::cin >> season;
    } while (stringToSeason(season) == Season_Invalid);
    //Ask for detailed info
    do {
        std::cout << "Print detailed info?('y' or 'n'):" << std::endl;
        std::cin >> detailedInfo;
    } while (detailedInfo != 'y' && detailedInfo != 'Y' && detailedInfo != 'n' && detailedInfo != 'N');
    std::cout << "Seed:(type 0 for random seed)" << std::endl;
    std::cin >> seed;
    if (seed == 0)
        srand((unsigned int)time(NULL));
    else
        srand(seed);
    Ecosystem *ecosystem = new Ecosystem(dim,lakeSize,hills,stringToSeason(season), detailedInfo == 'y' || detailedInfo == 'Y');
    //Read amount for each plant species
    do {
        std::cout << "Grasses:" << std::endl;
        std::cin >> grasses;
    } while (grasses < 0);
    do {
        std::cout << "Algaes:" << std::endl;
        std::cin >> algaes;
    } while (algaes < 0);
    do {
        std::cout << "Maples:" << std::endl;
        std::cin >> maples;
    } while (maples < 0);
    do {
        std::cout << "Oaks:" << std::endl;
        std::cin >> oaks;
    } while (oaks < 0);
    do {
        std::cout << "Pines:" << std::endl;
        std::cin >> pines;
    } while (pines < 0);
    if (ecosystem->placePlants(grasses,algaes,maples,oaks,pines))
    {
        //Read amount for each plant species
        do {
            std::cout << "Deers:" << std::endl;
            std::cin >> deers;
        } while (deers < 0);
        do {
            std::cout << "Rabbits:" << std::endl;
            std::cin >> rabbits;
        } while (rabbits < 0);
        do {
            std::cout << "Groundhogs:" << std::endl;
            std::cin >> groundhogs;
        } while (groundhogs < 0);
        do {
            std::cout << "Salmon:" << std::endl;
            std::cin >> salmon;
        } while (salmon < 0);
        do {
            std::cout << "Foxes:" << std::endl;
            std::cin >> foxes;
        } while (foxes < 0);
        do {
            std::cout << "Wolves:" << std::endl;
            std::cin >> wolves;
        } while (wolves < 0);
        do {
            std::cout << "Bears:" << std::endl;
            std::cin >> bears;
        } while (bears < 0);
        ecosystem->placeAnimals(deers,rabbits,groundhogs,salmon,foxes,wolves,bears);
        //Read simulation days
        do {
            std::cout << "Simulation days:" << std::endl;
            std::cin >> days;
        } while (days <= 0);
        ecosystem->RunEcosystem(days);
    }
    delete ecosystem;
    return 0;
}
