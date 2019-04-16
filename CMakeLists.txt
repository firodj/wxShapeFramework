cmake_minimum_required (VERSION 3.9)

project (wxShapeFramework)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 11)
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base adv html xml xrc)
include(${wxWidgets_USE_FILE})

set(wxSf_SOURCE_FILES
src/FixedRectShape.cpp
src/TextShapeXml.cpp
src/LineShape.cpp
src/ShapeCanvas.cpp
src/MultiSelRect.cpp
src/FlexGridShape.cpp
src/ScaledDC.cpp
src/EllipseShape.cpp
src/wx_pch.h
src/OrthoShape.cpp
src/OpenArrow.cpp
src/BitmapShapeXml.cpp
src/ControlShape.cpp
src/Printout.cpp
src/DiamondArrow.cpp
src/DiamondShape.cpp
src/CommonFcn.cpp
src/RoundOrthoShape.cpp
src/ArrowBase.cpp
src/Thumbnail.cpp
src/PolygonShapeXml.cpp
src/CurveShape.cpp
src/TextShape.cpp
src/DiagramManager.cpp
src/CircleShape.cpp
src/GridShape.cpp
src/CircleArrow.cpp
src/PolygonShape.cpp
src/RoundRectShape.cpp
src/SolidArrow.cpp
src/AutoLayout.cpp
src/ShapeHandle.cpp
src/EditTextShape.cpp
src/ShapeDockpoint.cpp
src/CanvasState.cpp
src/CanvasHistory.cpp
src/BitmapShape.cpp
src/ShapeBaseXml.cpp
src/RectShape.cpp
src/ShapeDataObject.cpp
src/ShapeBase.cpp
src/SFEvents.cpp

src/wxxmlserializer/XmlSerializer.cpp
src/wxxmlserializer/PropertyIO.cpp

include/wx/wxsf/CurveShape.h
include/wx/wxsf/RoundOrthoShape.h
include/wx/wxsf/DiagramManager.h
include/wx/wxsf/CanvasHistory.h
include/wx/wxsf/SolidArrow.h
include/wx/wxsf/ShapeBase.h
include/wx/wxsf/Defs.h
include/wx/wxsf/RectShape.h
include/wx/wxsf/CanvasState.h
include/wx/wxsf/CommonFcn.h
include/wx/wxsf/ShapeHandle.h
include/wx/wxsf/RoundRectShape.h
include/wx/wxsf/EllipseShape.h
include/wx/wxsf/ShapeCanvas.h
include/wx/wxsf/ShapeDockpoint.h
include/wx/wxsf/LineShape.h
include/wx/wxsf/Thumbnail.h
include/wx/wxsf/CircleArrow.h
include/wx/wxsf/ArrowBase.h
include/wx/wxsf/DiamondShape.h
include/wx/wxsf/wxShapeFramework.h
include/wx/wxsf/TextShape.h
include/wx/wxsf/FlexGridShape.h
include/wx/wxsf/OrthoShape.h
include/wx/wxsf/GridShape.h
include/wx/wxsf/AutoLayout.h
include/wx/wxsf/EditTextShape.h
include/wx/wxsf/CircleShape.h
include/wx/wxsf/ScaledDC.h
include/wx/wxsf/MultiSelRect.h
include/wx/wxsf/FixedRectShape.h
include/wx/wxsf/ShapeDataObject.h
include/wx/wxsf/Printout.h
include/wx/wxsf/BitmapShape.h
include/wx/wxsf/SFEvents.h
include/wx/wxsf/ControlShape.h
include/wx/wxsf/PolygonShape.h
include/wx/wxsf/DiamondArrow.h
include/wx/wxsf/OpenArrow.h

include/wx/wxxmlserializer/Defs.h
include/wx/wxxmlserializer/XmlSerializer.h
include/wx/wxxmlserializer/PropertyIO.h
)

if (WIN32)
  list(APPEND wxSf_SOURCE_FILES src/wxSF.rc)
endif (WIN32)

message(STATUS "wxWidgets LIB: ${wxWidgets_LIBRARIES}")
add_library(wxSf ${wxSf_SOURCE_FILES})
target_include_directories(wxSf PRIVATE include
  PRIVATE src)
target_include_directories(wxSf INTERFACE include)

###############################################################################

