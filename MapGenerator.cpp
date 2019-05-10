#include <cstdlib>
#include "MapGenerator.h"


MapGenerator::MapGenerator(Ecosystem* ecosystem)
{
    this->ecosystem = ecosystem;
}

void MapGenerator::ResetMap()
{
    //Resets all the tiles and places the empty token on them.
    for (int i = 0; i < this->ecosystem->terrainSize; ++i) {
        for (int j = 0; j < this->ecosystem->terrainSize; ++j) {
            this->ecosystem->terrain[i][j].token = '.';
            this->ecosystem->terrain[i][j].plant = NULL;
        }
    }
}

void MapGenerator::placeWater(int x, int y)
{
    ecosystem->terrain[x][y].token = '#';
    ecosystem->availableWater++;
    ecosystem->availableMeadow--;
}

void MapGenerator::GenerateRiver()
{
    int start = rand() % (ecosystem->terrainSize - 9) + 4;
    for (int i = 0; i < ecosystem->terrainSize; ++i) {
        double outcome = (double)rand()/(double)RAND_MAX;
        if (outcome <= 0.3)//River Diverges
        {
            int direction = rand() % 4 + 1;
            switch (direction)
            {
                case 1://1 tile right
                    if(start < ecosystem->terrainSize - 1)
                    {
                        if(i > 0)
                            placeWater(i-1,++start);
                        else
                            start++;
                        placeWater(i,start);
                    }
                    else
                        placeWater(i,start);
                    break;
                case 2://1 tile left
                    if(start > 0)
                    {
                        if(i > 0)
                            placeWater(i-1,--start);
                        else
                            start--;
                        placeWater(i,start);
                    }
                    else
                        placeWater(i,start);
                    break;
                case 3://2 tiles right;
                    if(start < ecosystem->terrainSize - 2)
                    {
                        if(i > 0)
                        {
                            placeWater(i-1,++start);
                            placeWater(i-1,++start);
                        }
                        else
                            start+=2;
                        placeWater(i,start);
                    }
                    else
                        placeWater(i,start);
                    break;
                case 4://2 tiles left
                    if(start > 1)
                    {
                        if(i > 0)
                        {
                            placeWater(i-1,--start);
                            placeWater(i-1,--start);
                        }
                        else
                            start-=2;
                        placeWater(i,start);
                    }
                    else
                        placeWater(i,start);
                    break;
                default:
                    break;
            }
        }
        else//Straight forward
            placeWater(i,start);
    }
}

void MapGenerator::GenerateLake(int lakeSize)
{
    int x,y;
    bool ok;
    do
    {
        x = rand() % (this->ecosystem->terrainSize - lakeSize);
        y = rand() % (this->ecosystem->terrainSize - lakeSize);
        //Check if the lake overlaps with the river or any other water
        ok = true;
        for (int i = x; i < x+lakeSize && ok; ++i) {
            for (int j = y; j < y+lakeSize && ok; ++j) {
                if(this->ecosystem->terrain[j][i].token == '#')
                    ok = false;
            }
        }
    } while (!ok);//Loop until we find an area for the lake that does not overlap any water
    for (int i = x; i < x+lakeSize; ++i) {
        for (int j = y; j < y+lakeSize; ++j) {
            placeWater(j,i);
        }
    }
}

void MapGenerator::placeHill(int x, int y)
{
    this->ecosystem->terrain[x][y].token = '^';
    this->ecosystem->availableHills++;
    this->ecosystem->availableMeadow--;
}

void MapGenerator::GenerateHills(int hills)
{
    int x,y,hillSize;
    bool ok;
    for (int k = 0; k < hills; ++k) {
        hillSize = rand() % 3 + 2;
        do
        {
            x = rand() % (this->ecosystem->terrainSize - hillSize);
            y = rand() % (this->ecosystem->terrainSize - hillSize);
            //Check if hills overlap water or other hills
            ok = true;
            for (int i = x; i < x+hillSize && ok; ++i) {
                for (int j = y; j < y+hillSize && ok; ++j) {
                    if(this->ecosystem->terrain[j][i].token == '#' || this->ecosystem->terrain[j][i].token == '^')
                        ok = false;
                }
            }
        } while (!ok);//Loop until we find an area for the hills that does not overlap any water or other hills
        for (int i = x; i < x+hillSize; ++i) {
            for (int j = y; j < y+hillSize; ++j) {
                placeHill(j,i);
            }
        }
    }
}

void MapGenerator::GenerateMeadow()
{
    //Fills the tiles that do not contain any water or hills with meadow
    for (int i = 0; i < this->ecosystem->terrainSize; ++i) {
        for (int j = 0; j < this->ecosystem->terrainSize; ++j) {
            if (this->ecosystem->terrain[i][j].token == '.')
                this->ecosystem->terrain[i][j].token = '"';
        }
    }
}