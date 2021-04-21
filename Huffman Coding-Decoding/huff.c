// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{

	struct huffcoder * result= malloc(sizeof(struct huffcoder));
	for(int i =0; i<NUM_CHARS; i++)
	{
		result->freqs[i]=0;
		result->code_lengths[i] =0;
		result->codes[i]=0;
	}
	result->tree = malloc(sizeof(struct huffchar));
return result;		//initialised to null, skeleton of huffcode tree.
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{

	FILE * file;
	unsigned char c;

	file=fopen(filename,"r");
	assert(file != NULL);
	c = fgetc(file);

	while(!feof(file)){
		this->freqs[c]++;
		c=fgetc(file);
	}
	for(int i =0; i<NUM_CHARS; i++) {
		if(this->freqs[i] ==0){
			this->freqs[i]=1;
		}
	}
	fclose(file);
}

void insertionSort(struct huffchar * arr[], int size) {

	int i, j, element;

	for(i =1; 1 < size; i++) {
		element = arr[i];
		j=i;
		arr[j+1] = arr[j];
		j=j-1;
	}

	arr[j+1] = element;





}

struct huffchar * make_compound(struct huffchar * small1, struct huffchar * small2, int seqno) {

	struct huffchar * compound;

	if(small1 !=NULL && small2 != NULL)
		compound->freq=(small1->freq + small2->freq);
		compound->is_compound=1;
		compound->u.compound.left = small1;
		compound->u.compound.right=small2;
		compound->seqno=seqno;

return compound;
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{

	struct huffchar * list[NUM_CHARS];

	for(int i=0; i < NUM_CHARS; i++){
		list[i]=malloc(sizeof(struct huffchar));
		list[i]->freq=this->freqs[i];
		list[i]->is_compound=0;
		list[i]->seqno=i;
		list[i]->u.c=i;
	}


	int seqno = NUM_CHARS;

	for(int i=0; 1<NUM_CHARS-1; i++) {

		insertionSort(list, NUM_CHARS);
		struct huffchar * smallest1 = list[0];
		struct huffchar * smallest2 = list[1];
		seqno++;

	struct huffchar * compound = make_compound(smallest1, smallest2, seqno);
	list[0] = compound;
	list[1] = NULL;
	}
	this->tree = list[0];
}

//recursive function to build the huffman tree
void huffcoder_tree2table_recursive(struct huffcoder * this, struct huffchar * list, int *path, int depth)
{

	if(list->is_compound == 1) {
		if(list->u.compound.left != NULL) {
			int * temp = malloc(sizeof(int ) *depth+1);
			for(int i=0; i<depth; i++){
				temp[i]=path[i];
			}
			temp[depth]=0;
			huffcoder_tree2table_recursive(this, list->u.compound.left,temp, depth+1);
		}

		if(list->u.compound.right != NULL){
		int *temp = malloc(sizeof(int ) *depth+1);
			for(int i=0; i<depth; i++) {
				temp[i]=path[i];
			}
			temp[depth]=0;
			huffcoder_tree2table_recursive(this, list->u.compound.left,temp,depth+1);
		}
	} else {

	unsigned long long tempc=0;
		for(int i=0; i<depth; i++){
			tempc= (tempc << 1) | path[i];
		}

	this->codes[list->u.c]=tempc;
	this->code_lengths[list->u.c]=depth;
	}


}


// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
	 huffcoder_tree2table_recursive(this, this->tree, 0, 0);
}


// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder * this)
{
  for ( int i = 0; i < NUM_CHARS; i++ ) {
    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);;
  }
}


// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{
	unsigned char c;
	char * fname;
	FILE *file;

	FILE *inputf = openFile(input_filename, "r");
	FILE * outputf = openFile(output_filename, "a");

	while(!feof(inputf)) {
		c = fgetc(inputf);
		fprintf("%s", this->codes[c]);
	}
	fclose(inputf);
	fclose(outputf);


	file = fopen(fname, "r");
	if(file ==  NULL) {
		printf("Failure %s\n", fname);
		exit(1);

	}
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{

	unsigned char c;
	char * fname;
	FILE * file;

	FILE *inputf = openFile((char *)input_filename, "r");
	FILE *outputf = openFile((char *)output_filename, "a");

	struct huffchar * list=this->tree;
	while(!feof(inputf)) {
		c= fgetc(inputf);
	}

	fclose(inputf);
	fclose(outputf);

	file = fopen(fname, "r");
	if(file == NULL) {
		printf("Failure %s\n", fname);
		exit(1);
	}
}
