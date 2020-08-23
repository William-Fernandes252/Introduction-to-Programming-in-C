#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t ** point = hand->cards;
  for(int i = 0; i < (hand -> n_cards); i++) {
    print_card(**point);
    printf("%s", " ");
    point++;
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** point = d->cards;
  for(int j = 1; j < (d->n_cards); j++) {
    if(suit_letter(**point) == suit_letter(c) && value_letter(**point) == value_letter(c)) {
      return 1;
    }
    point++;
  }
  return 0;
}

void cardPointSwap(card_t ** point1, card_t ** point2) {
  card_t * tempr = *point1;
  *point1 = *point2;
  *point2 = tempr;
}

void shuffle(deck_t * d){
  card_t ** point = d->cards;
  int size = (int)(d->n_cards);
  for(int k = 0; k < size; k++) {
    int shuffle = ((int)rand()) % size;
    cardPointSwap(point + k, point + shuffle);
  }
}

void assert_full_deck(deck_t * d) {
  card_t ** point = d->cards;
  deck_t tempr_deck;
  tempr_deck.cards = d->cards;
  for(int l = 0; l < (d->n_cards); l++) {
    card_t tempr_card = **point;
    assert_card_valid(tempr_card);
    if(l > 0) {
      tempr_deck.n_cards = (size_t)l;
      assert(!deck_contains(&tempr_deck, tempr_card));
    }
    point++;
  }
}
