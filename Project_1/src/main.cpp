#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "vertice.hpp"
#include "fileHandler.hpp"

void printFilesInMemory(std::vector<std::string> mem){
   for(int i = 0; i < mem.size(); i++){
      std::cout << "Index " << i << " :" << mem[i] << "\n";
   }
}

void djikstraPathPrint(const int startVertice, const int currentVertice, const std::vector<std::pair<float, int>> &djikstraResult){
   int parentId = djikstraResult[currentVertice].second;

   if(parentId == startVertice){
      std::cout << startVertice << " -> " << currentVertice;
      return;
   }

   if (parentId == -1){
      if (djikstraResult[currentVertice].first == 0) {
         std::cout << currentVertice; 
      } else{
         std::cout << "There is no path to this vertice\n";
      }
      return; 

   }

   djikstraPathPrint(startVertice, parentId, djikstraResult);

   std::cout << " -> " << currentVertice;
   return;
}

int main(){
   std::vector<Graph> graphMemory;
   std::vector<std::string> filesLoadedMemory, matrixesFileNamesLoadedMemory;
   std::vector<std::vector<bool>> adjacencyMatrixMemory;
   std::vector<bool> auxAdjacencyMatrix;
   std::vector<int> treePiVectorMemory;
   std::vector<std::pair<float, int>> djikstraMemory;
   int control = 0, subcontrol = 0, thirdControl = 0, fourthControl;
   Graph auxGraph;
   char fileName[100];

   while(control != -1){
      std::cout 
         << "-------------------------------------------\n" 
         << "Your options are:\n"
         << "-1 - Close the program\n"
         << " 1 - Read a file to load your graph into the memory\n"
         << " 2 - Write your graph data to make a correctly formatted file\n"
         << " 3 - Print a loaded graph on the console\n"
         << " 4 - Create and/or load in memory the adjacency matrix of a graph loaded in memory\n" 
         << " (You can opt to save the matrix in a file)\n"
         << " 5 - Print a loaded matrix on the console\n"
         << " 6 - Calculate the degree of each vertice\n"
         << " 7 - Find the minimum spanning tree of a graph loaded in memory\n"
         << " 8 - Apply Djikstra's algorithm to a graph loaded in memory\n"
         << " 9 - \n"
         << "10 - \n"
         << "\n" //Kept isolated to make it easier to add new options
      ;

      std::cin >> control;

      if(control == 1){
         std::string fileNameS;
         std::cout  
            << "-------------------------------------------\n" 
            << "Enter the file name/file path: \n"
            << "\n"
         ;

         std::cin >> fileNameS;
         int readPtr = 0, writePtr = 0;
         
         while(fileNameS[readPtr] != '\0'){
            fileName[writePtr] = fileNameS[readPtr];
            readPtr++;
            writePtr++;
            
         }
         
         fileName[writePtr] = '\0';
         
         int fileDiagnose = graphDiagnose(fileName);
         
         if(fileDiagnose == -3) return 1;
         else if(fileDiagnose == -2) return 1;
         else if(fileDiagnose == -1) return 1;
         else if(fileDiagnose == 1) graphInfoReading(fileName, auxGraph);
         else if(fileDiagnose == 2) digraphInfoReading(fileName, auxGraph);    
         
         graphMemory.push_back(auxGraph);
         auxGraph.Setup(0 , 0, 'g', false);
         filesLoadedMemory.push_back(fileNameS);

         std::cout 
            << "\n" 
            << "Successfuly loaded the graph to the memory\n"
            << "\n"
         ;

      } else if(control == 2){
         std::string fileToWriteS;
         char fileToWriteName[100];
         int readNamePtr = 0, writeNamePtr = 0;

         std::cout 
            << "-------------------------------------------\n"
            << "Name the file/path to the file (100 characters max): \n"
            << "\n"
         ;
         std::cin >> fileToWriteS;

         while(fileToWriteS[readNamePtr] != '\0'){
            fileToWriteName[writeNamePtr] = fileToWriteS[readNamePtr];
         
            readNamePtr++;
            writeNamePtr++;

         }

         if(!formattedFileWriter(fileToWriteName)){
            return 1;
         };

         std::cout 
            << "\n" 
            << "Successfully wrote and saved the file\n"
            << "\n"
         ;

      } else if(control == 3){
         while(true){
            std::cout  
               << "-------------------------------------------\n" 
               << "What's the index of the graph you wish to print on the console? (Choose by index): \n"
               << "-2 if you want to remember where each graph was saved\n"
               << "-1 if you want to leave this option\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < graphMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if (subcontrol > 0){
                  std::cout 
                     << "\n" 
                     << "-------------------------------------------\n"  
                     << graphMemory[subcontrol] << "\n"
                     << "-------------------------------------------\n"
                  ;

                  for(int i = 0; i < graphMemory[subcontrol].verticeList.size(); i++){
                     std::cout 
                        << graphMemory[subcontrol].verticeList[i]
                        << "-------------------------------------------\n"
                     ;
                  }

                  std::cout 
                     << "\n" 
                     << "Successfully printed the graph and its vertices\n"
                     << "\n"
                  ;

                  break;

               } else {
                  std::cout << "Invalid input, try again: \n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Invalid input, try again:\n";

            }
         }

      } else if(control == 4){
         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Which graph will have it's matrix done? (Choose by index)\n"
               << "-2 if you want to remember where each graph was saved\n"
               << "-1 if you want to leave this option\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < graphMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if (subcontrol == -1){
                  break;

               } else if(subcontrol > 0){
                  graphMemory[subcontrol] >> auxAdjacencyMatrix;//Creates adjacency matrix

                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "1 - Save the adjacency matrix on a file besides the memory\n"
                        << "2 - Save the adjacency matrix only in memory\n"
                        << "3 - save the adjacency matrix only in a file\n"
                        << "\n"
                     ;

                     if(std::cin >> thirdControl){
                        if(thirdControl == 1){
                           std::string fileNameS;
                           std::cout  
                              << "-------------------------------------------\n" 
                              << "Enter the file name/file path to save the adjacency matrix: \n"
                              << "\n"
                           ;

                           std::cin >> fileNameS;
                           int readPtr = 0, writePtr = 0;
         
                           while(fileNameS[readPtr] != '\0'){
                              fileName[writePtr] = fileNameS[readPtr];
                              readPtr++;
                              writePtr++;
                  
                           }
               
                           fileName[writePtr] = '\0';

                           
                           if(!adjacencyMatrixFileWriter(fileName, auxAdjacencyMatrix)) std::cerr << "CRITICAL ERROR: could not create file";
                           matrixesFileNamesLoadedMemory.push_back(fileNameS);
                           adjacencyMatrixMemory.push_back(std::move(auxAdjacencyMatrix)); 
                           //CUIDADO EXTREMO!! auxAdjacencyMatrix TEM TAMANHO 0 APOS ESSA LINHA, NAO TENTE ACESSAR NADA POR INDICE
                           //Como so sao utilizados push_backs e loops baseados no tamanho atual do vector, nao ocorrerao erros neste programa, mas fica o aviso
                           //caso queira replicar. Isso acontece pois std::move rouba o ponteiro do inicio do vector auxAdjacencyMatrix e entrega para adjacencyMatrixMemory[0]
                           //movendo assim o vector inteiro em tempo mínimo e igual independentemente do tamanho de auxAdjacencyMatrix pois nao ha realocacao de memoria. 
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Successfully created the adjacency matrix, loaded in memory and saved it in a file\n"
                              << "\n"
                           ;

                           break;

                        } else if(thirdControl == 2){
                           adjacencyMatrixMemory.push_back(std::move(auxAdjacencyMatrix));
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Succesfully created the adjacency matrix and loaded it in the memory\n"
                              << "\n"
                           ;
                           break;

                        } else if(thirdControl == 3){
                           std::string fileNameS;
                           std::cout  
                              << "-------------------------------------------\n" 
                              << "Enter the file name/file path to save the adjacency matrix: \n"
                              << "\n"
                           ;

                           std::cin >> fileNameS;
                           int readPtr = 0, writePtr = 0;
               
                           while(fileNameS[readPtr] != '\0'){
                              fileName[writePtr] = fileNameS[readPtr];
                              readPtr++;
                              writePtr++;
                  
                           }
               
                           fileName[writePtr] = '\0';

                           if(!adjacencyMatrixFileWriter(fileName, auxAdjacencyMatrix)) std::cerr << "CRITICAL ERROR: could not create file" <<std::endl;
                           matrixesFileNamesLoadedMemory.push_back(fileNameS);
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Successfuly created the adjacency matrix and stored it in a file named: " << fileName << "\n"
                              << "\n"
                           ;

                           break;

                        } else{
                           std::cout << "Invalid input, try again:\n";

                        }
                     } else{
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Invalid input, try again:\n";

                     }
                  }

                  break;

               } else{
                  std::cout << "Invalid input, try again:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Invalid input, try again:\n";

            }

         }

      } else if(control == 5){

         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Which matrix will be printed? (Choose by index)\n"
               << "-2 if you want to remember where each matrix was saved\n"
               << "-1 if you want to leave this option\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < adjacencyMatrixMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(matrixesFileNamesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol > 0){
                  int8_t colTotal = sqrt(adjacencyMatrixMemory[subcontrol].size()), auxCol = 0;
                  std::cout << "\n";
                  for(bool b: adjacencyMatrixMemory[subcontrol]){
                     std::cout << "<" << b << ">";
                     auxCol++;
                     if(auxCol == colTotal){
                        auxCol = 0;
                        std::cout <<"\n";
                     }
                  }

                  break;

               } else {
                  std::cout << "Invalid input, try again:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Invalid input, try again:\n";

            }
         }

      } else if(control == 6){

         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Which graph will have it's vertices degree calculated? (Choose by index)\n"
               << "-2 if you want to remember where each graph was saved\n"
               << "-1 if you want to leave this option\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < graphMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol > 0){
                  degreeCalc(graphMemory[subcontrol]);

                  std::cout 
                     << "Succesfully calculated all vertices degrees\n"
                     << "\n"
                  ;

                  if(graphMemory[subcontrol].type == 'G'){
                     for(int i = 0; i < graphMemory[subcontrol].verticeList.size(); i++){
                        std::cout 
                           << "ID: " << graphMemory[subcontrol].verticeList[i].id 
                           << " | UserGivenName: " << graphMemory[subcontrol].verticeList[i].userName 
                           << " | Degree: " << graphMemory[subcontrol].verticeList[i].degree.first << "\n"
                        ; 
                     }

                     break;

                  } else {
                     for(int i = 0; i < graphMemory[subcontrol].verticeList.size(); i++){
                        std::cout 
                           << "ID: " << graphMemory[subcontrol].verticeList[i].id 
                           << " | UserGivenName: " << graphMemory[subcontrol].verticeList[i].userName 
                           << " | In-degree: " << graphMemory[subcontrol].verticeList[i].degree.first 
                           << " | Out-degree: " << graphMemory[subcontrol].verticeList[i].degree.second << "\n"
                        ;
                     }

                     break;

                  }

               } else {
                  std::cout << "Invalid input, try again:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Invalid input, try again:\n";

            }
         }   

      } else if(control == 7){
         while(true){

            std::cout 
               << "-------------------------------------------\n"
               << "Which graph will have it's minimum spanning tree done? (Choose by index)\n"
               << "-2 if you want to remember where each graph was saved\n"
               << "-1 if you want to leave this option\n"
               << "This program only saves the last tree done, if you try doing more than one, the last tree will be overwritten by the new one\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < graphMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol > 0){
                  if(!graphMemory[subcontrol].hasWeight || graphMemory[subcontrol].type == 'D'){
                     std::cout 
                        << "Digraphs or graphs without weighted edges are not supported\n"
                        <<"\n"
                     ;
                     break;
                  }

                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "Which vertice do you want to have as the root for this tree? (Choose by index)\n"
                        << "\n"
                     ;

                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Index: " << v.id << " | UserGivenName: " << v.userName << "\n";
                     }
                     std::cout << "\n";

                     if(std::cin >> thirdControl && thirdControl > 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        treePiVectorMemory = primMST(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);

                        for(int i = 0; i < treePiVectorMemory.size(); i++){
                           std::cout << "ID: " << i << " | Parent: " << treePiVectorMemory[i] << "\n";
                        }
                        std::cout << "\n";

                        std::cout 
                           << "Succesfully created the minimum spanning tree\n"
                           << "\n"
                        ;

                        break;

                     } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Invalid input, try again:\n";
                     }
                  }

               } else{
                  std::cout << "Invalid input, try again:\n";

               }
               
               break;

            }
         }

      } else if(control == 8){
         while(true){

            std::cout 
               << "-------------------------------------------\n"
               << "On which graph do you want to aplly djikstra? (Choose by index)\n"
               << "-2 if you want to remember where each graph was saved\n"
               << "-1 if you want to leave this option\n"
               << "This program only saves the last application, if you try doing more than one, the previous application will be overwritten by the new one\n"
               << "\n"
            ;

            if(std::cin >> subcontrol && subcontrol < graphMemory.size()){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol > 0){
                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "Which vertice do you want to have as the starting point? (Choose by index)\n"
                        << "\n"
                     ;

                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Index: " << v.id << " | UserGivenName: " << v.userName << "\n";
                     }
                     std::cout << "\n";

                     if(std::cin >> thirdControl && thirdControl > 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        djikstraMemory = djikstra(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);
                        
                        for(const std::pair<float, int> &distPi : djikstraMemory){
                           std::cout << "Distance : " << distPi.first << " | Parent: " << distPi.second << "\n"; 
                        }

                        std::cout 
                           << "Succesfully applied djikstra's algorithm on the selected graph\n"
                           << "\n"
                        ;

                        while(true){
                           std::cout 
                              << "Based on this tree generated with djikstra's algorithm, do you want to choose a vertice to know if there is path leading to it from another vertice?\n"
                              << "IMPORTANT: this option repeats until the user voluntarily exits\n"
                              << "1 - Yes; 2 - No\n"
                           ;

                           if(std::cin >> thirdControl){
                              if(thirdControl == 1){
                                 while(true){
                                    std::cout 
                                       << "Type the ID of the starting vertice: \n"
                                       << "-1 to leave this option\n"
                                    ;

                                    if(std::cin >> thirdControl && thirdControl >= 0){
                                       if(thirdControl < graphMemory[subcontrol].verticeList.size()){
                                          while(true){
                                             std::cout 
                                                << "Type the ID of the ending vertice:\n"
                                             ;

                                             if(std::cin >> fourthControl){
                                                if(fourthControl < graphMemory[subcontrol].verticeList.size()){
                                                   std::cout << "\n";
                                                   djikstraPathPrint(thirdControl, fourthControl, djikstraMemory);
                                                   std::cout << "\n";
                                                   break;

                                                } else{
                                                   std::cout << "Chosen value is bigger than existent ID values. Try again\n";

                                                }
                                             } else{
                                                std::cout << "Invalid input, try again:\n";

                                             }
                                          }

                                       } else{
                                          std::cout << "Chosen value is bigger than existent ID values. Try again\n";

                                       }

                                    } else if(thirdControl == -1){
                                       break;

                                    } else{
                                       std::cout << "Invalid input, try again:\n";

                                    }

                                 }

                                 break;

                              } else if(subcontrol == 2){
                                 break;

                              } else{
                                 std::cout << "Invalid input, try again:\n";

                              }
                           }
                        }

                        break;

                     } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Invalid input, try again:\n";
                     }
                  }

                  break;

               } else{
                  std::cout << "Invalid input, try again:\n";

               }

            } else {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Invalid input, try again:\n";

            }
         }

      } else if(control == 9){
          
      } else if(control == 10){

      } else if(control != -1){
         std::cout << "Invalid input, try again:\n";
      }

      subcontrol = 0;
      thirdControl = 0;
   }


   //DEBUG comments:

   // int a, b;
   // bool c;
   // char ty;

   // a = auxGraph.verticeNum;
   // b = auxGraph.edgeNum;
   // c = auxGraph.hasWeight;
   // ty = auxGraph.type;

   // std::cout << a << " " << b << " " << ty << " " << c <<std::endl;

   // for(int i = 0; i < auxGraph.verticeList.size(); i++){
   //    std::cout << auxGraph.verticeList[i].userName <<std::endl;
   // }

   return 0;
}