# We want a recent CMake file
cmake_minimum_required(VERSION 3.0)

# The projectc
project(echopenLightDicom)

#Enable C++11
set (CMAKE_CXX_STANDARD 11)

# Create variables with files to be compiled
set(SRCS
    ./DicomFormat/DicomMap.cpp
    ./DicomFormat/DicomValue.cpp
    ./DicomFormat/DicomTag.cpp
    Enumerations.cpp
    Logging.cpp
    Toolbox.cpp
    SystemToolbox.cpp
    main.cpp
    )

set(HEADERS
  ./DicomFormat/DicomMap.h
  ./DicomFormat/DicomValue.h
  ./DicomFormat/DicomTag.h
	Endianness.h
	Enumerations.h
	Logging.h
  OrthancException.h
  Toolbox.h
  SystemToolbox.h
    )

#Compile with debug symbol
set(CMAKE_BUILD_TYPE Debug)

#Define Orthanc specific macro
add_definitions(-DORTHANC_ENABLE_BASE64=0)
add_definitions(-DORTHANC_ENABLE_LOGGING=1)
add_definitions(-DORTHANC_ENABLE_LOGGING_PLUGIN=0)

add_definitions(-DORTHANC_ENABLE_LOCALE=0)
add_definitions(-DORTHANC_ENABLE_MD5=0)
add_definitions(-DORTHANC_ENABLE_PUGIXML=0)

add_definitions(-DORTHANC_DEFAULT_DICOM_ENCODING=Encoding_Latin1)
add_definitions(-DORTHANC_SANDBOXED=0)

# Include Boost library
FIND_PACKAGE( Boost 1.40 COMPONENTS date_time filesystem system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

#Include UUID Library
FIND_PATH(UUID_INCLUDE_DIR uuid/uuid.h)
FIND_LIBRARY(UUID_LIBRARY NAMES uuid PATH)
INCLUDE_DIRECTORIES( ${UUID_INCLUDE_DIR} )

IF(NOT UUID_LIBRARY)
	SET(UUID_LIBRARY "")
ENDIF(NOT UUID_LIBRARY)

IF(UUID_INCLUDE_DIR)
	SET(UUID_FOUND TRUE)
ENDIF(UUID_INCLUDE_DIR)

IF(NOT UUID_FOUND)
	IF(UUID_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find UUID")
	ENDIF(UUID_FIND_REQUIRED)
ENDIF(NOT UUID_FOUND)

add_executable(echOpenDICOMLight ${SRCS} ${HEADERS})
target_link_libraries(echOpenDICOMLight  ${Boost_LIBRARIES} ${UUID_LIBRARY})
