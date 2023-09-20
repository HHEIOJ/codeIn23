#include "cflukadose.h"
#include "cstdio"  // FILE
#include <iostream>
#include <fstream>
#include "alg_logger.h"
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

CFlukaDose::CFlukaDose(const string &filename, const int flag)
{

   LOG_INFO("parse dosebin file:"<< filename);
  ifstream infile(filename, std::ios::in|std::ios::binary);
  if (!infile)
    {
      LOG_ERROR("open file:"<< filename<<" failed");
      return;
    }

  char* buffer = new char[85];
  infile.read(buffer, sizeof(char)*85);
  LOG_INFO("read in:"<< buffer);
  memset(buffer, 0, sizeof(char)*85);
  infile.read(buffer, sizeof(char)*31);
  LOG_INFO("read in:"<< buffer);
  memset(buffer, 0, sizeof(char)*85);
  infile.read(buffer, sizeof(char)*46);
  LOG_INFO("read in:"<< buffer);
  memset(buffer, 0, sizeof(char)*85);
  float xstart, xend, xstep;
  int xsize;
  infile.read((char*)&xstart, sizeof(float));
  infile.read((char*)&xend, sizeof(float));

  LOG_INFO("read in xstart:"<<xstart);
  LOG_INFO("read in xend:"<<xend);
  memset(buffer, 0, sizeof(char)*85);
  infile.read((char*)&xsize, sizeof(int));
  LOG_INFO("read in xsize:"<<xsize);

  infile.read((char*)&xstep, sizeof(float));
  LOG_INFO("read in xstep:"<<xstep);

  float ystart, yend, ystep;
  // uint8_t ysize;
  int ysize;
  infile.read((char*)&ystart, sizeof(float));
  infile.read((char*)&yend, sizeof(float));

  // infile.read(buffer, sizeof(char)*3);
  LOG_INFO("read in ystart:"<<ystart);
  LOG_INFO("read in yend:"<<yend);
  infile.read((char*)&ysize, sizeof(int));
  LOG_INFO("read in ysize:"<<ysize);

  infile.read((char*)&ystep, sizeof(float));
  LOG_INFO("read in ystep:"<<ystep);



  float zstart, zend, zstep;
  // uint8_t zsize;
  int zsize;
  infile.read((char*)&zstart, sizeof(float));
  infile.read((char*)&zend, sizeof(float));
  // infile.read(buffer, sizeof(char)*3);
  LOG_INFO("read in zstart:"<<zstart);
  LOG_INFO("read in zend:"<<zend);
  infile.read((char*)&zsize, sizeof(int));
  LOG_INFO("read in zsize:"<<zsize);

  infile.read((char*)&zstep, sizeof(float));
  LOG_INFO("read in zstep:"<<zstep);
  //skip 6 float
  infile.read((char*)buffer, sizeof(float)*6);



  int totalSize = xsize*ysize*zsize;
  LOG_INFO("total data size:"<< totalSize);
  m_pfDose = new float[totalSize];
  memset(m_pfDose, 0, sizeof(float)*totalSize);
  infile.read((char*)m_pfDose, sizeof(float)*totalSize);
  infile.close();
  //set ctinfo datafield to (fluka y is ct z)
  //sway(y,z)

  m_xsize = xsize;
  m_ysize = ysize;
  m_zsize = zsize;

  m_xstart = xstart;
  m_ystart = ystart;
  m_zstart = zstart;
  m_xstep = xstep;
  m_ystep = ystep;
  m_zstep = zstep;



}
CFlukaDose::CFlukaDose(const string &csDoseFile)
{
    FILE *fpr = fopen(csDoseFile.c_str(), "rb");
    if(fpr==NULL)
    {
        cout<<"Files open error\n";
    }


    const int iNTitle=85;//85 char
    static char gcTitleContent[iNTitle]={0};
    fread(gcTitleContent,sizeof(char),iNTitle,fpr);
//    for (int i=0;i<iNTitle;i++)
//         cout<<gcTitleContent[i];

    fseek(fpr,iNTitle,0);
    const int iNother1 = 31;//char
    static char gcNother1[iNother1]={0};
    fread(gcNother1,sizeof(char),iNother1,fpr);
//    for (int i=0;i<iNother1;i++)
//         cout<<gcNother1[i];

    fseek(fpr,iNTitle+iNother1,0);
    const int iNother2 = 46;//char
    static char gcNother2[iNother2]={0};
    fread(gcNother2,sizeof(char),iNother2,fpr);
//    for (int i=0;i<iNother2;i++)
//         cout<<gcNother2[i];
//    cout<<endl<<endl;

    // xstart, xend,xsize, xstep, ystart,yend,ysize,ystep, zstart,zend,zsize,zstep都是4个字节的int或float,
    // have problems
    fseek(fpr,iNTitle+iNother1+iNother2,0);
    const int iNAxis = 12;//char
    static float gcAxis[iNAxis]={0};
    fread(gcAxis,sizeof(float),iNAxis,fpr);
//    for (int i=0;i<iNAxis;i++)
//         cout<<gcAxis[i]<<"\t";

    // do not read
    fseek(fpr,iNTitle+iNother1+iNother2+iNAxis*4,0);
    const int iNother3 = 24;//char
    static char gcNother3[iNother3]={0};
    fread(gcNother3,sizeof(char),iNother3,fpr);
//    for (int i=0;i<iNother3;i++)
//         cout<<gcNother3[i];
//    cout<<endl<<endl;


    fseek(fpr,iNTitle+iNother1+iNother2+iNAxis*4+iNother3,0);
//     const int iNDose=20240901;
//     static float gfDoseData[iNDose]={0};
//     float *gfDoseData = new float[iNDose];
    fread(m_pfDose,sizeof(float),N,fpr);
//     for(float &i:gfDoseData)
//         cout<<i<<"\t";
//     cout<<endl;
   fclose(fpr);

}

