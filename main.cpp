#include "DicomFormat/DicomMap.h"
#include <fstream>
#include <string>
#include <iostream>

int main ()
{

  std::ifstream lIfs("PatternSignedGrayscale16.dcm", std::ios::in | std::ios::binary);
  std::string lContent( (std::istreambuf_iterator<char>(lIfs) ),
                     (std::istreambuf_iterator<char>()    ) );


  std::cout << " Content " << lContent.size() << std::endl;

  Orthanc::DicomMap lDicomMap;
  Orthanc::DicomMap::ParseDicomMetaInformation(lDicomMap, lContent.c_str(), lContent.size());
  std::cout << "Map size" << lDicomMap.GetSize() << std::endl;
  std::string lPatientStr;
  lDicomMap.CopyToString(lPatientStr, Orthanc::DICOM_TAG_PATIENT_ID, true);

  std::cout << "Patient Name" << lPatientStr << std::endl;
  return 0;

}
