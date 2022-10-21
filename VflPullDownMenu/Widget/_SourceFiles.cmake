# $Id:$

set( RelativeDir "./Widget" )
set( RelativeSourceGroup "Source Files\\Widget" )

set( DirFiles
	_SourceFiles.cmake
	VwBorderView.cpp
	VwBorderView.h
	VwBorderWidget.cpp
	VwBorderWidget.h
	VwCheckBoxWidget.cpp
	VwCheckBoxWidget.h
	VwCheckBoxWidgetControl.cpp
	VwCheckBoxWidgetControl.h
	VwCheckBoxWidgetView.cpp
	VwCheckBoxWidgetView.h
	VwCircleWidget.cpp
	VwCircleWidget.h	
	VwCircleWidgetView.cpp
	VwCircleWidgetView.h
	VwPlaneWidgetControl.cpp
	VwPlaneWidgetControl.h
	VwScalerWidgetControl.cpp
	VwScalerWidgetControl.h
	VwSliderWidgetControl.cpp
	VwSliderWidgetControl.h
	VwTexturePlaneWidget.cpp
	VwTexturePlaneWidget.h
	VwTexturePlaneWidgetControl.cpp
	VwTexturePlaneWidgetControl.h
	VwWidgetControl.cpp
	VwWidgetControl.h
	VwScalerWidget.cpp
	VwScalerWidget.h
	VwScalerWidgetView.cpp
	VwScalerWidgetView.h

)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

