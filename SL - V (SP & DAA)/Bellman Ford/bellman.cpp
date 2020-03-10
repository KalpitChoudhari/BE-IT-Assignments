#include <stdio.h>
struct node
{
	int wt, data;
	struct node* next; 
};

struct list
{
	struct node* head;
};

struct graph
{
	int V;
	struct list *array;
}

struct graph *create_graph(int v)
{
	struct graph* graph = (struct graph *)malloc(sizeof(struct graph));
	graph->V = v;
	graph->array = (struct list *)malloc(v * sizeof(struct list));
	
	for(int i=0;i<v;i++)
		graph->array[i].head = NULL;
	return graph;
}

struct node* c_node(int x, int weight)
{
	struct node* q = (struct node *)malloc(sizeof(struct node));
	q->wt = weight;
	q->data = x;
	q->next = NULL;
	return q;
}

void add_edge(struct graph* graph, int src, int dest, int wt)
{
	struct node *temp = c_node(dest, wt);
	temp->next = graph->array[src].head;
	graph->array[src].head = temp;
}

void print_graph(struct graph *graph, int v)
{
	for(int i=0;i<v;i++)
	{
		struct node* traverse = graph->array[i].head;
		while(traverse != NULL)
		{
			printf("-> %d ",traverse->data);
			traverse = traverse->next;
		}
	}
}

int main()
{
	int v, ch;
	printf("\nEnter number of vertices:");
	scanf("%d",&v);
	
	struct graph* graph = create_graph(v);
	
	do
	{
		printf("\n1.Add Edge\n2.Print Graph\n3.Exit");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				int src, dest, wight;
				printf("\nEnter source, destination and weight:");
				scanf("%d%d%d",&src,&dest,&weight);
				add_edge(graph, src, dest, weight);
				break;
			case 2:
				print_graph(graph);
				break;
			default:
				break;
		}
	}while(ch != 3);
	return 0;
}
