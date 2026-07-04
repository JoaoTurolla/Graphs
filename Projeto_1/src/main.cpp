#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "vertice.hpp"
#include "fileHandler.hpp"

void printFilesInMemory(std::vector<std::string> mem){
   for(int i = 0; i < mem.size(); i++){
      std::cout << "Índice " << i << " :" << mem[i] << "\n";
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
         std::cout << "Não existe um caminho até este vértice\n";
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
   std::vector<std::pair<int, int>> BFSMemory;
   std::vector<std::tuple<int, int, int>> DFSMemory;
   int control = 0, subcontrol = 0, thirdControl = 0, fourthControl = 0;
   Graph auxGraph;
   char fileName[100];

   while(control != -1){
      std::cout 
         << "-------------------------------------------\n" 
         << "TODAS AS OPERAÇÕES SOBRE GRAFOS REQUEREM QUE O GRAFO ESTEJA NA MEMÓRIA ANTES DE SEREM CHAMADAS\n"
         << "Suas opções são:\n"
         << "-1 - Fechar o programa\n"
         << " 1 - Ler um arquivo para carregar um grafo na memória\n"
         << " 2 - Escrever os dados de um grafo para criar um arquivo correspondente\n"
         << " 3 - Visualizar um grafo pelo console\n"
         << " 4 - Criar e/ou carregar na memória a matriz de adjacência de um grafo (Você pode optar por salvar a matriz em um arquivo)\n"
         << " 5 - Visualizar uma matrix de adjacência pelo console\n"
         << " 6 - Calcular o grau de cada vértice de um grafo\n"
         << " 7 - Encontrar a árvore geradora mínima de um grafo\n"
         << " 8 - Aplicar o algoritmo de Djikstra em um grafo\n"
         << " 9 - Realizar uma busca em largura (BFS) em um grafo\n"
         << "10 - Realizar uma busca em profundidade (DFS) em um grafo\n"
         << "\n" //Mantido isolado para facilitar adição de novas operações
      ;

      while(true){
         if(std::cin >> control){
            break;
            
         } else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            std::cout << "Entrada inválida, tente novamente:\n";

         }
      }

      if(control == 1){
         std::string fileNameS;
         std::cout  
            << "-------------------------------------------\n" 
            << "Escreva o nome do arquivo/caminho até o arquivo: \n"
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
            << "Grafo carregado na memória com sucesso\n"
            << "\n"
         ;

      } else if(control == 2){
         std::string fileToWriteS;
         char fileToWriteName[100];
         int readNamePtr = 0, writeNamePtr = 0;

         std::cout 
            << "-------------------------------------------\n"
            << "Nomeie o arquivo/caminho até o arquivo (máximo de 100 caracteres): \n"
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
            << "Arquivo salvo e escrito com sucesso\n"
            << "\n"
         ;

      } else if(control == 3){
         while(true){
            std::cout  
               << "-------------------------------------------\n" 
               << "Qual o índice na memória do grafo que você deseja visualizar?: \n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if (subcontrol >= 0 && subcontrol < graphMemory.size()){
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
                     << "O grafo e seus vértices foram imprimidos no console com sucesso\n"
                     << "\n"
                  ;

                  break;

               } else {
                  std::cout << "Entrada inválida, tente novamente:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";

            }
         }

      } else if(control == 4){
         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Que grafo terá sua matriz de adjacência feita? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if (subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < graphMemory.size()){
                  graphMemory[subcontrol] >> auxAdjacencyMatrix;//Creates adjacency matrix

                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "1 - Salvar a matriz de adjacência em um arquivo e na memória\n"
                        << "2 - Salvar a matriz de adjacência apenas na memória\n"
                        << "3 - Salvar a matriz de adjacência apenas em um arquivo\n"
                        << "\n"
                     ;

                     if(std::cin >> thirdControl){
                        if(thirdControl == 1){
                           std::string fileNameS;
                           std::cout  
                              << "-------------------------------------------\n" 
                              << "Nomeie o arquivo/caminho até o arquivo para salvar a matriz de adjacência: \n"
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

                           
                           if(!adjacencyMatrixFileWriter(fileName, auxAdjacencyMatrix)){ 
                              std::cerr << "ERRO CRÍTICO: arquivo não pôde ser criado";
                              auxAdjacencyMatrix.clear();
                              fileNameS.clear();
                              break;
                           }
                           matrixesFileNamesLoadedMemory.push_back(fileNameS);
                           adjacencyMatrixMemory.push_back(std::move(auxAdjacencyMatrix)); 
                           //CUIDADO EXTREMO!! auxAdjacencyMatrix TEM TAMANHO 0 APOS ESSA LINHA, NAO TENTE ACESSAR NADA POR INDICE
                           //Como so sao utilizados push_backs e loops baseados no tamanho atual do vector, nao ocorrerao erros neste programa, mas fica o aviso
                           //caso queira replicar. Isso acontece pois std::move rouba o ponteiro do inicio do vector auxAdjacencyMatrix e entrega para adjacencyMatrixMemory[0]
                           //movendo assim o vector inteiro em tempo mínimo e igual independentemente do tamanho de auxAdjacencyMatrix pois nao ha realocacao de memoria. 
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Matriz de adjacência criada, carregada na memória e salva em um arquivo com sucesso\n"
                              << "\n"
                           ;

                           break;

                        } else if(thirdControl == 2){
                           adjacencyMatrixMemory.push_back(std::move(auxAdjacencyMatrix));
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Matriz de adjacência criada e salva na memória com sucesso\n"
                              << "\n"
                           ;
                           break;

                        } else if(thirdControl == 3){
                           std::string fileNameS;
                           std::cout  
                              << "-------------------------------------------\n" 
                              << "Nomeie o arquivo/caminho até o arquivo para salvar a matriz de adjacência: \n"
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

                           if(!adjacencyMatrixFileWriter(fileName, auxAdjacencyMatrix)){
                              std::cerr << "ERRO CRÍTICO: arquivo não pôde ser criado" <<std::endl;
                              auxAdjacencyMatrix.clear();
                              fileNameS.clear();
                              break;
                           }
                           matrixesFileNamesLoadedMemory.push_back(fileNameS);
                           auxAdjacencyMatrix.clear();

                           std::cout 
                              << "Matriz de adjacência criada com sucesso e salva no arquivo de nome/caminho: " << fileName << "\n"
                              << "\n"
                           ;

                           break;

                        } else{
                           std::cout << "Entrada inválida, tente novamente:\n";

                        }
                     } else{
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Entrada inválida, tente novamente:\n";

                     }
                  }

                  break;

               } else{
                  std::cout << "Entrada inválida, tente novamente:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";

            }

         }

      } else if(control == 5){

         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Qual matriz será imprimida no console? (Escolha por índice)\n"
               << "-2 se quiser lembrar o índice em que cada matriz foi salva\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(matrixesFileNamesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < adjacencyMatrixMemory.size()){
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
                  std::cout << "Entrada inválida, tente novamente:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";

            }
         }

      } else if(control == 6){

         while(true){
            std::cout 
               << "\n" 
               << "-------------------------------------------\n"
               << "Qual o índice do grafo que você deseja calcular o grau dos vértices? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < graphMemory.size()){
                  degreeCalc(graphMemory[subcontrol]);

                  std::cout 
                     << "Todos os graus foram calculados com sucesso\n"
                     << "\n"
                  ;

                  if(graphMemory[subcontrol].type == 'G'){
                     for(int i = 0; i < graphMemory[subcontrol].verticeList.size(); i++){
                        std::cout 
                           << "ID: " << graphMemory[subcontrol].verticeList[i].id 
                           << " | Nome dado pelo usuário: " << graphMemory[subcontrol].verticeList[i].userName 
                           << " | Grau: " << graphMemory[subcontrol].verticeList[i].degree.first << "\n"
                        ; 
                     }

                     break;

                  } else {
                     for(int i = 0; i < graphMemory[subcontrol].verticeList.size(); i++){
                        std::cout 
                           << "ID: " << graphMemory[subcontrol].verticeList[i].id 
                           << " | Nome dado pelo usuário: " << graphMemory[subcontrol].verticeList[i].userName 
                           << " | Grau de entrada: " << graphMemory[subcontrol].verticeList[i].degree.first 
                           << " | Grau de saída: " << graphMemory[subcontrol].verticeList[i].degree.second << "\n"
                        ;
                     }

                     break;

                  }

               } else {
                  std::cout << "Entrada inválida, tente novamente:\n";

               }

            } else{
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";

            }
         }   

      } else if(control == 7){
         while(true){

            std::cout 
               << "-------------------------------------------\n"
               << "Você quer gerar a árvore geradora mínima de qual grafo? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "Este programa salva apenas a última árvore feita, se você tentar fazer mais de uma, a próxima árvore sobrescreverá a árvore que estiver na memória\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < graphMemory.size()){
                  if(!graphMemory[subcontrol].hasWeight || graphMemory[subcontrol].type == 'D'){
                     std::cout 
                        << "Dígrafos ou grafos que não têm peso na arestas não podem servir de entrada\n"
                        <<"\n"
                     ;
                     break;
                  }

                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "Qual vértice você quer que seja a raiz da árvore? (Escolha por índice)\n"
                        << "\n"
                     ;

                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Índice: " << v.id << " | Nome dado pelo usuário: " << v.userName << "\n";
                     }
                     std::cout << "\n";

                     if(std::cin >> thirdControl && thirdControl >= 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        treePiVectorMemory = primMST(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);

                        for(int i = 0; i < treePiVectorMemory.size(); i++){
                           std::cout << "ID: " << i << " | Vértice pai: " << treePiVectorMemory[i] << "\n";
                        }
                        std::cout << "\n";

                        std::cout 
                           << "Árvore geradora mínima criada com sucesso\n"
                           << "\n"
                        ;

                        break;

                     } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Entrada inválida, tente novamente:\n";
                     }
                  }

               } else{
                  std::cout << "Entrada inválida, tente novamente:\n";

               }
            }
         }

      } else if(control == 8){
         while(true){

            std::cout 
               << "-------------------------------------------\n"
               << "Em qual grafo você deseja aplicar o algoritmo de Djikstra? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "Este programa salva apenas a última aplicação, a próxima aplicação do algoritmo sobrescreverá a existente na memória\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < graphMemory.size()){
                  while(true){
                     std::cout 
                        << "-------------------------------------------\n"
                        << "Qual vértice você quer que seja o ponto de partida? (Escolha por índice)\n"
                        << "\n"
                     ;

                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Índice: " << v.id << " | Nome dado pelo usuário: " << v.userName << "\n";
                     }
                     std::cout << "\n";

                     if(std::cin >> thirdControl && thirdControl >= 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        djikstraMemory = djikstra(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);

                        std::cout << "\n";
                        for(const std::pair<float, int> &distPi : djikstraMemory){
                           std::cout << "Distância : " << distPi.first << " | Vértice pai: " << distPi.second << "\n"; 
                        }

                        std::cout 
                           << "\n"
                           << "Algoritmo de Djikstra aplicado com sucesso no grafo selecionado\n"
                           << "\n"
                        ;

                        while(true){
                           std::cout 
                              << "A partir dessa árvore gerada com djikstra, você quer escolher um vértice e descobrir se há um caminho até ele de um outro vértice?\n"
                              << "IMPORTANTE: esta opção se repetirá até a saída voluntária do usuário\n"
                              << "1 - Sim; 2 - Não\n"
                           ;

                           if(std::cin >> thirdControl){
                              if(thirdControl == 1){
                                 while(true){
                                    std::cout 
                                       << "Digite o id do vértice inicial desejado: \n"
                                       << "-1 para sair desta opção\n"
                                    ;

                                    if(std::cin >> thirdControl && thirdControl >= 0){
                                       if(thirdControl < graphMemory[subcontrol].verticeList.size()){
                                          while(true){
                                             std::cout 
                                                << "Digite o id do vértice final desejado:\n"
                                             ;

                                             if(std::cin >> fourthControl){
                                                if(fourthControl < graphMemory[subcontrol].verticeList.size()){
                                                   std::cout << "\n";
                                                   djikstraPathPrint(thirdControl, fourthControl, djikstraMemory);
                                                   std::cout << "\n";
                                                   break;

                                                } else{
                                                   std::cout << "Valor escolhido é maior que o maior ID existente. Tente novamente\n";

                                                }
                                             } else{
                                                std::cout << "Entrada inválida, tente novamente:\n";

                                             }
                                          }

                                       } else{
                                          std::cout << "Valor escolhido é maior que o maior ID existente. Tente novamente\n";

                                       }

                                    } else if(thirdControl == -1){
                                       break;

                                    } else{
                                       std::cout << "Entrada inválida, tente novamente:\n";

                                    }

                                 }

                                 break;

                              } else if(subcontrol == 2){
                                 break;

                              } else{
                                 std::cout << "Entrada inválida, tente novamente:\n";

                              }
                           }
                        }

                        break;

                     } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Entrada inválida, tente novamente:\n";
                     }
                  }

                  break;

               } else{
                  std::cout << "Entrada inválida, tente novamente:\n";

               }

            } else {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";

            }
         }

      } else if(control == 9){
         while(true){
            std::cout
               << "-------------------------------------------\n"
               << "Em qual grafo vocẽ quer aplicar BFS? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"  
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);
               
               } else if(subcontrol == -1){
                  break;
               
               } else if (subcontrol >= 0 && subcontrol < graphMemory.size()){
                  while(true){
                     
                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Índice: " << v.id << " | Nome dado pelo usuário: " << v.userName << "\n";
                     }
                     std::cout << "\n";
                     
                     std::cout
                        << "-------------------------------------------\n"
                        << "Qual vértice você quer como seu ponto de partida? (Escolha por índice / opções acima)\n"
                        << "\n"
                     ;

                     if(std::cin >> thirdControl && thirdControl >= 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        BFSMemory = BFS(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);
                        break;

                     } else{
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Entrada inválida, tente novamente:\n";
                     }

                  }

                  break;

               } else{
                  std::cin.clear();
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                  std::cout << "Entrada inválida, tente novamente:\n"; 
               }
            }

         }
          
      } else if(control == 10){
         while(true){
            std::cout 
               << "-------------------------------------------\n"
               << "Em qual grafo vocẽ quer aplicar DFS? (Escolha por índice)\n"
               << "-2 se você quiser lembrar em qual índice cada grafo está\n"
               << "-1 se você quiser sair dessa opção\n"
               << "\n"
            ;

            if(std::cin >> subcontrol){
               if(subcontrol == -2){
                  printFilesInMemory(filesLoadedMemory);

               } else if(subcontrol == -1){
                  break;

               } else if(subcontrol >= 0 && subcontrol < graphMemory.size()){
                  while(true){
                     for(const Vertice &v: graphMemory[subcontrol].verticeList){
                        std::cout << "Índice: " << v.id << " | Nome dado pelo usuário: " << v.userName << "\n";
                     }
                     std::cout << "\n";
                        
                     std::cout
                        << "-------------------------------------------\n"
                        << "Qual vértice você quer como ponto de partida? (Escolha por índice / opções acinma)\n"
                        << "\n"
                     ;

                     if(std::cin >> thirdControl && thirdControl >= 0 && thirdControl < graphMemory[subcontrol].verticeList.size()){
                        DFSMemory = DFS(graphMemory[subcontrol], graphMemory[subcontrol].verticeList[thirdControl]);

                        std::cout
                           << "\n"
                           << "Árvore DFS e tempos de descoberta e finalização"
                        ;

                        int tempId = 0;

                        for(const std::tuple<int, int, int> &DFSTuple: DFSMemory){
                           std::cout
                              << "\n"
                              << "ID: " << tempId << " | Tempo de descoberta: " << std::get<0>(DFSTuple) << " | Tempo de finalização: " << std::get<1>(DFSTuple) << " | Vértice pai: " << std::get<2>(DFSTuple);
                           ;
                           tempId++;
                        }

                        std::cout << "\n";

                        break;

                     } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                        std::cout << "Entrada inválida, tente novamente:\n";
                     }
                  }

                  break;

               }

            } else {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max());
               std::cout << "Entrada inválida, tente novamente:\n";
            }
         }

      } else if(control != -1){
         std::cout << "Entrada inválida, tente novamente:\n";
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
