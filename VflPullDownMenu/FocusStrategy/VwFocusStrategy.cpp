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
#include "VwFocusStrategy.h"
#include"VwFocusStrategyUtility.h"
#include "VistaWidgets/VwFocusHandle.h"
#include "VistaWidgets/FocusHandleAspects/VwCenterFocusHandleAspect.h"
#include "VistaWidgets/FocusHandleAspects/VwPlaneFocusHandleAspect.h"
#include "VistaWidgets/FocusHandleAspects/VwRadiusFocusHandleAspect.h"

		  
#include "VistaWidgets/FocusStrategies/HandleInfos/VwHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwPlaneHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwSphereHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwCylinderHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwBoxHandleInfo.h"
#include "VistaWidgets/FocusStrategies/HandleInfos/VwPlaneInfiniteHandleInfo.h"

#include "VistaWidgets/Aspects/VwAspect.h"

#include <VistaMath/VistaBoundingBox.h>

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
/*============================================================================*/
/* CONSTRUCTORS / DESTRUCTOR                                                  */
/*============================================================================*/
VwFocusStrategy::VwFocusStrategy( void )
: m_pPoseInputSlot( nullptr ),
m_pSelectInputSlot(nullptr ),
m_bClickState(false )
{

}

VwFocusStrategy::~VwFocusStrategy( void )
{
	for( auto* pHandleInfo : m_vecHandleInfos )
	{
		delete pHandleInfo;
	}
}

/*============================================================================*/
/* IMPLEMENTATION                                                             */
/*============================================================================*/
bool VwFocusStrategy::DoRegistration( VwFocusHandle* pHandle )
{
	//@TODO: React to VwFocusHandle::GetGoingToBeDeletedSignal
	//@TODO: Test if the handle was already registered
	bool bSuccess = false;

	VwSphereHandleInfo* pSphereHandleInfo = VwSphereHandleInfo::Create( pHandle );
	if( pSphereHandleInfo != nullptr )
	{
		m_vecHandleInfos.push_back( pSphereHandleInfo );
		bSuccess = true;
	}

	VwPlaneHandleInfo* pPlaneHandleInfo = VwPlaneHandleInfo::Create( pHandle );
	if( pPlaneHandleInfo != nullptr )
	{
		m_vecHandleInfos.push_back( pPlaneHandleInfo );
		bSuccess = true;
	}

	VwCylinderHandleInfo* pCylinderHandleInfo = VwCylinderHandleInfo::Create( pHandle );
	if( pCylinderHandleInfo != nullptr )
	{
		m_vecHandleInfos.push_back( pCylinderHandleInfo );
		bSuccess = true;
	}

	VwBoxHandleInfo* pBoxHandleInfo = VwBoxHandleInfo::Create( pHandle );
	if( pBoxHandleInfo != nullptr )
	{
		m_vecHandleInfos.push_back( pBoxHandleInfo );
		bSuccess = true;
	}

	VwPlaneInfiniteHandleInfo* pPlaneInfiniteHandleInfo =
		VwPlaneInfiniteHandleInfo::Create( pHandle );
	if( pPlaneInfiniteHandleInfo != nullptr )
	{
		m_vecHandleInfos.push_back( pPlaneInfiniteHandleInfo );
		bSuccess = true;
	}

	if( bSuccess )
	{
		auto pIntersectionAspect = std::make_shared<VwResultAspect<VistaVector3D, VwSemanticTypeIntersection>>( );
		auto pDistanceAspect = std::make_shared<VwResultAspect<float, VwSemanticTypeDistance>>( );
		auto pOriginAspect = std::make_shared<VwResultAspect<VistaVector3D, VwSemanticTypeOrigin>>( );

		auto pGroup = std::make_shared<VwRayAspect>( );
		pGroup->SetIsCurrent( true );
		pGroup->SetValue( std::make_tuple( pIntersectionAspect, pDistanceAspect, pOriginAspect ) );

		pHandle->GetFocusResultAspects( ).Add( pGroup );

		m_mapResultAspects.insert( std::make_pair( pHandle, pGroup ) );
	}

	return bSuccess;
}

bool VwFocusStrategy::DoUnRegistration( VwFocusHandle* pHandle )
{
	HandleInfoContainer::iterator itFound = std::find_if(
		m_vecHandleInfos.begin( ),
		m_vecHandleInfos.end( ),
		[pHandle]( VwHandleInfo* pInfo )
	{
		return ( pHandle == pInfo->GetHandle( ) );
	}
	);

	if( itFound == m_vecHandleInfos.end( ) )
	{
		return false;
	}
	auto pGroup = m_mapResultAspects[ pHandle ];

	pHandle->GetFocusResultAspects( ).Remove( pGroup );

	m_mapResultAspects.erase( pHandle );

	delete *itFound;
	m_vecHandleInfos.erase( itFound );

	return true;
}

