#
# 1394020320@qq.com
#

cmake_minimum_required(VERSION 3.4.3)
project(SouiEditor)
file (TO_CMAKE_PATH "$ENV{SOUIPATH}" SOUI_ROOT)

message(STATUS "SOUI_ROOT: ${SOUI_ROOT}")
if ("${SOUI_ROOT}" STREQUAL "")
	message(FATAL_ERROR "FATAL:can't find env variable SOUIPATH, clone soui core and install wizard first, please.")
endif()

include(${SOUI_ROOT}/__cmake/cotire.cmake)
include(${SOUI_ROOT}/__cmake/internal_utils.cmake)
include(${SOUI_ROOT}/__cmake/global.cmake)

readSettingFile(UNICODE "1" USE_UNICODE)
readSettingFile(WCHAR "1" WCHAR_AS_DEFAULT)
readSettingFile(MT "0" SHARED_CRT)
readSettingFile(SUPPORT_XP "1" XP_TOOLSET)

#message(STATUS "USE_UNICODE: ${USE_UNICODE}")
#message(STATUS "WCHAR_AS_DEFAULT: ${WCHAR_AS_DEFAULT}")
#message(STATUS "SHARED_CRT: ${SHARED_CRT}")
#message(STATUS "XP_TOOLSET: ${XP_TOOLSET}")

config_compiler_and_linker()

include_directories(${SOUI_ROOT}/config)
include_directories(${SOUI_ROOT}/components)
include_directories(${SOUI_ROOT}/utilities/include)
include_directories(${SOUI_ROOT}/SOUI/include)
include_directories(${SOUI_ROOT}/third-part/Scintilla/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_ROOT}/controls.extend)


set(EXTENDCOTROLS ${EXTENDCOTROLS}
	${SOUI_ROOT}/controls.extend/image3d/3dlib.h
	${SOUI_ROOT}/controls.extend/image3d/3dmatrix.h
	${SOUI_ROOT}/controls.extend/image3d/3dTransform.h
	${SOUI_ROOT}/controls.extend/ExtendSkins.h
	${SOUI_ROOT}/controls.extend/image3d/PerspectiveTransform.h
	${SOUI_ROOT}/controls.extend/gif/SAniImgFrame.h
	${SOUI_ROOT}/controls.extend/SButtonEx.h
	${SOUI_ROOT}/controls.extend/SChromeTabCtrl.h
	${SOUI_ROOT}/controls.extend/SFreeMoveWindow.h
	${SOUI_ROOT}/controls.extend/gif/SGifPlayer.h
	#${SOUI_ROOT}/controls.extend/SImageEx.h
	${SOUI_ROOT}/controls.extend/SImageMaskWnd.h
	${SOUI_ROOT}/controls.extend/gif/SSkinAPNG.h
	${SOUI_ROOT}/controls.extend/gif/SSkinGif.h
	${SOUI_ROOT}/controls.extend/SSkinMutiFrameImg.h
	${SOUI_ROOT}/controls.extend/STabCtrl2.h
	${SOUI_ROOT}/controls.extend/SText.h
	${SOUI_ROOT}/controls.extend/STurn3DView.h
	${SOUI_ROOT}/controls.extend/SScrollText.h
	${SOUI_ROOT}/controls.extend/SIPAddressCtrl.h
	${SOUI_ROOT}/controls.extend/SListCtrlEx.h
	${SOUI_ROOT}/controls.extend/SRatingBar.h
	${SOUI_ROOT}/controls.extend/SRadioBox2.h
	${SOUI_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.h
	${SOUI_ROOT}/controls.extend/SGroupList.h
)

set(EXTENDCOTROLS ${EXTENDCOTROLS}
	${SOUI_ROOT}/controls.extend/image3d/3dlib.cpp
	${SOUI_ROOT}/controls.extend/image3d/3dmatrix.cpp
	${SOUI_ROOT}/controls.extend/image3d/3dtransform.cpp
	${SOUI_ROOT}/controls.extend/ExtendSkins.cpp
	${SOUI_ROOT}/controls.extend/SButtonEx.cpp
	${SOUI_ROOT}/controls.extend/SChromeTabCtrl.cpp
	${SOUI_ROOT}/controls.extend/SFreeMoveWindow.cpp
	${SOUI_ROOT}/controls.extend/gif/SGifPlayer.cpp
	#${SOUI_ROOT}/controls.extend/SImageEx.cpp
	${SOUI_ROOT}/controls.extend/SImageMaskWnd.cpp
	${SOUI_ROOT}/controls.extend/gif/SSkinAPNG.cpp
	${SOUI_ROOT}/controls.extend/gif/SSkinGif.cpp
	${SOUI_ROOT}/controls.extend/SSkinMutiFrameImg.cpp
	${SOUI_ROOT}/controls.extend/STabCtrl2.cpp
	${SOUI_ROOT}/controls.extend/SText.cpp
	${SOUI_ROOT}/controls.extend/STurn3DView.cpp
	${SOUI_ROOT}/controls.extend/SScrollText.cpp
	${SOUI_ROOT}/controls.extend/SIPAddressCtrl.cpp
	${SOUI_ROOT}/controls.extend/SListCtrlEx.cpp
	${SOUI_ROOT}/controls.extend/SRatingBar.cpp
	${SOUI_ROOT}/controls.extend/SRadioBox2.cpp
	${SOUI_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.cpp
	${SOUI_ROOT}/controls.extend/SGroupList.cpp
)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
file(GLOB_RECURSE CURRENT_SRCS  *.cpp)
file(GLOB_RECURSE CURRENT_SOUIS  *.xml *.idx *.ico)
file(GLOB_RECURSE CURRENT_RC *.rc *.rc2)

source_group("Header Files" FILES ${CURRENT_HEADERS})
source_group("Source Files" FILES ${CURRENT_SRCS})
source_group("SoUI Resouece" FILES ${CURRENT_SOUIS})
source_group("Resource Files" FILES ${CURRENT_RC})
source_group("Extend Cotrols" FILES ${EXTENDCOTROLS})

link_directories(${SOUI_ROOT}/bin)
add_executable(SouiEditor WIN32 ${CURRENT_HEADERS} ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC} ${EXTENDCOTROLS})

#add_dependencies(SouiEditor soui-sys-resource)
#target_link_libraries(SouiEditor utilities soui Scintilla imm32)
target_link_libraries(SouiEditor
        debug utilitiesd optimized utilities
        debug souid optimized soui
        debug Scintillad optimized Scintilla
        imm32
)

set_target_properties(SouiEditor PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties (SouiEditor PROPERTIES
    FOLDER demos
)
cotire(SouiEditor)
