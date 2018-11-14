/*  Applies BFS from both source and destination side and checks after each iteration ,
if the visited list from each side are intersecting at any point. If yes, then thats the meeting point and gives
the path from source to that point and from that point to destination. */

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<stdlib.h>
using namespace std;

class Graph
{
  int V;
  vector<int> *adj;
  vector<int> *wgt;
public:
  Graph(int V);
  void addEdge(int v, int w, int wgt);
  void BDS(int s, int t);
  void BFS(list<int> *queue, bool *visited, int *prev);
  int visitedIntersect(bool *s_visited, bool *t_visited);
  void displayPathBDS(int s, int t, int *s_prev,int *t_prev, int m_p);
  void displayQueue(list<int> queue);
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new vector<int>[V];
  wgt = new vector<int>[V];
}

void Graph::addEdge(int v, int w, int wt) {
  adj[v].push_back(w);
  wgt[v].push_back(wt);
  adj[w].push_back(v);
  wgt[w].push_back(wt);
}

int Graph::visitedIntersect(bool *s_visited, bool *t_visited)
{
  int j;
  for(j = V-1; j >= 0; j--)
  {
    if(s_visited[j] && s_visited[j] == t_visited[j])
    return j;
  }
  return -1;
}

void Graph::BDS(int s, int t){
  bool *s_visited = new bool[V];
  bool *t_visited = new bool[V];
  int *s_prev = new int[V];
  int *t_prev = new int[V];
  int meet_pt = -1;

  for (int i = 0; i < V; ++i) {
    s_visited[i] = false;
    t_visited[i] = false;
  }

  list<int> s_queue, t_queue;

  s_visited[s] = true;
  s_prev[s] = -1;
  s_queue.push_back(s);

  t_visited[t] = true;
  t_prev[t] = -1;
  t_queue.push_back(t);

  while(!s_queue.empty() && !t_queue.empty())
  {
    //from front
    BFS(&s_queue, s_visited, s_prev);
    //from back
    BFS(&t_queue, t_visited, t_prev);
    //  cout<<"Mani at line 80";
    meet_pt = visitedIntersect(s_visited, t_visited);
    if(meet_pt != -1)
    {
      cout<<"Intersect at "<<meet_pt;
      displayPathBDS(s, t, s_prev, t_prev, meet_pt);
      exit(0);
    }
  }
}
void Graph::BFS(list<int> *queue, bool *visited, int *prev) {
  displayQueue(*queue);
  int current = queue->front();
  queue->pop_front();
  vector<int>::iterator i;
  for (i = adj[current].begin(); i != adj[current].end(); ++i)
  {
    if(!visited[*i])
    {
      cout<<current;
      prev[*i] = current;
      visited[*i] = true;
      queue->push_back(*i);
    }
  }
}
void Graph::displayPathBDS(int s, int t, int *s_prev,int *t_prev, int m_pt)
{
  
  int p,q,pos,pathlen = 0;
  int *prev;
  vector<int> result;
  cout<<"\nPath is: ";
  int count = 2;
  prev = s_prev;
   // cout<<"Mani at line 114";
  while(count-->0)
  {
    p = m_pt;
    while(p!=-1)
    {
      result.push_back(p);
      q = prev[p];
      if(q!=-1)
      {
        pos = find(adj[p].begin(), adj[p].end(), q) - adj[p].begin();
        pathlen = pathlen + wgt[p].at(pos);
      }
      p = q;
    }
    prev = t_prev;
  }

  vector<int>::iterator i;
  for(i = result.begin()+1; i!=result.end();i++)
  {
    cout<<"->"<<*i;
  }

  cout<<endl;
  cout<<"pathlength : "<<pathlen;
  cout<<endl;
}

void Graph::displayQueue(list<int> queue)
{
  cout<<"\nqueue:";
  list<int>::iterator i;
  for(i = queue.begin(); i != queue.end(); ++i)
  {
    cout<<(*i)<<" ";
  }
  cout<<"\n";
}

int main()
{
 // cout<<"Mani at line 154";
  int n = 16;
  Graph g(n);
  g.addEdge(0, 1, 12);
  g.addEdge(0, 2, 8);
  g.addEdge(0, 3, 7);
  g.addEdge(1, 4, 8);
  g.addEdge(1, 5, 7);
  g.addEdge(2, 6, 6);
  g.addEdge(2, 7, 5);
  g.addEdge(3, 8, 4);
  g.addEdge(3, 9, 3);
  g.addEdge(9, 10, 3);
  g.addEdge(9, 11, 3);
  g.addEdge(10, 12, 4);
  g.addEdge(10, 13, 3);
  g.addEdge(11, 14, 3);
  g.addEdge(11, 15, 3);
  g.BDS(0, 12);
 
  return 0;
}

/*
Running on Linux/Unix System :-
step 1 :- Open Terminal.
step 2 :- Go to directory where file is saved
step 3 :- Command for compile g++ filename.cpp
step 4 :- Command to run ./a.out.

output:- Results the shortest path lenght between two vertices
*/

/* Running in Microsoft Visual Studio :-

If you want to build a sample with Microsoft Visual Studio, then you need to create a project and copy the sample into that project by your own.
In order to build each sample, simply cd to its directory and run make to build the required executable. 
Run make clean to clean-up your directory. Also make full, first cleans and then rebuilds each sample. */

