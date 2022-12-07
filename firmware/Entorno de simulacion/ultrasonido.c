#include <stdio.h>
#include "main.h"
#include "map.c"
#include <stdbool.h>
float getDistanceFront(USdistances *measurement);
float getDistanceBack(USdistances *measurement);
float getDistanceLeft(USdistances *measurement);
float getDistanceRight(USdistances *measurement);
void mapFront(int measure, int currentX, int currentY);
void mapBack(int measure, int currentX, int currentY);
void mapRigth(int measure, int currentX, int currentY);
void mapLeft(int measure, int currentX, int currentY);
void Map_From_currentPoint(int currentX, int currentY, float incertidumbre);
float secureReading(direction myDir, float inc);
bool igualdad(float v1, float v2, float v3, float inc);

float getDistanceFront(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USfront > 200) // distance where we don't rely on the measurement
    {
        measurement->USfront = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USfront; // function in zephyr, here is a function in the sim.
}

float getDistanceBack(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USback > 200) // distance where we don't rely on the measurement
    {
        measurement->USback = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USback;
}

float getDistanceLeft(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USleft > 200) // distance where we don't rely on the measurement
    {
        measurement->USleft = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USleft;
}

float getDistanceRight(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USright > 200) // distance where we don't rely on the measurement
    {
        measurement->USright = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USright;
}

void getAll(USdistances *measurement)
{
    measurement->USback = getDistanceBack(measurement);
    measurement->USfront = getDistanceFront(measurement);
    measurement->USleft = getDistanceLeft(measurement);
    measurement->USright = getDistanceRight(measurement);
}

void Map_From_currentPoint(int currentX, int currentY, float incertidumbre)
{
    int M_R, M_L, M_F, M_B;
    M_R = roundf(secureReading(RIGHT, incertidumbre) / stepGrid);
    M_L = roundf(secureReading(LEFT, incertidumbre) / stepGrid);

    if (CurrentDirectionMovement == FRONT)
    {
        if (Wall_to_allign == LEFT)
        {
            mapRigth(M_R, currentX, currentY);
        }
        else
        {
            mapRigth(M_L, currentX, currentY);
        }
    }
    else if (CurrentDirectionMovement == BACK)
    {
        if (Wall_to_allign == LEFT)
        {
            mapLeft(M_R, currentX, currentY);
        }
        else
        {
            mapLeft(M_L, currentX, currentY);
        }
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        if (Wall_to_allign == LEFT)
        {
            mapBack(M_R, currentX, currentY);
        }
        else
        {
            mapBack(M_L, currentX, currentY);
        }
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        if (Wall_to_allign == LEFT)
        {
            mapFront(M_R, currentX, currentY);
        }
        else
        {
            mapFront(M_L, currentX, currentY);
        }
    }
}

float secureReading(direction myDir, float inc)
{ // 3 mediciones para asegurarse que el valor medido tiene sentido
    float medicion1, medicion2, medicion3, result;
    while (1)
        if (myDir == FRONT)
        {
            medicion1 = getDistanceFront(&measurement1);
            medicion2 = getDistanceFront(&measurement1);
            medicion3 = getDistanceFront(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == BACK)
        {
            medicion1 = getDistanceBack(&measurement1);
            medicion2 = getDistanceBack(&measurement1);
            medicion3 = getDistanceBack(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == RIGHT)
        {
            medicion1 = getDistanceRight(&measurement1);
            medicion2 = getDistanceRight(&measurement1);
            medicion3 = getDistanceRight(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == LEFT)
        {
            medicion1 = getDistanceLeft(&measurement1);
            medicion2 = getDistanceLeft(&measurement1);
            medicion3 = getDistanceLeft(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }

    return result;
}

bool igualdad(float v1, float v2, float v3, float inc)
{
    if ((v1 > (v2 - inc)) && (v1 > (v2 - inc)) && (v1 > (v3 - inc)) && (v1 > (v3 - inc)))
        return true;
    else
        return false;
}

void mapFront(int measure, int currentX, int currentY)
{
    int i;
    if (measure < mapHeight / 2)
    {
        Grid[currentX][currentY + measure].obstacle = true;
        for (i = currentY; i < (currentY + measure); i++)
        {
            Grid[currentX][i].obstacle = false;
        }
       // printGrid(Grid);
    }
    else
    {
    /*     for (i = currentY; i <= mapHeight / 2; i++) // mapear solo la mitad
        {
            Grid[currentX][i].obstacle = false;
        } */
    }
}
void mapBack(int measure, int currentX, int currentY)
{
    int i;
    if (measure < mapHeight / 2)
    {
        Grid[currentX][currentY - measure-5].obstacle = true;
        for (i = currentY; i > (currentY - measure); i--)
        {
            Grid[currentX][i].obstacle = false;
        }
       // printGrid(Grid);
    }
    else
    {
/*         for (i = currentY; i >= (currentY - mapHeight / 2); i--) // mapear solo la mitad
        {
            Grid[currentX][i].obstacle = false;
        } */
    }
}
void mapRigth(int measure, int currentX, int currentY)
{
    int i;
    if (measure < mapWidth / 2)
    {
        Grid[currentX + measure+7][currentY].obstacle = true;
        for (i = currentX; i < (currentX + measure); i++)
        {
            Grid[i][currentY].obstacle = false;
        }
       // printGrid(Grid);
    }
    else
    {
/*         for (i = currentX; i <= mapWidth / 2; i++) // mapear solo la mitad
        {
            Grid[i][currentY].obstacle = false;
        } */
    }
}
void mapLeft(int measure, int currentX, int currentY)
{
    int i;
    if (measure < mapWidth / 2)
    {
        Grid[currentX - measure][currentY].obstacle = true;
        for (i = currentX; i > (currentX - measure); i--)
        {
            Grid[i][currentY].obstacle = false;
        }
       // printGrid(Grid);
    }
    else
    {
  /*       for (i = currentX; i >= (currentX - mapWidth / 2); i--) // mapear solo la mitad
        {
            Grid[i][currentY].obstacle = false;
        } */
    }
}
