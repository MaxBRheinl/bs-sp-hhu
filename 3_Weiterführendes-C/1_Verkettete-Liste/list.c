#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct list_node{
	int value;
	struct list_node *next;
	} node_t;
/*	
node_t* add_element_sorted(node_t *head, int v){
	node_t *new_node = malloc(sizeof(node_t));
	if(new_node == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	new_node->value = v;
	new_node->next = NULL;
	
	if(head == NULL || v < head->value){
		new_node->next = head;
		return new_node;
		}
		
	node_t* current = head;	
	while(current->next != NULL && current->next->value < v){
		current = current->next;
		}
	new_node->next = current->next;
	current->next = new_node;
	return head;
	}
*/

node_t* add_element_sorted(node_t *head, int v){
	node_t *new_node = malloc(sizeof(node_t));
	if(new_node == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	new_node->value = v;
	new_node->next = NULL;
	
	node_t **current = &head;
	while(*current != NULL && (*current)->value < v){
		current = &((*current)->next);
		}
	if(*current == head){
		new_node->next = head;
		return new_node;
		} else {
			new_node->next = *current;
			*current = new_node;
			return head;
			}
	}
	
node_t* remove_element(node_t *head, int v){
	node_t **current = &head;
	node_t *entry;
	node_t *ret = head;
	
	while(*current != NULL){
		entry = *current;
		if(entry->value == v){
			*current = entry->next;
			if(entry == head){
				ret = *current;
				}
				
			free(entry);
			entry = NULL;
			return ret;
			}
		current = &(entry->next);
		}
		
	printf("%d nicht in Liste vorhanden.\n", v);
	return ret;
	}
	
void print_list(node_t *head){
	while(head != NULL){
		printf("%d ", head->value);
		head = head->next;
		}
	printf("\n");
	}
	
void free_list(node_t *head){
	node_t *temp;
	while(head != NULL){
		temp = head;
		head = head->next;
		
		free(temp);
		temp = NULL;
		}
	}
	
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Eingabefehler. Erwartet: <Anzahl add> <Anzahl remove>\n");
		exit(EXIT_FAILURE);
		}
	long add = strtol(argv[1], NULL, 10);
	long remove = strtol(argv[2], NULL, 10);
	
	node_t *list = NULL;
	srand(time(NULL));
	
	for(int i = 0; i < add; i++){
		list = add_element_sorted(list, rand()%100);
		}
	print_list(list);
	
	for(int i = 0; i < remove; i++){
		list = remove_element(list, rand()%100);
		}
	print_list(list);
	
	free_list(list);
	list = NULL;
	
	exit(EXIT_SUCCESS);
	}
