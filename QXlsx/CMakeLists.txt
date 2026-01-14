# CMakeLists.txt for QXlsx Library

cmake_minimum_required(VERSION 3.16)

project(avm-qxlsx
    VERSION 2.0.1
    LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

if (QT_VERSION_MAJOR EQUAL 6)
    set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
else()
    set(CMAKE_CXX_STANDARD 11 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT DEFINED QXLSX_PARENTPATH)
	set(QXLSX_PARENTPATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
endif()

if(NOT DEFINED QXLSX_HEADERPATH)
	set(QXLSX_HEADERPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/header/)
endif()

if(NOT DEFINED QXLSX_SOURCEPATH)
	set(QXLSX_SOURCEPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/source/)
endif()

set(SRC_FILES
    source/xlsxcellrange.cpp
    source/xlsxcellrange.cpp
    source/xlsxcontenttypes.cpp
    source/xlsxdrawinganchor.cpp
    source/xlsxrichstring.cpp
    source/xlsxworkbook.cpp
    source/xlsxabstractooxmlfile.cpp
    source/xlsxcellreference.cpp
    source/xlsxdatavalidation.cpp
    source/xlsxdrawing.cpp
    source/xlsxsharedstrings.cpp
    source/xlsxworksheet.cpp
    source/xlsxabstractsheet.cpp
    source/xlsxchart.cpp
    source/xlsxdatetype.cpp
    source/xlsxformat.cpp
    source/xlsxsimpleooxmlfile.cpp
    source/xlsxzipreader.cpp
    source/xlsxcell.cpp
    source/xlsxchartsheet.cpp
    source/xlsxdocpropsapp.cpp
    source/xlsxmediafile.cpp
    source/xlsxstyles.cpp
    source/xlsxzipwriter.cpp
    source/xlsxcellformula.cpp
    source/xlsxcolor.cpp
    source/xlsxdocpropscore.cpp
    source/xlsxnumformatparser.cpp
    source/xlsxtheme.cpp
    source/xlsxcelllocation.cpp
    source/xlsxconditionalformatting.cpp
    source/xlsxdocument.cpp
    source/xlsxrelationships.cpp
    source/xlsxutility.cpp
    header/xlsxabstractooxmlfile_p.h
    header/xlsxchartsheet_p.h
    header/xlsxdocpropsapp_p.h
    header/xlsxformat_p.h
    header/xlsxsharedstrings_p.h
    header/xlsxworkbook_p.h
    header/xlsxabstractsheet_p.h
    header/xlsxcolor_p.h
    header/xlsxdocpropscore_p.h
    header/xlsxmediafile_p.h
    header/xlsxsimpleooxmlfile_p.h
    header/xlsxworksheet_p.h
    header/xlsxcellformula_p.h
    header/xlsxconditionalformatting_p.h
    header/xlsxdocument_p.h
    header/xlsxnumformatparser_p.h
    header/xlsxstyles_p.h
    header/xlsxzipreader_p.h
    header/xlsxcell_p.h
    header/xlsxcontenttypes_p.h
    header/xlsxdrawinganchor_p.h
    header/xlsxrelationships_p.h
    header/xlsxtheme_p.h
    header/xlsxzipwriter_p.h
    header/xlsxchart_p.h
    header/xlsxdatavalidation_p.h
    header/xlsxdrawing_p.h
    header/xlsxrichstring_p.h
    header/xlsxutility_p.h
)

set(QXLSX_PUBLIC_HEADERS
    header/xlsxabstractooxmlfile.h
    header/xlsxabstractsheet.h
    header/xlsxabstractsheet_p.h
    header/xlsxcellformula.h
    header/xlsxcell.h
    header/xlsxcelllocation.h
    header/xlsxcellrange.h
    header/xlsxcellreference.h
    header/xlsxchart.h
    header/xlsxchartsheet.h
    header/xlsxconditionalformatting.h
    header/xlsxdatavalidation.h
    header/xlsxdatetype.h
    header/xlsxdocument.h
    header/xlsxformat.h
    header/xlsxglobal.h
    header/xlsxrichstring.h
    header/xlsxworkbook.h
    header/xlsxworksheet.h
)

find_package(avm-gen QUIET)
if(${avm-gen_FOUND})
  message(STATUS "Found package avm-gen")
else()
  include(gen)
endif()

# Library building settings
if(BUILD_SHARED_LIBS)
    message(STATUS "${PROJECT_NAME} SHARED LIBRARY")
    add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${QXLSX_PUBLIC_HEADERS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DAVM_EXPORTS)
    target_compile_definitions(${PROJECT_NAME} INTERFACE -DAVM_IMPORTS)
else()
    message(STATUS "${PROJECT_NAME} STATIC LIBRARY")
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${QXLSX_PUBLIC_HEADERS})
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DHAVE_STATIC_BUILD)
endif()

# Creating library target
add_library(avm-energo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_NO_KEYWORDS
    QT_NO_CAST_TO_ASCII
    QT_NO_CAST_FROM_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_USE_QSTRINGBUILDER
    QT_NO_SIGNALS_SLOTS_KEYWORDS
    QT_USE_FAST_OPERATOR_PLUS
    QT_DISABLE_DEPRECATED_BEFORE=0x060600
)

if (NOT WIN32)
    # Strict iterators can't be used on Windows, they lead to a link error
    # when application code iterates over a QVector<QPoint> for instance, unless
    # Qt itself was also built with strict iterators.
    # See example at https://bugreports.qt.io/browse/AUTOSUITE-946
    target_compile_definitions(${PROJECT_NAME} PRIVATE QT_STRICT_ITERATORS)
endif()

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

# Set project version as qxlsx target property
target_link_libraries(${PROJECT_NAME}
   Qt${QT_VERSION_MAJOR}::Core
   Qt${QT_VERSION_MAJOR}::Gui
   avm-gen
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${QXLSX_HEADERPATH}
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/header>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOVERSION 0.${PROJECT_VERSION}
    PUBLIC_HEADER "${QXLSX_PUBLIC_HEADERS}"
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}_Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} COMPONENT devel
)

install(EXPORT ${PROJECT_NAME}_Targets
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    COMPONENT devel
)

# create version file for cmake project
write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

set(VERSION_IN ${CMAKE_CURRENT_SOURCE_DIR}/VERSION.in)
set(VERSION_OUT ${CMAKE_CURRENT_SOURCE_DIR}/package/src/VERSION)
configure_file(${VERSION_IN} ${VERSION_OUT} @ONLY)
