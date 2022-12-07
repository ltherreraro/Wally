#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <stdbool.h>
#include "ultrasonido.c"

bool controlDistance(direction relativeDir, float referenceDistance, float incertidumbre);
bool controlV_position(int currentX, int currentY, float incertidumbre);
bool controlH_position(int currentX, int currentY, float incertidumbre);
void moveAheadGrid();
bool controlDistance(direction relativeDir, float referenceDistance, float incertidumbre)
{
    bool controlDoneFlag = false;
    float measured_Distance;
    if (relativeDir == RIGHT)
    {
        measured_Distance = getDistanceRight(&measurement1);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
            turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    if (relativeDir == LEFT)
    {

        measured_Distance = getDistanceLeft(&measurement1);
        // DebugPrint2("leftDistance",0,measured_Distance);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    return controlDoneFlag;
}

// la referencia es la que se guarda en el mapeo.

bool controlH_position(int currentX, int currentY, float incertidumbre)
{

    bool controlDoneFlag = false;
    int referenceDistance;

    // dependiendo de la dirección se basa en una u otra posición absoluta
    if (CurrentDirectionMovement == FRONT || CurrentDirectionMovement == BACK)
    {
        // Aquí se observa si está más cerca las referencias de grilla normales o invertidas, para saber con cual dis hacer control
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx;
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
        }
    }
    else if (CurrentDirectionMovement == RIGHT || CurrentDirectionMovement == LEFT)
    {
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
        }
    }

    float measured_Distance;

    if (Wall_to_allign == LEFT)
    {
        measured_Distance = getDistanceLeft(&measurement1);

        // DebugPrint("Reference, measured", referenceDistance, measured_Distance);
        // DebugPrint("currentMovement",CurrentDirectionMovement,0);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead();     // certain time
                             // turnRight();     // 1grado o algo así.
            moveBackwards(); // certain time
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            // turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    if (Wall_to_allign == RIGHT)
    {

        measured_Distance = getDistanceRight(&measurement1);
        /* DebugPrint("measuredDistance: ", 0, measured_Distance);
         DebugPrint2("referenceDistance: ", 0, referenceDistance); */
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
                         // turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            // turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    return controlDoneFlag;
}

bool controlV_position(int currentX, int currentY, float incertidumbre)
{
    bool controlDoneFlag = false;
    int referenceDistance;
    float measured_Distance;

    // dependiendo de la dirección se basa en una u otra posición absoluta
    if (CurrentDirectionMovement == FRONT)
    {
        // Aquí se observa si está más cerca las referencias de grilla normales o invertidas, para saber con cual dis hacer control
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                // DebugPrint2("Done,measured", controlDoneFlag, measured_Distance);
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceBack(&measurement1) < (referenceDistance - incertidumbre))
                {
                    // DebugPrint2("referenceV,measured", referenceDistance, measured_Distance);
                    moveAhead();
                }
                controlDoneFlag = false;
            }
            else if (getDistanceBack(&measurement1) > (referenceDistance + incertidumbre))
            {
                while (measured_Distance > (referenceDistance + incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                // DebugPrint2("Done,measured", controlDoneFlag, measured_Distance);
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceFront(&measurement1) < (referenceDistance - incertidumbre))
                {
                    // DebugPrint2("referenceV,measured", referenceDistance, measured_Distance);
                    moveAhead();
                    moveBackwards();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceFront(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == BACK)
    {
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceFront(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceFront(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceBack(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceBack(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceBack(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceBack(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceFront(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceFront(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceFront(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceFront(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
            measured_Distance = getDistanceBack(&measurement1);
            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                while (getDistanceBack(&measurement1) < (referenceDistance - incertidumbre))
                {
                    moveAhead();
                }
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                while (getDistanceBack(&measurement1) > (referenceDistance + incertidumbre))
                {
                    moveBackwards();
                }
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    // DebugPrint4("Done vertical control", 0, controlDoneFlag);
    return controlDoneFlag;
}

void turnEvaluation(int currentX, int currentY)
{
    if ((Grid[currentX + SafeDistance / stepGrid][currentY].obstacle == true && CurrentDirectionMovement == RIGHT) || (Grid[currentX - SafeDistance / stepGrid][currentY].obstacle == true) && CurrentDirectionMovement == LEFT || (Grid[currentX][currentY + SafeDistance / stepGrid].obstacle == true) && CurrentDirectionMovement == FRONT || (Grid[currentX][currentY - SafeDistance / stepGrid].obstacle == true) && CurrentDirectionMovement == BACK)
    {
        
        if (Wall_to_allign == LEFT)
        {   
            // DebugPrint4("gire", 0, 0);
            turnRight();
        }
        else
        {
            turnLeft();
        }
    }
}

void moveAhead()
{
    // just turn motors on
    moveAheadSimulation();
}

void moveAheadGrid()
{
    // move ahead in the grid.

    if (SimCurrentDirectionMovement == FRONT)
    {
        if (!Grid[currentPointX][currentPointY + SafeDistance / stepGrid].obstacle)
        {
            currentPointY++;
        }
    }
    else if (SimCurrentDirectionMovement == BACK)
    {
        if (!Grid[currentPointX][currentPointY - SafeDistance / stepGrid].obstacle)
        {
            currentPointY--;
        }
    }
    else if (SimCurrentDirectionMovement == LEFT)
    {
        if (!Grid[currentPointX - SafeDistance / stepGrid][currentPointY].obstacle)
        {
            currentPointX--;
        }
    }
    else if (SimCurrentDirectionMovement == RIGHT)
    {
        if (!Grid[currentPointX + SafeDistance / stepGrid][currentPointY].obstacle)
        {
            currentPointX++;
        }
    }
}

void moveBackwards()
{
    moveBackwardsSimulation();
}

void moveBackwardsGrid()
{
}

void stop()
{
    stopSimualtion();
}

void turnBack()
{

    // aquí es necesario actualizar la dirección actual
    // mensaje de confirmación cuando no haya simulación
    turnBackSimulation();

    if (startPointFlag) // solo si se está moviendo en la grid actualizar direcciones
    {
        if (CurrentDirectionMovement == FRONT)
        {
            CurrentDirectionMovement = BACK;
        }
        else if (CurrentDirectionMovement == BACK)
        {
            CurrentDirectionMovement = FRONT;
        }
        else if (CurrentDirectionMovement == LEFT)
        {
            CurrentDirectionMovement = LEFT;
        }
        else if (CurrentDirectionMovement == RIGHT)
        {
            CurrentDirectionMovement = RIGHT;
        }
    }
}

void turnLeft()
{

    turnLeftSimulation();

    if (startPointFlag) // solo si se está moviendo en la grid actualizar direcciones
    {
        if (CurrentDirectionMovement == FRONT)
        {
            CurrentDirectionMovement = LEFT;
        }
        else if (CurrentDirectionMovement == BACK)
        {
            CurrentDirectionMovement = RIGHT;
        }
        else if (CurrentDirectionMovement == LEFT)
        {
            CurrentDirectionMovement = BACK;
        }
        else if (CurrentDirectionMovement == RIGHT)
        {
            CurrentDirectionMovement = FRONT;
        }
    }
}

void turnRight()
{

    turnRightSimulation();
    if (startPointFlag) // solo si se está moviendo en la grid actualizar direcciones
    {
        if (CurrentDirectionMovement == FRONT)
        {
            CurrentDirectionMovement = RIGHT;
        }
        else if (CurrentDirectionMovement == BACK)
        {
            CurrentDirectionMovement = LEFT;
        }
        else if (CurrentDirectionMovement == LEFT)
        {
            CurrentDirectionMovement = FRONT;
        }
        else if (CurrentDirectionMovement == RIGHT)
        {
            CurrentDirectionMovement = BACK;
        }
    }
}
