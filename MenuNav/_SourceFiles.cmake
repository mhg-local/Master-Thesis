# $Id: _SourceFiles.cmake 49363 2015-04-20 14:24:47Z dz762974 $

set( RelativeDir "." )
set( RelativeSourceGroup "Source Files" )

set( DirFiles
	MenuNav.cpp
	MenuNav.h
	Hand.cpp
	Hand.h
	HandInteractionManager.cpp
	HandInteractionManager.h
	main.cpp
	InitConstants.cpp
	InitConstants.h
	MassegeWidget.cpp
	MassegeWidget.h
	setup.ini
	_SourceFiles.cmake
)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

