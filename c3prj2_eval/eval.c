#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  
  int valDiffr = (**cp2).value - (**cp1).value;
  int suitDiffr = (**cp2).suit - (**cp1).suit;

  if((valDiffr == 0) && (suitDiffr == 0)) {
    return 0;
  }
  else if((valDiffr == 0) && (suitDiffr != 0)) {
    return suitDiffr;
  }
  else {
    return valDiffr;
  }
}

suit_t flush_suit(deck_t * hand) {
  suit_t currSuit;
  int spadesCnt = 0, heartsCnt = 0, diamondsCnt = 0, clubsCnt = 0;

  for(size_t i = 0; i < hand->n_cards; i++) {
    currSuit = (*hand->cards[i]).suit;
    switch (currSuit) {
    case SPADES: spadesCnt++; break;
    case HEARTS: heartsCnt++; break;
    case DIAMONDS: diamondsCnt++; break;
    case CLUBS: clubsCnt++; break;
    default: printf("Found a invalid suit when searching for a flush\n"); break;
    }
  }

  if(spadesCnt >= 5) return SPADES;
  else if(heartsCnt >= 5) return HEARTS;
  else if(diamondsCnt >= 5) return DIAMONDS;
  else if(clubsCnt >= 5) return CLUBS;
  else return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest = arr[0];
  for(size_t i = 1; i < n; i++) {
    if(arr[i] > largest) {
      largest = arr[i];
    }
  }
  return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for(size_t i = 0; i < n; i++) {
    if(match_counts[i] == n_of_akind) {
      return i;
    }
  }
  printf("n_of_akind not found in the array match_counts\n");
  return 0;
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  for(size_t i = 0; i < hand->n_cards; i++) {
    if((*hand->cards[i]).value == (*hand->cards[match_idx]).value) {
      continue;
    }
    else if(match_counts[i] > 1) {
      return i;
    }
  }
  return -1;
}

unsigned counterForStraight(deck_t * hand, unsigned startIndex) {
  unsigned counter = 1;
  unsigned valDiffr;

  for(size_t i = startIndex; i < hand->n_cards - 1; ++i) {
    if(counter < 5) {
      valDiffr = (*hand->cards[i]).value - (*hand->cards[i + 1]).value;
      if(valDiffr == 1) {
	counter++;
      }
      else if(valDiffr == 0) {
	continue;
      }
      else {
	break;
      }
    }
    else {
      break;
    }
  }
  return counter;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  unsigned aceLow = 0;
  unsigned flushCheck = 1;
  card_t suitedCard = {(*hand->cards[index]).value, fs};

  unsigned cardsInRow = counterForStraight(hand, index);

  if((*hand->cards[index]).value == VALUE_ACE) {
    for(size_t i = index; i < hand->n_cards; ++i) {
      if((*hand->cards[i]).value == 5) {
	if(counterForStraight(hand, i) == 4) {
	  aceLow = 1;
	  suitedCard.value = 5;
	}
	break;
      }
    }
  }

  if(((cardsInRow == 5) || (aceLow == 1)) && (fs != NUM_SUITS)) {
    if((aceLow != 1) && ((*hand->cards[index]).suit != fs)) {
      flushCheck = 0;
    }
    else {
      for(size_t i = 0; i < (5 - aceLow); i++) {
	if(deck_contains(hand, suitedCard) == 0) {
	  flushCheck = 0;
	  break;
	}
	--suitedCard.value;
      }
      if (hand->cards[index]->suit != fs) {
	flushCheck = 0;
      }
    }
  }

  if((flushCheck == 1) || (fs == NUM_SUITS)) {
    if(aceLow == 1) {
      return -1;
    }
    else if(cardsInRow == 5) {
      return 1;
    }
  }
  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  unsigned cardCount = n;
  ans.ranking = what;

  for(size_t i = 0; i < n; i++) {
    ans.cards[i] = hand->cards[idx + i];
  }

  for(size_t i = 0; i < idx; i++) {
    if(cardCount >= 5) {
      break;
    }
    ans.cards[n+i] = hand->cards[i];
    cardCount++;
  }

  for(size_t i = 0; cardCount < 5; i++) {
    ans.cards[cardCount] = hand->cards[idx + n + i];
    cardCount++;
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(const card_t *), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(const card_t *), card_ptr_comp);

  hand_eval_t hand1ranked = evaluate_hand(hand1);
  hand_eval_t hand2ranked = evaluate_hand(hand2);

  int handRankDiffr = hand2ranked.ranking - hand1ranked.ranking;

  if(handRankDiffr != 0) {
    return handRankDiffr;
  }
  else {
    int cardDiffr;
    for(size_t i = 0; i < 5; i++) {
      cardDiffr = (*hand1ranked.cards[i]).value - (*hand2ranked.cards[i]).value;
      if(cardDiffr != 0) {
	return cardDiffr;
      }
    }
    return 0;
  }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
  unsigned * counts = malloc(hand->n_cards * sizeof(unsigned));
  unsigned aceCnt = 0, kingCnt = 0, queenCnt = 0, jackCnt = 0, tenCnt = 0, nineCnt = 0, eightCnt = 0, sevenCnt = 0, sixCnt = 0, fiveCnt = 0, fourCnt = 0, threeCnt = 0, twoCnt = 0;

  for(size_t i = 0; i < hand->n_cards; i++) {
    switch(hand->cards[i]->value) {
    case VALUE_ACE: aceCnt++; break;
    case VALUE_KING: kingCnt++; break;
    case VALUE_QUEEN: queenCnt++; break;
    case VALUE_JACK: jackCnt++; break;
    case 10: tenCnt++; break;
    case 9: nineCnt++; break;
    case 8: eightCnt++; break;
    case 7: sevenCnt++; break;
    case 6: sixCnt++; break;
    case 5: fiveCnt++; break;
    case 4: fourCnt++; break;
    case 3: threeCnt++; break;
    case 2: twoCnt++; break;
    }
  }
  
  for(size_t i = 0; i < hand->n_cards; i++) {
    switch(hand->cards[i]->value) {
    case VALUE_ACE: counts[i] = aceCnt; break;
    case VALUE_KING: counts[i] = kingCnt; break;
    case VALUE_QUEEN: counts[i] = queenCnt; break;
    case VALUE_JACK: counts[i] = jackCnt; break;
    case 10: counts[i] = tenCnt; break;
    case 9: counts[i] = nineCnt; break;
    case 8: counts[i] = eightCnt; break;
    case 7: counts[i] = sevenCnt; break;
    case 6: counts[i] = sixCnt; break;
    case 5: counts[i] = fiveCnt; break;
    case 4: counts[i] = fourCnt; break;
    case 3: counts[i] = threeCnt; break;
    case 2: counts[i] = twoCnt; break;
    }
  }
  return counts;
}


// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
