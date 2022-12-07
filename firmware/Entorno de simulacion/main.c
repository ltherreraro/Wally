#include <stdio.h>

#include <stdlib.h>

#include "movement.c"
#include "main.h"

// cambiar a uint8_t

// Incertidumbres
float incertidumbre_control = 1;
float incertidumbre_ajuste = 0.1;
float incertidumbre_medicion = 0.5;

// variables para mapeo y movimiento

// Separacion de cada punto en la grid

// auxiliares
int NearestPlace1;
SafeDistance = 6;
stepGrid = 2;
void init();
void Map_around();
void fillGrid(int tamx, int tamy);

// aqui va a estar el "cerebro"
int main()
{

    currentPointX = SafeDistance / stepGrid;
    currentPointY = SafeDistance / stepGrid;

    // Para el mapeo
    mapping();
    DebugPrint("All fine", 0, 0);
    // llena el mapa

    // 1.init: Distancias iniciales y acercarse a la pared más cercana
    init();
    /* 2.edgeSearching: Al acercarse a la pared más cercana, considera las distancias
    perpendiculares, y se va a la más cercana. En este momento se debe buscar estar
    paralelo a la pared, luego a cada movimiento hacia adelante se hará
    una corrección de distancia para siempre mantenerse al margen */
    edgeSearching();
    startPointFlag = true; // para que el robot se mueva en la grid

    /* 3.Map walls*/
    Map_walls();
    /* 4.initialMapping(), va llenar un arreglo de 100*100 .............................................................................. v
     */
    Map_around();
    printGrid(Grid);
    return 0;
}

void init()
{
    getAll(&measurement1);
    NearestPlace1 = nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright);

    if (NearestPlace1 == FRONT)
    {
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == BACK)
    {
        turnBack();
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == RIGHT)
    {
        turnRight();
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));

            moveAhead();
        }
    }
    else if (NearestPlace1 == LEFT)
    {
        turnLeft();
        DebugPrint("safeDistance, DFRONT", SafeDistance, getDistanceFront(&measurement1));
        while (getDistanceFront(&measurement1) > SafeDistance)
        {

            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == EQUAL)
    { // significará que son iguales las distancias
        moveAhead();
        init();
    }
    else
    {
        /*NearestPLACE1 == NONVALID
        (todas las distancias son asignadas con 10k),
        que es el valor que se escogió para asignar un error en la medición, o una distancia muy grande .*/
        moveAhead();
        init();
    }
}

