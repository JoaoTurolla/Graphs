#include <iostream>
#include "graph.hpp"
#include "vertice.hpp"
#include "fileHandler.hpp"

int main(){

   int errorFileQuantity = 18;

   Graph Test;
   std::string errorFileNames[errorFileQuantity] = {
      ".././errorFiles/error1File.txt", ".././errorFiles/error2File.txt", ".././errorFiles/error3File.txt", ".././errorFiles/error4File.txt",
      ".././errorFiles/error5File.txt", ".././errorFiles/error6File.txt", ".././errorFiles/error7File.txt", ".././errorFiles/error8File.txt", 
      ".././errorFiles/error9File.txt", ".././errorFiles/error10File.txt", ".././errorFiles/error11File.txt", ".././errorFiles/error12File.txt", 
      ".././errorFiles/error13File.txt", ".././errorFiles/error14File.txt", ".././errorFiles/error15File.txt", ".././errorFiles/error16File.txt",
      ".././errorFiles/error17File.txt", ".././errorFiles/error18File.txt" 
   }; 

   for(int i = 0; i < errorFileQuantity; i++){
      int readNamePtr = 0, writeNamePtr = 0;
      char fileOpening[50]; 

      while(errorFileNames[i][readNamePtr] != '\0'){
         fileOpening[writeNamePtr] = errorFileNames[i][readNamePtr];
         
         readNamePtr++;
         writeNamePtr++;

      }
      std::cout << "Iteração: " << i + 1 << "\n";
      graphInfoReading(fileOpening, Test);
      std::cout<< "\n";
   }
}