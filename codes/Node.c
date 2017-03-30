
typedef struct Node
{
	int data;
	Node *next;
}Node;

void printfNodeList(Node *nodes)
{
	while(nodes != NULL){
		printf("%d->", nodes->data);
		nodes = nodes->next;
	}
	printf("\n");
}