void CFlukaDose::UpdateIDD()
{
    std::ofstream iddDoseFile(siddDoseFile, std::ios::out | std::ios::trunc);
    std::ofstream PrimaryDoseFile(sPrimaryDoseFile, std::ios::out | std::ios::trunc);
    if(!iddDoseFile)
        std::cerr<<"File for output open error.";

    for(int i=0;i<Nz;i++)
    {
        for(int j=0; j<Nx*Ny;j++)
        {
            m_pfIDD[i]+=m_pfDose[Nx*Ny*i+j];
            PrimaryDoseFile<<m_pfDose[Nx*Ny*i+j]<<endl;
        }
//        m_pfIDD[i]=m_pfIDD[i]/Nx/Ny;
        iddDoseFile<<m_pfIDD[i]<<endl;
    }

    iddDoseFile.close();
    PrimaryDoseFile.close();

}

void CFlukaDose::UpdateInpProfile(float depth)
{


    int zIndex = depth/zStep;
    int xIndex = Nx/2;

    std::ofstream inpfile;
     inpfile.open(sInp,std::ios::out | std::ios::trunc);
    if (!inpfile)
        std::cout<<"Inp file open failed!"<<std::endl;

    for (size_t i = 0; i < Ny; ++i )
      {
        int index = zIndex * Nx* Ny + Nx * i + xIndex;

        int index0 = zIndex * Nx* Ny  + Nx * i + xIndex-1;
        int index2 = zIndex *  Nx* Ny  + Nx * i + xIndex-2;

        int index1 = zIndex *  Nx* Ny  + Nx * i + xIndex+1;
        int index3 = zIndex *  Nx* Ny  + Nx * i + xIndex+2;


        m_pfInpProfile[i] = m_pfDose[index] + m_pfDose[index0] + m_pfDose[index1] + m_pfDose[index2] + m_pfDose[index3];

        if(i<2)
        {
            std::cout<<m_pfDose[index]<<" "<<m_pfDose[index2]<<" "<<m_pfDose[index0]<<" "<<m_pfDose[index1]<<" "<<m_pfDose[index3]<<std::endl;
            std::cout<<index<<" "<<index2<<" "<<index0<<" "<<index1<<" "<<index3<<std::endl;
        }

        inpfile<<m_pfInpProfile[i]<<std::endl;

      }

    inpfile.close();


}

