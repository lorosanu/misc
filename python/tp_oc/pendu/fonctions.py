#!/usr/bin/env python
# -*- coding:utf-8 -*

import os
import pickle

from donnees import *
from random import choice

def read_scores():
    scores = {}
    if os.path.isfile(scores_fname):
        with open(scores_fname, 'rb') as f_scores:
            s_scores = pickle.Unpickler(f_scores)
            scores = s_scores.load()
    return scores

def save_scores(scores):
    with open(scores_fname, 'wb') as f_scores:
        s_scores = pickle.Pickler(f_scores)
        s_scores.dump(scores)

def name_user():
    name = raw_input("Veuillez introduire votre nom: ")
    name = name.capitalize()

    if not name.isalnum() or len(name) < 4:
        print('Nom invalide: utilisez minimum 4 caracteres alpha-numeriques')
        # appel recursif
        return name_user()

    return name

def choose_word(my_words):
    # un element au hasard dans la liste
    return choice(my_words)

def choose_letter(chosen_letters):
    letter = ''
    while letter == '':
        letter = raw_input('Veuillez choisir une lettre: ')
        if letter.isalpha() == False or len(letter) != 1:
            letter = ''
        elif letter in chosen_letters:
            print('Lettre deja utilisé. Choisisez une nouvelle!')
            letter = ''
    return letter.lower()

def format_word(chosen_word, chosen_letters):
    new_match = ""
    for letter in chosen_word:
        if letter in chosen_letters:
            new_match += letter
        else:
            new_match += '*'
    return new_match

def play_game(chosen_word):
    c_score = max_trials
    current_match = '*' * len(chosen_word)
    chosen_letters = []

    while c_score > 0 and current_match != chosen_word:
        # show letters found so far
        print("\n")
        print(current_match)
        print("Il vous restent {} essai(s)".format(c_score))

        # choose letter
        letter = choose_letter(chosen_letters)
        chosen_letters.append(letter)

        # check letter
        current_match = format_word(chosen_word, chosen_letters)

        if ( letter not in chosen_word ):
            c_score -= 1
            print("Mauvais choix !")
        else:
            print("Bon choix !")

    print("\nLa partie est fini !")
    if (c_score > 0):
        print("Vous avez gagné {} points".format(c_score))
    else:
        print('Vous avez perdu !')
        print("Le mot recherche etait {}".format(chosen_word))
    return c_score
