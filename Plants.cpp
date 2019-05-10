#include <iostream>
#include <cstdlib>
#include "Plants.h"

int Plant::total = 0;

Plant::Plant(std::string name,std::string species, int size, int x, int y, char token, int life, int lifeFactor, double breedingProb, double illnessProb) : Entity(name,species,size,x,y,token),life(life),lifeFactor(lifeFactor),breedingProb(breedingProb),illnessProb(illnessProb) { total++; }

bool Plant::isAlive() const
{
    return this->life > 0;
}

void Plant::printInfo() const
{
    Entity::printInfo();
    std::cout << '\t' << "Life:" << this->life << std::endl;
}

void Plant::printTotal()
{
    std::cout << "Total Plants:" << total << std::endl;
}

int Seedless::total = 0;

//All the plants have size.
//Size on seedless plants is always 0
Seedless::Seedless(std::string name,std::string species, int x, int y, char token, int life, int lifeFactor, double breedingProb, double illnessProb) : Plant(name,species,0,x,y,token,life,lifeFactor,breedingProb,illnessProb) { total++; }

void Seedless::LoseLife(int amount)
{
    this->life -= amount;
}

void Seedless::Raise()
{
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->illnessProb)
        this->life -= this->lifeFactor;
    else
        this->life += this->lifeFactor;
}

void Seedless::printTotal()
{
    std::cout << "\tSeedless:" << total << std::endl;
}

int Grass::total = 0;

Grass::Grass(std::string name) : Seedless(name,"Grass",0,0,'G',5,4,0.15,0.15) { total++; }

bool Grass::enoughSpace(int amount, int availableMeadow)
{
    return amount <= availableMeadow;
}

bool Grass::canGrowHere(char tile)
{
    return tile == '"';
}

bool Grass::canBreedHere(char tile)
{
    return tile == '"';//Grass can breed only where it can grow
}

Plant* Grass::Breed(char tile)
{
    Plant *newPlant;
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->breedingProb && tile == '"') {
        newPlant = new Grass(this->name + "'s child");
    } else {
        newPlant = NULL;
    }
    return newPlant;
}

void Grass::printTotal()
{
    std::cout << "\t\tGrasses:" << total << std::endl;
}

int Algae::total = 0;

Algae::Algae(std::string name) : Seedless(name,"Algae",0,0,'A',5,2,0.25,0.25) { total++; }

bool Algae::enoughSpace(int amount, int availableWater)
{
    return amount <= availableWater;
}

bool Algae::canGrowHere(char tile)
{
    return tile == '#';
}

bool Algae::canBreedHere(char tile)
{
    return tile == '#';
}

Plant* Algae::Breed(char tile)
{
    Plant *newPlant;
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->breedingProb && tile == '#') {
        newPlant = new Algae(this->name + "'s child");
    } else {
        newPlant = NULL;
    }
    return newPlant;
}

void Algae::printTotal()
{
    std::cout << "\t\tAlgaes:" << total << std::endl;
}

int Seeded::total = 0;

Seeded::Seeded(std::string name,std::string species, int x, int y, char token, int life, int lifeFactor, double breedingProb, double illnessProb,int foliage, int seeds, int size) : Plant(name,species,size,x,y,token,life,lifeFactor,breedingProb,illnessProb),foliage(foliage),seeds(seeds) { total++; }

void Seeded::LoseLife(int amount)
{
    //On seeded plants reduce their seeds foliage and amount using staggered reduction method with the priority specified
    int am;
    if(this->seeds > 0) {
        if (amount > this->seeds) {
            am = amount - this->seeds;
            this->seeds = 0;
            if (am > this->foliage) {
                am -= this->foliage;
                this->foliage = 0;
                if (am > this->life)
                    life = 0;
                else
                    life -= am;
            } else {
                this->foliage -= am;
            }
        } else {
            this->seeds -= amount;
        }
    }
    else if(this->foliage > 0) {
        if (amount > this->foliage) {
            am = amount - this->foliage;
            this->foliage = 0;
            if (am > this->life)
                life = 0;
            else
                life -= am;
        } else {
            this->foliage -= amount;
        }
    }
    else {
        if (amount > this->life)
            life = 0;
        else
            life -= amount;
    }
}

