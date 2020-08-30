#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "future.h"
#include "cards.h"
#include "eval.h"
#include "input.h"

deck_t hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * hand = malloc(sizeof(deck_t));
  hand->n_cards = 0;
  hand->cards = NULL;
  card_t cardToAdd;
  int unkIdx;
  card_t * futureCardPtr = NULL;

  for(size_t i = 0; i < strlen(str); i++) {
    if(issuper(str[i]) || isdigit(str[i])) {
      cardToAdd = card_from_letters(str[i], str[i + 1]);
      add_card_to(hand, cardToAdd);
    }
    else if(str[i] == '?') {
      unkIdx = atoi(&str[i + 1]);

      futureCardPtr = add_empty_card(hand);

      do {
	i++;
      }while(isdigit(str[i]));
    }
  }

  return hand;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  char * handStr = NULL;
  size_t handStrSz = 0;
  deck_t ** hands = NULL;
  *n_hands = 0;
  while(getline(&handStr, &handStrSz, f) > 0) {
    *n_hands = *n_hands + 1;
    if(strlen(handStr) < 15) {
      fprintf(stderr, "There is something wrong with one of the input lines.\n");
      exit(EXIT_FAILURE);
    }

    hands = realloc(hands, *n_hands * sizeof(deck_t*));
    hands[*n_hands - 1] = hand_from_string(handStr, fc);
  }

  free(handStr);

  return hands;
}
