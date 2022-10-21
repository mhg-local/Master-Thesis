#pragma once
#include"../VglConfig.h"
#include "VistaWidgets/VwFocusStrategy.h"
#include "VistaWidgets/VwInputSlot.h"

#include "VistaWidgets/Aspects/VwAspects.h"
#include <VistaBase/VistaVectorMath.h>

#include <map>
/*============================================================================*/
/* FORWARD DECLARATIONS                                                       */
/*============================================================================*/
class VwHandleInfo;
class VwPlaneHandleInfo;
class VwSphereHandleInfo;
class VwCylinderHandleInfo;
class VwBoxHandleInfo;
class IVwPlaneFocusHandleAspect;
class VwRadiusFocusHandleAspect;
class VwCenterFocusHandleAspect;

class VGLWAPI  VwFocusStrategyUtility
{
public:
	
	static float CalculateDistance( VwHandleInfo* info, const VistaVector3D& v3Position );



private:

	static float CalculateDistancePlane( VwPlaneHandleInfo* info, const VistaVector3D& v3Position );
	static float CalculateDistanceBox( VwBoxHandleInfo* info, const VistaVector3D& v3Position );
	static float CalculateDistanceCylinder( VwCylinderHandleInfo* info, const VistaVector3D& v3Position );
	static float CalculateDistanceSphere( VwSphereHandleInfo* info, const VistaVector3D& v3Position );


};

//#endif // _VwFocusStrategyUtility_H
