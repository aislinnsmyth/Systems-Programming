
//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_string.h"



// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string * new_list_string(char * text) {			//WORKS.


	struct list_string * mystring;				//initialise the linked list.
	struct ls_node * node;					//initialise nodes in linked list.

	mystring = malloc(sizeof(struct list_string));			//stores memory the size of list_string in mystring.
	assert(mystring != NULL);					//ensure enough memory.
	mystring-> head = NULL;						//initialise linked list to NULL- so its empty.

	for(int i=0; text[i] != '\0'; i++) {				//for loop to loop through the contents of text in order to put the d=same data into the linked list.

		node = malloc(sizeof(struct ls_node));			//initialise the memory for the node in linked list.
		assert(node != NULL);					//ensure enough memory.
		node->c=text[i];					//set the character c (a character in the string) to data from text.
		node->next=mystring->head;				//set next node to the head of the linked list.
		mystring->head=node;					//set head equal to the new node we have created, thus it is the start of the linked list.
	}
return mystring;
}


// find the length of the list string
int list_string_length(struct list_string * this) {		//WORKS.

	int count =0;										//initialise count which counts the length of characters in the list string.
	struct ls_node * current;								//initialise pointer to new node - current.

		for(current=this->head; current != NULL; current=current->next) {		//for loop which begins at the head of the linked list and runs through it node by node.
				count++;							//count stores the number of characters the for loop runs through.
		}
		return count;									//return count returns the length of the linked list in an int.
}


// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd". 
int list_string_compare(struct list_string * s1, struct list_string * s2) {

	struct ls_node * current;													//initialise node current for string s1.
	struct ls_node * node;														//initialise node node for string s2.


	for(current=s1->head, node=s2->head; current != NULL && node != NULL; current=current->next, node=node->next) {			//for loop for both node and current, which runs through each of the same character comparing them.

			if(current->c == node->c) {											// if the strings are lexigraphically equal we return 0 as there are no changes.
				return 0;
		} else if( current->c > node->c) {											//if string s1 is lexigraphically larger than string s2 then return 1 as there is a greater difference.
				return 1;
		} else if(current->c < node->c) {											//if string s1 is lexigraphically less than string s2 then return -1 as there is a negative difference.

			return -1;
		}
	}
return;
}


//i		int i;
//		unsigned char length1 = list_string_length(s1);
//		unsigned char length2 = list_string_length(s2);
//	for(i =0; i < length1; i++) {
///		for(i=0; i < length2; i++) {
//			if(length1 == length2) {
//			return 0;

//			} else if(length1 > length2) {
//			return 1;
//			} else {
//		return -1;




// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string * text, struct list_string * str) {

	struct ls_node * current;													//node called current for text.
	struct ls_node * node;														//nodde called node for str.

	for(current=text->head, node=str->head; current != NULL && node != NULL; current=current->next, node=node->next) {		//for looping through both strings
			if(current == node->c) {											//search for str in text to see if its a substring return 0 if it is .
				return 1;
			} else{
		return 0;
			}
	}
}


