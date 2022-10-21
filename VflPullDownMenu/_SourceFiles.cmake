# $Id:$

set( RelativeDir "." )
set( RelativeSourceGroup "Source Files" )
set( SubDirs Elements FocusStrategy Widget)

set( DirFiles
	_SourceFiles.cmake
     VglConfig.h
	VpmGlobalConfiguration.cpp
	VpmGlobalConfiguration.h
	VpmPullDownMenu.cpp
	VpmPullDownMenu.h
	VpmPullDownMenuView.cpp
	VpmPullDownMenuView.h
	VpmAnimation.cpp
	VpmAnimation.h
	VpmTimer.cpp
	VpmTimer.h
	
)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

set( SubDirFiles "" )
foreach( Dir ${SubDirs} )
	list( APPEND SubDirFiles "${RelativeDir}/${Dir}/_SourceFiles.cmake" )
endforeach()

foreach( SubDirFile ${SubDirFiles} )
	include( ${SubDirFile} )
endforeach()

