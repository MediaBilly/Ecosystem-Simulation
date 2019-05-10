#include <iostream>
#include "Animals.h"

int Animal::total = 0;

Animal::Animal(std::string name,std::string species, char token, int size, int maxSize, int eatCount, int speed, int maxSpeed,bool hibernates,int neededFood, int maxNeededFood) : Entity(name,species,size,0,0,token) ,prevDir(NONE),moveTries(0),maxSize(maxSize),hungerCount(0),eatenFood(0),eatCount(eatCount),_isAlive(true),isHungry(true),_inHeat(false),speed(speed),maxSpeed(maxSpeed),hibernates(hibernates),_inHibernation(false),neededFood(neededFood),maxNeededFood(maxNeededFood),startX(this->x),startY(this->y),currentTile('"') { total++; }

void Animal::setHome(char tile)
{
    this->startX = this->x;
    this->startY = this->y;
    this->currentTile = tile;
}

bool Animal::isAdult() const
{
    return this->size == this->maxSize && this->speed == this->maxSpeed && this->neededFood == this->maxNeededFood;
}

int Animal::getSpeed() const
{
    return this->speed;
}

bool Animal::isAlive() const
{
    return this->_isAlive;
}

bool Animal::hungry() const
{
    return this->isHungry;
}

bool Animal::inHibernation() const
{
    return this->_inHibernation;
}

bool Animal::inHeat() const
{
    return this->_inHeat;
}

void Animal::Die()
{
    this->_isAlive = false;
}

void Animal::setHeat(bool heat)
{
    this->_inHeat = heat;
}

void Animal::hibernate()
{
    if(this->hibernates && !this->_inHibernation)
        this->_inHibernation = true;
}

void Animal::wakeUp()
{
    if(this->hibernates && this->_inHibernation)
        this->_inHibernation = false;
}

void Animal::resetHunger()
{
    this->eatenFood = 0;
}

void Animal::CheckHunger()
{
    if (this->eatenFood == 0)
        this->hungerCount++;
    if (this->hungerCount >= 10)
        this->Die();
}

bool Animal::Eat(Plant *)
{
    this->hungerCount = 0;
    return true;
}

bool Animal::Eat(Animal *)
{
    this->hungerCount = 0;
    return true;
}

bool Animal::Move(Direction direction, char)
{
    //If it is able to the animal should not move to the opposite direction of the previous one in order to achieve a more stable simulation.
    //For example,if the previous direction was FRONT, it cannot go back etc.At the first time it can move to any direction without any restrictions.
    //Also if there is not other option,it can go to the opposite direction of the previous one(if it tried to satisfy the restriction above and failed).
    bool ret = false;
    switch (direction)
    {
        case LEFT:
            if (this->prevDir != RIGHT || this->moveTries > 0)
            {
                this->prevDir = LEFT;
                this->x--;
                this->moveTries = 0;
                ret = true;
            }
            else
                this->moveTries++;
            break;
        case RIGHT:
            if (this->prevDir != LEFT || this->moveTries > 0)
            {
                this->prevDir = RIGHT;
                this->x++;
                this->moveTries = 0;
                ret = true;
            }
            else
                this->moveTries++;
            break;
        case UP:
            if (this->prevDir != DOWN || this->moveTries > 0)
            {
                this->prevDir = UP;
                this->y--;
                this->moveTries = 0;
                ret = true;
            }
            else
                this->moveTries++;
            break;
        case DOWN:
            if (this->prevDir != UP || this->moveTries > 0)
            {
                this->prevDir = DOWN;
                this->y++;
                this->moveTries = 0;
                ret = true;
            }
            else
                this->moveTries++;
            break;
        default:
            break;
    }
    return ret;
}

void Animal::printInfo() const
{
    Entity::printInfo();
    std::cout << '\t' << "HungerCount:" << this->hungerCount << std::endl;
    std::cout << '\t' << "EatenFood:" << this->eatenFood << std::endl;
    std::cout << '\t' << "IsAlive:" << (this->_isAlive ? "yes" : "no") << std::endl;
    std::cout << '\t' << "IsHungry:" << (this->isHungry ? "yes" : "no") << std::endl;
    std::cout << '\t' << "InHeat:" << (this->_inHeat ? "yes" : "no") << std::endl;
    if (this->hibernates)
        std::cout << '\t' << "InHibernation:" << (this->_inHibernation ? "yes" : "no") << std::endl;
}

