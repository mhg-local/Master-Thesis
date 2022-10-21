# $Id:$

set( RelativeDir "./FocusStrategy" )
set( RelativeSourceGroup "Source Files\\FocusStrategy" )
set( DirFiles
	VwFocusStrategy.h	
	VwFocusStrategy.cpp
	VwFocusStrategyUtility.cpp
	VwFocusStrategyUtility.h
	VwHandleSignal.cpp
	VwHandleSignal.h
	_SourceFiles.cmake
)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

