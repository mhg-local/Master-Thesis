set( VFLPULLDOWNMENU_ROOT_DIR "G:/Dev/VflPullDownMenu" )
set( VFLPULLDOWNMENU_INCLUDE_DIRS "G:/Dev/VflPullDownMenu" )
set( VFLPULLDOWNMENU_LIBRARY_DIRS "G:/Dev/VflPullDownMenu/build/win32-x64.vc12/lib" )
set( VFLPULLDOWNMENU_SHADER_DIRS "" )
set( VFLPULLDOWNMENU_DEFINITIONS "" )
set( VFLPULLDOWNMENU_HWARCH "win32-x64.vc12" )
set( VFLPULLDOWNMENU_LIBRARIES
		optimized VflPullDownMenu
		debug VflPullDownMenuD )
set( VFLPULLDOWNMENU_DEPENDENCIES package;VistaCoreLibs;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaWidgets;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaOGLExt;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VflTextRendering;HEAD;REQUIRED;FIND_DEPENDENCIES;package;VistaOpenGLWidgets;REQUIRED;FIND_DEPENDENCIES )

# msvc-project for inclusion in other solutions
# Format: ( PROJ name location [DEP ( dependency )+ ] )*
set( VFLPULLDOWNMENU_MSVC_PROJECT PROJ VflPullDownMenu "G:/Dev/VflPullDownMenu/build/win32-x64.vc12/VflPullDownMenu.vcxproj" )

set( VFLPULLDOWNMENU_FOUND TRUE )
