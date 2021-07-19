// CVRP

#include<bits/stdc++.h>
using namespace std;

vector<int> G = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};// vector of all vertices including source
int V = G.size();
vector<pair<int, int>> *E = new vector<pair<int, int>>[V];// adjacency list
vector<int> R(V, 0);// vector of requirements storing quantity needed
vector<pair<int, int>> dist(V, std::make_pair(INT_MAX, 0));//stores parent of the visited node with distance
int C = 15;      // carrier capacity
int cost = 0;// total transportation cost
int carriers = 0;// num of carriers required
stack <int> s;// to store path of a particular carrier while backtracking using btrack()
queue <int> q;// to store path of a particular carrier
vector<pair<int, int>> eligibleNodes(V, std::make_pair(INT_MAX, 0));// vector to store distance of all eligible nodes from the current source node

//Declaration of heap
struct Heap
{
    pair<int, int> *array;
    int count, capacity;                                   // capacity = count = num of shops or node
};

//Creating heap
struct Heap* CreateHeap(int capacity)
{
    struct Heap *h = (struct Heap*)malloc(sizeof(struct Heap));
    h->count = 0;
    h->capacity = capacity;
    h->array = (pair<int, int>*)malloc(sizeof(pair<int, int>)*h->capacity);
    return h;
}

// Parent node
int Parent(struct Heap *h, int i)
{
    if(i <= 0 || i >= h->count)
        return -1;
    return (i-1)/2;
}

// Left child
int LeftChild(struct Heap *h, int i)
{
    int left = (2*i)+1;
    if(left >= h->count)
        return -1;
    return left;
} 

// Right child
int RightChild(struct Heap *h, int i)
{
    int right = (2*i)+2;
    if(right >= h->count)
        return -1;
    return right;
} 

// Getting max
std::pair<int, int> GetMaximum(Heap *h)
{
    return std::make_pair(h->array[0].first, h->array[0].second);                         // h->array[0]
}

//Heaping ith element
void PercolateDown(struct Heap *h, int i)
{
    int max;
    int l = LeftChild(h, i);
    int r = RightChild(h, i); 
  
    // If left child is larger than root 
    if (l != -1 && h->array[l].second > h->array[i].second) 
        max = l; 
    else
        max = i;  
    
    if (r != -1 && h->array[r].second > h->array[max].second) 
        max = r; 
  
    // If largest is not root 
    if (max != i)  
    {
        h->array[i].swap(h->array[max]);
        PercolateDown(h, max);    
    }
}

// Delete max
void Pop(struct Heap *h)
{
    h->array[0].swap(h->array[h->count-1]);
    h->count -= 1;
    PercolateDown(h, 0);
}

void ResizeHeap(struct Heap *h)
{
    pair<int, int> *array_old = h->array;                                                      // copying pair
    h->array = (pair<int, int>*)malloc(sizeof(pair<int, int>) * h->capacity * 2);                
    if(h->array == NULL)
    {
        cout << "Memory Error" << endl;
        return;
    }
    for(int i=0;i<h->capacity;i++)
        h->array[i] = array_old[i];
    h->capacity *= 2;                                                        
    free(array_old);                         
}

// Inserting element 
void Push(struct Heap *h, int node, int dist)
{
    int i, pi;
    if(h->count == h->capacity)
        ResizeHeap(h);
    h->count += 1;
    i= h->count - 1;
    while(i > 0 && dist > h->array[(i-1)/2].second)  {
        h->array[i].first = h->array[(i-1)/2].first;
	    h->array[i].second = h->array[(i-1)/2].second;
	    i = (i-1)/2;
    }
    h->array[i] = make_pair(node, dist);
}

// Delete particular node
void DeleteNode(struct Heap *h, int nd)
{
    int i;
    for(i=0;i<h->count;i++)
    {
        if(h->array[i].first == nd)
        {
            h->array[i].swap(h->array[h->count-1]);
            h->count -= 1;
            PercolateDown(h, i);
            break;
        }
    }
}

// IsEmpty
bool IsEmpty(struct Heap *h)
{
    if(h->count == 0)
        return true;
    return false;
}

int btrack(struct Heap *upq,vector<pair<int, int>> &distance, int src, int del, int qty, int tempcap) {
    s.push(del); // push the del into stack first
    R[del] = 0;
    int par = distance[del].second; // parent of node selected for delivery
    int temp = tempcap - qty; // carrier capacity without del's requirement
    while(par != src) {
        if(!temp)
            break;
        if(R[par] > 0 && R[par] <= temp) {
            // Delete par from priority queue
			DeleteNode(upq,par);
            temp -= R[par];
            R[par] = 0; // delivery done to par
            s.push(par); // push par to the stack
        }
        par = distance[par].second; // updating parent(backtracking)
    }    
    while(!s.empty()) { // transfer elements from stack to queue for maintaining sequence of delivery
        int tp = s.top();
        s.pop();
        q.push(tp);
    }
    return temp;
}