void edgeSearching()
{
    NearestPlace1 = nearest(10000, 10000, getDistanceLeft(&measurement1), getDistanceRight(&measurement1));
    if (NearestPlace1 == LEFT)
    {
        turnLeft();
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            bool ctrlDistance = controlDistance(RIGHT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {

                ctrlDistance = controlDistance(RIGHT, SafeDistance, incertidumbre_control);
            }

            moveAhead();
        }
        turnLeft();
        DebugPrint("Left turn: Distance left:", 0, getDistanceLeft(&measurement1));
        Wall_to_allign = RIGHT;
    }
    else if (NearestPlace1 == RIGHT)
    {
        turnRight();
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            bool ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {
                ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);

            } // función para que siempre se mantenga paralelo a la pared.

            moveAhead();
        }
        turnRight();
        DebugPrint("Right turn: Distance LEFT:", 0, getDistanceLeft(&measurement1));
        Wall_to_allign = LEFT;
    }
    else if (NearestPlace1 == EQUAL)
    { // significará que son iguales las distancias
        turnRight();
        while (getDistanceFront(&measurement1) > SafeDistance)
        {
            bool ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {
                ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            } // función para que siempre se mantenga paralelo a la pared.
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else
    { // NON valid
        turnRight();
        moveAhead();
        init();
    }
}
void Map_walls()
{
    int topW = roundf(secureReading(FRONT, 0.5) / stepGrid);
    int leftW = roundf(secureReading(LEFT, 0.5) / 2);
    int backW = roundf(secureReading(BACK, 0.5) / stepGrid);
    int rightW = roundf(secureReading(RIGHT, 0.5) / stepGrid);
    mapHeight = topW + backW;
    mapWidth = leftW + rightW;

    // DebugPrint("topW,secureRead", topW, secureReading(FRONT, 0.5));
    // DebugPrint2("LefW,secureRead", leftW, secureReading(LEFT, 0.5));
    // DebugPrint3("grid init invposx,invposxy", Grid[currentPointX][currentPointY].AbsPosx_inv, Grid[currentPointX][currentPointY].AbsPosy_inv);
    // DebugPrint4("grid init posx,posxy", Grid[currentPointX][currentPointY].AbsPosx, Grid[currentPointX][currentPointY].AbsPosy);
    fillGrid(mapWidth, mapHeight);

    /*     DebugPrint3("grid init invposx,invposxy", Grid[25][30].AbsPosx_inv, Grid[25][30].AbsPosy_inv);
        DebugPrint4("grid init posx,posxy", Grid[25][30].AbsPosx, Grid[25][30].AbsPosy); */
    int i, j;

    if (Wall_to_allign == LEFT)
    {
        // map wall left;
        for (i = 0; i < mapHeight; i++)
        {
            Grid[currentPointX - leftW][i].obstacle = true;
        }
        // map wall right
        for (i = 0; i < mapHeight; i++)
        {
            Grid[currentPointX + rightW][i].obstacle = true;
        }
        // map wall TOP
        for (i = 0; i < mapWidth; i++)
        {
            Grid[i][currentPointX + topW].obstacle = true;
        }
        // map wall BACK
        for (i = 0; i < mapWidth; i++)
        {
            Grid[i][currentPointX - backW].obstacle = true;
        }
    }
    else if (Wall_to_allign == RIGHT) // esto es como hacer un mirror
    {
        // map wall left;
        for (i = 0; i < mapHeight; i++)
        {
            Grid[currentPointX + leftW][i].obstacle = true;
        }
        // map wall right
        for (i = 0; i < mapHeight; i++)
        {
            Grid[currentPointX - rightW][i].obstacle = true;
        }
        // map wall TOP
        for (i = 0; i < mapWidth; i++)
        {
            Grid[i][currentPointX + topW].obstacle = true;
        }
        // map wall BACK
        for (i = 0; i < mapWidth; i++)
        {
            Grid[i][currentPointX - backW].obstacle = true;
        }
    }
}
void Map_around()
{
    /*
    Para moverse alrededor:
    1. Verifica que está en la posición adecauda haciendo el control, primero horizontal y luego V
    2. Luego de estar en la posición adecuada, mapea el punto y sus alrededores.
    3. Gira si necesita girar
    4. se mueve hacia adelante 1 punto en la grilla,  y vuelve a repetir.
    */
    int i = 0;
    bool end_flag = false;
    while (1)
    {
        // DebugPrint3("i", i, 0);
        //   i++;
        //  ;
        DebugPrint3("coordenada x,y", Grid[currentPointX][currentPointY].AbsPosx, Grid[currentPointX][currentPointY].AbsPosy);
        DebugPrint3("coordenada x,y", currentPointX, currentPointY);

        bool ctrlH_position = controlH_position(currentPointX, currentPointY, incertidumbre_ajuste);
        while (!ctrlH_position)
        {
            ctrlH_position = controlH_position(currentPointX, currentPointY, incertidumbre_ajuste);

            // DebugPrint4("encerrado en controlH", 0, 0);
        }
        bool ctrlV_position = controlV_position(currentPointX, currentPointY, incertidumbre_ajuste);
        while (!ctrlV_position)
        {

            ctrlV_position = controlV_position(currentPointX, currentPointY, incertidumbre_ajuste);
            //  DebugPrint4("encerrado en controlV", 0, 0);
        }

        Map_From_currentPoint(currentPointX, currentPointY, incertidumbre_medicion);
        DebugPrint2("SecureFront,SecureBack", secureReading(FRONT, 0.5), secureReading(BACK, 0.5));
        DebugPrint("SecureLEFT,SecureRight", secureReading(LEFT, 0.5), secureReading(RIGHT, 0.5));
        turnEvaluation(currentPointX, currentPointY); // si queda tiempo, es posible evaluar giros más complicados
        moveAheadGrid();
        // DebugPrint4("final", 0, 0);
        if (currentPointX == SafeDistance / stepGrid && currentPointY == SafeDistance / stepGrid)
        {
            break; // volvió al inicio.
        }
    }
    DebugPrint("sali", 0, 0);
}

direction nearest(float front_, float back_, float left_, float right_)
{
    if (front_ == 10000 && back_ == 10000 && left_ == 10000 && right_ == 10000)
    {
        return NONVALID;
    }
    else if (front_ < back_ && front_ < left_ && front_ < right_)
    {
        return FRONT;
    }
    else if (back_ < front_ && back_ < left_ && back_ < right_)
    {
        return BACK;
    }
    else if (left_ < front_ && left_ < right_ && left_ < back_)
    {
        return LEFT;
    }
    else if (right_ < left_ && right_ < front_ && right_ < back_)
    {
        return RIGHT;
    }
    else
    {
        return EQUAL;
    }
}

direction furthest(float front_, float back_, float left_, float right_)
{
    if (front_ > back_ && front_ > left_ && front_ > right_)
    {
        return FRONT;
    }
    else if (back_ > front_ && back_ > left_ && back_ > right_)
    {
        return BACK;
    }
    else if (left_ > front_ && left_ > right_ && left_ > back_)
    {
        return LEFT;
    }
    else if (right_ > left_ && right_ > front_ && right_ > back_)
    {
        return RIGHT;
    }
    else
    {
        return EQUAL; // si hay la misma distancia en dos lugares, ir adelante
    }
}

direction directionOpposite(direction myDir)
{

    if (myDir == LEFT)
        return RIGHT;
    else if (myDir == RIGHT)
        return LEFT;
    else if (myDir == FRONT)
        return BACK;
    else if (myDir == BACK)
        return FRONT;
}
void fillGrid(int tamx, int tamy)
{
    int x, y;
    for (x = 0; x < tamx; x++)
    {
        for (y = 0; y < tamy; y++)
        {
            Grid[x][y].AbsPosy = y * stepGrid;
            Grid[x][y].AbsPosy_inv = tamy * stepGrid - y * stepGrid;

            Grid[x][y].AbsPosx = x * stepGrid;
            Grid[x][y].AbsPosx_inv = tamx * stepGrid - x * stepGrid;

            Grid[x][y].obstacle = false;
        }
    }
    //  DebugPrint2("entre aqui0->", Wall_to_allign, Grid[0][0].obstacle);
}
