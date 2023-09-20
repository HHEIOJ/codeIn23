#include "cflukadose.h"
#include <iostream>
using namespace std;

void printMenu();
void printCalcMenu();

void computeFLUKADose(const string & filename);

void computeDose();


int main()
{
//    CFlukaDose dose("/home/tree/Fluka/NEUTRON/ShieldingDesign/floor/Iron/2cm/quanyu15_50.bnn",1);
//    dose.getXZXMaxDose();

    while (true) {
         printMenu();
         int choice;
         cin >> choice;

         switch (choice) {
             case 1: {
                 string fileName;
                 cout << "请输入需要处理的文件名: ";
                 cin >> fileName;
                 computeFLUKADose(fileName);
                 break;
             }
             case 2:
                 cout << "退出程序。\n";
                 return 0;
             default:
                 cout << "无效的选项，请重新输入。\n";
                 break;
         }
     }

//    computeDose();
//    return 0;
}


void printMenu() {
    cout << "******计算FLUKA剂量*************\n";
    cout << "1. 开始\n";
    cout << "2. 退出\n";
    cout << "请选择一个选项: ";
}

void printCalcMenu() {
    cout << "******choose what to calculate*************\n";
    cout << "1. calulate XZ plane\n";
    cout << "2. calculate YZ plane\n";
    cout << "3. quit\n";
    cout << "请选择一个选项: ";
}



void computeFLUKADose(const string& fileName)
{
//    string filePath="/home/tree/Fluka/NEUTRON/ShieldingDesign/floor/Iron/";

//    filePath+=fileName;

    CFlukaDose flukadose(fileName,1);

    while (true) {
        printCalcMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            flukadose.getXZMaxDose();
            break;
        }

        case 2:
        {
            flukadose.getYZMaxDose();
            break;
        }

        case 3:
        {
            cout << "exit program.\n";
            return;
        }
        default:
        {
            cout << "Invalid input, please re-enter.\n";
            break;
        }
        }

    }

}

void computeDose()
{
    string path="/home/tree/Fluka/NEUTRON/ShieldingDesign/side/IRON/";
    int depth[15]={2, 4, 6, 8, 10, 15, 20, 25, 30, 35, 40, 45, 50,  60,  70};
    string fileName;
    for(int i=0; i<15;++i)
    {
        fileName=path+std::to_string(depth[i])+"/shielding001_fort.50";
        CFlukaDose dose(fileName,1);
//        cout<<"depth "<<depth[i]<<" XZ maximum dose: \n";
        std::cout << "\033[32mdepth " << depth[i] << " XZ maximum dose:\033[0m" << std::endl;
        dose.getXZMaxDose(1);
//        cout<<"depth "<<depth[i]<<" YZ maximum dose: \n";
        std::cout << "\033[32mdepth " << depth[i] << " YZ maximum dose:\033[0m" << std::endl;
        dose.getYZMaxDose(1);

        std::cout << "\033[32mdepth " << depth[i] << " XY maximum dose:\033[0m" << std::endl;
        dose.getXYXMaxDose(1);
//        cout<<"depth "<<depth[i]<<" YZ maximum dose: \n";
        std::cout << "\033[32mdepth " << depth[i] << " XZ maximum dose:\033[0m" << std::endl;
        dose.getXZXMaxDose(1);


    }
}





