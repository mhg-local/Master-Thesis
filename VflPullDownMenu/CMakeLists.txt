	# $Id:$

cmake_minimum_required( VERSION 2.8 )

if( NOT VW_COMMON_BUILD )
	project( VflPullDownMenu )
	list( APPEND CMAKE_MODULE_PATH "$ENV{VISTA_CMAKE_COMMON}" )
	include( VistaCommon )
endif( NOT VW_COMMON_BUILD )

vista_set_version( VflPullDownMenu HEAD "HEAD" svn_rev )

vista_use_package( VistaCoreLibs "HEAD" REQUIRED FIND_DEPENDENCIES )
vista_use_package( VistaWidgets "HEAD" REQUIRED FIND_DEPENDENCIES )
vista_use_package( VistaOGLExt "HEAD" REQUIRED FIND_DEPENDENCIES )
vista_use_package( VflTextRendering "HEAD" REQUIRED FIND_DEPENDENCIES )
vista_use_package( VistaOpenGLWidgets   REQUIRED FIND_DEPENDENCIES )

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}" )

# Including the source files of all source subfolders recursively
include( "./_SourceFiles.cmake" )

add_library( VflPullDownMenu ${ProjectSources} )

#The following line prevent CMake from adding all depencies to other projects that link it from within the same cmake build
#set_property( TARGET VflPullDownMenu PROPERTY LINK_INTERFACE_LIBRARIES "" )
target_link_libraries( VflPullDownMenu
	${VISTA_USE_PACKAGE_LIBRARIES} # contains all libraries from vista_use_package() calls
)

vista_configure_lib( VflPullDownMenu )
if( VW_COMMON_BUILD )
	vista_install( VflPullDownMenu VflPullDownMenu )
else( VW_COMMON_BUILD )
	vista_install( VflPullDownMenu )
endif( VW_COMMON_BUILD )
vista_create_cmake_configs( VflPullDownMenu )
vista_create_default_info_file( VflPullDownMenu )
