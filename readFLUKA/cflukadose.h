#ifndef CFLUKADOSE_H
#define CFLUKADOSE_H
#include <iostream>
#include <string>
#include "externdata.h"
using std::string;


class CFlukaDose
{
public:
    CFlukaDose(const string & ifstream, const int flag);
    CFlukaDose(const string & ifstream);

    void UpdateIDD();

    float* GetIDD() const {return m_pfIDD;}

    void UpdateInpProfile(float depth);

    void UpdateXplProfile(float depth);

    float* GetXplProfile(){return m_pfXplProfile;}

    float getXZMaxDose();
    float getYZMaxDose();

    float getXZMaxDose(bool flag);
    float getYZMaxDose(bool flag);

    float getXYXMaxDose();
    float getXZXMaxDose();

    float getXYXMaxDose(bool flag);
    float getXZXMaxDose(bool flag);




    ~CFlukaDose()
    {
        delete [] m_pfDose;
        delete [] m_pfIDD;
        delete [] m_pfInpProfile;
        delete [] m_pfXplProfile;
    }

private:
    float* m_pfDose=NULL;
    float* m_pfIDD=NULL;
    float* m_pfInpProfile = NULL;
    float* m_pfXplProfile = NULL;
    float m_xstart=0;
    float m_ystart;
    float m_zstart;
    int m_xsize =0;
    int m_ysize=0;
    int m_zsize=0;
    float m_xstep=0;
    float m_ystep=0;
    float m_zstep=0;

};

#endif // CFLUKADOSE_H
