#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmrt/drtstrct.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmrt/drtstrct.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <RS_file>" << std::endl;
        return 1;
    }

    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filename);
    if (status.bad())
    {
        cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;
        return 1;
    }

    DcmDataset* dataset = fileformat.getDataset();
    DRTStructureSetIOD structureSet(*dataset);

    for (Uint16 i = 0; i < structureSet.getNumberOfROIs(); ++i)
    {
        DRTROIContourSequence& roiContourSequence = structureSet.getROIContourSequence(i);
        DRTROIContourSequence::Item& roiContourItem = roiContourSequence.getItem(0);

        cout << "ROI Number: " << i+1 << endl;
        cout << "ROI Name: " << roiContourItem.getROIName() << endl;
        cout << "Number of Contours: " << roiContourItem.getNumberOfContours() << endl;

        for (Uint16 j = 0; j < roiContourItem.getNumberOfContours(); ++j)
        {
            DRTContourSequence& contourSequence = roiContourItem.getContourSequence(j);
            DRTContourSequence::Item& contourItem = contourSequence.getItem(0);

            cout << "Contour Number: " << j+1 << endl;
            cout << "Contour Name: " << contourItem.getContourName() << endl;
            cout << "Number of Contour Points: " << contourItem.getNumberOfContourPoints() << endl;

            const Sint32* contourData;
            contourItem.getContourData(contourData);

            for (Uint16 k = 0; k < contourItem.getNumberOfContourPoints(); ++k)
            {
                Sint32 x = contourData[2*k];
                Sint32 y = contourData[2*k+1];

                cout << "Contour Point " << k+1 << ": (" << x << ", " << y << ")" << endl;
            }
        }
    }

}