const IVwFocusStrategy::FocusResultVector& VwFocusStrategy::EvaluateFocus()
{
	bool cliked = false;
	m_vecFocusedFocusHandles.clear();
	m_vecClickedHandles.clear();
	for( auto pInfo : m_vecHandleInfos )
	{
		VwFocusHandle* pHandle = pInfo->GetHandle();
		assert( pHandle != nullptr );
		if( pHandle->GetEnabled() )
		{
			float flag = false;
			if( pInfo->Intersects( m_pPoseInputSlot->GetValue( 0 ) ) )
			{
				
				VistaVector3D v3Intersection = pInfo->GetIntersection();
				float fDistance = VwFocusStrategyUtility::CalculateDistance( pInfo, m_pPoseInputSlot->GetValue( 0 ).GetTranslation() );
		//		float fDistance = ( pInfo->GetIntersection() - m_pPoseInputSlot->GetValue( 0 ).GetTranslation() ).GetLength();
			
				if( fDistance <= m_fFocusRadius )
				{
					auto pGroup = m_mapResultAspects[ pHandle ];
					pGroup->SetIsCurrent( true );
					std::get<0>( pGroup->GetValue() )->SetValue( v3Intersection );
					std::get<1>( pGroup->GetValue( ) )->SetValue( fDistance );
					std::get<2>( pGroup->GetValue() )->SetValue( m_pPoseInputSlot->GetValue( 0 ).GetTranslation() );
					flag = true;

					m_vecFocusedFocusHandles.push_back( pHandle );
				}

			}
			if( !flag )
			{
				auto pGroup = m_mapResultAspects[ pHandle ];
				// Set to IsCurrent so the aspects inside pGroup can be updated
				pGroup->SetIsCurrent( true );
				std::get<0>( pGroup->GetValue() )->SetIsCurrent( false );
				std::get<1>( pGroup->GetValue() )->SetIsCurrent( false );
				std::get<2>( pGroup->GetValue() )->SetIsCurrent( false );
				// Set to !IsCurrent to reflect the real state of pGroup
				pGroup->SetIsCurrent( false );
			}
		}
	}

	// sort results in ascending order by distance to the origin of the ray
	std::sort(
		m_vecFocusedFocusHandles.begin(),
		m_vecFocusedFocusHandles.end(),
		[this]( VwFocusHandle* pLeft, VwFocusHandle* pRight )
	{
		return std::get<1>( m_mapResultAspects[ pLeft ]->GetValue() )->GetValue()
			< std::get<1>( m_mapResultAspects[ pRight ]->GetValue() )->GetValue();
	}
	);
	

	std::sort(
		m_vecClickedHandles.begin(),
		m_vecClickedHandles.end(),
		[this]( VwFocusHandle* pLeft, VwFocusHandle* pRight )
	{
		return std::get<1>( m_mapResultAspects[ pLeft ]->GetValue() )->GetValue()
			< std::get<1>( m_mapResultAspects[ pRight ]->GetValue() )->GetValue();
	}
	);

	if( m_vecFocusedFocusHandles.size()==0 )
	{
		m_bLocked = false;
	}

	if( m_bLocked )
	{
		m_vecFocusedFocusHandles.clear();
	}
	
	return m_vecFocusedFocusHandles;
}

VwHandleSignal& VwFocusStrategy::GetClickSignal( )
{
	return m_sigClick;
	
}

VwHandleSignal&  VwFocusStrategy::GetButtonDownSignal( )
{
	return m_sigButtonDown;
}

VwHandleSignal&  VwFocusStrategy::GetButtonUpSignal( )
{
	return m_sigButtonUp;
}

VwInputSlot<bool>* VwFocusStrategy::GetSelectInputSlot( ) const
{
	return m_pSelectInputSlot;
}

void VwFocusStrategy::SetSelectInputSlot( VwInputSlot<bool>* pInputSlot )
{
	if( pInputSlot == nullptr )
	{
		throw std::invalid_argument( "pInputSlot must be a valid pointer that is not null" );
	}
	m_pSelectInputSlot = pInputSlot;
}

VwInputSlot<VistaTransformMatrix>* VwFocusStrategy::GetPoseInputSlot( ) const
{
	return m_pPoseInputSlot;
}

void VwFocusStrategy::SetPoseInputSlot( VwInputSlot<VistaTransformMatrix>* pInputSlot )
{
	if( pInputSlot == nullptr )
	{
		throw std::invalid_argument( "pInputSlot must be a valid pointer that is not null" );
	}
	m_pPoseInputSlot = pInputSlot;
}

std::vector<VwFocusHandle*> VwFocusStrategy::GetRegisteredFocusHandles( ) const
{
	std::vector<VwFocusHandle*> vecRegisteredFocusHandles;

	std::transform(
		m_vecHandleInfos.begin( ),
		m_vecHandleInfos.end( ),
		vecRegisteredFocusHandles.begin( ),
		[]( const VwHandleInfo* pHandleInfo )
	{
		return pHandleInfo->GetHandle( );
	} );

	return vecRegisteredFocusHandles;
}



float VwFocusStrategy::GetSelectionRadius() const
{
	return m_pSelectionRadius;
}
void VwFocusStrategy::SetSelectionRadius( const float& oValue )
{
	m_pSelectionRadius = oValue;
}

float VwFocusStrategy::GetFocusRadius( ) const
{
	return m_fFocusRadius;
}
void VwFocusStrategy::SetFocusRadius( const float& oValue )
{
	m_fFocusRadius = oValue;
}