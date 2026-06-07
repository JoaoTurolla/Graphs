#ifndef fileHandlerUTILS_HPP
#define fileHandlerUTILS_HPP

#include "graph.hpp"
#include "vertice.hpp"

bool graphInfoReading(const char* file, Graph &graph);

bool digraphInfoReading(const char* file, Graph &graph);

int graphDiagnose(const char* file);

bool formattedFileWriter(const char* fileName);

bool adjacencyMatrixFileWriter(const char* fileName, std::vector<bool> aMI);

std::istream& operator>>(std::istream& is, Graph &g);

std::istream& operator>>(std::istream& is, std::vector<Vertice> &vLs);

#endif