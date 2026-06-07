#include "vertice.hpp"

void Vertice::Setup(int idAssign, std::string userN){
   id = idAssign;
   userName = userN;

}

std::ostream& operator<<(std::ostream& os, Vertice &vertToPrint){//Imprime o vértice no console (Encerra a linha com "\n" no final)
   os << "ID do vértice: " << vertToPrint.id << " | Nome dado pelo usuário: " << vertToPrint.userName << "\n";
   
   if(vertToPrint.allEdges.empty()){
      os << "Esse vértice não tem arestas.\n";
      return os;

   }

   if(vertToPrint.allEdges[0].second != std::numeric_limits<float>::infinity()){
      os << "Este vértice é adjacente aos vértices correspondentes aos IDs: " << "\n";

      for(int i = 0; i < vertToPrint.allEdges.size(); i++){
         os << vertToPrint.allEdges[i].second << " | Peso da aresta: " << vertToPrint.allEdges[i].first << "\n";
      }
      
   } else {
      os << "Este vértice é adjacente aos vértices correspondentes aos IDs: " << "\n";

      for(int i = 0; i < vertToPrint.allEdges.size(); i++){
         os << vertToPrint.allEdges[i].second << "\n";      
      }

   }

   return os;

}