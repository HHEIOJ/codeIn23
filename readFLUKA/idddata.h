#ifndef IDDDATA_H
#define IDDDATA_H
#include "externdata.h"

void iddData( const int & Nx,  const int & Ny,  const int & Nz );
/**
 * @brief profileData
 * @param Nx
 * @param Ny
 * @param Nz
 * @param depth
 * @param flag: flag==0, calculate xpl profile; flag==others, calculate inp profile.
 */
void profileData(const int & Nx,  const int & Ny,  const int & Nz, const double depth, const bool flag);
void Test_iddData();
#endif // IDDDATA_H
