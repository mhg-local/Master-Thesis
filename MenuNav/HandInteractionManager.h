/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      Header   :	ProcessMicrophoneThread.h	 RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  			                 RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  			                   Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2001   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*                                                                            */
/*    THIS SOFTWARE IS PROVIDED 'AS IS'. ANY WARRANTIES ARE DISCLAIMED. IN    */
/*    NO CASE SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DAMAGES.    */
/*    REDISTRIBUTION AND USE OF THE NON MODIFIED TOOLKIT IS PERMITTED. OWN    */
/*    DEVELOPMENTS BASED ON THIS TOOLKIT MUST BE CLEARLY DECLARED AS SUCH.    */
/*                                                                            */
/*============================================================================*/
/* $Id: HandInteractionManager.h 49363 2015-04-20 14:24:47Z dz762974 $ */

#ifndef _HANDINTERACTIONMANAGER_H
#define _HANDINTERACTIONMANAGER_H

/*============================================================================*/
/* FORWARD DECLARATIONS														  */
/*============================================================================*/

/*============================================================================*/
/* INCLUDES																	  */
/*============================================================================*/
#include <VistaAspects/VistaUncopyable.h>

#include <VistaBase/VistaTransformMatrix.h>
#include <VistaKernel/EventManager/VistaEventHandler.h>
#include <VistaBase/VistaBaseTypes.h>
#include "VwInputSlot.h"

#include <VistaAspects/VistaPropertyList.h>
#include<ctime>
#include <vector>
#include <array>
#include<VistaWidgets\SignalSystem\Signals\VwSignals.h>
#include<VistaWidgets\SignalSystem\Signals\VwEmptySignal.h>
#include <VistaWidgets/VwWidgetModel.h>

class Hand;
class IVwFocusStrategy;
class VwVirtualDevice;
class VwWidgetManager;
class VwPlaneWidget;
class VpmPullDownMenu;
class VpmElement;
class VwTextLabelWidget;
class VglwDynamicTextWidget;
class VistaPropertyList;
class VwArrowWidget;
class VwFocusStrategy;
/*===========================================================================*/
/* CLASS DEFINITION															  */
/*============================================================================*/
class HandInteractionManager : public VistaEventHandler
{
	VISTA_UNCOPYABLE( HandInteractionManager );
public:
	HandInteractionManager(VwWidgetManager *pWidgetmanager);
	virtual ~HandInteractionManager();
	void Init( VwWidgetManager* pWidgetManager);
	void RegisterHand(Hand* pHand ,const std::array< VwInputSlot< VistaTransformMatrix >*, 4 >& aFingerInputSlots,
		const std::array< VwVirtualDevice*, 4 >& aFingerDevices);
	void UnregisterHand( Hand* pHand );
	clock_t GetStartTimer();
	void SetStartTimer();
	void CreateFirstTask();
	void CreateSecondTask();
	void CreateThirdTask();
	void CreateFourthTask();
	void CreateFifthTask();
	void CreateSixTask();
	void CreateSevenTask();
	void CreateEithTask();
	void CreateNineTask();
	void CreateTenTask();
	void ThanksMassege();
	void CreateIndicator( );
	void RandomTaskCreator( );
	VwPlaneWidget* CreatePlane( const VistaVector3D& v3PlanePosition, const VistaQuaternion& qOri);

	VpmPullDownMenu* CreateMenu( const VistaVector3D& v3MenuPosition, const VistaQuaternion& qOri ); 
	VpmPullDownMenu* CreateTrainingMenu( const VistaVector3D& v3MenuPosition, const VistaQuaternion& qOri );
	VwPlaneWidget* CreateMassege( );
	VwFocusStrategy* GetStrategy( ) { return m_pFocusStrategy; }
	
	VwBoolChangedSignal& GetSelectionChanged( );
	

