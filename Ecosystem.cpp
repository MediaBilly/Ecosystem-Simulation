#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Ecosystem.h"

Ecosystem::Ecosystem(int size,int lakeSize,int hills,Season season, bool printDetailedInfo)
{
    this->terrainSize = size;
    this->dayOfYear = 1;
    this->season = season;
    this->printDetailedInfo = printDetailedInfo;
    this->availableWater = this->availableHills = 0;
    this->availableMeadow = size * size;
    this->terrain = new tile*[this->terrainSize];
    for (int i = 0; i < this->terrainSize; ++i)
        this->terrain[i] = new tile[this->terrainSize];
    this->mapGenerator = new MapGenerator(this);
    this->mapGenerator->ResetMap();
    this->mapGenerator->GenerateRiver();
    this->mapGenerator->GenerateLake(lakeSize);
    this->mapGenerator->GenerateHills(hills);
    this->mapGenerator->GenerateMeadow();
}

bool Ecosystem::placePlants(int grasses, int algaes, int maples, int oaks, int pines)
{
    Plant *plant;
    //Check if there is enough space for all plants
    if (!Grass::enoughSpace(grasses,this->availableMeadow))
    {
        std::cout << "Not enough space for grasses." << std::endl;
        return false;
    }
    if (!Algae::enoughSpace(algaes,this->availableWater))
    {
        std::cout << "Not enough space for algaes." << std::endl;
        return false;
    }
    if (!Maple::enoughSpace(maples,this->availableMeadow,this->availableHills))
    {
        std::cout << "Not enough space for maples." << std::endl;
        return false;
    }
    if (!Oak::enoughSpace(oaks,this->availableMeadow))
    {
        std::cout << "Not enough space for oaks." << std::endl;
        return false;
    }
    if (!Pine::enoughSpace(pines,this->availableHills))
    {
        std::cout << "Not enough space for pines." << std::endl;
        return false;
    }
    for (int i = 0; i < grasses; ++i) {
        plant = new Grass("Grass");
        do {
            plant->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (this->terrain[plant->getY()][plant->getX()].plant != NULL || !plant->canGrowHere(this->terrain[plant->getY()][plant->getX()].token));
        this->plants.push_back(plant);
        this->terrain[plant->getY()][plant->getX()].plant = plant;
    }
    for (int i = 0; i < algaes; ++i) {
        plant = new Algae("Algae");
        do {
            plant->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (this->terrain[plant->getY()][plant->getX()].plant != NULL || !plant->canGrowHere(this->terrain[plant->getY()][plant->getX()].token));
        this->plants.push_back(plant);
        this->terrain[plant->getY()][plant->getX()].plant = plant;
    }
    for (int i = 0; i < maples; ++i) {
        plant = new Maple("Maple");
        do {
            plant->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (this->terrain[plant->getY()][plant->getX()].plant != NULL || !plant->canGrowHere(this->terrain[plant->getY()][plant->getX()].token));
        this->plants.push_back(plant);
        this->terrain[plant->getY()][plant->getX()].plant = plant;
    }
    for (int i = 0; i < oaks; ++i) {
        plant = new Oak("Oak");
        do {
            plant->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (this->terrain[plant->getY()][plant->getX()].plant != NULL || !plant->canGrowHere(this->terrain[plant->getY()][plant->getX()].token));
        this->plants.push_back(plant);
        this->terrain[plant->getY()][plant->getX()].plant = plant;
    }
    for (int i = 0; i < pines; ++i) {
        plant = new Pine("Pine");
        do {
            plant->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (this->terrain[plant->getY()][plant->getX()].plant != NULL || !plant->canGrowHere(this->terrain[plant->getY()][plant->getX()].token));
        this->plants.push_back(plant);
        this->terrain[plant->getY()][plant->getX()].plant = plant;
    }
    return true;
}

void Ecosystem::placeAnimals(int deers, int rabbits, int groundhogs, int salmon, int foxes, int wolves, int bears)
{
    Animal *animal;
    for (int i = 0; i < deers; ++i) {
        animal = new Deer("Deer", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < rabbits; ++i) {
        animal = new Rabbit("Rabbit", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < groundhogs; ++i) {
        animal = new Groundhog("Groundhog", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < salmon; ++i) {
        animal = new Salmon("Salmon");
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < foxes; ++i) {
        animal = new Fox("Fox", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < wolves; ++i) {
        animal = new Wolf("Wolf", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
    for (int i = 0; i < bears; ++i) {
        animal = new Bear("Bear", true);
        do {
            animal->setPos(rand() % this->terrainSize,rand() % this->terrainSize);
        } while (!animal->canLiveHere(this->terrain[animal->getY()][animal->getX()].token));
        animal->setHome(this->terrain[animal->getY()][animal->getX()].token);
        this->animals.push_back(animal);
        this->terrain[animal->getY()][animal->getX()].animals.push_back(animal);
    }
}

void Ecosystem::ApplySeason(bool firstTime)//Change season and apply values
{
    if (!firstTime)
    {
        switch (this->season)
        {
            case Spring:
                this->season = Summer;
                break;
            case Summer:
                this->season = Autumn;
                break;
            case Autumn:
                this->season = Winter;
                break;
            case Winter:
                this->season = Spring;
                break;
            default:
                break;
        }
    }
    switch (this->season)
    {
        case Spring:
            this->plantsGrowthPeriod = 5;
            this->animalsGrowthPeriod = 20;
            this->plantsBreedingRepPeriod = 10;
            this->herbivoreAnimalsBreedingRepPeriod = 12;
            this->carnivoreAnimalsBreedingRepPeriod = 11;
            for (unsigned int i = 0; i < this->animals.size(); ++i) {
                this->animals[i]->wakeUp();//Wake up animals in hibernation
            }
            break;
        case Summer:
            this->plantsGrowthPeriod = 10;
            this->animalsGrowthPeriod = 30;
            this->plantsBreedingRepPeriod = 10;
            this->herbivoreAnimalsBreedingRepPeriod = 8;
            this->carnivoreAnimalsBreedingRepPeriod = 9;
            break;
        case Autumn:
            this->plantsGrowthPeriod = 0;
            this->animalsGrowthPeriod = 15;
            this->plantsBreedingRepPeriod = 20;
            this->herbivoreAnimalsBreedingRepPeriod = 5;
            this->carnivoreAnimalsBreedingRepPeriod = 9;
            break;
        case Winter:
            for (unsigned int i = 0; i < this->animals.size(); ++i) {
                this->animals[i]->hibernate();//Hibernate all hibernating animals
            }
            this->plantsBreedingRepPeriod = 0;
            this->plantsGrowthPeriod = 10;
            this->animalsGrowthPeriod = 30;
            this->herbivoreAnimalsBreedingRepPeriod = 18;
            this->carnivoreAnimalsBreedingRepPeriod = 10;
            break;
        default:
            break;
    }
}

void Ecosystem::DailyReset()
{
    //Reset hunger for all animals that are not currently in hibernation
    for (unsigned int i = 0; i < this->animals.size(); ++i) {
        if (!this->animals[i]->inHibernation())
            this->animals[i]->resetHunger();
    }
    //Raise all the plants
    if (this->plantsGrowthPeriod != 0 && this->dayOfYear % this->plantsGrowthPeriod == 0) {
        for (unsigned int i = 0; i < this->plants.size(); ++i) {
            this->plants[i]->Raise();
        }
    }
    //Raise all the animals
    if (this->dayOfYear % this->animalsGrowthPeriod == 0) {
        for (unsigned int i = 0; i < this->animals.size(); ++i) {
            this->animals[i]->Raise();
        }
    }
    //Set herbivore animals heat
    if (this->dayOfYear % this->herbivoreAnimalsBreedingRepPeriod == 0) {
        for (unsigned int i = 0;i < this->animals.size();i++) {
            if (!this->animals[i]->inHibernation())//Animals in hibernation cannot breed
                this->animals[i]->setHeat(this->animals[i]->getToken() == 'H');
        }
    } else {
        for (unsigned int i = 0;i < this->animals.size();i++) {
            if (this->animals[i]->getToken() == 'H')
                this->animals[i]->setHeat(false);
        }
    }
    //Set carnivore animals heat
    if (this->dayOfYear % this->carnivoreAnimalsBreedingRepPeriod == 0) {
        for (unsigned int i = 0;i < this->animals.size();i++) {
            if (!this->animals[i]->inHibernation())//Animals in hibernation cannot breed
                this->animals[i]->setHeat(this->animals[i]->getToken() == 'C');
        }
    } else {
        for (unsigned int i = 0;i < this->animals.size();i++) {
            if (this->animals[i]->getToken() == 'C')
                this->animals[i]->setHeat(false);
        }
    }
}

//Removes a specific animal from a specific list
void remove(std::vector<Animal*> &animals,Animal *toDel)
{
    for (unsigned int i = 0; i < animals.size(); ++i) {
        if (animals[i] == toDel) {
            animals.erase(animals.begin() + i);
        }
    }
}

bool Ecosystem::MoveAnimal(Direction dir, int i, int x, int y)//Moves the ith animal with coordinates (x,y) to the direction specified
{
    bool ok = false;
    switch (dir)
    {
        case UP://UP
            if (y > 0) {
                if ((ok = this->animals[i]->Move(UP,this->terrain[y - 1][x].token))) {
                    remove(this->terrain[y][x].animals,this->animals[i]);
                    this->terrain[y - 1][x].animals.push_back(this->animals[i]);
                }
            }
            break;
        case DOWN://DOWN
            if (y < this->terrainSize - 1) {
                if ((ok = this->animals[i]->Move(DOWN,this->terrain[y + 1][x].token))) {
                    remove(this->terrain[y][x].animals,this->animals[i]);
                    this->terrain[y + 1][x].animals.push_back(this->animals[i]);
                }
            }
            break;
        case LEFT://LEFT
            if (x > 0) {
                if ((ok = this->animals[i]->Move(LEFT,this->terrain[y][x - 1].token))) {
                    remove(this->terrain[y][x].animals,this->animals[i]);
                    this->terrain[y][x - 1].animals.push_back(this->animals[i]);
                }
            }
            break;
        case RIGHT://RIGHT
            if (x < this->terrainSize - 1) {
                if ((ok = this->animals[i]->Move(RIGHT,this->terrain[y][x + 1].token))) {
                    remove(this->terrain[y][x].animals,this->animals[i]);
                    this->terrain[y][x + 1].animals.push_back(this->animals[i]);
                }
            }
            break;
        default:
            break;
    }
    return ok;
}

void Ecosystem::AnimalMovement()
{
    int rnd,y,x;
    for (unsigned int i = 0; i < this->animals.size(); ++i) {
        if (!this->animals[i]->inHibernation()) {//Move only animals that are not in hibernation
            x = this->animals[i]->getX();
            y = this->animals[i]->getY();
            //For each animal that can move try all movement cases that are available depending on it's current position.
            //All animals move in random directions with the restrictions that are implemented in the Move function of each animal.
            if (y == 0)
            {
                if (x == 0)//Top left corner
                {
                    rnd = rand() % 2;
                    switch (rnd)
                    {
                        case 0://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                                this->MoveAnimal(RIGHT,i,x,y);
                            break;
                        case 1://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                                this->MoveAnimal(DOWN,i,x,y);
                            break;
                        default:
                            break;
                    }
                }
                else if (x == this->terrainSize - 1)//Top right corner
                {
                    rnd = rand() % 2;
                    switch (rnd)
                    {
                        case 0://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                                this->MoveAnimal(LEFT,i,x,y);
                            break;
                        case 1://LEFT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                                this->MoveAnimal(LEFT,i,x,y);
                            break;
                        default:
                            break;
                    }
                }
                else//Top side
                {
                    rnd = rand() % 3;
                    switch (rnd)
                    {
                        case 0://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    case 1://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 1://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(DOWN,i,x,y);
                                        break;
                                    case 1://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 2://LEFT
                            if (!this->MoveAnimal(LEFT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(DOWN,i,x,y);
                                        break;
                                    case 1://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            else if (y == this->terrainSize - 1)
            {
                if (x == 0)//Bottom left corner
                {
                    rnd = rand() % 2;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                                this->MoveAnimal(RIGHT,i,x,y);
                            break;
                        case 1://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                                this->MoveAnimal(UP,i,x,y);
                            break;
                        default:
                            break;
                    }
                }
                else if (x == this->terrainSize - 1)//Bottom right corner
                {
                    rnd = rand() % 2;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                                this->MoveAnimal(LEFT,i,x,y);
                            break;
                        case 1://LEFT
                            if (!this->MoveAnimal(LEFT,i,x,y))
                                this->MoveAnimal(UP,i,x,y);
                            break;
                        default:
                            break;
                    }
                }
                else//Bottom side
                {
                    rnd = rand() % 3;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    case 1://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 1://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    case 1://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 2://LEFT
                            if (!this->MoveAnimal(LEFT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    case 1://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            else
            {
                if (x == 0)//Left side
                {
                    rnd = rand() % 3;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    case 1://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(DOWN,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 1://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 2://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(RIGHT,i,x,y);
                                        break;
                                    case 1://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                else if (x == this->terrainSize - 1)//Right side
                {
                    rnd = rand() % 3;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(DOWN,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 1://LEFT
                            if (!this->MoveAnimal(LEFT,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(DOWN,i,x,y);
                                        break;
                                    case 1://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 2://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                            {
                                int rnd2 = rand() % 2;
                                switch (rnd2)
                                {
                                    case 0://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                            this->MoveAnimal(LEFT,i,x,y);
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                            this->MoveAnimal(UP,i,x,y);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                else//Elsewhere
                {
                    rnd = rand() % 4;
                    switch (rnd)
                    {
                        case 0://UP
                            if (!this->MoveAnimal(UP,i,x,y))
                            {
                                int rnd2 = rand() % 3;
                                switch (rnd2)
                                {
                                    case 0://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 2://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                case 1://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 1://DOWN
                            if (!this->MoveAnimal(DOWN,i,x,y))
                            {
                                int rnd2 = rand() % 3;
                                switch (rnd2)
                                {
                                    case 0://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 2://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                case 1://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 2://LEFT
                            if (!this->MoveAnimal(LEFT,i,x,y))
                            {
                                int rnd2 = rand() % 3;
                                switch (rnd2)
                                {
                                    case 0://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(RIGHT,i,x,y);
                                                    break;
                                                case 1://RIGHT
                                                    if (!this->MoveAnimal(RIGHT,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 2://RIGHT
                                        if (!this->MoveAnimal(RIGHT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                case 1://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        case 3://RIGHT
                            if (!this->MoveAnimal(RIGHT,i,x,y))
                            {
                                int rnd2 = rand() % 3;
                                switch (rnd2)
                                {
                                    case 0://DOWN
                                        if (!this->MoveAnimal(DOWN,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                case 1://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1://LEFT
                                        if (!this->MoveAnimal(LEFT,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(UP,i,x,y);
                                                    break;
                                                case 1://UP
                                                    if (!this->MoveAnimal(UP,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    case 2://UP
                                        if (!this->MoveAnimal(UP,i,x,y))
                                        {
                                            int rnd3 = rand() % 2;
                                            switch (rnd3)
                                            {
                                                case 0://LEFT
                                                    if (!this->MoveAnimal(LEFT,i,x,y))
                                                        this->MoveAnimal(DOWN,i,x,y);
                                                    break;
                                                case 1://DOWN
                                                    if (!this->MoveAnimal(DOWN,i,x,y))
                                                        this->MoveAnimal(LEFT,i,x,y);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void Ecosystem::AnimalEating()
{
    for (unsigned int i = 0; i < this->animals.size(); ++i) {
        if (!this->animals[i]->inHibernation()) {//Only animals that are not in hibernation can eat
            //Each herbivore animal tries to eat the plant that is on the same tile with it(if there is one).
            if (this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].plant != NULL && this->animals[i]->getToken() == 'H') {
                this->animals[i]->Eat(this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].plant);
            }
            //Each carnivore animal tries to eat all the other animals that are on the same tile with it(if there are any).
            if (this->animals[i]->getToken() == 'C') {
                for (unsigned int j = 0; j < this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].animals.size() && this->animals[i]->hungry(); ++j) {
                    //Animals in hibernation cannot be eaten.
                    //Also all the animals can't eat themselves.
                    if (!this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].animals[j]->inHibernation() && this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].animals[j] != this->animals[i])
                        this->animals[i]->Eat(this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].animals[j]);
                }
            }
        }
    }
}

void Ecosystem::CheckDeadEntities()
{
    //Erase DeadAnimals
    for (unsigned int i = 0; i < this->animals.size(); ++i) {
        if (!this->animals[i]->inHibernation()) {//Erase only dead animals that are not in hibernation
            this->animals[i]->CheckHunger();
            if (!this->animals[i]->isAlive()) {
                remove(this->terrain[this->animals[i]->getY()][this->animals[i]->getX()].animals,this->animals[i]);
                delete this->animals[i];
                this->animals.erase(this->animals.begin() + i);
            }
        }
    }
    //Erase Dead Plants
    for (unsigned int i = 0; i < this->plants.size(); ++i) {
        if (!this->plants[i]->isAlive()) {
            this->terrain[this->plants[i]->getY()][this->plants[i]->getX()].plant = NULL;
            delete this->plants[i];
            this->plants.erase(this->plants.begin() + i);
        }
    }
}

void Ecosystem::AnimalBreeding()
{
    Animal *newAnimal;
    unsigned long n = this->animals.size();
    //Breed adult animals
    for (unsigned int i = 0; i < n; ++i) {
        if (this->animals[i]->inHeat() && !this->animals[i]->inHibernation()) {//Animals in hibernation cannot breed
            if ((newAnimal = this->animals[i]->Breed()) != NULL) {
                this->animals.push_back(newAnimal);
                this->terrain[newAnimal->getY()][newAnimal->getX()].animals.push_back(newAnimal);
            }
        }
    }
}

void Ecosystem::FindFreeTile(Plant *plant, int &x, int &y)
{
    x = y = -1;
    int xCenter = plant->getX();
    int yCenter = plant->getY();
    for (int i = yCenter > 0 ? yCenter - 1 : yCenter;i < this->terrainSize && i <= yCenter + 1 && y == -1; ++i) {
        for (int j = xCenter > 0 ? xCenter - 1 : xCenter; j < this->terrainSize && j <= xCenter + 1 && x == -1; ++j) {
            if (i != yCenter && j != xCenter && this->terrain[i][j].plant == NULL && plant->canBreedHere(this->terrain[i][j].token)) {
                x = j;
                y = i;
            }
        }
    }
}

void Ecosystem::PlantBreeding()
{
    Plant *newPlant;
    int x,y;
    unsigned long n = this->plants.size();
    if (this->plantsBreedingRepPeriod != 0 && this->dayOfYear % this->plantsBreedingRepPeriod == 0) {
        for (unsigned int i = 0; i < n; ++i) {
            this->FindFreeTile(this->plants[i],x,y);
            if (x != -1 && y != -1) {
                if ((newPlant = this->plants[i]->Breed(this->terrain[y][x].token)) != NULL) {
                    newPlant->setPos(x,y);
                    this->plants.push_back(newPlant);
                    this->terrain[newPlant->getY()][newPlant->getX()].plant = newPlant;
                }
            }
        }
    }
}

void Ecosystem::printSystem() const
{
    for (int i = 0; i < this->terrainSize; ++i) {
        for (int j = 0; j < this->terrainSize; ++j) {
            if(this->terrain[i][j].plant != NULL)
                std::cout << this->terrain[i][j].plant->getToken() << ' ';
            else
                std::cout << this->terrain[i][j].token << ' ';
        }
        std::cout << std::endl;
    }
}

void Ecosystem::printPlantStatistics() const
{
    Plant::printTotal();
    Seedless::printTotal();
    Grass::printTotal();
    Algae::printTotal();
    Seeded::printTotal();
    Maple::printTotal();
    Oak::printTotal();
    Pine::printTotal();
    if (this->printDetailedInfo)//Print detailed info for each plant if that option is on
    {
        for (unsigned int i = 0; i < this->plants.size(); ++i)
        {
            std::cout << "Plant " << i + 1 << ':' << std::endl;
            this->plants[i]->printInfo();
        }
    }
}

void Ecosystem::printAnimalStatistics() const
{
    Animal::printTotal();
    Herbivore::printTotal();
    Deer::printTotal();
    Rabbit::printTotal();
    Groundhog::printTotal();
    Salmon::printTotal();
    Carnivore::printTotal();
    Fox::printTotal();
    Wolf::printTotal();
    Bear::printTotal();
    if (this->printDetailedInfo)//Print detailed info for each animal if that option is on
    {
        for (unsigned int i = 0; i < this->animals.size(); ++i)
        {
            std::cout << "Animal " << i + 1 << ':' << std::endl;
            this->animals[i]->printInfo();
        }
    }
}

std::string seasonToString(Season season)
{
    switch (season)
    {
        case Winter:
            return "Winter";
        case Spring:
            return "Spring";
        case Summer:
            return "Summer";
        case Autumn:
            return "Autumn";
        default:
            return "";
    }
}

Season stringToSeason(std::string season)
{
    std::string s;
    s.resize(season.size());
    std::transform(season.begin(),season.end(),s.begin(),::tolower);
    if (s == "winter")
        return Winter;
    if (s == "spring")
        return Spring;
    if (s == "summer")
        return Summer;
    if (s == "autumn")
        return Autumn;
    return Season_Invalid;
}

void Ecosystem::printInfo() const
{
    this->printSystem();
    std::cout << "Current Season:" << seasonToString(this->season) << std::endl;
    this->printPlantStatistics();
    this->printAnimalStatistics();
}

void Ecosystem::RunEcosystem(int days)
{
    this->ApplySeason(true);
    this->printInfo();
    //Run the simulation for all days
    for (;this->dayOfYear <= days;this->dayOfYear++) {
        if (this->dayOfYear % 90 == 0) {
            this->ApplySeason(false);
            this->printInfo();
        }
        this->DailyReset();
        for (int i = 0; i < 24; ++i) {//24 hours for each day
            this->AnimalMovement();
            this->AnimalEating();
        }
        this->CheckDeadEntities();
        this->AnimalBreeding();
        this->PlantBreeding();
    }
    this->printInfo();
}

Ecosystem::~Ecosystem()
{
    for (unsigned int i = 0; i < this->plants.size(); ++i) {
        delete this->plants[i];
    }
    for (unsigned int i = 0; i < this->animals.size(); ++i) {
        delete this->animals[i];
    }
    for (int i = 0; i < this->terrainSize; ++i) {
        delete[] this->terrain[i];
    }
    delete[] this->terrain;
    delete this->mapGenerator;
}
