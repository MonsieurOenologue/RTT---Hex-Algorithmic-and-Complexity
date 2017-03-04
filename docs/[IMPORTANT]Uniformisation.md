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
Pas de documentation au niveau du code source (pour le moment du moins) afin d'éviter l'explosion de HTML sur le repo git.

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

### Documenter les méthodes

Pensez à écrire la documentation d'une méthode avant ou juste après l'avoir écrite, documentez les problèmes et erreurs également.

#### Exemple de documentation de méthode

```
/**
 *  @brief sum of param a and b giving a result c (basically just a sum of two integer)
 *  @param a
 *  @param b
 *  @return c
 *
 *\
 function (int a, int b) {
     c = a + b;
     return c;
 }
```

## Pour plus de détails

- [Documentation de Doxygen - Documenting the code](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html)
- [Documentation de Doxygen - Special Commands](http://www.stack.nl/~dimitri/doxygen/manual/commands.html)
