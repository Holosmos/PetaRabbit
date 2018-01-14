# PetaRabbit

Pour compiler :

## sous Linux : 
Installer openMP (openmp pour archlinux, libomp-dev ou sous debian et dérivés)

``cmake .`` puis ```make -j4```

## sous OS X :
Pour installer openMP: voir [ici](https://stackoverflow.com/questions/35134681/installing-openmp-on-mac-os-x-10-11#35417448)

``g++ -c *.cpp -std=c++11 -fopenmp`` puis ``g++ *.o -o petarabbit -lpthread -fopenmp``


# Pour activer le service web

Se placer dans le dosser "webservice" et lancer `FLASK_APP=./main.py flask run`.

La page web est sur 127.0.0.1:5000.

Pour nettoyer le cache : supprimer le sous-dossier cache et ne pas oublier de vider le cache du navigateur
