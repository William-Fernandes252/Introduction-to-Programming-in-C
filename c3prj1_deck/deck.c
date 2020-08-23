#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(int i = 0; i < (hand -> n_cards); i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t checkCard;
  for(int i = 0; i < d->n_cards; i++) {
    checkCard.value = (*d->cards[i]).value;
    checkCard.suit = (*d->cards[i]).suit;
    if((checkCard.value == c.value) && (checkCard.suit == c.suit)) {
	return 1;
      }
  }
  return 0;
}

int randomCardSorter(const void * random1_vp, const void * random2_vp) {
  typedef struct randomCard {
    card_t * card_p;
    long int random;
  } cardRandom;

  const cardRandom * random1_p = random1_vp;
  const cardRandom * random2_p = random2_vp;

  long int randDiffr = random1_p->random - random2_p->random;

  return randDiffr;
}

void shuffle(deck_t * d){
  size_t deckSize = d->n_cards;
  typedef struct randomCard {
    card_t * card_p;
    long random;
  } cardRandom;

  cardRandom deckRandoms[deckSize];

  for(size_t i = 0; i < deckSize; i++) {
    deckRandoms[i].card_p = d->cards[i];
    deckRandoms[i].random = random();
  }

  qsort(deckRandoms, deckSize, sizeof(cardRandom), randomCardSorter);

  for(size_t i = 0; i < deckSize; i++) {
    d->cards[i] = deckRandoms[i].card_p;
  }
}

void assert_full_deck(deck_t * d) {
  card_t card;

  int fullDeck = 1;

  for(suit_t i = SPADES; i < NUM_SUITS; i++) {
    for(unsigned j = 2; j <= VALUE_ACE; j++) {
      card.value = j;
      card.suit = i;
      int contains = deck_contains(d, card);
      if(contains == 0) {
	printf("deck is missing %c%c\n", value_letter(card), suit_letter(card));
	fullDeck = 0;
      }
    }
  }
  assert(fullDeck);
}
