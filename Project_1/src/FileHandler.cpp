#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <utility>
#include "vertice.hpp"
#include "graph.hpp"
#include "fileHandler.hpp"

std::istream& operator>>(std::istream& fileInput, Graph& graphToUpd){//Operador leitor da primeira linha
   std::string line, tempVertCountS, tempEdgeCountS, tempTypeS, tempWeightS;
   //A funcao nao apenas le, mas tambem atribui os valores e consegue encerrar sem explodir caso algo esteja errado
   if(std::getline(fileInput, line)){
      if(line.empty()) return fileInput;

      std::stringstream ss(line);
      char bracket;

      if(ss >> bracket && bracket == '<') std::getline(ss, tempVertCountS, '>');
      else{ 
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }
      if(ss >> bracket && bracket == '<') std::getline(ss, tempEdgeCountS, '>');
      else {
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }
      if(ss >> bracket && bracket == '<') std::getline(ss, tempTypeS, '>');
      else{ 
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }
      if(ss >> bracket && bracket == '<') std::getline(ss, tempWeightS, '>');
      else{
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }

      // Conversoes e tratamento de erros imediatos
      size_t pos;
      int tempVertCountInt, tempEdgeCountInt;
      int tempWeightB;
      char tempTypeC;

      try{
         tempVertCountInt = std::stoi(tempVertCountS, &pos);
      } catch(const std::invalid_argument &e){
         std::cerr << "Vertices were not provided as numbers" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      } catch(const std::out_of_range &e){
         std::cerr << "Vertice count is too big" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      } 

      if(pos < tempVertCountS.length()){
         std::cerr << "Decimals and/or letters are not allowed in the vertice camp" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }
      if(tempVertCountInt < 0) {
         std::cerr << "Vertice count can never be negative" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }
      try{
         tempEdgeCountInt = std::stoi(tempEdgeCountS, &pos);
      } catch(const std::invalid_argument &e){
         std::cerr << "Edges were not provided as numbers" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      } catch(const std::out_of_range &e){
         std::cerr << "Edge count is too big" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }

      if(pos < tempEdgeCountS.length()){
         std::cerr << "Decimals and/or letters are not allowed in the edge camp" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }
         if(tempEdgeCountInt < 0){
         std::cerr << "Edge count can never be negative" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }

      try {
         tempWeightB = std::stoi(tempWeightS, &pos);
      } catch(const std::invalid_argument &e){
         std::cerr << "Weight was not provided as a number" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      } catch(const std::out_of_range &e){
         std::cerr << "Weight is too big" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }

      if(pos < tempWeightS.length()){
         std::cerr << "Decimals and/or letters are not allowed in the weight camp" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }
      if(tempWeightB != 1 && tempWeightB != 0){ 
         std::cerr << "Invalid input for weight (Must be 1 or 0)" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }

      tempTypeC = tempTypeS[0];
      tempTypeC = std::toupper(static_cast<unsigned char>(tempTypeC));

      if(isdigit(tempTypeC)){
         std::cerr << "Type was not provided as a character" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      } else if(tempTypeC != 'G' && tempTypeC != 'D'){
         std::cerr << "Invalid type of Graph (Must be G or D)" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;

      }
      
      if(tempVertCountInt == 0 && tempEdgeCountInt != 0){
         std::cerr << "An empty graph can't possibly have any edges. Edge count has been automatically changed to 0" <<std::endl;
         tempEdgeCountInt = 0;
      }
      // Todos os cout ficarao comentados para facilitar possiveis DEBUGS futuros 
      // std::cout <<"DEBUG: VertInt: " << tempVertCountInt << " | EdgeCount: " << tempEdgeCountInt << " | Type: " << tempTypeC << " | weightBool: " << tempWeightB <<std::endl;


      //Repasse dos dados para o grafo existente
      graphToUpd.Setup(tempVertCountInt, tempEdgeCountInt, tempTypeC, tempWeightB);
      
   }
   
   return fileInput;
}