	VwEmptySignal&  GetCloseMenuSignal() { return m_closeMenuSignal; }
	VwEmptySignal&  GetCloseTrainingMenuSignal( ) { return m_closeTrainingMenuSignal; }
	VwEmptySignal&  GetShowMenuSignal( ) { return m_showMenuSignal; }
	VwEmptySignal&  GetShowTrainingMenuSignal( ) { return m_showMenuTrainingMenuSignal; }
	VwEmptySignal&  GetMoveDownSignal( ) { return m_MoveDownMenuSignal; }
	VwEmptySignal&  GetMoveUpSignal( ) { return m_MoveUpMenuSignal; }
	VwBoolChangedSignal&  GetHandVitualizationSignal( ) { return m_HandVitualizationSignal; }
	VwEmptySignal&  GetTimerSignal( ) { return m_TimerSignal; }
	VwEmptySignal& GetSelectionDisable( ){return m_selectionDisable;}
	VwEmptySignal&  getProgressInvisible( ) { return m_InvisibleShowProgressSignal; }
	VwEmptySignal&   getProgressVisible() { return m_visibleShowProgressSignal; }
	
	
	void OnClicked( const VwEmptySignalArgs& oArgs );
	VwFloatChangedSignal&  GetProgressValueChangedSignal( ) { return m_ProgressValueSignal; }
	VwFloatChangedSignal&  GetDeepValueChangedSignal( ) { return m_DeepValueSignal; }
	void  SetSelectionData( VistaVector3D center, VistaQuaternion plane, float selectionDiff, float selectPositionView, float focusPositionView, bool OculusActivated );


	std::vector< VpmPullDownMenu* > GetMenuVector( );
	std::vector< VpmPullDownMenu* >GetMenuTrainingVector( );
	bool ActiveMenu = false;
	bool ActiveTrainMenu = true;
	bool ScalerElement= false;
	void Update();
	void UpdateTime( clock_t   CurrentTime );
	virtual void HandleEvent( VistaEvent *pEvent );
	void SetTableHeight(const float oValue) { m_nTableHeight = oValue; }


	VwVirtualDevice* GetFingerDevice(int handIndex,int fingerIndex)
	{
		return m_vecHands[handIndex].m_aFingerDevices[fingerIndex];
	}

private:


	enum Gesture
	{
		GESTURE_NONE,
		GESTURE_GRAB,
		GESTURE_FILL_LEVEL_SNAP,
		GESTURE_FILL_LEVEL_FREE,
	};
	struct HandData
	{
		HandData();

		Hand* m_pHand;
		std::array< VwInputSlot< VistaTransformMatrix >*, 4 > m_aFingerInputSlots;
		std::array< VwVirtualDevice*, 4 > m_aFingerDevices;
		std::array< bool, 4 > m_aUseFingersForPointing;
		std::array< bool, 4 > m_aFingersPointerIsDisabled;

		
		Gesture m_eActiveGesture;
		Gesture m_eFillingActiveGesture;
		VistaTimer* m_pTimer;
	
		VistaTimer* m_pFillTimer;
		bool m_bHandFillIsGoingToChange;

		VistaType::microtime m_nLastCheckedHandUpdateTime;

	};


	
	void  ReturnTaskNumber();
	
	void UpdateAllHandPointers();
	void UpdateHandPointers( HandData& oHand );

	void UpdatePointer( HandData& oHand );
	void SetFingerToDisabledState(  HandData& oHand, int nFingerIndex );
	void SetVisibilityChanged( bool VisibilityChanged , bool ButtonVisibility );
	void UpdateLabelText( clock_t  Timer );
	
	float GetAngle(VistaQuaternion& q);

private:
    void OnChechBox();
    void SaveTimeToIniFile( const std::string & strFileName ); 

	void OnElementClick1( const VwEmptySignalArgs& oArgs );
	void OnElementClick2( const VwEmptySignalArgs& oArgs );
	void OnElementClick3( const VwEmptySignalArgs& oArgs );
	void OnElementClick4( const VwEmptySignalArgs& oArgs );
	void OnElementClick5( const VwEmptySignalArgs& oArgs );
	void OnElementClick6( const VwEmptySignalArgs& oArgs );
	void OnElementClick7( const VwEmptySignalArgs& oArgs ); 
	void OnElementClick8( const VwEmptySignalArgs& oArgs );
	void OnElementClick9( const VwEmptySignalArgs& oArgs );
	void OnElementClick10( const VwEmptySignalArgs& oArgs );
	void OnElementClick11( const VwEmptySignalArgs& oArgs );
	void OnElementClick12( const VwEmptySignalArgs& oArgs );
	void OnElementClick13( const VwEmptySignalArgs& oArgs );
	void OnElementClick14( const VwEmptySignalArgs& oArgs );
	void OnElementClick15( const VwEmptySignalArgs& oArgs );
	void OnElementClick16( const VwEmptySignalArgs& oArgs );
	void OnElementClick17( const VwEmptySignalArgs& oArgs ); 
	void OnElementClick18( const VwEmptySignalArgs& oArgs );
	void VisibleIndicator( bool ChangeVisibility );

