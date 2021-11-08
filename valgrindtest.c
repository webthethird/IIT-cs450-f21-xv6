#include <stdlib.h>
#include <stdio.h>

struct node {
  struct node *children[2];
};

int main(int argc, char const *argv[])
{
  //test code that properly mallocs and frees one time each
  /*
  int *arr = malloc(sizeof(int) * 5);

  free(arr);
  */

  //test code that mallocs and fails to free
  /*
  int *arr = malloc(sizeof(int) * 5);
  */

  //test code that mallocs twice, and only frees once
  /*
  int *arr = malloc(sizeof(int) * 5);
  int *arr2 = malloc(sizeof(int) * 6);

  free(arr);
  */

  //test code where you malloc once and free twice
  /*
  int *arr = malloc(sizeof(int) * 5);
  
  free(arr);
  free(arr);
  */

  //test code that does not malloc and frees anyway
  /*
  int num = 5;
  int *point = &num;

  free(point);
  */

  //test code where we have a tree of pointers and free the root pointer
  /*
  struct node *root = malloc(sizeof(struct node));
  for (int i = 0; i < 2; i++) {
    root->children[i] = (struct node*) malloc(sizeof(struct node));
    for (int j = 0; j < 2; j++) {
      root->children[i]->children[j] = (struct node*) malloc(sizeof(struct node));
    }
  }
  free(root);
  */

  //test code to malloc a pointer, add to the pointer, and then free
  int *arr = malloc(sizeof(int) * 5);
  arr += 5;
  free(arr);
  

  return 0;
}