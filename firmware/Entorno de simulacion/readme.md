

-Se busco **separar** el codigo que va en zephyr del mapa de simulación. De este modo solo se requiere exportar las funciones en C. 

-En lo único que interactua el mapa y el codigo del robot es en la medición del ultrasonido, de este modo se logra un entorno de pruebas útil.

-El robot busca en una esquina y comienza a mapear rodeando el mapa. Como se ve al final de la ejecución el robot guarda en memoria el obstaculo. El paso que sigue solo es recoger el objeto identificado.

-Se busco considerar aspectos **realistas**, como que midiera 3 veces el ultra sonido para estar seguro de la medición, también, en cada punto de la grilla que se mapee el robot  haga un control vertical y horizontal de posición

![Mi-proyecto-1-2022-12-07_07-36-17](https://user-images.githubusercontent.com/70418457/206181681-c0cd7033-9c84-4bce-8a5c-5327af41197f.gif)
