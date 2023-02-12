#include "llist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

   if (argc < 2){                           // User must input atleast 2 arguments that way the user can still print an empty list. 
    printf("ERROR: Need More Arguments\n"); // Error message when no additional arguments are added after ./llist (./llist counts as an argument)
  }                                         // My initial implemenation had 3 arguments because I figured the user would start by inputting "ih" or "it" followed by its value for a total of 3 arguments
    
  else {                                    // If more than 2 arguments are inputted
    struct node *head = NULL;               // Init the head node to NULL
  
    for (int i = 0; i < argc; ++i) {        // For Loop for command line parser
  
      if (strcmp(argv[i],"ih") == 0) {      // Compare the user input to "ih" (Insert Head) for a match
        int value = atoi(argv[++i]);        // Converts the next user input into an int value
        struct node *n = node_alloc(value); // New node n is allocated to memory 
        llist_insert_head(&head, n);        // The Head and New node is inputted as parameters into llist_insert_head
      }

      else if (strcmp(argv[i],"it") == 0) { // Compare the user input to "it" (Insert Tail) for a match
        int value = atoi(argv[++i]);        // Converts the next user input into an int value
        struct node *n = node_alloc(value); // New node n is allocated memory 
        llist_insert_tail(&head, n);        // The head and New node is inputted as paramters into llist_insert_tail
      }
  
      else if (strcmp(argv[i],"dh") == 0) { // Compare the user input to "dh" (Delete Head) for a match
        llist_delete_head(&head);           // The head is inputted into llist_delete_head to delete head
      }

      else if (strcmp(argv[i],"f") == 0) { // Compare the user input to "f" (Free) for a match
        llist_free(&head);                 // The head is inputted into llist_free to free list
      }
  
      else if (strcmp(argv[i],"p") == 0) { // Compare the user input to "p" (print) for a match
        llist_print(head);                 // The head is inputted into the llist_print to print out the current list
      }
    }
  }
  return 0;                                // Exit program 
}

void llist_insert_head(struct node **head, struct node *n){
  if(*head!=NULL){                         // If head is not Null, run if statement
    n->next=*head;                         // Set the new node's next to point at the current head
  }
  *head = n;                               // Set new node as head, this executes once for either a NULL list or a non NULL list
}

struct node *llist_delete_head(struct node **head){
  if(*head==NULL){                         // If the Head of the list is Null, run if statement
    return *head;                          // Just return the NULL *Head
  }
  struct node *temp_node = *head;          // Create a new temporary node that points to the head
  *head = temp_node -> next;               // Set the head equal the temp node's next node in the list, this will uncouple the old head from the list, although it has not been freed
}

void llist_insert_tail(struct node **head, struct node *n){
  if (*head == NULL){                     // If the head is null, the list must be empty
    *head = n;                            // Just insert n node at the head
  }
  else{                                   // Else (*Head != NULL)
    struct node *temp_node = *head;       // Create a temp_node head pointer
    while(temp_node->next != NULL){       // While loop to itterate through until next is null 
      temp_node = temp_node->next;        // This will prove we are at the end of the list
    }
    temp_node->next = n;                  // Since Next is NULL, insert n node at the tail
  }
}

void llist_print(struct node *head){
  if (head != NULL){                      // Check to see if *head is NULL
    while(head->next != NULL){            // Create a while loop to itterate through until next is NULL
      printf("%d -> ",head->value);       // Print the head's value, followed by an "->" with each itteration
      head = head->next;                  // Itterate through the list
    }                                     // Can't forget the tail, the while loop above will ignore tail since next is NULL
    printf("%d\n",head->value);           // Once while loop finishes, it will print the next value (the tail)
  }
  else{                                   // Else statement for an Empty list (head==NULL)
    printf("[empty]\n");                  // Print "[empty]\n", added a new line after to make it cleaner.
  }
}

void llist_free(struct node **head){
  while (*head != NULL) {                 // A while loop to itterate through the list until the head is NUll (list is empty)
    struct node *temp_node = *head;       // Create a temporary node pointer that points to the head node pointer 
    *head = temp_node->next;              // Itterate through the list using the temp_node's next and make tem_node->next as the new head
    node_free(temp_node);                 // Free the temp_node after each itteration, this allwos us to move the head down the list and free the old heads using the temp_node
  } 
  return;                            
}

struct node *node_alloc(int value){
  struct node *new_node = malloc(sizeof(struct node)); // Create new node and allocate its memory
  new_node->value = value;                             // Give the new node its inputed value
  new_node->next = NULL;                               // Make its next = NULL
  return new_node;
}

void node_free(struct node *n){
  free(n);                                  // Frees the inputted node from memory
}
