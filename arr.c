#include <stdio.h>
#include <stdlib.h>

int *arr ;
	int i=0,n;

void Insertion(){
	int j , item;
	printf("\nPlace to insert : ");
	scanf("%d",&j);
	printf("Enter item to place : ");
	scanf("%d",&item);
	for (i=n;i>=0;i--){
		if (i > j){
			arr[i] = arr[i-1];
		}
		else if (i == j)
		{
			arr[i] = arr[i-1];
			arr[i-1] = item;
			++n;
		}
	}
	printf("\nAfter modified : \n\n");
	for (i = 0; i < n; i++)
	{
		printf("arr[%d] : %d\n",i,arr[i]);
	}
}
void Deletion(){
	int item;
	int flag=0;
	printf("Enter item to delete : ");
	scanf("%d",&item);
	for (int i = 0; i < n; ++i)
	{
		if (flag == 0 && arr[i] == item){
			flag =1;
			arr[i] = arr[i+1];
			--n;
		}
		else if(flag ==1){
			arr[i] = arr[i+1]; 
		}
	}

	printf("\nAfter modified : \n\n");
	for (i = 0; i < n; i++)
	{
		printf("arr[%d] : %d\n",i,arr[i]);
	}	
}
void Search(){
	int item;
	printf("Enter item to search: ");
	scanf("%d",&item);
	for (int i = 0; i < n; ++i)
	{
		if (arr[i] == item){
			printf("Item %d is at place %d.\n", item,i+1);
		}
	}
	printf("\nAfter modified : \n\n");
	for (i = 0; i < n; i++)
	{
		printf("arr[%d] : %d\n",i,arr[i]);
	}
}
void Update(){
	int j, item;
	printf("\nPlace to insert : ");
	scanf("%d",&j);
	printf("Enter item to update: ");
	scanf("%d",&item);
	arr[j-1] = item;


}

int main()
{
	/* code */
	int op;
	int flag = 0;

	printf("size of array: ");
	scanf("%d",&n);
	arr = malloc(n*sizeof *arr);
	for (i = 0; i < n; ++i)
	{
		printf("Please enter number arr[%d] : ",i);
		scanf("%d",&arr[i]);
	}
	printf("\nbefore array modified\n\n");
	for (i = 0; i < n; ++i)
	{
		printf("Please enter number arr[%d] : %d\n",i,arr[i]);
	}
	do{
		printf("\n1 - Insertion\n2 - Deletion\n3 - Search\n4 - Update\n");
		printf("\nPlease select option : ");
		scanf("%d",&op);
		switch(op) {
			case 1:
			Insertion();
			break;
			case 2:
			Deletion();
			break;
			case 3:
			Search();
			break;
			case 4:
			Update();
			break;
			default:
			flag = 1;
			printf("wrong choice!!! Bye...bye....\n");
			break;
		}
	}while(flag == 0);

	return 0;
}