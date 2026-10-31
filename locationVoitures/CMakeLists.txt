cmake_minimum_required(VERSION 3.19)
project(locationVoitures LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(locationVoitures
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    locationsForm.h locationsForm.cpp locationsForm.ui



    ressources.qrc
    factureform.h factureform.cpp factureform.ui
    qrcodegenerator.h qrcodegenerator.cpp


)

target_link_libraries(locationVoitures
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt::PrintSupport
)

install(TARGETS locationVoitures
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET locationVoitures
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
