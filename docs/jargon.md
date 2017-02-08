# Jargon sur le jeu (combinatoire), Hex, la théorie des jeux combinatoires

## Qu'est-ce qu'un jeu ?

Du latin *jocus*, plaisanterie

"Activité d'ordre physique ou mental, non imposée, ne visant à aucune fin utilitaire, et à laquelle on s'adonne pour se divertir, en tirer un plaisir"

## Différents types de jeux

En 1958, Roger Caillois s'essaye à donner une classification des jeux dans son ouvrage *"Les jeux et les hommes"*


## Qu'est-ce qu'un jeu combinatoire ?

Un jeu selon la théorie des jeux combinatoires possède les propriétés suivantes :
- Deux joueurs appelés **Left**(gauche) et **Right**(droite) jouent alternativement
- Le jeu consiste en un nombre finis de **positions** et il existe une **position de départ**
- Le jeu est à **information complète** (L et R connaissent l'état du jeu)
- Il n'y a aucune intervention du hasard
- La partie se termine lorsqu'un joueur ne peut plus jouer (c'est la **condition de terminaison**)
- Dans la convention normale de jeu, le joueur qui ne peut plus jouer est le perdant.

## Catégorisation des jeux combinatoires

- Jeu **partisan** : Il existe des positions avec des options différentes pour les 2 joueurs

- Jeu **impartial** : Les options disponibles sont toujours les mêmes pour les 2 joueurs.

- Jeu **abstrait** : Au sens de théorique, absence de thème ou thème n'ayant pas d'influence sur les mécanismes du jeu, d'où l'aspect purement théorique

- Jeu de **connexion** : Type de jeu combinatoire dans lequel le but est de compléter une certaine connexion entre les pièces. Dans la plupart des cas, on doit connecter deux côtés opposés du plateau de jeu (Hex) mais il peut également s'agir de compléter une boucle ou de relier toutes les pièces telles qu'elles soient toutes adjacentes entres-elles par exemple.

- Jeu à **somme nulle** : Le gain d'un des joueurs constitue obligatoirement une perte pour l'autre.

- Information **complète** : A partir d'une position donnée, les joueurs peuvent toujours estimer les positions accessibles, l'information est disponible.

- Information **parfaite** : Chaque joueur observe les actions de l'autre joueur.

On peut avoir un jeu à information incomplète mais parfaite et inversement (jeu à information complète mais imparfaite).



## Catégorisation du jeu de Hex

Hex est un jeu combinatoire c'est à dire un jeu **abstrait** (à **information parfaite**) à **somme nulle** opposant 2 joueurs {L|R} jouant alternativement et où le hasard n'intervient pas.

Joué sur une grille hexagonale composé d'hexagones organisés en un losange de taille NxN (souvent 10x10, 11x11 ou 14x14, parfois plus, rarement moins) représentant le plateau.

On dit également du Hex que c'est un jeu de **connexion**, **partisan**

## Vocabulaire associé

- Position : état du plateau à un instant du jeu.

- Position de départ : état du plateau au début du jeu (premier coup joué ou plateau vide).

- Options : coups disponibles ({L|R}).

- Condition de terminaison : l'un des joueurs ne peut plus jouer, c'est la fin de la partie.

## Théorie des jeux combinatoires

Théorie mathématique qui étudie les **jeux combinatoires**.

### Notations de la théorie des jeux combinatoires
