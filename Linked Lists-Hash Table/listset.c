#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

struct listset * listset_new() {

	struct listset *result;

	result = malloc(sizeof(struct listset));
	assert(result != NULL);
	result->head = NULL;

	return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {

	struct listnode * current = this->head;

	while(current != NULL) {
	if(strcmp(current->str, item) == 0)
			return 1;
	current = current->next;
	}
		return 0;

}

void listset_add(struct listset * this, char * item) {

	struct listnode * node;

	if(listset_lookup(this, item) == 0) {
		node = malloc(sizeof(struct listnode));
		node->str = item;
		node->next = this->head;
		this->head = node;
	}
}

void listset_remove(struct listset * this, char * item) {

	struct listnode * temp = this->head;
	struct listnode * prev = this->head;

	if(temp == NULL) {
		return;
	}

	if(strcmp(this->head->str, item) == 0) {
		this->head=temp->next;
		temp = NULL;
		return;
	}

		for(temp=this->head->next; temp != NULL; temp=temp->next) {
			if(strcmp(temp->str, item) == 0){
				prev->next=temp->next;
				free(temp);
				return;
			}
			prev=prev->next;
		}
return;
}

// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
  struct listset * src2) {

	struct listnode * current;

	for(current=src1->head; current != NULL; current=current->next) {
		listset_add(dest, current->str);
	}
		for(current=src2->head; current != NULL; current=current->next) {
			listset_add(dest, current->str);
		}
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
  struct listset * src2) {

	struct listnode * current;

	for(current = src1->head; current != NULL; current = current->next) {
		if(listset_lookup(src2, current->str) == 1) {
			listset_add(dest, current->str);
		}
	}
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {

	int count =0;
	struct listnode * current;

		for(current=this->head; current != NULL; current=current->next) {
			count++;
		}
	return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;
  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
