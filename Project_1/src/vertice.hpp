#ifndef vertice_HPP
#define vertice_HPP


#include <string>
#include <vector>
#include <ostream>

class Vertice{
   public:
   
   int id;//Also works as an index to where it's stored on the graph
   std::pair<int, int> degree;//degree.first is the in-degree or the total degree depending on the type of graph, degree.second is always out-degree;
   std::vector<std::pair<float, int>> allEdges;//allEdges[0].first is the weight of the edge, allEdges[0].second is the target vertice id
   std::vector<bool> adjacencyArray; //Stores if there is an edge between this vertice and the one represented by adjacencyArray[i], where i == anotherVertice.id
   std::string userName;

   Vertice(int idAssign = -1, std::string userN = ""){
      Setup(idAssign, userN);
   };

   void Setup(int idAssign, std::string userN);

   friend std::ostream& operator<<(std::ostream& os, Vertice &vTP);

};

#endif