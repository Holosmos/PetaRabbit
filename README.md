# PetaRabbit

PetaRabbit utilise OpenMP et la SFML, veuillez les installer sur votre machine.

Pour installer openMP sous Mac OS, [voir ici](https://stackoverflow.com/questions/35134681/installing-openmp-on-mac-os-x-10-11#35417448).

Sous linux, installer le paquet openmp pour archlinux, libomp-dev ou sous
debian et dérivés.

## Compilation hors source avec CMake

    mkdir build
    cd build
    cmake ..
    make -j4

## Compilation sans CMake

    g++ -c *.cpp -std=c++11 -fopenmp
    g++ *.o -o petarabbit -lsfml-graphics -lsfml-window -lsfml-system -lpthread -fopenmp
