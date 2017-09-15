#!/usr/bin/env python
# -*-coding:utf-8 -*

from random import randrange
from math import ceil

argent = 1000
continue_play = True

print("Vous vous installez � la table de roulette avec {}$".format(argent))

def input_number(message, nmin, nmax):
    x = -1
    while (x < nmin or x > nmax):
        x = raw_input(message)
        try:
            x = int(x)
            assert x > nmin and x < nmax
        except ValueError:
            print("Erreur : le num�ro n'est pas entier")
            x = -1
            continue
        except AssertionError:
            print("Erreur : le num�ro n'appartient pas a ({}, {})"
                .format(nmin, nmax))

while continue_play:
    numero_mise = input_number('Donnez votre num�ro de mis�: ', 0, 50)
    mise = input_number('Donnez votre mise: ', 0, argent + 1)

    print("L'utilisateur mise {}$ sur le num�ro {}".format(mise, numero_mise))

    numero_gagnant = randrange(50)
    print("Le num�ro gagnant est", numero_gagnant)

    if numero_gagnant == numero_mise:
        argent += mise * 3
        print("L'utilisateur a gagn� {}$".format(mise * 3))
    elif numero_gagnant % 2 == numero_mise % 2:
        argent += ceil(mise / 2)
        print("L'utilisateur a gagn� {}$".format(ceil(mise / 2)))
    else:
        argent -= mise
        print("L'utilisateur a perdu {}$".format(mise))

    if argent > 0:
        print("L'utilisateur pos�de actuellement {}$".format(argent))

        choix = "x"
        while (choix != "O" and choix != "N"):
            choix = raw_input('Voullez-vous continuer � jouer? O/N ')

        if choix == "N":
            print("L'utilisateur conclut la partie avec {}$ en poche!".
                format(argent))
            continue_play = False
    else:
        print("L'utilisateur est ruin�! C'est la fin de la partie.")
        continue_play = False
