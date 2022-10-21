
#ifndef _VGLW_CONFIG_H
#define _VGLW_CONFIG_H

// Windows DLL build
#if defined(WIN32) && !defined(VISTAWIDGETS_STATIC) 
#ifdef VFLPULLDOWNMENU_EXPORTS
#define VGLWAPI __declspec(dllexport)
#else
#define VGLWAPI __declspec(dllimport)
#endif
#else // no Windows or static build
#define VGLWAPI
#endif

#endif //_VWCONFIG_H
