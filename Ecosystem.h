#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <vector>
#include <string>
#include "MapGenerator.h"
#include "Plants.h"
#include "Animals.h"

enum Season{Winter,Spring,Summer,Autumn,Season_Invalid};
Season stringToSeason(std::string);
class MapGenerator;
class Ecosystem {
private:
    typedef struct
    {
        char token;
        Plant *plant;
        std::vector<Animal*> animals;
    }tile;
    tile **terrain;
    int dayOfYear;
    int plantsGrowthPeriod;
    int plantsBreedingRepPeriod;
    int animalsGrowthPeriod;
    int herbivoreAnimalsBreedingRepPeriod;
    int carnivoreAnimalsBreedingRepPeriod;
    int terrainSize;
    int availableMeadow;
    int availableWater;
    int availableHills;
    MapGenerator *mapGenerator;
    Season season;
    std::vector<Plant*> plants;
    std::vector<Animal*> animals;
    void ApplySeason(bool);
    void DailyReset();
    void AnimalMovement();
    void AnimalEating();
    void CheckDeadEntities();
    bool MoveAnimal(Direction, int, int, int);
    void AnimalBreeding();
    void FindFreeTile(Plant*, int&, int&);
    void PlantBreeding();
    void printSystem() const;
    void printPlantStatistics() const;
    void printAnimalStatistics() const;
    void printInfo() const;
    friend class MapGenerator;
    bool printDetailedInfo;
public:
    Ecosystem(int,int ,int ,Season, bool);
    bool placePlants(int, int, int, int, int);
    void placeAnimals(int, int, int, int, int, int, int);
    void RunEcosystem(int);
    virtual ~Ecosystem();
};


#endif
