#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"

class Plant : public Entity {
private:
    static int total;
protected:
    int life;
    int lifeFactor;
    double breedingProb;
    double illnessProb;
public:
    Plant(std::string,std::string, int ,int ,int ,char ,int, int, double , double);
    virtual ~Plant() { total--; };
    virtual void LoseLife(int amount) = 0;
    virtual void Raise() = 0;
    virtual Plant *Breed(char) = 0;
    virtual bool canGrowHere(char) = 0;
    virtual bool canBreedHere(char) = 0;
    bool isAlive() const;
    virtual void printInfo() const;
    static void printTotal();
};

class Seedless : public Plant {
private:
    static int total;
public:
    Seedless(std::string,std::string,int ,int ,char ,int, int, double , double);
    ~Seedless() { total--; };
    void LoseLife(int);
    void Raise();
    static void printTotal();
};

class Grass : public Seedless {
private:
    static int total;
public:
    explicit Grass(std::string);
    ~Grass() { total--; };
    static bool enoughSpace(int, int);
    bool canGrowHere(char);
    bool canBreedHere(char);
    Plant *Breed(char);
    static void printTotal();
};

class Algae : public Seedless {
private:
    static int total;
public:
    explicit Algae(std::string);
    ~Algae() { total--; };
    static bool enoughSpace(int, int);
    bool canGrowHere(char);
    bool canBreedHere(char);
    Plant *Breed(char);
    static void printTotal();
};

class Seeded : public Plant {
private:
    static int total;
protected:
    int foliage;
    int seeds;
public:
    Seeded(std::string,std::string,int ,int ,char ,int, int, double , double, int, int, int);
    ~Seeded() { total--; };
    void LoseLife(int);
    void Raise();
    void printInfo() const;
    static void printTotal();
};

class Maple : public Seeded {
private:
    static int total;
public:
    explicit Maple(std::string);
    ~Maple() { total--; };
    static bool enoughSpace(int, int, int);
    bool canGrowHere(char);
    bool canBreedHere(char);
    Plant *Breed(char);
    static void printTotal();
};

class Oak : public Seeded {
private:
    static int total;
public:
    explicit Oak(std::string);
    ~Oak() { total--; };
    static bool enoughSpace(int, int);
    bool canGrowHere(char);
    bool canBreedHere(char);
    Plant *Breed(char);
    static void printTotal();
};

class Pine : public Seeded {
private:
    static int total;
public:
    explicit Pine(std::string);
    ~Pine() { total--; };
    static bool enoughSpace(int, int);
    bool canGrowHere(char);
    bool canBreedHere(char);
    Plant *Breed(char);
    static void printTotal();
};

#endif
