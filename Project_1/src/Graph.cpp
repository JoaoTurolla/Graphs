#include "graph.hpp"
#include <queue>
#include <iostream>
#include <stack>

using distPiPair_1 = std::pair<float, int>;//float -> distance, int -> ID/Index of the parent vertice
using distPiPair_2 = std::pair<int, int>;//int -> distance, int -> ID/Index of the parent vertice

const int INF_I = std::numeric_limits<int>::max();
const float INF_F = std::numeric_limits<float>::infinity();

void Graph::Setup(int verts, int edges, char t, bool hasW){
   verticeNum = verts;
   edgeNum = edges;
   type = t;
   hasWeight = hasW;

   verticeList.reserve(verticeNum);
}

std::ostream& operator<<(std::ostream& os, Graph& graphToPrint){//Prints the graph (does not end the line)
   os << "Vertice total: " << graphToPrint.verticeNum 
      << " |Edge total: " << graphToPrint.edgeNum 
      << " |Type: " << graphToPrint.type 
      << " |Has weight: " << graphToPrint.hasWeight
   ;
   return os;
}

Graph& Graph::operator>>(std::vector<bool>& adjacencyMatrixOutput){//Creates the adjacency matrix based on the graph provided
   adjacencyMatrixOutput.reserve(this->verticeNum * this->verticeNum);
   for(const Vertice& v: this->verticeList){
      for(bool b: v.adjacencyArray){
         adjacencyMatrixOutput.push_back(b);
      }
   }

   return *this;
} 

void degreeCalc(Graph& graphInput){//Calculates the degree of all vertices; Stores in [0] if type == 'G' and stores in-degree in [0] out-degree in [1] if type == 'D'
   int auxInDegree = 0, auxOutDegree = 0;
   std::pair<int, int> endDegree;

   if(graphInput.type == 'G'){
      for(Vertice &v: graphInput.verticeList){
         auxInDegree = 0;
         for(int i = 0; i < v.allEdges.size(); i++){
            if(v.allEdges[i].first == v.id){
               auxInDegree += 2;
            } else{
               auxInDegree++;
            };
         }

         v.degree.first = auxInDegree;

      }

   } else{
      for(Vertice &v: graphInput.verticeList){
         auxInDegree = 0, auxOutDegree = 0;
         for(int i = 0; i < v.allEdges.size(); i++){
            if(v.allEdges[i].first == v.id){
               auxInDegree++;
               auxOutDegree++;
            } else{
               graphInput.verticeList[v.allEdges[i].first].degree.first += 1;
               auxOutDegree++;
            } 
         }

         v.degree.first += auxInDegree;
         v.degree.second += auxOutDegree;
      }
   }

   return;
}

std::vector<int> primMST(const Graph &graphInput,const Vertice &root){   
   using anyEdge = std::pair<float, int>; //float -> Edge Weight, int -> target Vertice Idx

   std::vector<bool> inMST(graphInput.verticeNum, false);
   std::vector<int> piVector(graphInput.verticeNum, -1);
   std::vector<float> keyVector(graphInput.verticeNum, INF_F); 
   std::priority_queue<anyEdge, std::vector<anyEdge>, std::greater<anyEdge>> pq;

   pq.push({0, root.id});

   while(!pq.empty()){
      int u = pq.top().second;
      pq.pop();

      if(inMST[u]) continue;


      inMST[u] = true;

      for(const anyEdge &e: graphInput.verticeList[u].allEdges){
         float weight = e.first;
         int v = e.second;

         if(!inMST[v] && weight < keyVector[v]){
            keyVector[v] = weight;
            piVector[v] = u;
            pq.push({keyVector[v], v});
         }
      }
   }

   return piVector;
}

std::vector<std::pair<float, int>> djikstra(const Graph &graphInput, const Vertice &startingPoint){
   std::vector<distPiPair_1> distPiVector(graphInput.verticeNum, {INF_F, -1});
   std::vector<bool> visited(graphInput.verticeNum, false);
   std::priority_queue<distPiPair_1, std::vector<distPiPair_1>, std::greater<distPiPair_1>> pq;

   distPiVector[startingPoint.id].first = 0.0f;
   pq.push({0, startingPoint.id});

   while(!pq.empty()){
      int u = pq.top().second;
      pq.pop();

      if(visited[u]) continue;

      visited[u] = true;

      for(const std::pair<float, int> &edge: graphInput.verticeList[u].allEdges){
         float weight = edge.first;
         int v = edge.second;

         if(distPiVector[v].first > distPiVector[u].first + weight){
            distPiVector[v].first = distPiVector[u].first + weight;
            distPiVector[v].second = u;
            pq.push({distPiVector[v].first, v});
         }
      }
   }

   return distPiVector;

}

std::vector<std::pair<int, int>> BFS(const Graph &graphInput, const Vertice &startingPoint){
   std::vector<distPiPair_2> distPiVector(graphInput.verticeNum, {INF_I, -1});
   std::vector<char> visitStatus(graphInput.verticeNum, 'w');
   std::queue<int> q;

   visitStatus[startingPoint.id] = 'g';
   distPiVector[startingPoint.id] = {0, -1};

   q.push(startingPoint.id);

   std::cout 
      << "\n"
      << "Visit order: <<"
      << "\n"
   ;

   while(!q.empty()){
      int u = q.front();
      q.pop();

      std::cout << u << " -> ";

      for(const std::pair<float, int> &edge: graphInput.verticeList[u].allEdges){
         int v = edge.second;
         if(v == u) continue;//Edges that have the origin vertice as the target vertice should be skipped to avoid adding +1 to the distance incorrectly 

         if(visitStatus[v] == 'w'){
            visitStatus[v] = 'g';
            distPiVector[v].first = distPiVector[u].first + 1;
            distPiVector[v].second = u;
            q.push(v);
            
         }
      }
      
      visitStatus[u] = 'b';

   }

   std::cout << "END\n";

   return distPiVector;
}

std::vector<std::tuple<int, int, int>> DFS(const Graph &graphInput, const Vertice &startingPoint){
   using DFSTuple = std::tuple<int, int, int>;//int -> time of discovery, int -> time of finalization, int -> ID/Idx of parent Vertice
   
   std::vector<char> visitStatus(graphInput.verticeNum, 'w');
   std::vector<DFSTuple> DFSReturn(graphInput.verticeNum, {0, 0, -1});
   std::stack<int> s;
   int timer = 0;

   s.push(startingPoint.id);
   visitStatus[startingPoint.id] = 'g';
   timer++;
   
   std::get<0>(DFSReturn[startingPoint.id]) = timer;

   std::cout
      << "\n"
      << "Visit order:"
      <<"\n"
   ;

   while(!s.empty()){
      int u = s.top();
      bool divedDeeper = false;

      std::cout << u << " -> ";

      for(const std::pair<float, int> &edge: graphInput.verticeList[u].allEdges){
         int v = edge.second;

         if(visitStatus[v] == 'w'){
            visitStatus[v] = 'g';
            std::get<2>(DFSReturn[v]) = u;
            
            timer++;
            std::get<0>(DFSReturn[v]) = timer;
            
            s.push(v);
            divedDeeper = true;

            break;
         }
      }

      if(!divedDeeper){
         s.pop();
         visitStatus[u] = 'b';

         timer++;
         std::get<1>(DFSReturn[u]) = timer;
      }
   }

   std::cout << "END\n";
   
   return DFSReturn;
}