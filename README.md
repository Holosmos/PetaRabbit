# PetaRabbit

Pour compiler :

## sous Linux : 
Installer openMP (openmp pour archlinux, libomp-dev ou sous debian et dérivés)

``cmake .`` puis ```make -j4```

## sous OS X :
Pour installer openMP: voir [ici](https://stackoverflow.com/questions/35134681/installing-openmp-on-mac-os-x-10-11#35417448)

``g++ -c *.cpp -std=c++11 -fopenmp`` puis ``g++ *.o -o petarabbit -lsfml-graphics -lsfml-window -lsfml-system -lpthread -fopenmp``
