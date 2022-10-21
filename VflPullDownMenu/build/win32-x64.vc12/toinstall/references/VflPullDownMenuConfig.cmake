set( VFLPULLDOWNMENU_REFERENCED_FILE "G:/Dev/VflPullDownMenu/dist/win32-x64.vc12/share/VflPullDownMenu/cmake/VflPullDownMenuConfig.cmake" )

if( EXISTS "${VFLPULLDOWNMENU_REFERENCED_FILE}" )
	if( NOT PACKAGE_REFERENCE_EXISTS_TEST )
		# we let the variable XYZ_DIR to the actual config file
		get_filename_component( VflPullDownMenu_DIR  "${VFLPULLDOWNMENU_REFERENCED_FILE}" PATH )
		set( VflPullDownMenu_ACTUAL_DIR "${VflPullDownMenu_DIR}" )
		include( ${VFLPULLDOWNMENU_REFERENCED_FILE} )
	endif( NOT PACKAGE_REFERENCE_EXISTS_TEST )
else( EXISTS "${VFLPULLDOWNMENU_REFERENCED_FILE}" )
	set( PACKAGE_REFERENCE_OUTDATED TRUE )
	# if case a version is searched, we output an unsuitable error (but should not happen)
	set( PACKAGE_VERSION_UNSUITABLE TRUE )
	set( PACKAGE_VERSION "Outdated - Referenced file \"G:/Dev/VflPullDownMenu/dist/win32-x64.vc12/share/VflPullDownMenu/cmake/VflPullDownMenuConfig.cmake\" does not exist anymore" )
endif( EXISTS "${VFLPULLDOWNMENU_REFERENCED_FILE}" )