void addRequirement(int node, int req) {
    R[node] = req;
}

void addEdge(int u, int v, int wt) // Adding an edge with weight to the graph
{ 
    E[u].push_back(make_pair(v, wt)); 
    E[v].push_back(make_pair(u, wt)); 
}

void shortestPath(vector<pair<int,int>> adj[], vector<pair<int, int>> &distance, int V, int src) { 
    priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq; 
    pq.push(make_pair(0, src)); 
    distance[src].first = 0; 
    distance[src].second = -1;
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
        for (auto x : adj[u]) 
        { 
            int v = x.first;
            int weight = x.second;
            if (distance[v].first > distance[u].first + weight) 
            { 
                distance[v].first = distance[u].first + weight;
                distance[v].second = u;
                pq.push(make_pair(distance[v].second, v)); 
            } 
        } 
    } 
}

int main() {
    
    addEdge(0, 1, 4);
    addEdge(1, 2, 6);
    addEdge(2, 3, 7);
    addEdge(4, 3, 5);
    addEdge(5, 4, 2);
    addEdge(2, 6, 4);
    addEdge(7, 3, 7);
    addEdge(5, 6, 3);
    addEdge(0, 6, 10);
    addEdge(7, 6, 3);
    addEdge(8, 7, 6);
    addEdge(1, 8, 8);
    //addEdge(5, 6, 10);
    addEdge(8, 11, 1);
    addEdge(7, 9, 5);
    addEdge(2, 9, 5);
    addEdge(11, 4, 3);
    addEdge(9, 13, 1);
    addEdge(9, 12, 4);
    addEdge(12, 11, 7);
    addEdge(10, 11, 11);
    addEdge(10, 13, 12);
    shortestPath(E, dist, V, 0); // Find the shortest path for all the nodes 
    addRequirement(2, 9);
    addRequirement(4, 7);
    addRequirement(1, 6);
    addRequirement(11, 7);
    addRequirement(13, 17);
    addRequirement(5, 2);
    addRequirement(7, 22);
    addRequirement(9, 5);
    // Declare Updated Priority Queue upq here.
	struct Heap *upq = CreateHeap(V);
    for(int i = 0; i < R.size(); i++) {
        if(R[i]) {
            if(R[i]/C) {
                carriers += R[i]/C;
                printf("Node %d will recieve %d carriers of full capacity\n", i, R[i]/C);
                cost += (2 * dist[i].first * (R[i]/C));
                R[i] = R[i] % C;
            }
            if(R[i] != 0)
                Push(upq, i, dist[i].first);// Push it into the upq
        }
    }
    while(!IsEmpty(upq)/*while upq is not empty*/) {
        pair<int, int> delivery = GetMaximum(upq);// upq's top
        Pop(upq);// pop from upq
        cost += delivery.second;
        int del_f = delivery.first;
        int tempcap = btrack(upq, dist, 0, del_f, R[del_f], C);//remaining carrier capacity after delivering to selected node and it's parent.
        if(tempcap != 0) {
            while(tempcap) {
    			// erase the eligibleNodes vector
    			eligibleNodes.clear();
    			for(int i = 0; i < V; i++) {
    			    eligibleNodes.push_back(make_pair(INT_MAX, del_f));
    			}
    			shortestPath(E, eligibleNodes, V, del_f);// find and store all the eligible nodes in the global map declared and their shortest distance in it.
    			    int del_n;
    			    int min = INT_MAX;
    			    int sum = min;
    			    for(int i = 1; i < V; i++) {
    			        if(R[i] <= tempcap && R[i] > 0 && i != del_f) {
        			        sum = eligibleNodes[i].first + dist[i].first;
        			        if(sum < min) {
        			            min = sum;
        			            del_n = i;
        			        }
        			        else if(sum == min) {
        			            if(eligibleNodes[i].first < eligibleNodes[del_n].first) {
        			                del_n = i;
        			            }
        			        }
    			        }
    			    }
    			    if(min != INT_MAX) {
        			    cost += eligibleNodes[del_n].first;
        			    // delete del_n from upq;
    					DeleteNode(upq, del_n);
    					int x = tempcap;
        			    tempcap = btrack(upq, eligibleNodes, del_f, del_n, R[del_n], x);
        			    del_f = del_n;
    			    }
    			    else
    			        break;
    		}
        }
		cost += dist[del_f].first;
        carriers++;
        printf("The route for carrier %d is : 0 => ", carriers);
        while(!q.empty()) {
            int tp = q.front();
            q.pop();
            printf("%d => ", tp);
        }
        printf("0\n");
    }
    printf("All the retailers have received their order with total cost = %d", cost);
    return 0;
}
