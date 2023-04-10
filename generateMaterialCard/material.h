#ifndef MATERIAL_H
#define MATERIAL_H
#include<map>
#include<utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using std::vector;
using std::pair;
using std::map;
using std::string;

map<int, std::string> getElementMap();
void readMaterialTable();
const vector<int> readElementIndex();
const vector<float>readMaterialDensity();
const vector<string> readMaterialName();
const float* readMaterialData();





class Material
{
public:
    Material();
     static map<int,string> elementMap;
    string name{};
    float density=0;
    vector<int> elementIndex;
    vector<float> elementMassFraction{};
    void print()const;
};

#endif // MATERIAL_H


