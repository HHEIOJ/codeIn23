#include "idddata.h"
#include "cflukadose.h".h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

void iddData(const int & Nx, const int & Ny, const int & Nz )
{
    float *DoseData=ReadBinary(sFilePath);
    float * nfData = new float[Nz]{0};
    std::ofstream iddDoseFile(siddDoseFile, std::ios::out | std::ios::trunc);
    std::ofstream PrimaryDoseFile(sPrimaryDoseFile, std::ios::out | std::ios::trunc);
    if(!iddDoseFile)
        std::cerr<<"File open error.";

    for(int i=0;i<Nz;i++)
    {
//        float Data=0;
//        cout<<i<<endl;
        for(int j=0; j<Nx*Ny;j++)
        {
            nfData[i]+=DoseData[Nx*Ny*i+j];
            cout<<DoseData[Nx*Ny*i+j];
            PrimaryDoseFile<<DoseData[Nx*Ny*i+j]<<endl;
        }
        nfData[i]=nfData[i]/Nx/Ny;
        iddDoseFile<<nfData[i]<<endl;
//        cout<<nfData[i]<<std::endl;;
    }

    delete []nfData;
    delete []DoseData;
    nfData=NULL;
    DoseData=NULL;
    iddDoseFile.close();
    PrimaryDoseFile.close();
}


void Test_iddData()
{

    iddData(Nx, Ny, Nz);
}


void profileData( const int &Nx, const int &Ny, const int &Nz, const double depth, const bool flag)
{
    float *DoseData=ReadBinary(sFilePath);
    if(flag==0)
    {
        float * xplData = new float[Nx]{0};
    }
    else
    {
        float * inpData = new float[Ny]{0};
    }

    for(int i=0;i<Nz;++i)
    {
        for (int j=0; j<Ny;++j)
        {

        }

    }

}