void CFlukaDose::UpdateXplProfile(float depth)
{

    int zIndex = depth/zStep;

    int yIndex = Ny/2;

     std::cout<<"zIndex: "<<zIndex<<"; yIndex: "<<yIndex<<std::endl;


    std::ofstream xplfile;
    xplfile.open(sXpl,std::ios::out | std::ios::trunc);
    if (!xplfile)
        std::cout<<"Xpl file open failed!"<<std::endl;

    for (size_t i = 0; i < Nx; ++i )
      {
        int index = zIndex * Nx* Ny + yIndex * Nx + i;

        int index0 = zIndex * Nx* Ny  + (yIndex-1) * Nx + i;
        int index2 = zIndex *  Nx* Ny  + (yIndex-2) * Nx + i;

        int index1 = zIndex *  Nx* Ny  + (yIndex+1) * Nx + i;
        int index3 = zIndex *  Nx* Ny  + (yIndex+2) * Nx + i;

//        float pos = (i+0.5)*ctinfo->xstep + ctinfo->xstart;

        m_pfXplProfile[i] = m_pfDose[index] + m_pfDose[index0] + m_pfDose[index1] + m_pfDose[index2] + m_pfDose[index3];

        // float curdose = 2*ctdose[index] + ctdose[index0] + ctdose[index1];

  //       float curdose = ctdose[index];

//        tuple<float,float> xplItem(pos, curdose);
//        xpldata.push_back(xplItem);

        xplfile<<m_pfXplProfile[i]<<std::endl;

      }

    xplfile.close();

}

