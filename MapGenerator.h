#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Ecosystem.h"
class Ecosystem;
class MapGenerator {
private:
    Ecosystem *ecosystem;
    void placeWater(int, int);
    void placeHill(int, int);
public:
    MapGenerator(Ecosystem*);
    void ResetMap();
    void GenerateRiver();
    void GenerateLake(int);
    void GenerateHills(int);
    void GenerateMeadow();
};


#endif