void Animal::printTotal()
{
    std::cout << "Total Animals:" << total << std::endl;
}

int Herbivore::total = 0;

Herbivore::Herbivore(std::string name,std::string species, int size, int maxSize, int eatCount, int speed, int maxSpeed,bool hibernates, bool canClimb, int neededFood, int maxNeededFood) : Animal(name,species,'H',size,maxSize,eatCount,speed,maxSpeed,hibernates,neededFood,maxNeededFood),canClimb(canClimb) { total++; }

bool Herbivore::Eat(Animal *)
{
    return false;//Herbivores cannot eat Animals
}

bool Herbivore::Eat(Plant *plant)
{
    if (!this->_isAlive || !this->isHungry || !plant->isAlive())
        return false;
    if(this->eatenFood + this->eatCount <= this->neededFood) {
        this->eatenFood += this->eatCount;
        plant->LoseLife(this->eatCount);
        if (this->eatenFood >= this->neededFood)
            this->isHungry = false;
        return Animal::Eat(plant);
    } else {
        return false;
    }
}

void Herbivore::resetHunger()
{
    Animal::resetHunger();
    if (this->hungerCount == 7)//Herbivore animals need to eat after 7 days
        this->isHungry = true;
}

void Herbivore::printTotal()
{
    std::cout << "\tHerbivores:" << total << std::endl;
}

int Deer::total = 0;

Deer::Deer(std::string name, bool adult) : Herbivore(name,"Deer",adult ? 5 : 2,5,2,adult ? 8 : 4,8, false, false,adult ? 8 : 4,8) { total++; }

bool Deer::Move(Direction direction, char tile)
{
    return Animal::Move(direction,tile);
}

void Deer::Raise()
{
    if (this->size < this->maxSize)
        this->size++;
    if (this->speed + 2 <= this->maxSpeed)
        this->speed += 2;
    if (this->neededFood + 2 <= this->maxNeededFood)
        this->neededFood += 2;
}

bool Deer::Eat(Plant *plant)
{
    if(plant->getSize() <= this->size + 4)
        return Herbivore::Eat(plant);
    else
        return false;
}

bool Deer::canLiveHere(char tile) const
{
    return tile == '"';
}

