#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity {
protected:
    std::string name;
    std::string species;
    int size;
    int x;
    int y;
    char token;
public:
    Entity(std::string,std::string,int ,int, int, char);
    std::string getSpecies() const;
    int getSize() const;
    int getX() const;
    int getY() const;
    char getToken() const;
    void setPos(int, int);
    virtual void printInfo() const = 0;
};

#endif