float CFlukaDose::getXZMaxDose()
{
    float ymin,ymax;
    float zmin,zmax;
    cout<<"Enter the lower limits for the y-coordinate.:\n ";
    cin>>ymin;
    cout<<"Enter the upper limits for the y-coordinate.:\n ";
    cin>>ymax;

    cout<<"Enter the lower limits for the z-coordinate.:\n ";
    cin>>zmin;
    cout<<"Enter the upper limits for the z-coordinate.:\n ";
    cin>>zmax;

    cout<<"y_min ="<<ymin<<"\t y_max="<<ymax<<"\tz_min ="<<zmin<<"\t z_max= "<<zmax<<endl;

    float xzDose[m_xsize*m_zsize]{0};
    std::vector<float> dose;
   float curDose;

    int yBegin=(ymin-m_ystart)/m_ystep;
    int yEnd = (ymax-m_ystart)/m_ystep;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    for(size_t i=zBegin;i<zEnd;++i)
    {
        for (size_t j=0;j<m_xsize;++j)
        {
             curDose=0;
            for (size_t k=yBegin; k<yEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize];
            }

            curDose=curDose/(yEnd-yBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

            // verity
//            if (i==zBegin&&j<80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"maximum dose= "<<*maxDose <<"uSV/h for 60 nA particles"<<endl;

    return *maxDose;
}



float CFlukaDose::getYZMaxDose()
{
    float xmin,xmax;
    float zmin,zmax;
    cout<<"Enter the lower limits for the x-coordinate.:\n ";
    cin>>xmin;
    cout<<"Enter the upper limits for the x-coordinate.:\n ";
    cin>>xmax;

    cout<<"Enter the lower limits for the z-coordinate.:\n ";
    cin>>zmin;
    cout<<"Enter the upper limits for the z-coordinate.:\n ";
    cin>>zmax;

    cout<<"x_min ="<<xmin<<"\t y_max="<<xmax<<"\tz_min ="<<zmin<<"\t z_max= "<<zmax<<endl;

    float xzDose[m_xsize*m_zsize]{0};
    std::vector<float> dose;
   float curDose;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    for(size_t i=zBegin;i<zEnd;++i)
    {
        for (size_t j=0;j<m_ysize;++j)
        {
             curDose=0;
            for (size_t k=xBegin; k<xEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[k+m_xsize*j+i*m_xsize*m_ysize];
            }

            curDose=curDose/(xEnd-xBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

            // verity
//            if (i==zBegin&&j<80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"maximum dose= "<<*maxDose <<"uSV/h for 60 nA particles"<<endl;

    return *maxDose;


}

float CFlukaDose::getXZMaxDose(bool flag)
{
    float ymin=400,ymax=800;
    float zmin=-600,zmax=-430;
    cout<<"y_min ="<<ymin<<"\t y_max="<<ymax<<"\tz_min ="<<zmin<<"\t z_max= "<<zmax<<endl;

    float xzDose[m_xsize*m_zsize]{0};
    std::vector<float> dose;
   float curDose;

    int yBegin=(ymin-m_ystart)/m_ystep;
    int yEnd = (ymax-m_ystart)/m_ystep;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    for(size_t i=zBegin;i<zEnd;++i)
    {
        for (size_t j=0;j<m_xsize;++j)
        {
             curDose=0;
            for (size_t k=yBegin; k<yEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize];
            }

            curDose=curDose/(yEnd-yBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

            // verity
//            if (i==zBegin&&j<80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"\033[31mmaximum dose= "<<*maxDose <<"uSV/h for 60 nA particles\033[0m"<<endl;

    return *maxDose;

}

float CFlukaDose::getYZMaxDose(bool flag)
{
    float xmin=1050,xmax=1150;
    float zmin=-600,zmax=-430;
    cout<<"x_min ="<<xmin<<"\t y_max="<<xmax<<"\tz_min ="<<zmin<<"\t z_max= "<<zmax<<endl;

    float xzDose[m_xsize*m_zsize]{0};
    std::vector<float> dose;
   float curDose;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    for(size_t i=zBegin;i<zEnd;++i)
    {
        for (size_t j=0;j<m_ysize;++j)
        {
             curDose=0;
            for (size_t k=xBegin; k<xEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[k+m_xsize*j+i*m_xsize*m_ysize];
            }

            curDose=curDose/(xEnd-xBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

            // verity
//            if (i==zBegin&&j<80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"\033[31mmaximum dose= "<<*maxDose <<" uSV/h for 60 nA particles\033[0m"<<endl;

    return *maxDose;

}

float CFlukaDose::getXYXMaxDose()
{
    float xmin,xmax;
    float zmin,zmax;
    cout<<"Enter the lower limits for the z-coordinate.:\n ";
    cin>>zmin;
    cout<<"Enter the upper limits for the z-coordinate.:\n ";
    cin>>zmax;

    cout<<"Enter the lower limits for the x-coordinate.:\n ";
    cin>>xmin;
    cout<<"Enter the upper limits for the x-coordinate.:\n ";
    cin>>xmax;

    cout<<"z_min ="<<zmin<<"\t z_max="<<zmax<<"\tx_min ="<<xmin<<"\t x_max= "<<xmax<<endl;


    std::vector<float> dose;
   float curDose;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;
    cout<<m_xsize<<"\t"<<xBegin<<"\t"<<xEnd<<endl;

    for(size_t i=0;i<m_ysize;++i)
    {
        for (size_t j=xBegin;j<xEnd;++j)
        {
             curDose=0;
            for (size_t k=zBegin; k<zEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[k*m_xsize*m_ysize+i*m_xsize+j];
            }

            curDose=curDose/(zEnd-zBegin);

            //change to uSv/h for 60 nA particles
//            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

//             verity
//            if (i<3&&j<=xBegin+80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"maximum dose= "<<*maxDose <<"uSV/h for 60 nA particles"<<endl;

    return *maxDose;

}

float CFlukaDose::getXZXMaxDose()
{
    float xmin,xmax;
    float ymin,ymax;
    cout<<"Enter the lower limits for the y-coordinate.:\n ";
    cin>>ymin;
    cout<<"Enter the upper limits for the y-coordinate.:\n ";
    cin>>ymax;

    cout<<"Enter the lower limits for the x-coordinate.:\n ";
    cin>>xmin;
    cout<<"Enter the upper limits for the x-coordinate.:\n ";
    cin>>xmax;

    cout<<"y_min ="<<ymin<<"\t y_max="<<ymax<<"\tx_min ="<<xmin<<"\t x_max= "<<xmax<<endl;


    std::vector<float> dose;
   float curDose;

    int yBegin=(ymin-m_ystart)/m_ystep;
    int yEnd = (ymax-m_ystart)/m_ystep;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;
    cout<<m_xsize<<"\t"<<xBegin<<"\t"<<xEnd<<endl;

    for(size_t i=0;i<m_zsize;++i)
    {
        for (size_t j=xBegin;j<xEnd;++j)
        {
             curDose=0;
            for (size_t k=yBegin; k<yEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[i*m_xsize*m_ysize+k*m_xsize+j];
            }

            curDose=curDose/(yEnd-yBegin);

            //change to uSv/h for 60 nA particles
//            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

//             verity
            if (i<=0&&j<=xBegin+80)
                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"maximum dose= "<<*maxDose <<"uSV/h for 60 nA particles"<<endl;

    return *maxDose;

}

float CFlukaDose::getXYXMaxDose(bool flag)
{
    float xmin=1740,xmax=1900;
    float zmin=350,zmax=500;

    cout<<"z_min ="<<zmin<<"\t z_max="<<zmax<<"\tx_min ="<<xmin<<"\t x_max= "<<xmax<<endl;


    std::vector<float> dose;
   float curDose;

    int zBegin=(zmin-m_zstart)/m_zstep;
    int zEnd = (zmax-m_zstart)/m_zstep;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;
    cout<<m_xsize<<"\t"<<xBegin<<"\t"<<xEnd<<endl;
    int yEnd=(1067-m_ystart)/m_ystep;

    for(size_t i=0;i<yEnd;++i)
    {
        for (size_t j=xBegin;j<xEnd;++j)
        {
             curDose=0;
            for (size_t k=zBegin; k<zEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[k*m_xsize*m_ysize+i*m_xsize+j];
            }

            curDose=curDose/(zEnd-zBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

//             verity
//            if (i<3&&j<=xBegin+80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"\033[31mmaximum dose= "<<*maxDose <<" uSV/h for 60 nA particles\033[0m"<<endl;

    return *maxDose;

}

float CFlukaDose::getXZXMaxDose(bool flag)
{
    float xmin=1740,xmax=1900;
    float ymin=400,ymax=800;


    cout<<"y_min ="<<ymin<<"\t y_max="<<ymax<<"\tx_min ="<<xmin<<"\t x_max= "<<xmax<<endl;


    std::vector<float> dose;
   float curDose;

    int yBegin=(ymin-m_ystart)/m_ystep;
    int yEnd = (ymax-m_ystart)/m_ystep;

    int xBegin=(xmin-m_xstart)/m_xstep;
    int xEnd = (xmax-m_xstart)/m_xstep;
    cout<<m_xsize<<"\t"<<xBegin<<"\t"<<xEnd<<endl;

    for(size_t i=0;i<m_zsize;++i)
    {
        for (size_t j=xBegin;j<xEnd;++j)
        {
             curDose=0;
            for (size_t k=yBegin; k<yEnd;++k)
            {
//                xzDose[i*m_xsize+j]+=m_pfDose[j+m_xsize*k+i*m_xsize*m_ysize]*1.69*0.8*1e9;
                curDose+=m_pfDose[i*m_xsize*m_ysize+k*m_xsize+j];
            }

            curDose=curDose/(yEnd-yBegin);

            //change to uSv/h for 60 nA particles
            curDose=curDose*1.69*0.8*1e9;
            dose.push_back(curDose);

//             verity
//            if (i<=0&&j<=xBegin+80)
//                cout<<j<<": "<<curDose<<endl;
        }
    }


    auto maxDose=std::max_element(dose.begin(),dose.end());

    cout<<"\033[31mmaximum dose= "<<*maxDose <<" uSV/h for 60 nA particles\033[0m"<<endl;

    return *maxDose;

}


