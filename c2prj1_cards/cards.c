#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= 0 && c.suit <= 4);
}

const char * ranking_to_string(hand_ranking_t r) {
 switch(r) {
   case STRAIGHT_FLUSH: return "STRAIGHT FLUSH"; break;
   case FOUR_OF_A_KIND: return "FOUR OF A KING"; break;
   case FULL_HOUSE: return "FULL HOUSE"; break;
   case FLUSH: return "FLUSH"; break;
   case STRAIGHT: return "STRAIGHT"; break;
   case THREE_OF_A_KIND: return "THREE OF A KIND"; break;
   case TWO_PAIR: return "TWO PAIR"; break;
   case PAIR: return "PAIR"; break;
   case NOTHING: return "NOTHING"; break;   
   default: return "";
  }
}

char value_letter(card_t c) {
  if(c.value == 2) {
    return '2';
  }
  else if(c.value == 3) {
    return '3';
  }
  else if(c.value == 4) {
    return '4';
  }
  else if(c.value == 5) {
    return '5';
  }
  else if(c.value == 6) {
    return '6';
  }
  else if(c.value == 7) {
    return '7';
  }
  else if(c.value == 8) {
    return '8';
  }
  else if(c.value == 9) {
    return '9';
  }
  else if(c.value == 10) {
    return '0';
  }
  else if(c.value == VALUE_JACK) {
    return 'J';
  }
  else if(c.value == VALUE_QUEEN) {
    return 'Q';
  }
  else if(c.value == VALUE_KING) {
    return 'K';
  }
  else if(c.value == VALUE_ACE) {
    return 'A';
  }
  else {
    return '?';
  }
}

char suit_letter(card_t c) {
  if(c.suit == 0) {
    return 's';
  }
  else if(c.suit == 1) {
    return 'h';
  }
  else if(c.suit == 2) {
    return 'd';
  }
  else if(c.suit == 3) {
    return 'c';
  }
  else {
    return '?'; 
  }
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if(value_let == '2') {
    temp.value = 2;
  }
  else if(value_let == '3') {
    temp.value = 3;
  }
  else if(value_let == '4') {
    temp.value = 4;
  }
  else if(value_let == '5') {
    temp.value = 5;
  }
  else if(value_let == '6') {
    temp.value = 6;
  }
  else if(value_let == '7') {
    temp.value = 7;
  }
  else if(value_let == '9') {
    temp.value = 9;
  }
  else if(value_let == '0') {
    temp.value = 10;
  }
  else if(value_let == 'J') {
    temp.value = VALUE_JACK;
  }
  else if(value_let == 'Q') {
    temp.value = VALUE_QUEEN;
  }
  else if(value_let == 'K') {
    temp.value = VALUE_KING;
  }
  else if(value_let == 'A') {
    temp.value = VALUE_ACE;
  }

  assert(temp.value >= 2 && temp.value <= VALUE_ACE); 

  if(suit_let == 's') {
    temp.suit = 0;
  }
  else if(suit_let == 'h') {
    temp.suit = 1;
  }
  else if(suit_let == 'd') {
    temp.suit = 2;
  }
  else if(suit_let == 'c') {
    temp.suit = 3;
  }

  assert(temp.suit >= 0 && temp.suit <= 3);
  
  return temp;

}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = 2 + c % 13;
  temp.suit = c / 13;
  return temp;
}
