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

  for(size_t i = 2; i < deckSize; i++) {
    deckRandoms[i].card_p = d->cards[i];
    deckRandoms[i].random = random();
  }

  qsort(deckRandoms, deckSize, sizeof(cardRandom), randomCardSorter);

  for(size_t i = 2; i < deckSize; i++) {
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

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(card_t*));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(card_t));
  *deck->cards[deck->n_cards - 1] = c;
}

card_t * add_empty_card(deck_t * deck) {
  card_t empty;
  empty.value = 0;
  empty.suit = 0;
  add_card_to(deck, empty);
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * exclude_cards) {
  deck_t * buildDeck = malloc(sizeof(deck_t));
  buildDeck->cards = NULL;
  buildDeck->n_cards = 0;
  card_t card;
  for(size_t i = 0; i < 52; i++) {
    card = card_from_num(i);
    if(deck_contains(exclude_cards, card) == 0) {
      add_card_to(buildDeck, card);
    }
  }
  return buildDeck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * exclusionDeck = malloc(sizeof(deck_t));
  exclusionDeck->cards = NULL;
  exclusionDeck->n_cards = 0;
  card_t exclusionCard;
  for(size_t i = 0; i < n_hands; i++) {
    for(size_t j = 0; j < hands[i]->n_cards; j++) {
      exclusionCard = *(hands[i]->cards[j]);
      if(deck_contains(exclusionDeck, exclusionCard) == 0) {
	add_card_to(exclusionDeck, exclusionCard);
      }
    }
  }
  deck_t * remainingDeck = make_deck_exclude(exclusionDeck);
  free_deck(exclusionDeck);
  return remainingDeck;
}

void free_deck(deck_t * deck) {
  for(size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
