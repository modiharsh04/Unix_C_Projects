#include <stdio.h>
#include <stdlib.h>


typedef struct node
	{
		int value;
		struct node *next;
	} node_t;


	void display(node_t *head);
	void Initialize();
	void add(node_t *head);

node_t * head = NULL;

void Initialize(){
		head = malloc(sizeof(node_t));
		if (head == NULL){
			printf("invalid!!\n");;
		}
		int val;
		printf("Enter value for head : ");
		scanf("%d",&val);
		head->value = val;
		head->next == NULL;
}

void add(node_t *head){
	node_t *current = head;
	int i =1;
	while(current->next != NULL){
		current = current->next;
	}
	node_t * next_node = NULL;
	next_node = malloc(sizeof(node_t));
	current->next = next_node;
	printf("Enter value for new entry: ");
	scanf("%d", &next_node->value);
	next_node->next = NULL;
	printf("\nafter modifying\n");
	display(head);
}

void display(node_t *head){
	node_t *current = head;
	int i=1;

	while(current != NULL){
		printf("(%d,%d)\n",i, current->value);
		current=current->next;
		++i;
	}	
}

void pushAtStart(node_t **head){
	node_t *current;
	current = malloc(sizeof(node_t));
	printf("Enter value for new head: ");
	scanf("%d",&current->value);
	current->next= *head;
	*head = current;
	display(*head);
}

void pullFromFirst(node_t **head){
	node_t *current = NULL;
	if(head == NULL){
		printf("Nothing to delete!!\n");
	}
	current = (*head)->next;
	free(*head);
	*head = current;
	printf("After pulling...\n");	
}

void main(){
	Initialize();
	display(head);
	add(head);
	pushAtStart(&head);
	pullFromFirst(&head);
	display(head);
}