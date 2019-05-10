#ifndef ANIMALS_H
#define ANIMALS_H

#include "Entity.h"
#include "Plants.h"

enum Direction{UP,DOWN,RIGHT,LEFT,NONE};

class Animal : public Entity {
private:
    Direction prevDir;
    int moveTries;
    static int total;
protected:
    int maxSize;
    int hungerCount;
    int eatenFood;
    int eatCount;
    bool _isAlive;
    bool isHungry;
    bool _inHeat;
    int speed;
    int maxSpeed;
    bool hibernates;
    bool _inHibernation;
    int neededFood;//All animals have the neededFood property
    int maxNeededFood;
    int startX;
    int startY;
    char currentTile;
public:
    Animal(std::string,std::string,char,int, int, int, int, int, bool, int, int);
    virtual ~Animal() { total--; };
    virtual bool Move(Direction, char) = 0;
    virtual bool Eat(Plant*) = 0;
    virtual bool Eat(Animal*) = 0;
    virtual void Raise() = 0;
    virtual bool canLiveHere(char) const = 0;
    virtual Animal *Breed() = 0;
    int getSpeed() const;
    bool isAlive() const;
    bool hungry() const;
    bool inHibernation() const;
    bool inHeat() const;
    virtual bool isAdult() const;
    void Die();
    void setHome(char);
    void setHeat(bool);
    void hibernate();
    void wakeUp();
    void CheckHunger();
    virtual void resetHunger() = 0;
    void printInfo() const;
    static void printTotal();
};

class Herbivore : public Animal {
private:
    static int total;
protected:
    bool canClimb;
public:
    Herbivore(std::string,std::string, int, int, int, int, int ,bool ,bool ,int, int);
    ~Herbivore() { total--; };
    virtual bool Eat(Plant*) = 0;
    virtual bool Eat(Animal*);
    void resetHunger();
    static void printTotal();
};

class Deer : public Herbivore {
private:
    static int total;
public:
    Deer(std::string, bool);
    ~Deer() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Plant*);
    bool canLiveHere(char) const ;
    Animal *Breed();
    static void printTotal();
};

class Rabbit : public Herbivore {
private:
    static int total;
public:
    Rabbit(std::string, bool);
    ~Rabbit() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Plant*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

class Groundhog : public Herbivore {
private:
    static int total;
public:
    Groundhog(std::string, bool);
    ~Groundhog() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Plant*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

class Salmon : public Herbivore {
private:
    static int total;
public:
    explicit Salmon(std::string);
    ~Salmon() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Plant*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

class Carnivore : public Animal {
private:
    static int total;
protected:
    int attack;
    int defence;
    int maxAttack;
    int maxDefence;
public:
    Carnivore(std::string,std::string, int, int, int, int ,bool, int, int, int, int, int, int);
    ~Carnivore() { total--; };
    virtual bool Eat(Animal*) = 0;
    virtual bool Eat(Plant*);
    bool isAdult() const;
    int getDefence() const;
    void resetHunger();
    static void printTotal();
};

class Fox : public Carnivore {
private:
    static int total;
public:
    Fox(std::string, bool);
    ~Fox() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Animal*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

class Wolf : public Carnivore {
private:
    static int total;
public:
    Wolf(std::string, bool);
    ~Wolf() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Animal*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

class Bear : public Carnivore {
private:
    static int total;
public:
    Bear(std::string, bool);
    ~Bear() { total--; };
    bool Move(Direction, char);
    void Raise();
    bool Eat(Animal*);
    bool canLiveHere(char) const;
    Animal *Breed();
    static void printTotal();
};

#endif
