#include <stdio.h>
#include "cards.h"

int main(void) {

  card_t c;
  c.value = 2;
  c.suit = CLUBS;
  hand_ranking_t h;
  h = FLUSH;

  assert_card_valid(c);

  printf("Testing rank:\n%s\n", ranking_to_string(h));
  printf("Testing return of cards:\n%c%c\n", value_letter(c), suit_letter(c));

  printf("Testing cards from nums:\n");
  for(unsigned int i = 0; i < 52; i++) {
    /*card_from_num(i);*/
    printf("%c%c\n", value_letter(card_from_num(i)), suit_letter(card_from_num(i)));
  }
}
