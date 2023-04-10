#include "material.h"
#include <cctype>
#include<cstdio>

Material::Material()
{

}


void Material::print()const
{
    using namespace std;
    cout<<"* %%%"<<name<<endl; // comment line
    printf("MATERIAL%32f%38s\n", density,name.c_str());
    int elementN=elementIndex.size();
    int quotient=elementN/3;
    int remainder=elementN%3;
    if (quotient==0)
    {
        printf("COMPOUND");
        for(int i=3*quotient;i<elementN;++i)
        {
            if(i==0)
            {
              printf("%12f%10s",-1.0*elementMassFraction[i],elementMap.at(elementIndex[i]).c_str());
            }
            else
            {
               printf("%10f%10s",-1.0*elementMassFraction[i],elementMap.at(elementIndex[i]).c_str());
            }


        }

    }
    else
    {
        for(int i=0;i<quotient;++i)
        {
            printf("COMPOUND%12f%10s%10f%10s%10f%10s%8s\n",\
                   -1.0*elementMassFraction[3*i],elementMap.at(elementIndex[3*i]).c_str(),\
                    -1.0*elementMassFraction[i*3+1],elementMap.at(elementIndex[3*i+1]).c_str(),\
                   -1.0* elementMassFraction[3*i+2],elementMap.at(elementIndex[3*i+2]).c_str(),name.c_str());
        }


        if(remainder==1)
        {

            printf("COMPOUND%12f%10s",-1.0*elementMassFraction[quotient*3],elementMap.at(elementIndex[quotient*3]).c_str());
        }
        else if (remainder==2)
        {
            printf("COMPOUND%12f%10s%10f%10s",\
                   -1.0*elementMassFraction[quotient*3],elementMap.at(elementIndex[quotient*3]).c_str(),\
                    -1.0*elementMassFraction[quotient*3+1],elementMap.at(elementIndex[quotient*3+1]).c_str());
        }
    }


    switch (remainder)
    {
    case 1:
        printf("%48s\n",name.c_str());
        break;
    case 2:
        printf("%28s\n",name.c_str());
        break;
    default:
        break;
    }



}

 map<int,string>Material::elementMap=getElementMap();


 map<int, std::string> getElementMap()
{
     map<int,string> elementMap;
    elementMap.insert(pair<int,string>(1,"HYDROGEN" ));
    elementMap.insert(pair<int,string>(2,"HELIUM" ));
//    elementMap.insert(pair<int,string>(3," " ));
//    elementMap.insert(pair<int,string>(4," " ));
    elementMap.insert(pair<int,string>(5,"BORON" ));
    elementMap.insert(pair<int,string>(6,"CARBON" ));
    elementMap.insert(pair<int,string>(7,"NITROGEN" ));
    elementMap.insert(pair<int,string>(8,"OXYGEN" ));
    elementMap.insert(pair<int,string>(9,"FLUORINE" ));
//    elementMap.insert(pair<int,string>(10," " ));
    elementMap.insert(pair<int,string>(11,"SODIUM" ));
    elementMap.insert(pair<int,string>(12,"MAGNESIU" ));
    elementMap.insert(pair<int,string>(13,"ALUMINUM" ));
    elementMap.insert(pair<int,string>(14,"SILICON" ));
    elementMap.insert(pair<int,string>(15,"PHOSPHO" ));
    elementMap.insert(pair<int,string>(16,"SULFUR" ));
    elementMap.insert(pair<int,string>(17,"CHLORINE" ));
    elementMap.insert(pair<int,string>(18,"ARGON" ));
    elementMap.insert(pair<int,string>(19,"POTASSIU" ));
    elementMap.insert(pair<int,string>(20,"CALCIUM" ));
    elementMap.insert(pair<int,string>(26,"IRON" ));
    elementMap.insert(pair<int,string>(30,"ZINC" ));
    return elementMap;
}


void readMaterialTable()
{
    using namespace std;
    const vector<string> materialNames=readMaterialName();
    const vector<int> elementIndex=readElementIndex();
    const vector<float> materialDensity=readMaterialDensity();
    int materialN=materialNames.size();
    int elementN=elementIndex.size();

    if(materialNames.size()!=materialDensity.size())
    {
        cerr<<"The sizes of material name and density are not same.!\n";
        return;
    }
    ifstream materialDataInput("../config/materialData.txt");
    if (!materialDataInput) { // 检查文件是否成功打开
            cerr << "cannot open material data!\n" ;
            return;
        }
    int dataN=materialN*elementN;
    float *materialMassData=new float[dataN];
    for(int i=0;i<dataN;++i)
    {

        materialDataInput>>materialMassData[i];
//        cout<<materialMassData[i]<<" ";
    }




//    vector<Material*> materialData;

    for(int i=0;i<materialN;++i)
    {
        Material material;
        material.name=materialNames[i];
//        cout<<"name"<<material.name;
        material.density=materialDensity[i];
        for(int j=0;j<elementN;++j)
        {
            float massFraction=materialMassData[i*elementN+j];
            if(massFraction==0)
                continue;
            else
            {
                material.elementMassFraction.push_back(massFraction);
                material.elementIndex.push_back(elementIndex[j]);
//                cout<<"index"<<j<<endl;
            }
        }
        material.print();

//        if(i<3)
//        {
//           material.print();

//        }






    }



}

const vector<int> readElementIndex()
{
    using namespace std;
    ifstream elementIndexFile("../config/elementIndex.txt");
    vector<int> elementIndex;
    int number;
    while (elementIndexFile >> number)
       {
           elementIndex.push_back(number);
       }
       elementIndexFile.close();
       return elementIndex;
}

const vector<std::string> readMaterialName()
{
    using namespace std;
    vector<string> lines;
    ifstream inputFile("../config/materilaName.txt");

       if (inputFile.is_open())
       {
           string line;
           while (getline(inputFile, line))
           {
               string str = "";
               int count = 0;
               for (int i = 0; i < line.length() && count < 8; i++)
               {
                   if (isalpha(line[i]))
                   {
                       str += line[i];
                       count++;
                   }
               }
               lines.push_back(str);
           }
           inputFile.close();
       }
       else
       {
           cout << "Unable to open file." << endl;
       }
//       // Print the result
//       for (int i = 0; i < lines.size(); i++)
//       {
//           cout << lines[i] << endl;
//       }

       return lines;

}

const vector<float> readMaterialDensity()
{
    using namespace std;
    ifstream infile("../config/materialDensity.txt"); // 打开文本文件
    vector<float> data; //
    float value;

    while (infile >> value) { //
        data.push_back(value); //
    }

    infile.close(); // 关闭文件

    // 输出vector中存储的所有浮点数
//    for (float val : data) {
//        std::cout << val << std::endl;
//    }
    return data;
}
