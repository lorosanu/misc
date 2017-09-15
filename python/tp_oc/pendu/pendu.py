#!/usr/bin/env python
# -*- coding:utf-8 -*

from donnees import *
from fonctions import *

# read the file storing the player scores
scores = read_scores()

# new or old player ?
name = name_user()
if name not in scores:
    scores[name] = 0

# play
continue_play = 'o'
while continue_play != 'n':
    print("Joueur {} : {} points".format(name,scores[name]))

    # chose random word
    chosen_word = choose_word(my_words)

    # play
    c_score = play_game(chosen_word)
    scores[name] += c_score

    # continue playing ?
    continue_play = raw_input("Souhaitez-vous continuer ? (o/n) ")
    continue_play = continue_play.lower()

print("{} a le score final de {} points".format(name, scores[name]))

# save the player scores
save_scores(scores)
