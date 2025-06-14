set (LOCAL_TARGET_NAME "Mag_Elektr")

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools Sql)

set (INC_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
set (LANG_DIR ${CMAKE_CURRENT_LIST_DIR}/lang)
set (RES_DIR ${CMAKE_CURRENT_LIST_DIR}/res)
set (SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set (UI_DIR ${CMAKE_CURRENT_LIST_DIR}/ui)

set(LANG_PREFIX "/i18n")

################################################################################

set (RES_FILES
    ${RES_DIR}/resources.qrc
)

# set (UI_FILES )

set (SRC_FILES 
    ${SRC_DIR}/main.cpp

    ${SRC_DIR}/mainDatabase/mainDatabase.cpp

    ${SRC_DIR}/common/mainStyle.cpp

    ${SRC_DIR}/loginWindow/loginWindow.cpp

    ${SRC_DIR}/mainWindow/mainWindow.cpp
    ${SRC_DIR}/mainWindow/mainToolBar.cpp
    ${SRC_DIR}/mainWindow/mainToolButton.cpp

    ${SRC_DIR}/componentsPage/componentsPage.cpp
    ${SRC_DIR}/componentsPage/componentsPage/containerWidget.cpp
    ${SRC_DIR}/componentsPage/componentsPage/filterWidget.cpp
    ${SRC_DIR}/componentsPage/componentsPage/treeFilterWidget.cpp

    ${SRC_DIR}/componentsPage/component/componentWidget.cpp
    ${SRC_DIR}/componentsPage/component/editWidget.cpp
    ${SRC_DIR}/componentsPage/component/parametersWidget.cpp
    ${SRC_DIR}/componentsPage/component/quantityWidget.cpp

    ${SRC_DIR}/historyPage/historyPage.cpp
    ${SRC_DIR}/historyPage/historyPage/containerWidget.cpp
    ${SRC_DIR}/historyPage/historyPage/filterWidget.cpp

    ${SRC_DIR}/modifyPage/modifyPage.cpp
    ${SRC_DIR}/modifyPage/modComponentsPage.cpp
    ${SRC_DIR}/modifyPage/modUserPage.cpp
    ${SRC_DIR}/modifyPage/addUserDialog.cpp
    ${SRC_DIR}/modifyPage/addComponentDialog.cpp

)

################################################################################

qt_standard_project_setup(
    REQUIRES 6.7
    I18N_SOURCE_LANGUAGE pl
    I18N_TRANSLATED_LANGUAGES pl en
)

qt_add_executable(${LOCAL_TARGET_NAME} MANUAL_FINALIZATION)

target_include_directories(${LOCAL_TARGET_NAME} PRIVATE ${INC_DIR})

# qt_add_ui(${LOCAL_TARGET_NAME} SOURCES ${UI_FILES})

# qt_add_translations(${LOCAL_TARGET_NAME} TS_FILE_BASE ${LOCAL_TARGET_NAME} TS_OUTPUT_DIRECTORY ${LANG_DIR})

target_sources(${LOCAL_TARGET_NAME} PRIVATE ${SRC_FILES} ${RES_FILES})

target_link_libraries(${LOCAL_TARGET_NAME} PRIVATE Qt::Core Qt::Widgets Qt::Sql)

set_target_properties(${LOCAL_TARGET_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

qt_finalize_target(${LOCAL_TARGET_NAME})

# add_dependencies(${LOCAL_TARGET_NAME} update_translations)