 #include "bitset.h"
#include <limits.h>
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {

	struct bitset * result; //points to new bitset;
	result = malloc(sizeof(struct bitset));

	float word_size = sizeof(uint64_t);
	int words = ceil(size/word_size);

	result ->size_in_words = words;
	result ->universe_size = size;
	result -> bits = malloc(sizeof(uint64_t)*words);

	for(int i =0; i < words; i++) {
	result -> bits[i]=0  ;

	}
		return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {

	return this->universe_size;

}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){

	int count =0;

	for(int i=0; i < this->size_in_words; i++){
	uint64_t word1 = this->bits[i];
	uint64_t mask = 1;
	for(int bits = 0; bits < 63; bits++) {
		if((word1 & mask) == 1) {
	count++;
		}
		word1 = word1 >> 1;
	}
}
	//we need to shift and use bitwise operations and once = 1 count ++;
return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){

	int word_size = sizeof(uint64_t);	//length of set
	int word = item/word_size;
	int bit = item % word_size;
	uint64_t old_val = this->bits[word];

	uint64_t mask = 1 << bit;
	return((old_val & mask)!=0);
	
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {

	int word_size = sizeof(uint64_t);
	int word = item/word_size;
	int bit = item % word_size;
	uint64_t old_val = this->bits[word];

	uint64_t mask = 1 << bit;
	this->bits[word] = old_val | mask;
return;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {

	int word_size = sizeof(uint64_t);
	int word = item/word_size;
	int bit = item % word_size;
	uint64_t old_val = this->bits[word];

	uint64_t mask = 1 << bit;
	this->bits[word] = (old_val | mask)^mask;
return;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {

	if(dest->universe_size == src1->universe_size && src2->universe_size == dest->universe_size) { 
		for(int i = 0; i < dest->size_in_words; i++) {
			dest->bits[i] = src1->bits[i] | src2->bits[i];
		}
	}
	return;
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {

	if(dest->universe_size == src1->universe_size && src2->universe_size == dest->universe_size) {
		for(int i =0; i< dest->size_in_words; i++) {
			dest->bits[i] = src1->bits[i] & src2->bits[i];

		}

	}
	return;
}