	int value1 = 0;
	int value2 = 0;
	int value3 = 0;
	int value4 = 0;
	int value5 = 0;
	int value6 = 0;

	std::vector< VpmPullDownMenu* > m_vecTtrainingMenu;
	VpmPullDownMenu* m_pMenuWidgetTraining;
	std::vector< HandData > m_vecHands;
	std::vector< VwPlaneWidget* > m_vecPlane;
	std::vector< VpmPullDownMenu* > m_vecMenu;
	std::vector<VwPlaneWidget*>m_vecMessage;
	VwArrowWidget*    TopIndicator;
	VwArrowWidget*    bottomIndicator;
	
	std::vector< VwPlaneWidget* > m_vecPlanePrototypes;
	VistaPropertyList	pParticleProperties;
	VwWidgetManager* m_pWidgetManager;

	VistaVector3D    m_ptCenter;
	VistaQuaternion  m_qtPlane;
	bool m_AculusActivated;
	bool NextElemetActive=false;
	bool m_pClicked = false;
	float            m_ftSelectionDiff;
	float            m_ftSelectPositionView;
	float            m_ftfocusPositionView;
	float    ProgressValue;

	VwPlaneWidget*	m_MassegeBox;
	VwPlaneWidget*	m_MassegeButton;

	VglwDynamicTextWidget* m_TimerText;
	VglwDynamicTextWidget* m_MassegeBoxText;
	VglwDynamicTextWidget* m_MassegeBoxText1;
	VglwDynamicTextWidget*  m_MassegeBoxText2;
	VglwDynamicTextWidget*  m_MassegeBoxText3;
	VglwDynamicTextWidget*   m_MassegeBoxText4;
	VglwDynamicTextWidget*   m_MassegeBoxText5;
	VglwDynamicTextWidget* m_MassegeButtonText;

	bool  m_bAllOpen = false;
	bool m_bPreDisableState = false;
	bool   m_bUpState = true;

	bool m_PreStateOpened = false;
	bool m_PreStateclosed = false;

	bool m_MovedUp = false;
	bool m_MovedDown = false;

	VwEmptySignal       m_TimerSignal;
	VwEmptySignal       m_closeMenuSignal;
	VwEmptySignal       m_closeTrainingMenuSignal;
	VwEmptySignal       m_MoveUpMenuSignal;
	VwEmptySignal       m_MoveDownMenuSignal;
	VwEmptySignal       m_showMenuSignal;
	VwEmptySignal       m_showMenuTrainingMenuSignal;

	VwEmptySignal       m_InvisibleShowProgressSignal;
	VwEmptySignal       m_visibleShowProgressSignal;
	
	VwBoolChangedSignal       m_HandVitualizationSignal;
	VwBoolChangedSignal m_selectionChnaged;
	VwEmptySignal m_selectionDisable;
	VwFloatChangedSignal m_ProgressValueSignal; 
	VwFloatChangedSignal m_DeepValueSignal;

	VwFocusStrategy*         m_pFocusStrategy;
	float m_nTableHeight;

	clock_t   lastOpeingTime;
	clock_t   lastClosingTime;
	clock_t   lastMovingUpTime;
	clock_t   lastMovingDownTime;
	
	std::vector<int> myvector;
	int i = 0;
	int j = 0;
	int k = 0;
	int z = 0;
	float time1;
	float time2;
	float time3;
	float time4;
	float time5;
	float time6;
	float time7;
	float time8;
	float time9;
	float time10;
	clock_t Start;
	int counter = 0;
	int TaskNumber = 0;
	bool TaskCorrect = false;

	VistaVector3D oldPalmPosition;
};

#endif // _HANDINTERACTIONMANAGER_H

/*============================================================================*/
/* END OF FILE																  */
/*============================================================================*/