std::istream& operator>>(std::istream& fileInput, std::vector<Vertice>& vertList){//Operador leitor da segunda linha em diante
   std::string line, tempV1S, tempV2S, tempEWeightS;
   std::pair<int, float> noTargetEdge;
   if(std::getline(fileInput, line)){
      if(line.empty()) return fileInput;
      
      std::stringstream ss(line);
      char bracket;
      
      if(ss >> bracket && bracket == '<') std::getline(ss, tempV1S, '>');
      else{
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }
      if(ss >> bracket && bracket == '<') std::getline(ss, tempV2S, '>');
      else{
         std::cerr << "Tried to read a field that was never initialized" <<std::endl;
         fileInput.setstate(std::ios::failbit);
         return fileInput;
      }
      if(ss >> bracket && bracket == '<') {
         if(!(std::getline(ss, tempEWeightS, '>'))){
            std::cerr << "Tried to read inexistent field" <<std::endl;
            fileInput.setstate(std::ios::failbit);
            return fileInput;   
         }
      }
      
      //Conversoes e tratamentos de erros imediatos

      for(char &c : tempV1S){ //Conversao para minusculas
         c = std::tolower(static_cast<unsigned char>(c));
      }
      
      for(char &c : tempV2S){ //Conversao para minusculas
         c = std::tolower(static_cast<unsigned char>(c));
      }
      
      Vertice start, end;
      float tempEWeightF;
      size_t pos;
      
      if(!tempEWeightS.empty()){
         try{
            tempEWeightF = std::stof(tempEWeightS, &pos);
            
         } catch(const std::invalid_argument &e){
            std::cerr << "Improper declaration of edge weight" <<std::endl;
            fileInput.setstate(std::ios::failbit);
            return fileInput;
            
         } catch(const std::out_of_range &e){
            std::cerr << "Edge weight is out of range" <<std::endl;
            fileInput.setstate(std::ios::failbit);
            return fileInput;
            
         }
         
         if(pos < tempEWeightS.length()){
            std::cerr  << "Improper declaration of edge weight" <<std::endl;
            fileInput.setstate(std::ios::failbit);
            return fileInput;
            
         }

         noTargetEdge.first = tempEWeightF;
         start.allEdges.push_back(noTargetEdge);
      }
      
      
      //Atribuicao para aplicacao da logica real fora da leitura
      
      start.Setup(-1, tempV1S);
      end.Setup(-1, tempV2S);

      vertList.push_back(start);
      vertList.push_back(end);

   }

   return fileInput;
}

int graphDiagnose(const char* fileName){//Define através do valor de retorno qual função deve ser chamada para ler o arquivo corretamente
   std::ifstream file;
   
   file.open(fileName, std::ios::in);
   
   if(!file.is_open()){
      std::cerr << "CRITICAL ERROR: could not open file" <<std::endl;
      return -1;
      
   } 

   Graph diagnosticTemp;
   file >> diagnosticTemp;

   if(file.fail() && !file.eof()){
      return -3;
   }

   if(diagnosticTemp.type == 'G') return 1;
   else if(diagnosticTemp.type == 'D') return 2;
   else {
      std::cerr << "Unknown error occurred reading the first line of the file, review if your file follows the correct format" <<std::endl;
      return -2;
   }
}