set(wxSFSample1_SOURCE_FILES
samples/wxSFSample1/wxSFSample1Main.cpp
samples/wxSFSample1/wxSFSample1App.cpp

samples/wxSFSample1/wxSFSample1Main.h
samples/wxSFSample1/wxSFSample1App.h
)

if (WIN32)
  list(APPEND wxSFSample1_SOURCE_FILES samples/wxSFSample1/wxSF.rc)
endif (WIN32)

add_executable(sample1 WIN32 ${wxSFSample1_SOURCE_FILES})
target_link_libraries(sample1 PRIVATE ${wxWidgets_LIBRARIES} wxSf)

set(wxSFSample4_SOURCE_FILES
samples/wxSFSample4/wxSFSample4App.cpp
samples/wxSFSample4/wxSFSample4Main.cpp

samples/wxSFSample4/wxSFSample4App.h
samples/wxSFSample4/wxSFSample4Main.h
)

if (WIN32)
  list(APPEND wxSFSample4_SOURCE_FILES samples/wxSFSample4/wxSF.rc)
endif (WIN32)

add_executable(sample4 WIN32 ${wxSFSample4_SOURCE_FILES})
target_link_libraries(sample4 PRIVATE ${wxWidgets_LIBRARIES} wxSf)

set(wxSFSample3_SOURCE_FILES
samples/wxSFSample3/wxSFSample3Main.cpp
samples/wxSFSample3/wxSFSample3App.cpp
samples/wxSFSample3/StarShape.cpp

samples/wxSFSample3/wxSFSample3Main.h
samples/wxSFSample3/wxSFSample3App.h
samples/wxSFSample3/StarShape.h
)

if (WIN32)
  list(APPEND wxSFSample3_SOURCE_FILES samples/wxSFSample3/wxSF.rc)
endif (WIN32)

add_executable(sample3 WIN32 ${wxSFSample3_SOURCE_FILES})
target_link_libraries(sample3 PRIVATE ${wxWidgets_LIBRARIES} wxSf)

set(wxSFSample2_SOURCE_FILES
samples/wxSFSample2/wxSFSample2App.cpp
samples/wxSFSample2/wxSFSample2Main.cpp
samples/wxSFSample2/SampleCanvas.cpp
samples/wxSFSample2/SampleShape.cpp

samples/wxSFSample2/wxSFSample2App.h
samples/wxSFSample2/SampleCanvas.h
samples/wxSFSample2/wxSFSample2Main.h
samples/wxSFSample2/SampleShape.h
)

if (WIN32)
  list(APPEND wxSFSample2_SOURCE_FILES samples/wxSFSample2/wxSF.rc)
endif (WIN32)

add_executable(sample2 WIN32 ${wxSFSample2_SOURCE_FILES})
target_link_libraries(sample2 PRIVATE ${wxWidgets_LIBRARIES} wxSf)

set(wxSFDemo_SOURCE_FILES
samples/wxSFDemo/FrameCanvas.cpp
samples/wxSFDemo/MainFrame.cpp
samples/wxSFDemo/MainApp.cpp
samples/wxSFDemo/GUI.cpp

samples/wxSFDemo/Ids.h
samples/wxSFDemo/GUI.h
samples/wxSFDemo/Art.h
samples/wxSFDemo/MainApp.h
samples/wxSFDemo/MainFrame.h
)

if (WIN32)
  list(APPEND wxSFDemo_SOURCE_FILES samples/wxSFDemo/wxSF.rc)
endif (WIN32)

add_executable(demo WIN32 ${wxSFDemo_SOURCE_FILES})
target_link_libraries(demo PRIVATE ${wxWidgets_LIBRARIES} wxSf)

###############################################################################

if (WIN32)
else (WIN32)
  target_compile_options(wxSf PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )

  # set_target_properties(wxSf PROPERTIES 
  #   COMPILE_FLAGS "-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++"
  #   LINK_FLAGS "-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++"
  # target_link_options(wxSf PRIVATE
  #   -mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++)
  # set_target_properties(gui PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

  target_compile_options(sample1 PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )
  target_compile_options(sample2 PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )
  target_compile_options(sample3 PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )
  target_compile_options(sample4 PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )
  target_compile_options(demo PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>
    )
endif (WIN32)