Animal* Deer::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Deer(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Deer::printTotal()
{
    std::cout << "\t\tDeers:" << total << std::endl;
}

int Rabbit::total = 0;

Rabbit::Rabbit(std::string name, bool adult) : Herbivore(name,"Rabbit",adult ? 2 : 1,2,1,adult ? 6 : 2,6, false, false,adult ? 4 : 2,4) { total++; }

bool Rabbit::Move(Direction direction, char tile)
{
    if (tile != '^')
        return Animal::Move(direction,tile);
    else
        return false;
}

void Rabbit::Raise()
{
    if (this->size < this->maxSize)
        this->size++;
    if (this->neededFood < this->maxNeededFood)
        this->neededFood++;
    if (this->speed + 2 <= this->maxSpeed)
        this->speed += 2;
}

bool Rabbit::Eat(Plant *plant)
{
    if(plant->getToken() != 'A') {
        if(plant->getToken() == 'M' || plant->getToken() == 'O' || plant->getToken() == 'P') {
            if(plant->getSize() <= this->size)
                return Herbivore::Eat(plant);
            else
                return false;
        } else {
            return Herbivore::Eat(plant);
        }
    } else {
        return false;
    }
}

bool Rabbit::canLiveHere(char tile) const
{
    return tile == '"';
}

Animal* Rabbit::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Rabbit(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Rabbit::printTotal()
{
    std::cout << "\t\tRabbits:" << total << std::endl;
}

int Groundhog::total = 0;

Groundhog::Groundhog(std::string name, bool adult) : Herbivore(name,"Groundhog",adult ? 3 : 2,3,1,adult ? 5 : 3,5, true, true,adult ? 5 : 3,5) { total++; }

bool Groundhog::Move(Direction direction, char tile)
{
    if (tile != '#')
        return Animal::Move(direction,tile);
    else
        return false;
}

bool Groundhog::Eat(Plant *plant)
{
    if(plant->getToken() != 'A'){
        if(plant->getToken() == 'M' || plant->getToken() == 'O' || plant->getToken() == 'P') {
            if((this->canClimb && this->size >= plant->getSize() && this->isAdult()) || plant->getSize() <= 3*this->size)//Only adult groundhogs can climb
                return Herbivore::Eat(plant);
            else
                return false;
        } else {
            return Herbivore::Eat(plant);
        }
    } else {
        return false;
    }
}

void Groundhog::Raise()
{
    if (this->size < this->maxSize)
        this->size++;
    if (this->speed < this->maxSpeed)
        this->speed++;
    if (this->neededFood < this->maxNeededFood)
        this->neededFood++;
}

bool Groundhog::canLiveHere(char tile) const
{
    return tile == '"';
}

Animal* Groundhog::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Groundhog(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Groundhog::printTotal()
{
    std::cout << "\t\tGroundhogs:" << total << std::endl;
}

int Salmon::total = 0;

Salmon::Salmon(std::string name) : Herbivore(name,"Salmon",1,1,1,5,5, false, false,1,1) { total++; }

bool Salmon::Move(Direction direction, char tile)
{
    if (tile == '#')
        return Animal::Move(direction,tile);
    else
        return false;
}

bool Salmon::Eat(Plant *plant)
{
    if(plant->getToken() == 'A') {
        return Herbivore::Eat(plant);
    } else {
        return false;
    }
}

void Salmon::Raise() {}

bool Salmon::canLiveHere(char tile) const
{
    return tile == '#';
}

Animal* Salmon::Breed()
{
    Animal *child = new Salmon(this->name + "'s child");
    child->setPos(this->x,this->y);
    child->setHome(this->token);
    return child;
}

void Salmon::printTotal()
{
    std::cout << "\t\tSalmons:" << total << std::endl;
}

int Carnivore::total = 0;

//On carnivore animals,eat count doesn't matter so it equals 1
Carnivore::Carnivore(std::string name,std::string species, int size, int maxSize, int speed, int maxSpeed, bool hibernates, int attack, int defence,int maxAttack,int maxDefence,int neededFood, int maxNeededFood) : Animal(name,species,'C',size,maxSize,1,speed,maxSpeed,hibernates,neededFood,maxNeededFood),attack(attack),defence(defence),maxAttack(maxAttack),maxDefence(maxDefence) { total++; }

bool Carnivore::Eat(Animal *animal)
{
    if(!this->_isAlive || !animal->isAlive())
        return false;
    if(this->isHungry) {
        if (animal->getToken() == 'C') {
            if (this->hungerCount >= 8) {
                this->isHungry = false;
                animal->Die();
                return Animal::Eat(animal);
            } else {
                return false;
            }
        } else if (animal->getToken() == 'H') {
            this->isHungry = false;
            animal->Die();
            return Animal::Eat(animal);
        }
    } else {
        return false;
    }
    return false;
}

bool Carnivore::Eat(Plant *)
{
    return false;//Carnivores cannot eat Plants
}

int Carnivore::getDefence() const
{
    return this->defence;
}

bool Carnivore::isAdult() const
{
    return Animal::isAdult() && this->attack == this->maxAttack && this->defence == this->maxDefence;
}

void Carnivore::resetHunger()
{
    Animal::resetHunger();
    this->isHungry = true;
}

void Carnivore::printTotal()
{
    std::cout << "\tCarnivores:" << total << std::endl;
}

int Fox::total = 0;

Fox::Fox(std::string name, bool adult) : Carnivore(name,"Fox",adult ? 4 : 1,4,adult ? 6 : 1,6, false,adult ? 5 : 1,adult ? 5 : 1,5,5,adult ? 6 : 2,6) { total++; }

bool Fox::Move(Direction direction, char tile)
{
    return Animal::Move(direction,tile);
}

bool Fox::Eat(Animal *animal)
{
    switch (animal->getToken())
    {
        case 'H':
            if (animal->getSpecies() != "Salmon")//Fox cannot eat salmon
                return false;
            if(animal->getSize() <= this->size && animal->getSpeed() < this->speed)
                return Carnivore::Eat(animal);
            else
                return false;
        case 'C':
            if(animal->getSize() < this->size || (animal->getSize() == this->size && this->attack > ((Carnivore*)(animal))->getDefence()))
                return Carnivore::Eat(animal);
            else
                return false;
        default:
            break;
    }
    return false;
}

void Fox::Raise()
{
    if (this->size < this->maxSize)
        this->size++;
    if (this->attack < this->maxAttack)
        this->attack++;
    if (this->defence < this->maxDefence)
        this->defence++;
    if (this->speed < this->maxSpeed)
        this->speed++;
    if (this->neededFood < this->maxNeededFood)
        this->neededFood++;
}

bool Fox::canLiveHere(char tile) const
{
    return tile == '"';
}

Animal* Fox::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Fox(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Fox::printTotal()
{
    std::cout << "\t\tFoxes:" << total << std::endl;
}

int Wolf::total = 0;

Wolf::Wolf(std::string name, bool adult) : Carnivore(name,"Wolf",adult ? 7 : 1,7,adult ? 8 : 2,8, false,adult ? 8 : 2,adult ? 6 : 2,8,6,adult ? 8 : 2,8) { total++; }

bool Wolf::Move(Direction direction, char tile)
{
    return Animal::Move(direction,tile);
}

bool Wolf::Eat(Animal *animal)
{
    switch (animal->getToken())
    {
        case 'H':
            if (animal->getSpecies() != "Salmon")//Wolf cannot eat salmon
                return false;
            if(animal->getSize() <= this->size && animal->getSpeed() < this->speed)
                return Carnivore::Eat(animal);
            else
                return false;
        case 'C':
            if(animal->getSize() < this->size || (animal->getSize() == this->size && this->attack > ((Carnivore*)animal)->getDefence()))
                return Carnivore::Eat(animal);
            else
                return false;
        default:
            break;
    }
    return false;
}

void Wolf::Raise()
{
    if (this->size < this->maxSize)
        this->size++;
    if (this->attack + 2 <= this->maxAttack)
        this->attack+=2;
    if (this->defence + 2 <= this->maxDefence)
        this->defence+=2;
    if (this->speed + 2 <= this->maxSpeed)
        this->speed+=2;
    if (this->neededFood + 2 <= this->maxNeededFood)
        this->neededFood+=2;
}

bool Wolf::canLiveHere(char tile) const
{
    return tile != '#';
}

Animal* Wolf::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Wolf(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Wolf::printTotal()
{
    std::cout << "\t\tWolves:" << total << std::endl;
}

int Bear::total = 0;

Bear::Bear(std::string name, bool adult) : Carnivore(name,"Bear",adult ? 10 : 3,10,4,4, true,adult ? 10 : 6,adult ? 10 : 6,10,10,adult ? 10 : 5,10) { total++; }

bool Bear::Move(Direction direction, char tile)
{
    return Animal::Move(direction,tile);
}

bool Bear::Eat(Animal *animal)
{
    if (animal->getSpecies() != "Bear")//Bear cannot eat other bears
        return Carnivore::Eat(animal);
    else
        return false;
}

void Bear::Raise()
{
    if (this->size + 2 <= this->maxSize)
        this->size++;
    if (this->attack + 2 <= this->maxAttack)
        this->attack+=2;
    if (this->defence + 2 <= this->maxDefence)
        this->defence+=2;
    if (this->neededFood + 2 <= this->maxNeededFood)
        this->neededFood+=2;
}

bool Bear::canLiveHere(char tile) const
{
    return tile == '^';
}

Animal* Bear::Breed()
{
    Animal *child;
    if (this->isAdult()) {
        child = new Bear(this->name + "'s child", false);
        child->setPos(this->x,this->y);
        child->setHome(this->token);
    } else {
        child = NULL;
    }
    return child;
}

void Bear::printTotal()
{
    std::cout << "\t\tBears:" << total << std::endl;
}