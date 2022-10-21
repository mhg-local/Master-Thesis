/*============================================================================*/
/*                              ViSTA VR toolkit                              */
/*               Copyright (c) 1997-2010 RWTH Aachen University               */
/*============================================================================*/
/*                                  License                                   */
/*                                                                            */
/*  This program is free software: you can redistribute it and/or modify      */
/*  it under the terms of the GNU Lesser General Public License as published  */
/*  by the Free Software Foundation, either version 3 of the License, or      */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  This program is distributed in the hope that it will be useful,           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU Lesser General Public License for more details.                       */
/*                                                                            */
/*  You should have received a copy of the GNU Lesser General Public License  */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.     */
/*============================================================================*/
/*                                Contributors                                */
/*                                                                            */
/*============================================================================*/
/*
 * $Id: MenuNav.h 49363 2015-04-20 14:24:47Z dz762974 $
 */

#ifndef MenuNav_H
#define MenuNav_H

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/
#include "InitConstants.h"

#include <VistaBase/VistaVectorMath.h>
#include <VistaBase/VistaUtilityMacros.h>
#include <VistaKernel/VistaSystem.h>

#include <VistaWidgets/VwField.h>
#include <VistaWidgets/VwWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/Widgets/Views/VwEmptyView.h>
#include <VistaWidgets/SignalSystem/Signals/VwEmptySignal.h>
#include<FocusStrategy\VwHandleSignal.h>
#include <vector>
#include <array>
#include <VistaWidgets/FocusStrategies/VwAlwaysInFocusStrategy.h>
#include<VistaWidgets\SignalSystem\Signals\VwSignals.h>
/*============================================================================*/
/* MACROS AND DEFINES                                                         */
/*============================================================================*/

/*============================================================================*/
/* FORWARD DECLARATIONS                                                       */
/*============================================================================*/
class VistaSystem;
class IVistaNode;
class VistaTransformNode;
class Hand;
class HandInteractionManager;
class MassegeWidget;
class VwSphereWidget;
class VwPlaneWidget;
class VwTextLabelWidget;
class VglwDynamicTextWidget;

class VwWidgetManager;
class VwWidgetManagerUpdateHandler;
class VwDraggableLineWidget;

class VwIntenSelectFocusStrategy;
class VwRaycastingFocusStrategy;
class VwProximityFocusStrategy;
class VwPriorityMergerFocusStrategy;
class VistaColorOutstream;
class VfaBaseApplication;
class VwTransformWidget;

class VwManualPlaneFocusHandleAspect;
class IVwCenterFocusHandleAspect;
class VwClickable;
class VwFocusable;

class VpmPullDownMenu;
class VwFocusStrategy;
class VwFocusStrategyUtility;

class VwBackgroundWidget;
class VwBackgroundWidgetFocusHandleAspect;
class VpmTimer;

/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/
class MenuNav
{
public:
	MenuNav();
	virtual ~MenuNav();

	bool Init( int argc, char* argv[] );
	void Run();

	HandInteractionManager*			m_pHandInteraction;

private:
	
     void OnCloseMenu( const VwEmptySignalArgs& oArgs );
	 void  OnCloseTrainingMenu( const VwEmptySignalArgs& oArgs );
	 void OnShowMenu( const VwEmptySignalArgs& oArgs ); 
	 void OnShowTrainingMenu( const VwEmptySignalArgs& oArgs ); 
     void OnSelectionChanged( const VwBoolChangedSignalArgs& oArgs );
	 void OnTimeChanged( const VwBoolChangedSignalArgs& oArgs );	 
	 void OnMoveUpMenu( const VwEmptySignalArgs& oArgs );  
	 void OnMoveDownMenu( const VwEmptySignalArgs& oArgs );
	 void OnTimerChanged(const VwEmptySignalArgs& oArgs);
	 void OnProgressActivated( const VwFloatChangedSignalArgs& oArgs ); 
	 void OnDeepActivated( const VwFloatChangedSignalArgs& oArgs );
	 void OnButtonDownOnBackgroundWidget( const VwEmptySignalArgs& oArgs );

	 void OnVisibleProgress( const VwEmptySignalArgs& oArgs );
	 void OnInvisibleProgress( const VwEmptySignalArgs& oArgs );
	 void OnTimer( const VwEmptySignalArgs &oArgs );
	 VpmPullDownMenu* InitPullDownMenu( );
	 void UpdateLabelText( clock_t Timer );
	 //void InitVirtualDevice( );

