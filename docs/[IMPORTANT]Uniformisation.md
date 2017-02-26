# Document pour l'uniformisation du code et de la documentation

Ce document est une référence à suivre pour l'uniformisation du code et de la
documentation du projet, des ajouts et changements sont possibles après
discussion entre membres du groupe.

## Règles de base

- 1 tabulation = 4 espaces
- Sauter une ligne entre chaque fonction (méthode)
- Un espace entre chaque opérateur (1 + 1 = 2)
- N'oubliez pas de déclarer variables, fonctions et biblios dans les headers avant utlisation dans le code source

## Positionnement des accolades

```
doSomething() {

}
```

## Template pour la documentation

On utilise Doxygen pour générer la documentation (voir (http://www.doxygen.org)).

### Exemple de documentation au début d'un fichier 

```
/**
 *  @file    MinMax.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief here goes the brief description of the file
 *
 *  @section DESCRIPTION
 *  blablablablablablablabalabla
 *  blablablablablablablabalabla
 *\
```

### Exemple de documentation avant une méthode
