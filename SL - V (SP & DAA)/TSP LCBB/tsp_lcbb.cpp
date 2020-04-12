/*
  Name		: Kalpit R. Choudhari
  Roll Number	: 33315
  Batch		: K-11
  Assignment	: Travelling Salesman Problem using Branch and Bound (LCBB)

  Input Matrix	:
  			INF  20  30  10  11
  			15  INF  16  4   2
  			3    5  INF  2	 4
  			19   6  18  INF  3
  			16   4   7   16  INF
  Output	: Path And Minimum Cost (With all phases)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
using namespace std;
#define N 5
#define INF INT_MAX
struct Node
{
   
    vector<pair<int, int>> path;
    int reducedMatrix[N][N],cost,vertex,level;

};

void Input(int Matrix[N][N])
{

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)
			{
				Matrix[i][j]=INF;
			}
			else
			{
				scanf("%d",&Matrix[i][j]);
			}
		}	
	}
}
void display(int Matrix[N][N])
{
	for(int i=0;i<N;i++)
	{
		cout<<"\n";
		for(int j=0;j<N;j++)
		{
			if(Matrix[i][j]==INT_MAX)
				cout<<"INF"<<"\t";
			else
			cout<<Matrix[i][j]<<"\t";
		}
	}
	
}

Node* newNode(int parentMatrix[N][N], vector<pair<int, int>> const &path,
            int level, int i, int j)
{
    Node* node = new Node;
    node->path = path;
    if (level != 0)
        node->path.push_back(make_pair(i, j));

    memcpy(node->reducedMatrix, parentMatrix,
        sizeof node->reducedMatrix);

    for (int k = 0; level != 0 && k < N; k++)
    {
       
        node->reducedMatrix[i][k] = INF;
        node->reducedMatrix[k][j] = INF;
    }

 
    node->reducedMatrix[j][0] = INF;
    node->level = level;
	 node->vertex = j;
    return node;
}

int rowReduction(int reducedMatrix[N][N], int row[N])
{
   for(int i=0;i<N;i++)
	row[i]=INF;

  cout<<"\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < row[i])
                row[i] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && row[i] != INF)
                reducedMatrix[i][j] -= row[i];

	printf("Row Reduced Matrix:");
	display(reducedMatrix);
	printf("\n");
}


int columnReduction(int reducedMatrix[N][N], int col[N])
{
 
  for(int i=0;i<N;i++)
	col[i]=INF;
 
	cout<<"\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < col[j])
                col[j] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && col[j] != INF)
                reducedMatrix[i][j] -= col[j];
	printf("Column Reduced Matrix:");
	display(reducedMatrix);
	printf("\n");
}


int calculateCost(int reducedMatrix[N][N])
{
   int cost = 0;
	int row[N];
    rowReduction(reducedMatrix, row);

    int col[N];
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < N; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (col[i] != INT_MAX) ? col[i] : 0;

    return cost;
}

void printPath(vector<pair<int, int>> const &list)
{
    for (int i = 0; i < list.size(); i++)
        cout << list[i].first + 1 << " ----> "<< list[i].second + 1 << endl;
}


struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

int solve(int costMatrix[N][N])
{
   
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    vector<pair<int, int>> v;
    Node* root = newNode(costMatrix, v, 0, -1, 0);
    root->cost = calculateCost(root->reducedMatrix);
    pq.push(root);
    while (!pq.empty())
    {
       
        Node* min = pq.top();  
        pq.pop();
        int i = min->vertex;

       
        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));
		
	    printPath(min->path);
	cout<<"Minimum Cost is:";
	    return min->cost;
        }

        for (int j = 0; j < N; j++)
        {
		
            if (min->reducedMatrix[i][j] != INF)
            {
                Node* child = newNode(min->reducedMatrix, min->path,
                    min->level + 1, i, j);

                child->cost = min->cost + min->reducedMatrix[i][j]
                            + calculateCost(child->reducedMatrix);
                pq.push(child);
            }
        }
	delete min;
    }
}
// main function
int main()
{
	int costMatrix[N][N];
   	printf("Enter Cost matrix\n");
	Input(costMatrix);
	cout<<"Cost Matrix:";
	display(costMatrix);
	cout<<"\n";
   	cout<<solve(costMatrix)<<"\n";
	
    return 0;
}
