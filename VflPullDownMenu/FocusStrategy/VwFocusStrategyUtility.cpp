/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :                               RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  VistaWidgets                 RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  VistaWidgets                   Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  2012-2013   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
#include "VwFocusStrategyUtility.h"

#include "VistaWidgets/VwFocusHandle.h"
#include "VistaWidgets/FocusHandleAspects/VwCenterFocusHandleAspect.h"
#include "VistaWidgets/FocusHandleAspects/VwPlaneFocusHandleAspect.h"
#include "VistaWidgets/FocusHandleAspects/VwRadiusFocusHandleAspect.h"

		  
#include "VistaWidgets/FocusStrategies/HandleInfos/VwHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwPlaneHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwSphereHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwCylinderHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwBoxHandleInfo.h"

#include "VistaWidgets/Aspects/VwAspect.h"

#include <VistaMath/VistaBoundingBox.h>

#include <algorithm>
#include <cstddef>



float VwFocusStrategyUtility::CalculateDistance( VwHandleInfo* info, const VistaVector3D& v3Position )
{
	if( dynamic_cast< VwPlaneHandleInfo* >( info ) != NULL )
	{
		return CalculateDistancePlane( dynamic_cast< VwPlaneHandleInfo* >( info ), v3Position );			
	}
	else if( dynamic_cast< VwCylinderHandleInfo* >( info ) != NULL )
	{
		return CalculateDistanceCylinder( dynamic_cast< VwCylinderHandleInfo* >( info ), v3Position );
	}
	else if( dynamic_cast< VwBoxHandleInfo* >( info ) != NULL )
	{
		return CalculateDistanceBox( dynamic_cast< VwBoxHandleInfo* >( info ), v3Position );
	}
	else if( dynamic_cast< VwSphereHandleInfo* >( info ) != NULL )
	{
		return CalculateDistanceSphere( dynamic_cast< VwSphereHandleInfo* >( info ), v3Position );
	}
	return info->CalculateDistance( v3Position );
}

float VwFocusStrategyUtility::CalculateDistancePlane( VwPlaneHandleInfo* info, const VistaVector3D& v3Position )
{
	
	const VistaQuaternion qPlaneOri= info->GetHandle( )->GetAspect<IVwPlaneFocusHandleAspect>()->GetOrientation( );
	const VistaVector3D v3Normal = qPlaneOri.GetViewDir().GetNormalized();

	VistaVector3D v3Center =info->GetHandle()->GetAspect<IVwCenterFocusHandleAspect>()->GetCenter();
	return std::abs( ( v3Position - v3Center ) * v3Normal );

}

float VwFocusStrategyUtility::CalculateDistanceBox( VwBoxHandleInfo* info, const VistaVector3D& v3Position )
{

	return info->CalculateDistance( v3Position );
}

float VwFocusStrategyUtility::CalculateDistanceCylinder( VwCylinderHandleInfo* info, const VistaVector3D& v3Position )
{
	return info->CalculateDistance( v3Position );
}

float VwFocusStrategyUtility::CalculateDistanceSphere( VwSphereHandleInfo* info, const VistaVector3D& v3Position )
{


	return info->CalculateDistance( v3Position );
}







