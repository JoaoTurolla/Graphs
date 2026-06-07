#ifndef vertice_HPP
#define vertice_HPP


#include <string>
#include <vector>
#include <ostream>

class Vertice{
   public:
   
   int id;//Também funciona como um índice para o local em que o vértice está salvo na lista de vértices do grafo
   std::pair<int, int> degree;//degree.first é o grau de entrada ou o grau total, dependendo do tipo de grafo, degree.second é sempre o grau de saída;
   std::vector<std::pair<float, int>> allEdges;//allEdges[0].first é o peso da aresta, allEdges[0].second é o id do vertice final da aresta
   std::vector<bool> adjacencyArray;
   std::string userName;

   Vertice(int idAssign = -1, std::string userN = ""){
      Setup(idAssign, userN);
   };

   void Setup(int idAssign, std::string userN);

   friend std::ostream& operator<<(std::ostream& os, Vertice &vTP);

};

#endif