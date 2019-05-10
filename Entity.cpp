#include <iostream>
#include "Entity.h"

Entity::Entity(std::string name,std::string species,int size, int x, int y, char token) : name(name),species(species),size(size),x(x),y(y),token(token) {};

std::string Entity::getSpecies() const
{
    return this->species;
}

int Entity::getSize() const
{
    return this->size;
}

int Entity::getX() const
{
    return this->x;
}

int Entity::getY() const
{
    return this->y;
}

char Entity::getToken() const
{
    return this->token;
}

void Entity::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Entity::printInfo() const
{
    std::cout << '\t' << "Name:" << this->name << std::endl;
    std::cout << '\t' << "Species:" << this->species << std::endl;
    std::cout << '\t' << "Size:" << this->size << std::endl;
    std::cout << '\t' << "Position:" << '(' << this->x << ',' << this->y << ')' << std::endl;
    std::cout << '\t' << "Token:" << this->token << std::endl;
}