bool graphInfoReading(const char* fileName, Graph &graphToUpd){//Utiliza dos operadores >> acima para ler o arquivo e criar o grafo e seus vertices
   std::ifstream file;
   
   file.open(fileName, std::ios::in);
   
   if(!file.is_open()){
      std::cerr << "CRITICAL ERROR: could not open file" <<std::endl;
      return false;
      
   } else {
      std::vector<Vertice> createdVertices, testVertices;
      int vertCounter = -1, edgeCounter = 0, startVertIdx = -1, endVertIdx = -1, lineCounter = 1;
      
      file >> graphToUpd;

      if (file.fail() && !file.eof()) {
         return false; 
      }

      // std::cout << "DEBUG: GraphVertNum: " << graphToUpd.verticeNum << " | GraphEdgeNum: " << graphToUpd.edgeNum
      // << " | GraphType: " << graphToUpd.type << " | GraphWeightBool: " << graphToUpd.hasWeight <<std::endl;

      if(graphToUpd.verticeNum == 0) return true;

      std::pair<int, float> edge, reverseEdge;

      while(file >> testVertices){
         if(edgeCounter + 1 > graphToUpd.edgeNum){
            std::cerr << "Edge overflow" <<std::endl;
            return false;
         }

         for(int i = 0; i <= vertCounter; i++){ //Checando se e um vertice ja conhecido
            if(testVertices[0].userName == createdVertices[i].userName) startVertIdx = i;
         }
         
         if(startVertIdx == -1){ //Se desconhecido, adicione 1 ao contador que sera tanto index quanto id do vertice, crie e coloque o vertice no vector
            vertCounter++;
            startVertIdx = vertCounter; //necessario para guardar o indice de maneira legivel pois vertCounter sera mudado repetidamente
            if(vertCounter + 1 > graphToUpd.verticeNum){
               std::cerr << "Vertice overflow" <<std::endl;
               return false;
               
            } 
            createdVertices.push_back(Vertice(startVertIdx, testVertices[0].userName));
            
         }

         for(int i = 0; i <= vertCounter; i++){ //Checando se e um vertice ja conhecido
            if(testVertices[1].userName == createdVertices[i].userName) endVertIdx = i;
         }

         if(endVertIdx == -1){ //Se desconhecido, adicione 1 ao contador que sera tanto index quanto id do vertice, crie e coloque o vertice no vector
            vertCounter++;
            endVertIdx = vertCounter; //necessario para guardar o indice de maneira legivel pois vertCounter sera mudado repetidamente
            if(vertCounter + 1 > graphToUpd.verticeNum){
               std::cerr << "Vertice overflow" <<std::endl;
               return false;

            }
            createdVertices.push_back(Vertice(endVertIdx, testVertices[1].userName));

         }

         // std::cout << "DEBUG: Size: " << createdVertices.size() 
         // << " | StartIdx: " << startVertIdx 
         // << " | EndIdx: " << endVertIdx << std::endl;

         if(graphToUpd.hasWeight){
            if(testVertices[0].allEdges.empty()){
               std::cerr << "CRITICAL ERROR: missing edge weight on line: " << lineCounter <<std::endl;
               return false;

            } else{
               float edgeWeight = testVertices[0].allEdges[0].first;

               edge.first = edgeWeight;
               edge.second = endVertIdx;

               reverseEdge.first = edgeWeight;
               reverseEdge.second = startVertIdx;

               if(createdVertices[startVertIdx].adjacencyArray.size() == 0) createdVertices[startVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);
               if(createdVertices[endVertIdx].adjacencyArray.size() == 0) createdVertices[endVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);

               createdVertices[startVertIdx].allEdges.push_back(edge);
               createdVertices[startVertIdx].adjacencyArray[endVertIdx] = true;

               if(startVertIdx != endVertIdx){
                  createdVertices[endVertIdx].allEdges.push_back(reverseEdge);
                  createdVertices[endVertIdx].adjacencyArray[startVertIdx] = true;
               }
            }

         } else{

            edge.first = std::numeric_limits<float>::infinity();
            edge.second = endVertIdx;

            reverseEdge.first = std::numeric_limits<float>::infinity();
            reverseEdge.second = startVertIdx;

            if(createdVertices[startVertIdx].adjacencyArray.size() == 0) createdVertices[startVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);
            if(createdVertices[endVertIdx].adjacencyArray.size() == 0) createdVertices[endVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);

            createdVertices[startVertIdx].allEdges.push_back(edge);
            createdVertices[startVertIdx].adjacencyArray[endVertIdx] = true;
            
            if(startVertIdx != endVertIdx){
               createdVertices[endVertIdx].allEdges.push_back(reverseEdge);
               createdVertices[endVertIdx].adjacencyArray[startVertIdx] = true;
            }
         }


         //Atualizacao e reset das variaveis e vectors
         lineCounter++;
         edgeCounter++;
         startVertIdx = -1;
         endVertIdx = -1;
         testVertices.clear();

      }

      if (file.fail() && !file.eof()){
         return false; 
      }

      if(vertCounter + 1 < graphToUpd.verticeNum){
         std::cerr << "Vertice underflow" <<std::endl;
         return false;

      }

      if(edgeCounter < graphToUpd.edgeNum){
         std::cerr << "Edge underflow" <<std::endl;
         return false;

      }

      graphToUpd.verticeList.clear();
      for(Vertice v: createdVertices){
         graphToUpd.verticeList.push_back(v);
      }
   }

   file.close();
   return true;
}