	void CreateScene();
	void InitMenu();
	
	void CreateInteraction();
	void OnClicked( const VwEmptySignalArgs& oArgs );
	void PalmeActivate( const VwTransformMatrixChangedSignalArgs& oArgs );
	
	class ImageWriter;
	ImageWriter* m_pImageWriter;
	VpmTimer*   m_timer;
	VglwDynamicTextWidget* m_TimerText;
	// base
	VistaSystem*		m_pVistaSystem;
	InitConstants		m_InitConstants;
	std::string			m_sIniFile;
	
	clock_t   Start;

	// scene
	bool MassegeShown = false;
	Hand*	m_pRightHand;
	Hand*	m_pLeftHand;
	VistaVector3D m_v3TablePlateCenter;
	
	HandInteractionManager*         mHandInteraction;
	
	VpmPullDownMenu* m_pMenuWidget;
	std::vector< VpmPullDownMenu* > m_vecMenu;
	
	// Interaction related stuff
	std::shared_ptr< VwWidgetManager >				m_pWidgetManager;
	std::unique_ptr< VwWidgetManagerUpdateHandler >	m_pWidgetUpdateHandler;
	
	VwInputSlot<bool>*					m_pSelect;
	std::unique_ptr< VwVirtualDevice >						m_pPrimaryDevice;
	std::unique_ptr< VwInputSlot< VistaTransformMatrix > >	m_pDevicePoseSlot;
	std::unique_ptr< VwInputSlot< bool > >					m_pSelectSlot;

	std::unique_ptr< VwVirtualDevice >						m_pViewerDevice;
	std::unique_ptr< VwInputSlot< VistaTransformMatrix > >	m_pViewerPoseSlot;
	std::unique_ptr< VwBackgroundWidget >	m_pBackgroundWidget;
	
	VwVirtualDevice*			m_pDevice;
	IVwFocusStrategy*			m_pIVwFocusStrategy;
	std::unique_ptr< VwAlwaysInFocusStrategy< VwBackgroundWidgetFocusHandleAspect >	>	m_pBackgroundWidgetFocusStrategy;
	VwInputSlot<VistaTransformMatrix>*	m_pPose;
	/*VwInputSlot<bool>*                  m_pSelectMiddleMouse;
	VwInputSlot<VistaTransformMatrix>*	m_pPoseMouse;*/
	// Widget 
	std::unique_ptr< VwPlaneWidget >	m_pPlaneWidget;
	std::unique_ptr< VwIntenSelectFocusStrategy >	m_pIntenselectFocusStrategy;
	std::unique_ptr< VwRaycastingFocusStrategy >	m_pRaycastingFocusStrategy;
	std::unique_ptr< VwPriorityMergerFocusStrategy > m_pApplicationMergerStrategy;
	
	VistaTransformNode* m_pTransform;

		
	class Finger
	{
	public:
		Finger();
		virtual ~Finger();
		
		void Init( VwWidgetManager* pWidgetManager, VwInputSlot<bool>* pSelect, const std::string& strVirtualDeviceName, HandInteractionManager*handInteraction );
		VwVirtualDevice* GetVirtualDevice( ) const; 
		bool    GetPalmshow( ) const;
		void    SetPalmshow( bool PalmValue )const ;
		VwInputSlot<VistaTransformMatrix>* GetInputSlot() { return m_pPose; }

		VwFocusStrategy* GetStrategy() { return m_pFocusStrategy; }

		protected:
		virtual void OnHandleClicked( const VwHandleSignalArgs& oArgs );
		virtual void OnHandleButtonDown( const VwHandleSignalArgs& oArgs );
		virtual void OnHandleButtonUp( const VwHandleSignalArgs& oArgs );

	private:
	    HandInteractionManager*			m_pHandInteraction;
		VwVirtualDevice*					m_pVirtualDevice;
		bool Palmshow;
		VwDraggableLineWidget*				m_pCursor;
		//VwRaycastingFocusStrategy*			m_pFocusStrategy;
		VwFocusStrategy*         m_pFocusStrategy;
		//VwIntenSelectFocusStrategy* m_pFocusStrategy;
		VwInputSlot<VistaTransformMatrix>*	m_pPose;
		Hand*								m_pHand;
	};

	std::vector<Finger*>			m_vecFingers;

	
};



/*============================================================================*/
/* LOCAL VARS AND FUNCS                                                       */
/*============================================================================*/

#endif