void Seeded::Raise()
{
    double outcome = (double)rand()/(double)RAND_MAX;
    if(outcome <= this->illnessProb)
    {
        this->foliage -= this->lifeFactor;
        if (this->foliage > 0)//Foliage must not go below 0
            this->foliage = 0;
        this->seeds -= 2 * this->lifeFactor;
        if (this->seeds < 0)//Seeds must not go below 0
            this->seeds = 0;
        this->size--;//When the plant loses foliage equal to life factor
    }
    else
    {
        this->foliage += this->lifeFactor;
        this->seeds += 2 * this->lifeFactor;
        this->size++;//When the plant gets foliage equal to life factor
    }
}

void Seeded::printInfo() const
{
    Plant::printInfo();
    std::cout << '\t' << "Foliage:" << this->foliage << std::endl;
    std::cout << '\t' << "Seeds:" << this->seeds << std::endl;
}

void Seeded::printTotal()
{
    std::cout << "\tSeeded:" << total << std::endl;
}

int Maple::total = 0;

//On seeded plants life = foliage
Maple::Maple(std::string name) : Seeded(name,"Maple",0,0,'M',20,10,0.05,0.05,20,10,2) { total++; }

bool Maple::enoughSpace(int amount, int availableMeadow, int availableHills)
{
    return amount <= availableMeadow && amount <= availableHills;
}

bool Maple::canGrowHere(char tile)
{
    return tile == '"' || tile == '^';
}

bool Maple::canBreedHere(char tile)
{
    return tile == '"' || tile == '^';//Maple can breed only where it can grow
}

Plant* Maple::Breed(char tile)
{
    Plant *newPlant;
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->breedingProb && (tile == '"' || tile == '^')) {
        newPlant = new Maple(this->name + "'s child");
    } else {
        newPlant = NULL;
    }
    return newPlant;
}

void Maple::printTotal()
{
    std::cout << "\t\tMaples:" << total << std::endl;
}

int Oak::total = 0;

Oak::Oak(std::string name) : Seeded(name,"Oak",0,0,'O',30,15,0.2,0.2,30,15,5) { total++; }

bool Oak::enoughSpace(int amount, int availableMeadow)
{
    return amount <= availableMeadow;
}

bool Oak::canGrowHere(char tile)
{
    return tile == '"';
}

bool Oak::canBreedHere(char tile)
{
    return tile == '"';
}

Plant* Oak::Breed(char tile)
{
    Plant *newPlant;
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->breedingProb && tile == '"') {
        newPlant = new Oak(this->name + "'s child");
    } else {
        newPlant = NULL;
    }
    return newPlant;
}

void Oak::printTotal()
{
    std::cout << "\t\tOaks:" << total << std::endl;
}

int Pine::total = 0;

Pine::Pine(std::string name) : Seeded(name,"Pine",0,0,'P',40,20,0.15,0.15,40,20,5) { total++; }

bool Pine::enoughSpace(int amount, int availableHills)
{
    return amount <= availableHills;
}

bool Pine::canGrowHere(char tile)
{
    return tile == '^';
}

bool Pine::canBreedHere(char tile)
{
    return tile != '#';
}

Plant* Pine::Breed(char tile)
{
    Plant *newPlant;
    double outcome = (double)rand()/(double)RAND_MAX;
    if (outcome <= this->breedingProb && tile != '#') {
        newPlant = new Pine(this->name + "'s child");
    } else {
        newPlant = NULL;
    }
    return newPlant;
}

void Pine::printTotal()
{
    std::cout << "\t\tPines:" << total << std::endl;
}