bool digraphInfoReading(const char* fileName, Graph &graphToUpd){//Utiliza dos operadores >> acima para ler o arquivo e criar o digrafo e seus vertices
   std::ifstream file;
   
   file.open(fileName, std::ios::in);
   
   if(!file.is_open()){
      std::cerr << "CRITICAL ERROR: could not open file" <<std::endl;
      return false;
      
   } else {
      std::vector<Vertice> createdVertices, testVertices;
      int vertCounter = -1, edgeCounter = 0, startVertIdx = -1, endVertIdx = -1, lineCounter = 1;
      
      file >> graphToUpd;

      if (file.fail() && !file.eof()) {
         return false; 
      }

      // std::cout << "DEBUG: GraphVertNum: " << graphToUpd.verticeNum << " | GraphEdgeNum: " << graphToUpd.edgeNum
      // << " | GraphType: " << graphToUpd.type << " | GraphWeightBool: " << graphToUpd.hasWeight <<std::endl;

      if(graphToUpd.verticeNum == 0) return true;

      std::pair<int, float> edge;

      while(file >> testVertices){
         if(edgeCounter + 1 > graphToUpd.edgeNum){
            std::cerr << "Edge overflow" <<std::endl;
            return false;
         }

         for(int i = 0; i <= vertCounter; i++){ //Checando se e um vertice ja conhecido
            if(testVertices[0].userName == createdVertices[i].userName) startVertIdx = i;
         }
         
         if(startVertIdx == -1){ //Se desconhecido, adicione 1 ao contador que sera tanto index quanto id do vertice, crie e coloque o vertice no vector
            vertCounter++;
            startVertIdx = vertCounter; //necessario para guardar o indice de maneira legivel pois vertCounter sera mudado repetidamente
            if(vertCounter + 1 > graphToUpd.verticeNum){
               std::cerr << "Vertice overflow" <<std::endl;
               return false;
               
            } 
            createdVertices.push_back(Vertice(startVertIdx, testVertices[0].userName));
            
         }

         for(int i = 0; i <= vertCounter; i++){ //Checando se e um vertice ja conhecido
            if(testVertices[1].userName == createdVertices[i].userName) endVertIdx = i;
         }

         if(endVertIdx == -1){ //Se desconhecido, adicione 1 ao contador que sera tanto index quanto id do vertice, crie e coloque o vertice no vector
            vertCounter++;
            endVertIdx = vertCounter; //necessario para guardar o indice de maneira legivel pois vertCounter sera mudado repetidamente
            if(vertCounter + 1 > graphToUpd.verticeNum){
               std::cerr << "Vertice overflow" <<std::endl;
               return false;

            }
            createdVertices.push_back(Vertice(endVertIdx, testVertices[1].userName));

         }

         // std::cout << "DEBUG: Size: " << createdVertices.size() 
         // << " | StartIdx: " << startVertIdx 
         // << " | EndIdx: " << endVertIdx << std::endl;

         if(graphToUpd.hasWeight){
            if(testVertices[0].allEdges.empty()){
               std::cerr << "CRITICAL ERROR: missing edge weight on line: " << lineCounter <<std::endl;
               return false;

            } else{
               float edgeWeight = testVertices[0].allEdges[0].first;

               edge.first = edgeWeight;
               edge.second = endVertIdx;

               if(createdVertices[startVertIdx].adjacencyArray.size() == 0) createdVertices[startVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);
               if(createdVertices[endVertIdx].adjacencyArray.size() == 0) createdVertices[endVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);

               createdVertices[startVertIdx].allEdges.push_back(edge);
               createdVertices[startVertIdx].adjacencyArray[endVertIdx] = true;

            }

         } else{
            edge.first = std::numeric_limits<float>::infinity();
            edge.second = endVertIdx;

            if(createdVertices[startVertIdx].adjacencyArray.size() == 0) createdVertices[startVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);
            if(createdVertices[endVertIdx].adjacencyArray.size() == 0) createdVertices[endVertIdx].adjacencyArray.assign(graphToUpd.verticeNum, false);


            createdVertices[startVertIdx].allEdges.push_back(edge);
            createdVertices[startVertIdx].adjacencyArray[endVertIdx] = true;

         }


         //Atualizacao e reset das variaveis e vectors
         lineCounter++;
         edgeCounter++;
         startVertIdx = -1;
         endVertIdx = -1;
         testVertices.clear();

      }

      if (file.fail() && !file.eof()){
         return false; 
      }

      if(vertCounter + 1 < graphToUpd.verticeNum){
         std::cerr << "Vertice underflow" <<std::endl;
         return false;

      }

      if(edgeCounter < graphToUpd.edgeNum){
         std::cerr << "Edge underflow" <<std::endl;
         return false;

      }

      graphToUpd.verticeList.clear();
      for(Vertice v: createdVertices){
         graphToUpd.verticeList.push_back(v);
      }
   }

   file.close();
   return true;
}

