set( VFLPULLDOWNMENU_RELATIVE_INCLUDE_DIRS "include" )
set( VFLPULLDOWNMENU_RELATIVE_LIBRARY_DIRS "lib" )
set( VFLPULLDOWNMENU_RELATIVE_SHADER_DIRS "" )
set( VFLPULLDOWNMENU_DEFINITIONS "" )
set( VFLPULLDOWNMENU_HWARCH "win32-x64.vc12" )
set( VFLPULLDOWNMENU_LIBRARIES
		optimized VflPullDownMenu
		debug VflPullDownMenuD )
set( VFLPULLDOWNMENU_DEPENDENCIES package;VistaCoreLibs;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaWidgets;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaOGLExt;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VflTextRendering;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaOpenGLWidgets;REQUIRED;FIND_DEPENDENCIES )

# msvc-project for inclusion in other solutions - always empty for installations
set( VFLPULLDOWNMENU_MSVC_PROJECT )

# we're getting installed to ROOT_DIR/cmake, so to get our root dir, we have to take the current dir
# and look for the lib dir, which can be one, two, or three steps up
# we check if the folder is correct by testing if the first library dir exists there
set( _TEST_DIR "${VflPullDownMenu_DIR}" )
list( GET VFLPULLDOWNMENU_RELATIVE_LIBRARY_DIRS 0 _TEST_SUBDIR )
foreach( _STEP RANGE 3 )
	get_filename_component( _TEST_DIR "${_TEST_DIR}" PATH ) # one dir up
	if( EXISTS "${_TEST_DIR}/${_TEST_SUBDIR}" )
		set( VFLPULLDOWNMENU_ROOT_DIR "${_TEST_DIR}" )
		break()
	endif( EXISTS "${_TEST_DIR}/${_TEST_SUBDIR}" )
endforeach( _STEP RANGE 3 )

if( NOT VFLPULLDOWNMENU_ROOT_DIR )
	message( SEND_ERROR "Package configfile for \"VflPullDownMenu\" found in \"${VflPullDownMenu_DIR}\", "
                       "but matching library directory is missing" )
endif( NOT VFLPULLDOWNMENU_ROOT_DIR )


# set include/lib dirs relative to root dir
set( VFLPULLDOWNMENU_INCLUDE_DIRS  )
foreach( _DIR ${VFLPULLDOWNMENU_RELATIVE_INCLUDE_DIRS} )
	list( APPEND VFLPULLDOWNMENU_INCLUDE_DIRS "${VFLPULLDOWNMENU_ROOT_DIR}/${_DIR}" )
endforeach( _DIR ${VFLPULLDOWNMENU_RELATIVE_INCLUDE_DIRS} )

set( VFLPULLDOWNMENU_LIBRARY_DIRS  )
foreach( _DIR ${VFLPULLDOWNMENU_RELATIVE_LIBRARY_DIRS} )
	list( APPEND VFLPULLDOWNMENU_LIBRARY_DIRS "${VFLPULLDOWNMENU_ROOT_DIR}/${_DIR}" )
endforeach( _DIR ${VFLPULLDOWNMENU_RELATIVE_LIBRARY_DIRS} )

set( VFLPULLDOWNMENU_SHADER_DIRS  )
foreach( _DIR ${VFLPULLDOWNMENU_RELATIVE_SHADER_DIRS} )
	list( APPEND VFLPULLDOWNMENU_SHADER_DIRS "${VFLPULLDOWNMENU_ROOT_DIR}/${_DIR}" )
endforeach( _DIR ${VFLPULLDOWNMENU_RELATIVE_SHADER_DIRS} )

set( VFLPULLDOWNMENU_FOUND TRUE )
