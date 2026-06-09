#include "graph.hpp"
#include <iostream>
#include <queue>

void Graph::Setup(int verts, int edges, char t, bool hasW){
   verticeNum = verts;
   edgeNum = edges;
   type = t;
   hasWeight = hasW;

   verticeList.reserve(verticeNum);
}

std::ostream& operator<<(std::ostream& os, const Graph& graphToPrint){//Imprime o grafo (Não termina a linha com \n)
   os << "Total de vértices: " << graphToPrint.verticeNum 
      << " |Total de arestas: " << graphToPrint.edgeNum 
      << " |Tipo: " << graphToPrint.type 
      << " |Arestas têm peso (1 - Sim; 0 - Não): " << graphToPrint.hasWeight
   ;
   return os;
}

Graph& Graph::operator>>(std::vector<bool>& adjacencyMatrixOutput){//Cria a matriz de adjacência com base no grafo provido
   adjacencyMatrixOutput.reserve(this->verticeNum * this->verticeNum);
   for(const Vertice& v: this->verticeList){
      for(bool b: v.adjacencyArray){
         adjacencyMatrixOutput.push_back(b);
      }
   }

   return *this;
} 

void degreeCalc(Graph& graphInput){//Calcula o grau de todos os vértices. Armazena em [0] se type == 'G' e armazena grau de entrada em [0] e grau de saída em [1] se type == 'D'
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

   } else {
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
   using anyEdge = std::pair<float, int>; //float -> Peso da aresta, int -> Índice do vértice final da aresta

   const float INF = std::numeric_limits<float>::infinity();

   std::vector<bool> inMST(graphInput.verticeNum, false);
   std::vector<int> piVector(graphInput.verticeNum, -1);
   std::vector<float> keyVector(graphInput.verticeNum, INF); 
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
   using distPiPair = std::pair<float, int>;//float -> distância, int -> ID/Índice do vértice pai

   const float INF = std::numeric_limits<float>::infinity();

   std::vector<distPiPair> distPiVector(graphInput.verticeNum, {INF, -1});
   std::vector<bool> visited(graphInput.verticeNum, false);
   std::priority_queue<distPiPair, std::vector<distPiPair>, std::greater<distPiPair>> pq;

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
   using distPiPair = std::pair<int, int>;//int -> distância, int -> ID/Índice do vértice pai

   const int INF = std::numeric_limits<int>::max();

   std::vector<distPiPair> distPiVector(graphInput.verticeNum, {INF, -1});
   std::vector<char> visitStatus(graphInput.verticeNum, 'w');
   std::queue<int> q;

   visitStatus[startingPoint.id] = 'g';
   distPiVector[startingPoint.id] = {0, -1};

   q.push(startingPoint.id);

   while(!q.empty()){
      int u = q.front();
      q.pop();

      for(const std::pair<float, int> &edge: graphInput.verticeList[u].allEdges){
         int v = edge.second;
         if(v == u) continue;//Arestas que tem como destino o vértice de origem devem ser pulados para evitar distâncias erráticas

         if(visitStatus[v] == 'w'){
            visitStatus[v] = 'g';
            distPiVector[v].first = distPiVector[u].first + 1;
            distPiVector[v].second = u;
            q.push(v);
            
         }
      }
      
      visitStatus[u] = 'b';

   }

   return distPiVector;
}