bool formattedFileWriter(const char* outputFileName){//Permite o usuário escrever manualmente os dados do grafo
   std::ofstream file;
   std::string vertNumS, edgeNumS, typeS, hasWeightS;
   int ctrl = 0, vertNumW, edgeNumW, weightW;
   char typeW;

   std::cout
      << "\n" 
      << "WARNING:\n"
      << "Spaces between words/numbers will cut the name/number short.\n"
      << "Example: Input: My Vert; Output: My\n"
      << "\n"
   ;

   std::cout << "Total of vertices (Always greater than or equal to 0): ";
   std::cin >> vertNumS;

   std::cout << "Total of edges (Always greater than or equal to 0): ";
   std::cin >> edgeNumS;

   std::cout << "Graph type (G or D): ";
   std::cin >> typeS;

   std::cout << "Do the edges have weights? (1 - Yes; 0 - No): ";
   std::cin >> hasWeightS;

   try{
      vertNumW = stoi(vertNumS);
   } catch(const std::out_of_range& e){
      std::cerr << "This number of vertices is not supported by this program" <<std::endl;
      return false;
   } catch(const std::invalid_argument& e){
      std::cerr << "No decimals or letters allowed" <<std::endl;
      return false;
   }

   try{
      edgeNumW = stoi(edgeNumS);
   } catch(const std::out_of_range& e){
      std::cerr << "This number of edges is not supported by this program" <<std::endl;
      return false;
   } catch(const std::invalid_argument& e){
      std::cerr << "No decimals or letters allowed" <<std::endl;
      return false;
   }

   weightW = stoi(hasWeightS);

   file.open(outputFileName, std::ios::out);

   if(!file.is_open()){
      std::cerr << "CRITICAL ERROR: could not open file" <<std::endl;
      return false;
   } else {

      file << "<" << vertNumS << ">" 
         << "<" << edgeNumS << ">" 
         << "<" << typeS << ">" << "<" 
         << hasWeightS << ">" <<std::endl
      ;

      std::string startVertName, endVertName, weightS;

      if(weightW){
         for(int i = 0; i < edgeNumW; i++){
            std::cout << "First vertice of the edge: ";
            std::cin >> startVertName;

            std::cout << "Second vertice of the edge: ";
            std::cin >> endVertName;

            std::cout << "Edge weight: ";
            std::cin >> weightS;

            file << "<" << startVertName << ">" 
               << "<" << endVertName << ">" 
               << "<" << weightS << ">" <<std::endl;

            startVertName.clear();
            endVertName.clear();
            weightS.clear();
         }

         return true;
      } else {
         for(int i = 0; i < edgeNumW; i++){
            std::cout << "First vertice of the edge: ";
            std::cin >> startVertName;

            std::cout << "Second vertice of the edge: ";
            std::cin >> endVertName;

            file << "<" << startVertName << ">" 
               << "<" << endVertName << ">" <<std::endl;

            startVertName.clear();
            endVertName.clear();
         }
         return true;
      }
   }
};

bool adjacencyMatrixFileWriter(const char* outputFileName, std::vector<bool> adjacencyMatrixInput){//Se possivel nomeie o arquivo referenciando o arquivo em que o grafo correspondente esta salvo
   std::ofstream file;

   file.open(outputFileName, std::ios::out);

   if(!file.is_open()){
      std::cerr << "CRITICAL ERROR: could not open file"<<std::endl;
      return false;
   } else {
      int colTotal = sqrt(adjacencyMatrixInput.size()), colPos = 0;

      for(bool b: adjacencyMatrixInput){
         file << "<" << b << ">";
         colPos++;
         if(colPos == colTotal){
            colPos = 0;
            file << "\n";
         }
      }

      return true;
   }
}