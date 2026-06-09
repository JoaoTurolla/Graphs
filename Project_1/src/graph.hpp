#ifndef graph_HPP
#define graph_HPP

#include "vertice.hpp"

class Graph{
   public:
   
   int verticeNum;
   int edgeNum;
   char type;
   bool hasWeight;
   std::vector<Vertice> verticeList; //store vertices in order they are found
   
   Graph(int v = 0, int e = 0, char t = 'G', bool hW = false){
      Setup(v, e, t, hW);
   }
   
   Graph& operator>>(std::vector<bool>& adjM);
   
   void Setup(int verts, int edges, char t, bool hW);
   
   friend void degreeCalc(Graph& gI);
   
   friend std::ostream& operator<<(std::ostream& os, Graph &gTP);

   friend std::vector<int> primMST(const Graph &gI, const Vertice &r);

   friend std::vector<std::pair<float, int>> djikstra(const Graph &gI, const Vertice &sP);

   friend std::vector<std::pair<int, int>> BFS(const Graph &gI, const Vertice &sP);

   friend std::vector<std::pair<float, int>> DFS(const Graph &gI, const Vertice &sP); //Definetely not final

};


#endif 