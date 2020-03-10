#include <stdio.h>
#include <stdlib.h>
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
};

struct graph *create_graph(int v)
{
	struct graph* graph = (struct graph *)malloc(sizeof(struct graph));
	graph->V = v;
	graph->array = (struct list *)malloc(v * sizeof(struct list));
	
	for(int i=0;i<v;i++)
		graph->array[i].head = NULL;
	return graph;
};

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
	int flag = 0;
	if(graph->array[src].head == NULL)
	{
		temp->next = graph->array[src].head;
		graph->array[src].head = temp;
	}
	else
	{
		struct node* temp1 = graph->array[src].head;
		while(temp1 != NULL)
		{
			if(temp1->data == temp->data)
			{
				printf("\nAdding Duplicate edge!!\n");
				flag = 1;
			}
			temp1 = temp1->next;
		}
		if(!flag)
		{
			temp->next = graph->array[src].head;
			graph->array[src].head = temp;
		}
	}
}

void print_graph(struct graph *graph, int v)
{
	for(int i=0;i<v;i++)
	{
		printf("\nAdjacency list of vertex %d \n Head ", i);
		struct node* traverse = graph->array[i].head;
		if(traverse == NULL)
		{
			printf("--> NULL");
		}
		else
		{
			while(traverse != NULL)
			{
				printf("-->%d ",traverse->data);
				traverse = traverse->next;
			}
		}
		printf("\n");
	}
}

void bellman_ford(struct graph* graph, int src)
{
	int V = graph->V;
	int E = 0;
	int dist[V];
	/*for(int i =0 ;i<V;i++)
	{
		struct node* temp = graph->array[i].head;
		while(temp != NULL)
		{
			E++;
			temp = temp->next;
		}	
	}*/
	
	for(int i=0;i<V;i++)
		dist[i] = 9999;
	
	dist[src] = 0;
}

int main()
{
	int v, ch;
	int src, dest, weight, num_edges;
	printf("\nEnter number of vertices:");
	scanf("%d",&v);
	
	struct graph* graph = create_graph(v);
	
	do
	{
		printf("\n1.Add Edge\n2.Print Graph\n3.Bellman Ford\n4.Exit");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter how many edges you want to add:");
				scanf("%d",&num_edges);
				for(int i=0;i<num_edges;i++)
				{
					printf("\nEnter source, destination and weight:");
					scanf("%d%d%d",&src,&dest,&weight);
					add_edge(graph, src, dest, weight);
				}
				break;
			case 2:
				print_graph(graph, v);
				break;
			case 3:
				bellman_ford(graph,0);
				break;
			default:
				break;
		}
	}while(ch != 4);
	return 0;
}
