# $Id:$

set( RelativeDir "./Elements" )
set( RelativeSourceGroup "Source Files\\Elements" )

set( DirFiles
	_SourceFiles.cmake
	VpmBaseButtonElement.cpp
	VpmBaseButtonElement.h
	VpmCheckBoxElement.cpp
	VpmCheckBoxElement.h
	VpmElement.cpp
	VpmElement.h
	VpmElementView.cpp
	VpmElementView.h
	VpmLabelElement.cpp
	VpmLabelElement.h
	VpmRadioButtonElement.cpp
	VpmRadioButtonElement.h	
	VpmScalerElement.cpp
	VpmScalerElement.h
	VpmSliderElement.cpp
	VpmSliderElement.h
	VpmSoildButtonElement.cpp
	VpmSoildButtonElement.h
	VpmTextureButtonElement.cpp
	VpmTextureButtonElement.h
	
)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

