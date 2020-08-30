#include<stdio.h>
#include<stdlib.h>
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if(index >= fc->n_decks) {
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
    for(size_t i = fc->n_decks; i <= index; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index + 1;
  }

  fc->decks[index].n_cards++;
  fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(card_t*));
  fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if(deck->n_cards < fc->n_cards) {
    printf("There are more unknowns than known cards!\n");
    return EXIT_FAILURE;
  }

  card_t topCard;

  for(size_t i = 0; i < fc->n_decks; i++) {
    topCard.value = deck->cards[i]->value;
    topCard.suit = deck->cards[i]->suit;

    for(size_t j = 0; j < fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j]->value = topCard.value;
      fc->decks[i].cards[j]->suit = topCard.suit;
    }
  }
}
