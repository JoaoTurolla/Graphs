#include "vertice.hpp"

void Vertice::Setup(int idAssign, std::string userN){
   id = idAssign;
   userName = userN;

}

std::ostream& operator<<(std::ostream& os, Vertice &vertToPrint){//Prints the vertice (Does end the line)
   os 
      << "Vertice ID: " << vertToPrint.id << " | Name given by user: " << vertToPrint.userName << "\n"
      << "This vertice is adjacent to the vertices that hold the following IDs: " << "\n"
   ;
   
   if(vertToPrint.allEdges.empty()){
      os << "This vertice has no edges.\n";
      return os;

   }

   if(vertToPrint.allEdges[0].second != std::numeric_limits<float>::infinity()){
      for(int i = 0; i < vertToPrint.allEdges.size(); i++){
         os << vertToPrint.allEdges[i].second << " | Edge weight: " << vertToPrint.allEdges[i].first << "\n";
      }
      
   } else {
     for(int i = 0; i < vertToPrint.allEdges.size(); i++){
         os << vertToPrint.allEdges[i].second << "\n";      
      }

   }

   return os;

}