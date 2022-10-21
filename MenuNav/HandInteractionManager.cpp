/* $Id: HandInteractionManager.cpp 49363 2015-04-20 14:24:47Z dz762974 $ */

/*============================================================================*/
/* INCLUDES																	  */
/*============================================================================*/
#include "HandInteractionManager.h"
#include "Hand.h"
#include <VistaWidgets/Widgets/VwPlaneWidget.h>
#include "VistaBase/VistaUtilityMacros.h"
#include "VwWidgetManager.h"
#include "VwInputSlot.h"
#include <VistaBase/VistaTimer.h>
#include <VistaKernel/VistaSystem.h>
#include<VpmPullDownMenu.h>
#include<Elements\VpmLabelElement.h>
#include<FocusStrategy\VwFocusStrategy.h>
//Menu include
#include<VistaOGLExt\VistaOGLUtils.h>
#include<VpmPullDownMenu.h>
#include<Elements\VpmCheckBoxElement.h>
#include<Elements\VpmRadioButtonElement.h>
#include<Elements\VpmLabelElement.h>
#include<Elements\VpmSoildButtonElement.h>
#include<Elements\VpmTextureButtonElement.h>
#include<Elements\VpmScalerElement.h>
#include<VpmGlobalConfiguration.h>
#include <VistaBase/VistaTimer.h>

#include <VistaAspects/VistaPropertyList.h>
#include <VistaCoreLibs\VistaTools\VistaIniFileParser.h>
#include <VistaWidgets/Widgets/VwArrowWidget.h>
#include <VistaWidgets\FocusHandleAspects\VwPlaneFocusHandleAspect.h>
#include<VistaOpenGLWidgets\Widgets\VglwDynamicTextWidget.h>
#include<VistaWidgets\Widgets\VwTextLabelWidget.h>
namespace
{
	const VistaTransformMatrix S_matOffTransform( VistaVector3D( 1e5f, 1e5f, -1e5f ) );
}
/*============================================================================*/
/* HandData																	  */
/*============================================================================*/
HandInteractionManager::HandData::HandData()
: m_pHand( NULL )
, m_eActiveGesture( GESTURE_NONE )
, m_aUseFingersForPointing( )
, m_nLastCheckedHandUpdateTime()

{
	m_aUseFingersForPointing = { true, true, true, true };
	m_aFingersPointerIsDisabled = { false, false, false, false };

}

/*============================================================================*/
/* HandInteractionManager													  */
/*============================================================================*/

HandInteractionManager::HandInteractionManager(VwWidgetManager *pWidgetmanager)
:m_pWidgetManager(pWidgetmanager)

{	
	lastOpeingTime = clock();
	lastClosingTime = clock();
	
	m_MassegeBox = nullptr;
	m_MassegeButton = nullptr;

	m_MassegeBoxText = nullptr;
	m_MassegeButtonText = nullptr;
	
}

HandInteractionManager::~HandInteractionManager()
{
	for (VwPlaneWidget* pPlane : m_vecPlane)
	{
		delete pPlane;
	}
}
void Init( VwWidgetManager* pWidgetManager )
{

	
}
void  HandInteractionManager::SetSelectionData( VistaVector3D center, VistaQuaternion plane, float selectionDiff, float selectPositionView, float focusPositionView, bool OculusActivated )
{
	m_ftSelectionDiff = selectionDiff;
	m_ftSelectPositionView = selectPositionView;
	m_ftfocusPositionView = focusPositionView;
	m_ptCenter = center;
	m_qtPlane = plane;
	m_AculusActivated = OculusActivated;

	
}
void HandInteractionManager::RegisterHand(Hand* pHand, const std::array< VwInputSlot< VistaTransformMatrix >*, 4 >& aFingerInputSlots,
	const std::array< VwVirtualDevice*, 4 >& aFingerDevices)
{
	m_vecHands.push_back( HandData() );
	HandData& oData = m_vecHands.back();
	oData.m_pHand = pHand;

	oData.m_aFingerInputSlots = aFingerInputSlots;
	oData.m_aFingerDevices = aFingerDevices;
	oData.m_pTimer = new VistaTimer();
	oData.m_pFillTimer = new VistaTimer();
	oData.m_bHandFillIsGoingToChange = false;
	oData.m_eActiveGesture = GESTURE_NONE;
	oData.m_eFillingActiveGesture = GESTURE_NONE;
}

void HandInteractionManager::UnregisterHand( Hand* pHand )
{
	std::vector< HandData >::iterator itEntry = std::find_if( m_vecHands.begin(), m_vecHands.end(),
															  [pHand]( const HandData& oData ) -> bool { return ( oData.m_pHand == pHand ); } );
	if (itEntry != m_vecHands.end())
	{
		delete itEntry->m_pFillTimer;
		delete itEntry->m_pTimer;

		m_vecHands.erase(itEntry);
	}
		
}

void HandInteractionManager::Update()
{
	UpdateAllHandPointers();

}

void HandInteractionManager::UpdateTime( clock_t   CurrentTime )
{
}

void HandInteractionManager::UpdateAllHandPointers()
{
	for(HandData& oHand:m_vecHands)
	{
		UpdatePointer(oHand);
	}
}

void HandInteractionManager::HandleEvent( VistaEvent *pEvent )
{
	Update();
}

float HandInteractionManager::GetAngle( VistaQuaternion& q )
{
	float fAngle = 2 * std::acos( Vista::Clamp( q[ 3 ], -1.0f, 1.0f ) );
	return Vista::RadToDeg( fAngle );
}
void HandInteractionManager::UpdatePointer( HandData& oHand )
{
	
	VwEmptySignalArgs args( this );
	m_TimerSignal.Raise( args );
	VistaVector3D m_pPalmPotion = oHand.m_pHand->GetPalmPosition();
	auto posPlam = m_pPalmPotion[1];
 
	if( oHand.m_eActiveGesture != GESTURE_NONE )
		return;

	if( oHand.m_pHand->GetLastUpdateTime() == oHand.m_nLastCheckedHandUpdateTime )
		return;

	oHand.m_nLastCheckedHandUpdateTime = oHand.m_pHand->GetLastUpdateTime();
	bool bShowPalm = false;
	for( int nFinger = 0; nFinger < 4; ++nFinger )
	{
		Hand::Finger nHandFingerIndex = ( Hand::Finger )( nFinger + 1 );
		bool bDoesPoint = nFinger == 0 && oHand.m_aUseFingersForPointing[ nFinger ] && oHand.m_pHand->GetFingerIsExtended( nHandFingerIndex );
		
		if( bDoesPoint )
		{

			//GetHandVitualizationSignal().Raise( VwBoolChangedSignalArgs( this, false, true, false ) );

			oHand.m_aFingersPointerIsDisabled[ nFinger ] = false;
			VistaVector3D v3Pos = oHand.m_pHand->GetFingerTip( nHandFingerIndex );
			VistaVector3D v3Dir = v3Pos - oHand.m_pHand->GetIntermediateJoint( nHandFingerIndex );
			v3Dir.Normalize();
			VistaQuaternion qOri( Vista::ViewVector, v3Dir );
			VistaTransformMatrix matTransform( qOri, v3Pos );
			oHand.m_aFingerInputSlots[ nFinger ]->Update( matTransform );

			const VistaQuaternion qPlaneOri = m_qtPlane;

			const VistaVector3D v3Normal = qPlaneOri.GetViewDir().GetNormalized();

			const VistaVector3D v3X = qPlaneOri.Rotate( Vista::ZAxis );
			const VistaVector3D v3Y = qPlaneOri.Rotate( Vista::YAxis );
			const VistaVector3D posCenter = v3Pos + m_ptCenter;
			const VistaVector3D pos1 = -v3Pos;
			float fProjectedX1 = ( ( ( pos1 * v3X ) / ( v3X * v3X ) ) * v3X ).GetLength();
			float fProjectedX = ( ( ( posCenter * v3X ) / ( v3X * v3X ) ) * v3X ).GetLength();
			float fProjectedY = ( ( ( posCenter * v3Y ) / ( v3Y * v3Y ) ) * v3Y ).GetLength();

			{

			auto progress = ( ( ( fProjectedX1 - m_ftfocusPositionView ) / ( m_ftSelectPositionView - m_ftfocusPositionView ) ) );
				progress = progress <= 0 ? 0.001 : progress;
				progress = progress > 1 ? 1 : progress;
				ProgressValue = progress;
				if( m_pClicked == true )
				{
				GetProgressValueChangedSignal( ).Raise( VwFloatChangedSignalArgs( this, 1,  0.0000000001, false ) );
				}
				else
				{
				GetProgressValueChangedSignal( ).Raise( VwFloatChangedSignalArgs( this, 1, progress, false ) );
				}
				
				VwEmptySignalArgs args( this );
				m_visibleShowProgressSignal.Raise( args );
			}

			

			if( ProgressValue > 0.95 && fProjectedX <= m_ftSelectionDiff  && m_pClicked == false )
				{

					if( m_bUpState )
					{
						GetSelectionChanged( ).Raise( VwBoolChangedSignalArgs( this, false, true, false ) );
						m_pClicked = true;
					}
					m_bUpState = false;

				}
			else
			{
				if( m_bUpState == false )
				{
					GetSelectionChanged().Raise( VwBoolChangedSignalArgs( this, false, false, false ) );

				}
				m_bUpState = true;

			}

			if( m_pClicked &&  fProjectedX < 0.17  && ScalerElement ==false )
			{
			   GetDeepValueChangedSignal( ).Raise( VwFloatChangedSignalArgs( this, 1, 1, false ) );
				GetProgressValueChangedSignal( ).Raise( VwFloatChangedSignalArgs( this, 1, 0.000000000001, false ) );
				VwEmptySignalArgs args( this );
				m_InvisibleShowProgressSignal.Raise( args );
				
			
			}
			if( ScalerElement )
				{
				m_pClicked = false;
				VwEmptySignalArgs args( this );
				m_visibleShowProgressSignal.Raise( args );

				}
			if( fProjectedX >= 0.16 && ScalerElement == false )
			{
				m_pClicked = false;
				VwEmptySignalArgs args( this );
				m_visibleShowProgressSignal.Raise( args );
				
			}
			
		}
		
		else if( !oHand.m_aFingersPointerIsDisabled[ nFinger ] )
		{
			SetFingerToDisabledState( oHand, nFinger );

		}
	}

	if( !m_AculusActivated )
	{
		bShowPalm = !( oHand.m_pHand->GetPalmPosition( )[ 0 ] == 0 && oHand.m_pHand->GetPalmPosition( )[ 1 ] == 0 && oHand.m_pHand->GetPalmPosition( )[ 2 ] == 0 );// desktop 
	}


	if( m_AculusActivated )
	{
		bShowPalm = !( oHand.m_pHand->GetPalmPosition( )[0] == 0 && oHand.m_pHand->GetPalmPosition( )[2] == 0 ); // oculus 

	}
	
	oHand.m_pHand->SetPalmVisible( bShowPalm );
	if( oHand.m_pHand->IsLeftHand() == false )
		{
		bool hasFingerPoint = false;
		bool hasAllOpen = false;
		bool ClosedMenue = false;
		bool hasPalmTurnLeft = false;
		bool hasPalmTurnRight = false;
		bool hasHandTurnUp = false;
		bool hasHandTurnDown = false;

		for( int nFinger = 0; nFinger < 4; ++nFinger )
			{
			Hand::Finger nHandFingerIndex = ( Hand::Finger )( nFinger + 1 );

			hasFingerPoint |= oHand.m_aUseFingersForPointing[nFinger] && oHand.m_pHand->GetFingerIsExtended( nHandFingerIndex );


			}
		
		Hand::Finger nHandOneFingerIndex = ( Hand::Finger )(2);
		VistaVector3D handdirection = oHand.m_pHand->GetV3WristPosition( ); 
		VistaVector3D fingerDirection = oHand.m_pHand->GetFingerTip( nHandOneFingerIndex );

		// find distance to closed menu

		float xSqr = ( handdirection[ 0 ] - fingerDirection[ 0 ] ) * ( handdirection[ 0 ] - fingerDirection[ 0 ] );
		float ySqr = ( handdirection[ 1 ] - fingerDirection[ 1 ] ) * ( handdirection[ 1 ] - fingerDirection[ 1 ] );
		float zSqr = ( handdirection[ 2 ] - fingerDirection[ 2 ] ) * ( handdirection[ 2 ] - fingerDirection[ 2 ] );

		double mySqr = xSqr + ySqr + zSqr;
		double myDistance = sqrt( mySqr );

		

		float fPalmAngle = GetAngle( oHand.m_pHand->GetPalmOrientation() );
		VistaVector3D PalmPosition = oHand.m_pHand->GetPalmPosition( );
		auto pos = PalmPosition[1 ];

		VistaVector3D PalmPositionClosing = oHand.m_pHand->GetPalmPosition();
		auto posClosing = PalmPositionClosing[2];
		
	/////////////////////////////	    /*Desk*/

		if( m_AculusActivated == false )
		{
			if( pos != 0 )
			{
			
				if( pos >= 0.360f ) //  in top of hand coordinate
				{
				//if( fPalmAngle >= 20 )
					{
					//hasHandTurnDown = true;
				
					VwEmptySignalArgs args( this );
					m_MoveDownMenuSignal.Raise( args );
					}
				}
				if( pos <= 0.07/* 0.065f*/ ) //  in bottom of hand coordinate  
				{
					//if( fPalmAngle  >= 20   )
					{
						//hasHandTurnUp = true;
					VwEmptySignalArgs args( this );
					m_MoveUpMenuSignal.Raise( args );
					}
				}

			}
		}

		if( m_AculusActivated == false )
			{
			if( fPalmAngle >= 110 && hasFingerPoint == true )
			{
				hasAllOpen = true;
			}
			if( myDistance <= 0.064f && hasFingerPoint == false )
			{
				ClosedMenue = true;
			}

		}
	//////////////////////////		/* Oculus*/

		if( m_AculusActivated )
			{
			if( posClosing < 0 )
			{

				if( pos >= 0.28 ) //  in top of hand coordinate
				{
					//if( fPalmAngle <= 340 )
					{
						//hasHandTurnDown = true;
						VwEmptySignalArgs args( this );
						m_MoveDownMenuSignal.Raise( args );
					}
				}
				if( pos <= -0.03 ) //  in bottom of hand coordinate  
				{
					//	if( fPalmAngle <= 320 )
					{
						//hasHandTurnUp = true;
						VwEmptySignalArgs args( this );
						m_MoveUpMenuSignal.Raise( args );
					}
				}

			}

			}

		if( m_AculusActivated )
			{
			if( myDistance <= 0.070f && hasFingerPoint == false )
				{
				ClosedMenue = true;
				}
			if( fPalmAngle> 180 && fPalmAngle <= 230 && hasFingerPoint == true && posClosing < 0 )
			{
				hasAllOpen = true;
			}
			}
		
		
		if( ClosedMenue /*hasFingerPoint == false*/ )
			{
			
				//if( ( ( clock() - lastOpeingTime ) / ( double )CLOCKS_PER_SEC ) >= 0.08 )
					{
					if( m_bPreDisableState )
						{
						
						if( posClosing < 0.f )//if( pos != 0.f ) //		//if( pos >= 0.31f )// .0 for desktop
							{

							if( TaskCorrect )
								{
								if( j == 1 )
									{
									j = 0;
									for( VpmPullDownMenu* menu : GetMenuVector() )
										{
										menu->Hide();
										}
									TaskCorrect = false;
									ReturnTaskNumber();
									return;
									}
								else
									j++;

								}

							if( ActiveTrainMenu )
								{

								VwEmptySignalArgs args( this );
								m_closeTrainingMenuSignal.Raise( args );
								
								}
							else
								{

								VwEmptySignalArgs args( this );
								m_closeMenuSignal.Raise( args );
								//VisibleIndicator( false );
								}

							}
						}
					m_bPreDisableState = false;
					lastClosingTime = clock();
					//update your variable of condition
					}
				}
			else
				{
				m_bPreDisableState = true;
				ClosedMenue = false;
				}
	
	//////////////////////////////////

		if( ActiveMenu )
		{
			if( hasAllOpen )
			{

				//if( ( ( clock( ) - lastClosingTime ) / ( double )CLOCKS_PER_SEC ) >=  0.08 )
				{
					if( m_bAllOpen == false )
					{
						VwEmptySignalArgs args( this );
						m_showMenuSignal.Raise( args );
						//VisibleIndicator( true );
						//oHand.m_pTimer->ResetLifeTime();
					}
					m_bAllOpen = true;
					lastOpeingTime = clock( );
					//Update Your  Variable  of Condition
				}
			}
			else
			{

				m_bAllOpen = false;
			}

		}
		if( ActiveTrainMenu )
		{
			if( hasAllOpen )
			{

				//if( ( ( clock( ) - lastClosingTime ) / ( double )CLOCKS_PER_SEC ) >= 1 )
				{
					if( m_bAllOpen == false )
					{
						VwEmptySignalArgs args( this );
						m_showMenuTrainingMenuSignal.Raise( args );
						//VisibleIndicator(true );
						//oHand.m_pTimer->ResetLifeTime();
					}
					m_bAllOpen = true;
					lastOpeingTime = clock( );
					//Update Your  Variable  of Condition
				}
			}
			else
			{

				m_bAllOpen = false;
			}
		}
	}

}

void HandInteractionManager::CreateIndicator( )
	{

	TopIndicator = new VwArrowWidget;
	TopIndicator->Init();
	TopIndicator->GetModel()->Position.Set( VistaVector3D( 0.2, 0.29, -.3 ) );
	TopIndicator->GetModel()->LineWidth.Set( .001 );
	TopIndicator->GetModel()->LineLength.Set( .001 );
	TopIndicator->GetModel()->ConeBottomRadius.Set( .02 );
	TopIndicator->GetModel()->ConeHeight.Set( .02 );
	m_pWidgetManager->AddWidget( TopIndicator );

	/*bottomIndicator = new VwArrowWidget;
	bottomIndicator->Init();
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 1, 0, 0 ), Vista::DegToRad( 180 ) );
	bottomIndicator->GetModel( )->LineWidth.Set( .001 );
	bottomIndicator->GetModel( )->LineLength.Set( .001 );
	bottomIndicator->GetModel( )->ConeBottomRadius.Set( .02 );
	bottomIndicator->GetModel( )->ConeHeight.Set( .02 );
	bottomIndicator->GetModel( )->Position.Set( VistaVector3D( 0.2, -0.05, -.3 ) );
	bottomIndicator->GetModel()->Orientation.Set( qRot );
	m_pWidgetManager->AddWidget( bottomIndicator );*/
	VisibleIndicator(false);

	}
void HandInteractionManager::VisibleIndicator( bool ChangeVisibility )
	{
	//TopIndicator->SetVisible( ChangeVisibility );
	//bottomIndicator->SetVisible( ChangeVisibility );
	
	}
VwBoolChangedSignal& HandInteractionManager::GetSelectionChanged()
{
	return m_selectionChnaged;
}

void HandInteractionManager::SetFingerToDisabledState(HandData& oHand, int nFingerIndex)
{
	oHand.m_aFingerInputSlots[nFingerIndex]->Update(S_matOffTransform);
	oHand.m_aFingersPointerIsDisabled[nFingerIndex] = true;
}

std::vector< VpmPullDownMenu* > HandInteractionManager::GetMenuVector()
{
	return m_vecMenu;
}

VwPlaneWidget* HandInteractionManager::CreateMassege()
{
	
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeButton = new VwPlaneWidget;
	m_MassegeButton->Init( );
	m_MassegeButton->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );
	( ( VwColoredPlaneView* )( m_MassegeButton->GetView( ) ) )->SetColor( VistaColor::GRAY );
	if( m_AculusActivated == false )
	{
		m_MassegeButton->GetModel( )->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.17f ) ); // desktop 
	}
	if( m_AculusActivated )
	{
		m_MassegeButton->GetModel( )->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) ); // oculus
	}
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Height.Set( .15f );
	m_MassegeButton->GetModel( )->Width.Set( 0.35f );
	m_pWidgetManager->AddWidget( m_MassegeButton );

	m_MassegeButtonText = new  VglwDynamicTextWidget;
	m_MassegeButtonText->Init( );
	m_MassegeButtonText->GetModel()->Orientation.Set( qRot );
	m_MassegeButtonText->SetInteractionMode( VwWidget::INTERACTION_NONE );
	m_MassegeButtonText->SetEnabled( false );
	m_MassegeButtonText->GetView( )->SetColor( VistaColor::BLACK );
	m_MassegeButtonText->GetView( )->SetText( "Ready !!" );

	if( m_AculusActivated == false )
	{
		m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.169f ) );
	}
	if( m_AculusActivated )
	{
		m_MassegeButtonText->GetModel( )->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) ); // oculus 
	}
	m_MassegeButtonText->GetView( )->SetTextHeight( .05 );
	m_pWidgetManager->AddWidget( m_MassegeButtonText );

	m_MassegeBoxText = new  VglwDynamicTextWidget;
	m_MassegeBoxText->Init( );
	m_MassegeBoxText->SetInteractionMode( VwWidget::INTERACTION_NONE );
	m_MassegeBoxText->SetEnabled( false );
	m_MassegeButtonText->GetModel()->Orientation.Set( qRot );
	m_MassegeBoxText->GetView( )->SetColor( VistaColor::BLACK );
	if( m_AculusActivated == false )
	{
		m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.28f, 0.2f, -0.17f ) ); //desktop 
	}
	if( m_AculusActivated )
	{
		m_MassegeBoxText->GetModel( )->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );// oculus 
	}
	m_MassegeBoxText->GetView( )->SetTextHeight( .05 );
	m_pWidgetManager->AddWidget( m_MassegeBoxText );

	m_MassegeBox = new VwPlaneWidget( );
	m_MassegeBox->Init( );
	m_MassegeBox->SetInteractionMode( VwWidget::INTERACTION_NONE );
	m_MassegeBox->SetEnabled( false );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	( ( VwColoredPlaneView* )( m_MassegeBox->GetView( ) ) )->SetColor( VistaColor::LIGHT_GRAY );
	if( m_AculusActivated == false )
	{
		m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.18f ) );// desktop 
	}
	if( m_AculusActivated )
	{
		m_MassegeBox->GetModel( )->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );// oculus 
	}
	m_MassegeBox->GetModel( )->Width.Set( .70 );
	m_MassegeBox->GetModel( )->Height.Set( .30 );
	m_pWidgetManager->AddWidget( m_MassegeBox );

	m_MassegeButton->GetClickable( )->GetClickedSignal( ).AddSlot( this, &HandInteractionManager::OnClicked );
	SetVisibilityChanged( false ,false);
		
	for( HandData& oHand : m_vecHands )
	{
		for( VwVirtualDevice* pDevice : oHand.m_aFingerDevices )
			m_MassegeButton->RegisterVirtualDevice( pDevice );
	}
	m_vecMessage.push_back( m_MassegeButton );

	return m_MassegeButton;
}
void HandInteractionManager::OnClicked( const VwEmptySignalArgs& oArgs )
{
VisibleIndicator( true );
SetVisibilityChanged( false, false );


ActiveMenu = true;
VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( -40 ) );
m_MassegeBox->GetModel()->Orientation.Set(qRot);
m_MassegeButton->GetModel( )->Orientation.Set( qRot );
m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.6f, 0.2f, -0.3f ) );
m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.6f, 0.16f, -0.29f ) );
m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( 0.28f, 0.23f, -0.25f ) );
m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( 0.5f, 0.16f, -0.25f ) );
SetVisibilityChanged( true ,false);

switch( counter )
	{
		case 0:
			time1 = clock();
			counter++;
			break;
		case 1:
			time2 = clock();
			counter++;
			break;
		case 2:
			time3 = clock();
			counter++;
			break;
		case 3:
			time4 = clock();
			counter++;
			break;
		case 4:
			time5 = clock();
			counter++;
			break;
		case 5:
			time6 = clock();
			counter++;
			break;
		case 6:
			time7 = clock();
			counter++;
			break;
		case 7:
			time8 = clock();
			counter++;
			break;
		case 8:
			time9 = clock();
			counter++;
			break;
		case 9:
			time10 = clock();
			counter = 0;
			break;

	}

}

void HandInteractionManager::SetVisibilityChanged( bool VisibilityChanged , bool ButtonVisibility  )
{
	if( m_MassegeBox != nullptr )
	{
		
		m_MassegeBox->SetVisible( VisibilityChanged );
		m_MassegeButton->SetVisible( ButtonVisibility );
		m_MassegeBoxText->SetVisible( VisibilityChanged );
		m_MassegeButtonText->SetVisible( ButtonVisibility );

	}
}

VpmPullDownMenu* HandInteractionManager::CreateTrainingMenu( const VistaVector3D& v3MenuPosition, const VistaQuaternion& qOri )
{
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_pMenuWidgetTraining = new VpmPullDownMenu( );
	m_pMenuWidgetTraining->Init( );
	m_pMenuWidgetTraining->GetModel( )->Orientation.Set( qRot );
	m_pMenuWidgetTraining->GetModel( )->Position.Set( VistaVector3D( 0.f, 0.1f, -0.17f ) );
	m_pMenuWidgetTraining->GetModel( )->Height.Set( .30 );
	m_pMenuWidgetTraining->GetModel( )->Width.Set( 0.25 );


	auto element1 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "File" );
	element1->SetImage( VistaOGLUtils::LoadTextureFromTga( "res/icon_down.tga" ) );
	auto element2 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Edit" );
	auto element3 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "View" );
	auto element4 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element44 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element45 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element46 = m_pMenuWidgetTraining->AddElement<VpmCheckBoxElement>( "Project" );
	auto element47 = m_pMenuWidgetTraining->AddElement<>( "Project" );
	auto element48 = m_pMenuWidgetTraining->AddElement<VpmCheckBoxElement>( "Project" );
	

	auto element75 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element76 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element77 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element78 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	auto element79 = m_pMenuWidgetTraining->AddElement<VpmLabelElement>( "Project" );
	

	VpmPullDownMenu* m_pMenuWidgetTraining1 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining1->Init( );
	auto element5 = m_pMenuWidgetTraining1->AddElement<VpmLabelElement>( "New" );
	auto element6 = m_pMenuWidgetTraining1->AddElement<VpmLabelElement>( "Open" );
	auto element7 = m_pMenuWidgetTraining1->AddElement<VpmLabelElement>( "Add" );
	auto element9 = m_pMenuWidgetTraining1->AddElement<VpmLabelElement>( "Close Solution" );
	m_pMenuWidgetTraining->AddSubMenu( element1, m_pMenuWidgetTraining1 );

	VpmPullDownMenu* m_pMenuWidgetTraining2 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining2->Init( );
	auto element10 = m_pMenuWidgetTraining2->AddElement<VpmScalerElement>( "Undo   Ctrl+Z" );
	m_pMenuWidgetTraining->AddSubMenu( element2, m_pMenuWidgetTraining2 );

	element2->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick18 );//4
	element10->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick17 );//4

	VpmPullDownMenu* m_pMenuWidgetTraining3 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining3->Init( );
	auto element15 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Solution " );
	auto element16 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Team " );
	auto element17 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Server " );
	auto element18 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Object " );
	auto element53 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Solution " );
	auto element54 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Team " );
	auto element55 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Server " );
	auto element56 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Object " );
	auto element57 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Team " );
	auto element58 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Server " );
	auto element59 = m_pMenuWidgetTraining3->AddElement<VpmCheckBoxElement>( "Object " );
	m_pMenuWidgetTraining->AddSubMenu( element3, m_pMenuWidgetTraining3 );


	VpmPullDownMenu* m_pMenuWidgetTraining4 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining4->Init( );
	auto element19 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Add Class" );
	auto element20 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Class Wizard" );
	auto element21 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Rescan Solution" );
	auto element22 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Project Dependencies" );

	auto element60 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Add Class" );
	auto element61 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Class Wizard" );
	auto element62 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Rescan Solution" );
	auto element63 = m_pMenuWidgetTraining4->AddElement<VpmLabelElement>( "Project Dependencies" );
	m_pMenuWidgetTraining->AddSubMenu( element4, m_pMenuWidgetTraining4 );

	VpmPullDownMenu* m_pMenuWidgetTraining5 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining5->Init( );
	auto element23 = m_pMenuWidgetTraining5->AddElement<VpmLabelElement>( "Project  Ctrl+Shift+N" );
	auto element24 = m_pMenuWidgetTraining5->AddElement<VpmLabelElement>( "WebSite Shift+Alt+N" );
	auto element25 = m_pMenuWidgetTraining5->AddElement<VpmLabelElement>( "Team Project" );
	auto element26 = m_pMenuWidgetTraining5->AddElement<VpmLabelElement>( "File     Ctrl+N" );
	m_pMenuWidgetTraining1->AddSubMenu( element5, m_pMenuWidgetTraining5 );

	VpmPullDownMenu* m_pMenuWidgetTraining6 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining6->Init( );
	auto element27 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "Project/ Solution" );
	auto element28 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "WebSite Shift+Alt+N" );
	auto element29 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "Convert" );
	auto element64 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "Project/ Solution" );
	auto element65 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "WebSite Shift+Alt+N" );
	auto element66 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "Convert" );
	//auto element30 = m_pMenuWidget6->AddElement<VpmLabelElement>( "File       Ctrl+N" );
	auto element31 = m_pMenuWidgetTraining6->AddElement<VpmLabelElement>( "Tool" );
	m_pMenuWidgetTraining1->AddSubMenu( element6, m_pMenuWidgetTraining6 );

	VpmPullDownMenu* m_pMenuWidgetTraining7 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining7->Init( );
	auto element32 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New Project" );
	auto element33 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New WebSite" );
	auto element34 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Project" );
	auto element35 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Website" );

	auto element67 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New Project" );
	auto element68 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New WebSite" );
	auto element69 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Project" );
	auto element70 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Website" );

	auto element71 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New Project" );
	auto element72 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "New WebSite" );
	auto element73 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Project" );
	auto element74 = m_pMenuWidgetTraining7->AddElement<VpmRadioButtonElement>( "Existing Website" );
	m_pMenuWidgetTraining1->AddSubMenu( element7, m_pMenuWidgetTraining7 );

	VpmPullDownMenu* m_pMenuWidgetTraining8 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining8->Init( );
	auto element36 = m_pMenuWidgetTraining8->AddElement<VpmScalerElement>( "Color" );
	auto element37 = m_pMenuWidgetTraining8->AddElement<VpmScalerElement>( "Effect" );
	auto element38 = m_pMenuWidgetTraining8->AddElement<VpmScalerElement>( "Zoom in" );
	auto element39 = m_pMenuWidgetTraining8->AddElement<VpmScalerElement>( "Zoom out" );
	
	m_pMenuWidgetTraining6->AddSubMenu( element31, m_pMenuWidgetTraining8 );


	VpmPullDownMenu* m_pMenuWidgetTraining9 = new VpmPullDownMenu( );
	m_pMenuWidgetTraining9->Init( );
	auto element40 = m_pMenuWidgetTraining9->AddElement<VpmRadioButtonElement>( "Project" );
	auto element41 = m_pMenuWidgetTraining9->AddElement<VpmRadioButtonElement>( "Effect" );
	auto element42 = m_pMenuWidgetTraining9->AddElement<VpmRadioButtonElement>( "Setting" );
	auto element43 = m_pMenuWidgetTraining9->AddElement<VpmRadioButtonElement>( "Previous" );
	m_pMenuWidgetTraining6->AddSubMenu( element29, m_pMenuWidgetTraining9 );

	m_pWidgetManager->AddWidget( m_pMenuWidgetTraining );
	for( HandData& oHand : m_vecHands )
	{
		for( VwVirtualDevice* pDevice : oHand.m_aFingerDevices )
			m_pMenuWidgetTraining->RegisterVirtualDevice( pDevice );
	}
	m_vecTtrainingMenu.push_back( m_pMenuWidgetTraining );
	m_pMenuWidgetTraining->CloseActiveSubMenu( );
	return m_pMenuWidgetTraining;
}

VpmPullDownMenu* HandInteractionManager::CreateMenu( const VistaVector3D& v3MenuPosition, const VistaQuaternion& qOri )
{
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );

	VpmPullDownMenu* m_pMenuWidget = new VpmPullDownMenu( );
	m_pMenuWidget->Init( );
	m_pMenuWidget->GetModel( )->Orientation.Set( qRot );
	m_pMenuWidget->GetModel( )->Position.Set( VistaVector3D( 0.f, 0.1f, -0.17f ) );
	m_pMenuWidget->GetModel( )->Height.Set( .35f );
	m_pMenuWidget->GetModel( )->Width.Set( 0.30f );


	auto element1 = m_pMenuWidget->AddElement<VpmLabelElement>( "Country" );
	element1->SetImage( VistaOGLUtils::LoadTextureFromTga( "res/icon_down.tga" ) );
	auto element2 = m_pMenuWidget->AddElement<VpmLabelElement>( "Sport" );
	auto element3 = m_pMenuWidget->AddElement<VpmLabelElement>( "Education" );
	auto element6 = m_pMenuWidget->AddElement<VpmLabelElement>( "Weather" );
	auto element5 = m_pMenuWidget->AddElement<VpmLabelElement>( "Equipment" );
	auto element4 = m_pMenuWidget->AddElement<VpmLabelElement>( "Fruit" );
	auto element84 = m_pMenuWidget->AddElement<VpmLabelElement>( "Animal" );


	VpmPullDownMenu* m_pMenuWidget1 = new VpmPullDownMenu( );
	m_pMenuWidget1->Init( );
	auto element7 = m_pMenuWidget1->AddElement<VpmLabelElement>( "Germany" );
	auto element8 = m_pMenuWidget1->AddElement<VpmLabelElement>( "Italy" );
	auto element9 = m_pMenuWidget1->AddElement<VpmLabelElement>( "USA" );
	auto element10 = m_pMenuWidget1->AddElement<VpmLabelElement>( "Canada" );
	m_pMenuWidget->AddSubMenu( element1, m_pMenuWidget1 );

	VpmPullDownMenu* m_pMenuWidget2 = new VpmPullDownMenu( );
	m_pMenuWidget2->Init( );
	auto element14 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Swimming " );
	auto element15 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Basketball " );
	auto element16 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Football " );
	auto element17 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Yoga" );
	auto element18 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Reading " );
	auto element19 = m_pMenuWidget2->AddElement<VpmCheckBoxElement>( "Listening to music" );
	m_pMenuWidget->AddSubMenu( element2, m_pMenuWidget2 );


	VpmPullDownMenu* m_pMenuWidget3 = new VpmPullDownMenu( );
	m_pMenuWidget3->Init( );
	auto element20 = m_pMenuWidget3->AddElement<VpmLabelElement>( "Bachelors" );
	auto element21 = m_pMenuWidget3->AddElement<VpmLabelElement>( "Master" );
	auto element22 = m_pMenuWidget3->AddElement<VpmLabelElement>( "PhD Student" );
	auto element23 = m_pMenuWidget3->AddElement<VpmLabelElement>( "Doctorate" );
	auto element24 = m_pMenuWidget3->AddElement<VpmLabelElement>( "Post doctorate" );
	auto element25 = m_pMenuWidget3->AddElement<VpmLabelElement>( "Professor" );
	m_pMenuWidget->AddSubMenu( element3, m_pMenuWidget3 );


	VpmPullDownMenu* m_pMenuWidget4 = new VpmPullDownMenu( );
	m_pMenuWidget4->Init( );
	auto element26 = m_pMenuWidget4->AddElement<VpmLabelElement>( "Dog" );
	auto element27 = m_pMenuWidget4->AddElement<VpmLabelElement>( "Horse" );
	auto element28 = m_pMenuWidget4->AddElement<VpmLabelElement>( "Mouse" );
	auto element29 = m_pMenuWidget4->AddElement<VpmLabelElement>( "Cat" );
	m_pMenuWidget->AddSubMenu( element84, m_pMenuWidget4 );

	VpmPullDownMenu* m_pMenuWidget5 = new VpmPullDownMenu( );
	m_pMenuWidget5->Init( );
	auto element30 = m_pMenuWidget5->AddElement<VpmLabelElement>( "Desk" );
	auto element34 = m_pMenuWidget5->AddElement<VpmLabelElement>( "Computer" );
	auto element31 = m_pMenuWidget5->AddElement<VpmLabelElement>( "Pen" );
	auto element32 = m_pMenuWidget5->AddElement<VpmLabelElement>( "Book" );
	auto element33 = m_pMenuWidget5->AddElement<VpmLabelElement>( "Eraser" );

	m_pMenuWidget->AddSubMenu( element5, m_pMenuWidget5 );



	VpmPullDownMenu* m_pMenuWidget6 = new VpmPullDownMenu( );
	m_pMenuWidget6->Init( );
	auto element35 = m_pMenuWidget6->AddElement<VpmRadioButtonElement>( "Sunny" );
	auto element36 = m_pMenuWidget6->AddElement<VpmRadioButtonElement>( "Cloudy" );
	auto element37 = m_pMenuWidget6->AddElement<VpmRadioButtonElement>( "Rainy" );
	auto element38 = m_pMenuWidget6->AddElement<VpmRadioButtonElement>( "Dazzle" );
	auto element39 = m_pMenuWidget6->AddElement<VpmRadioButtonElement>( "Fog" );
	m_pMenuWidget->AddSubMenu( element6, m_pMenuWidget6 );


	VpmPullDownMenu* m_pMenuWidget7 = new VpmPullDownMenu( );
	m_pMenuWidget7->Init( );
	auto element40 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Aachen" );
	auto element41 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Dosseldorf" );
	auto element42 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Frankfurt" );
	auto element43 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Berlin" );
	auto element44 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Dortmund" );
	auto element45 = m_pMenuWidget7->AddElement<VpmLabelElement>( "Hamburg" );
	m_pMenuWidget1->AddSubMenu( element7, m_pMenuWidget7 );

	VpmPullDownMenu* m_pMenuWidget8 = new VpmPullDownMenu( );
	m_pMenuWidget8->Init( );
	auto element46 = m_pMenuWidget8->AddElement<VpmLabelElement>( "Milan" );
	auto element47 = m_pMenuWidget8->AddElement<VpmLabelElement>( "Venice" );
	auto element48 = m_pMenuWidget8->AddElement<VpmLabelElement>( "Rome" );
	auto element49 = m_pMenuWidget8->AddElement<VpmLabelElement>( "Pisa" );
	m_pMenuWidget1->AddSubMenu( element8, m_pMenuWidget8 );


	VpmPullDownMenu* m_pMenuWidget9 = new VpmPullDownMenu( );
	m_pMenuWidget9->Init( );
	auto element53 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "Turkey" );


	auto element50 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "Washington" );
	auto element51 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "New York City" );
	auto element52 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "Chicago" );
	auto element54 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "Boston" );
	auto element55 = m_pMenuWidget9->AddElement<VpmRadioButtonElement>( "Seattle" );
	m_pMenuWidget1->AddSubMenu( element9, m_pMenuWidget9 );


	VpmPullDownMenu* m_pMenuWidget10 = new VpmPullDownMenu( );
	m_pMenuWidget10->Init( );
	auto element56 = m_pMenuWidget10->AddElement<VpmRadioButtonElement >( "Toronto" );
	auto element57 = m_pMenuWidget10->AddElement<VpmRadioButtonElement >( "Ottawa" );
	auto element58 = m_pMenuWidget10->AddElement<VpmRadioButtonElement >( "Vancouver" );
	auto element59 = m_pMenuWidget10->AddElement<VpmRadioButtonElement >( "Montreal" );
	m_pMenuWidget1->AddSubMenu( element10, m_pMenuWidget10 );

	VpmPullDownMenu* m_pMenuWidget11 = new VpmPullDownMenu( );
	m_pMenuWidget11->Init( );
	auto element60 = m_pMenuWidget11->AddElement<VpmLabelElement >( "Mathematic" );
	auto element61 = m_pMenuWidget11->AddElement<VpmLabelElement >( "Engineering" );
	auto element62 = m_pMenuWidget11->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element20, m_pMenuWidget11 );



	VpmPullDownMenu* m_pMenuWidget12 = new VpmPullDownMenu( );
	m_pMenuWidget12->Init( );
	auto element63 = m_pMenuWidget12->AddElement<VpmLabelElement >( "Mathematic" );
	auto element64 = m_pMenuWidget12->AddElement<VpmLabelElement >( "Engineering" );
	auto element65 = m_pMenuWidget12->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element21, m_pMenuWidget12 );

	VpmPullDownMenu* m_pMenuWidget13 = new VpmPullDownMenu( );
	m_pMenuWidget13->Init( );
	auto element66 = m_pMenuWidget13->AddElement<VpmLabelElement >( "Mathematic" );
	auto element67 = m_pMenuWidget13->AddElement<VpmLabelElement >( "Engineering" );
	auto element68 = m_pMenuWidget13->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element22, m_pMenuWidget13 );



	VpmPullDownMenu* m_pMenuWidget14 = new VpmPullDownMenu( );
	m_pMenuWidget14->Init( );
	auto element69 = m_pMenuWidget14->AddElement<VpmLabelElement >( "Mathematic" );
	auto element70 = m_pMenuWidget14->AddElement<VpmLabelElement >( "Engineering" );
	auto element71 = m_pMenuWidget14->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element23, m_pMenuWidget14 );

	VpmPullDownMenu* m_pMenuWidget15 = new VpmPullDownMenu( );
	m_pMenuWidget15->Init( );
	auto element72 = m_pMenuWidget15->AddElement<VpmLabelElement >( "Mathematic" );
	auto element73 = m_pMenuWidget15->AddElement<VpmLabelElement >( "Engineering" );
	auto element74 = m_pMenuWidget15->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element24, m_pMenuWidget15 );

	VpmPullDownMenu* m_pMenuWidget16 = new VpmPullDownMenu( );
	m_pMenuWidget16->Init( );
	auto element75 = m_pMenuWidget16->AddElement<VpmLabelElement >( "Mathematic" );
	auto element76 = m_pMenuWidget16->AddElement<VpmLabelElement >( "Engineering" );
	auto element77 = m_pMenuWidget16->AddElement<VpmLabelElement >( "Science" );
	m_pMenuWidget3->AddSubMenu( element25, m_pMenuWidget16 );

	VpmPullDownMenu* m_pMenuWidget17 = new VpmPullDownMenu( );
	m_pMenuWidget17->Init( );
	auto element78 = m_pMenuWidget17->AddElement<VpmLabelElement >( "Area" );
	auto element81 = m_pMenuWidget17->AddElement<VpmLabelElement >( "Population" );
	m_pMenuWidget7->AddSubMenu( element41, m_pMenuWidget17 );

	VpmPullDownMenu* m_pMenuWidget18 = new VpmPullDownMenu( );
	m_pMenuWidget18->Init( );
	auto element79 = m_pMenuWidget18->AddElement<VpmLabelElement >( "Area" );
	auto element82 = m_pMenuWidget18->AddElement<VpmLabelElement >( "Population" );
	m_pMenuWidget7->AddSubMenu( element42, m_pMenuWidget18 );

	VpmPullDownMenu* m_pMenuWidget19 = new VpmPullDownMenu( );
	m_pMenuWidget19->Init( );
	auto element80 = m_pMenuWidget19->AddElement<VpmLabelElement >( "Area" );
	auto element83 = m_pMenuWidget19->AddElement<VpmLabelElement >( "Population" );
	auto element93 = m_pMenuWidget19->AddElement<VpmLabelElement >( "Time zone" );
	m_pMenuWidget7->AddSubMenu( element43, m_pMenuWidget19 );

	VpmPullDownMenu* m_pMenuWidget22 = new VpmPullDownMenu( );
	m_pMenuWidget22->Init( );
	auto element92 = m_pMenuWidget22->AddElement<VpmScalerElement >( "big" );
	m_pMenuWidget19->AddSubMenu( element83, m_pMenuWidget22 );

	VpmPullDownMenu* m_pMenuWidget20 = new VpmPullDownMenu( );
	m_pMenuWidget20->Init( );
	auto element85 = m_pMenuWidget20->AddElement<VpmLabelElement >( "Kiwi" );
	auto element86 = m_pMenuWidget20->AddElement<VpmLabelElement >( "Orange" );
	auto element87 = m_pMenuWidget20->AddElement<VpmLabelElement >( "Apple" );
	auto element89 = m_pMenuWidget20->AddElement<VpmLabelElement >( "Watermelon " );
	auto element90 = m_pMenuWidget20->AddElement<VpmLabelElement >( "Banana" );
	m_pMenuWidget->AddSubMenu( element4, m_pMenuWidget20 );


	VpmPullDownMenu* m_pMenuWidget21 = new VpmPullDownMenu( );
	m_pMenuWidget21->Init( );
	auto element91 = m_pMenuWidget21->AddElement<VpmSoildButtonElement >( "Apple" );
	element91->AddNewButton( VistaColor::GREEN, VistaColor::DARK_GREEN, VpmGlobalConfiguration::PressedColor );
	element91->AddNewButton( VistaColor::RED, VistaColor::DARK_RED, VpmGlobalConfiguration::PressedColor );
	m_pMenuWidget20->AddSubMenu( element87, m_pMenuWidget21 );


	element14->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick1 ); //1 
	element66->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick2 );//2
	element37->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick3 );//3
	element92->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick4 );//4
	element32->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick5 );//5
	//element43->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick5 );// 5
	element91->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick7 );// 6
	element64->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick12 );//7
	element46->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick13 );//8
	element35->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick14 );//9 
	element34->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick15 );// 10 

	element83->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick16 );
	element15->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick6 );
	element17->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick8 );
	element18->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick9 );
	element19->GetElementDownSignal( ).AddSlot( this, &HandInteractionManager::OnElementClick10 );

	m_pWidgetManager->AddWidget( m_pMenuWidget );
	for( HandData& oHand : m_vecHands )
	{
	for( VwVirtualDevice* pDevice : oHand.m_aFingerDevices )
		m_pMenuWidget->RegisterVirtualDevice( pDevice );
	}
	m_vecMenu.push_back( m_pMenuWidget );
	m_pMenuWidget->CloseActiveSubMenu();
	return m_pMenuWidget;

}
std::vector< VpmPullDownMenu* > HandInteractionManager::GetMenuTrainingVector( )
{
	return m_vecTtrainingMenu;
}

void HandInteractionManager::SaveTimeToIniFile( const std::string & strFileName )
{
	pParticleProperties.SetValue( "Time1", time1 );
	pParticleProperties.SetValue( "Time2", time2 );
	pParticleProperties.SetValue( "Time3", time3 );
	pParticleProperties.SetValue( "Time4", time4 );
	pParticleProperties.SetValue( "Time5", time5 );
	pParticleProperties.SetValue( "Time6", time6 );
	pParticleProperties.SetValue( "Time7", time7 );
	pParticleProperties.SetValue( "Time8", time8 );
	pParticleProperties.SetValue( "Time9", time9 );
	pParticleProperties.SetValue( "Time10", time10 );

	std::string filePath = "configfiles/TimeForImmirsiveMenu/";
	float fClock = clock();
	std::ostringstream buff;
	buff << fClock;
	std::string timeName = buff.str();

	VistaIniFileParser::WriteProplistToFile(
		filePath + strFileName + timeName,
		pParticleProperties,
		true  //delete this later on should not overwrite existingfile
		);
}

void HandInteractionManager::ReturnTaskNumber( )
	{
	VisibleIndicator( false);
	if( i == 10 )
		{
		ActiveMenu = false;
		time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );
		ThanksMassege();
		return;
		i = 0;
		}
	else
		{
		switch( myvector[i] )
			{
				case 1:
					i++;
					TaskNumber++;
					CreateFirstTask();

					break;
				case 2:
					i++;
					TaskNumber++;
					CreateSecondTask();
					break;
				case 3:
					i++;
					TaskNumber++;
					CreateThirdTask();

					break;
				case 4:
					i++;
					TaskNumber++;
					CreateFourthTask();

					break;
				case 5:
					i++;
					TaskNumber++;
					CreateFifthTask();

					break;
				case 6:
					i++;
					TaskNumber++;
					CreateSixTask();

					break;
				case 7:
					i++;
					TaskNumber++;
					CreateSevenTask();

					break;
				case 8:

					i++;
					TaskNumber++;
					CreateEithTask();

					break;
				case 9:
					i++;
					TaskNumber++;
					CreateNineTask();

					break;
				case 10:
					i++;
					TaskNumber++;
					CreateTenTask();

					break;
			}
		}




	}
void HandInteractionManager::RandomTaskCreator( )
	{
	
	std::srand( unsigned( std::time( 0 ) ) );
	// set some values:
	for( int i = 1; i < 11; ++i ) myvector.push_back( i ); //  1 2 3 4 5 6 7 8 9 10
	// using built-in random generator:
	std::random_shuffle( myvector.begin(), myvector.end() );
	ReturnTaskNumber();
	}
void HandInteractionManager::CreateFirstTask( )
{
	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel( )->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel( )->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel( )->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true,true );
	m_MassegeBoxText->GetView( )->SetText( "Sport->Swimming \n (Then  Close the Menu) " );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	TaskNumber = 1;


}

void HandInteractionManager::CreateSecondTask( )
{
	
     ActiveMenu = false;
	 VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	 m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	 m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	 m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	 m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	 m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	 m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	 m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	 m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	 SetVisibilityChanged( true, true );

	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView( )->SetText( "Education->PhD student \n ->mathematic" );
	
	TaskNumber = 2;
}

void HandInteractionManager::CreateThirdTask( )
{
	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView( )->SetText( "Weather->Rainy \n (Then  Close the Menu) " );
	
	TaskNumber = 3;
}

void HandInteractionManager::CreateFourthTask( )
{
	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView( )->SetText( "Country->Germany->Berlin\n population->(5 < X < 10)" );
	
	TaskNumber = 4;
}

void HandInteractionManager::CreateFifthTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Equipment\n->Book " );
	
	TaskNumber = 5;
	}

void HandInteractionManager::CreateSixTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Fruit->apple\n->green " );
	
	TaskNumber = 6;
	}

void HandInteractionManager::CreateSevenTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Education->Master\n -> Engineering " );
	TaskNumber = 7;
	}

void HandInteractionManager::CreateEithTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Country->Italy\n -> Milan  " );
	TaskNumber = 8;
	}
void HandInteractionManager::CreateNineTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Weather->Sunny \n (Then  Close the Menu)  " );
	
	TaskNumber = 9;
	}

void HandInteractionManager::CreateTenTask( )
	{

	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( "Equipment\n->Computer " );
	
	TaskNumber = 10;
	}

void HandInteractionManager::OnChechBox()
{
	if( TaskNumber = 1 )
	{
		if( value6 == 1 )
		{
			if( value1 == 0 && value2 == 0 && value3 == 0 && value4 == 0 && value5 == 0 )
			{
				TaskCorrect = true;
				//time1 = ( ( clock() - time1 )  / ( double )CLOCKS_PER_SEC );
				switch( counter )
				{
					case 1:
						time1 = ( ( clock( ) - time1 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 2:
						time2 = ( ( clock( ) - time2 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 3:
						time3 = ( ( clock( ) - time3 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 4:
						time4 = ( ( clock( ) - time4 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 5:
						time5 = ( ( clock( ) - time5 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 6:
						time6 = ( ( clock( ) - time6 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 7:
						time7 = ( ( clock( ) - time7 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 8:
						time8 = ( ( clock( ) - time8 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 9:
						time9 = ( ( clock( ) - time9 ) / ( double )CLOCKS_PER_SEC );

						break;
					case 10:
						time10 = ( ( clock( ) - time10 ) / ( double )CLOCKS_PER_SEC );

						break;

				}

				ActiveMenu = false;

			}
		}

		
	}
}

void HandInteractionManager::OnElementClick1( const VwEmptySignalArgs& p )
{
	switch( value6 )
	{
		case  0:
			value6 = 1;
			break;
		case 1:
			value6 = 0;
			break;
	}
	OnChechBox();

}

void HandInteractionManager::OnElementClick2( const VwEmptySignalArgs& p )
	{
	if( TaskNumber == 2 )
		{
		//time2 = ( ( clock( ) - time2 ) / ( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//TaskNumber = 3;
			}

	}


void HandInteractionManager::OnElementClick3( const VwEmptySignalArgs& p )
	{
	if( TaskNumber == 3 )
		{
		//time3 = ( ( clock( ) - time3 ) / ( double )CLOCKS_PER_SEC );
		TaskCorrect = true;
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		/*for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}*/
		ActiveMenu = false;
		//ReturnTaskNumber();
		//TaskNumber = 4;
			}


	}

void HandInteractionManager::OnElementClick4( const VwEmptySignalArgs& p )
	{
	ScalerElement = false;
	if( TaskNumber == 4 )
		{
		//time4 = ( ( clock( ) - time4 ) / ( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//TaskNumber = 5;
			}



	}


void HandInteractionManager::OnElementClick5( const VwEmptySignalArgs& p )
	{

	if( TaskNumber ==5 )
		{
		//time5 = ( ( clock() - time5) / ( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//TaskNumber = 6;
			}


	}
void HandInteractionManager::OnElementClick11( const VwEmptySignalArgs& p )
	{


	}

void HandInteractionManager::OnElementClick12( const VwEmptySignalArgs& p )
	{

	if( TaskNumber == 7 )
		{
		//time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//TaskNumber = 8;
			}




	}
void HandInteractionManager::OnElementClick13( const VwEmptySignalArgs& p )
	{


	if( TaskNumber == 8 )
		{
		//time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//TaskNumber = 9;
			}
	}

void HandInteractionManager::OnElementClick14( const VwEmptySignalArgs& p )
	{

	if( TaskNumber == 9 )
		{
		TaskCorrect = true;
		//time9 = ( ( clock() - time9 ) /( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
	/*	for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}*/
		ActiveMenu = false;
		//ReturnTaskNumber();
			}

	}

void HandInteractionManager::OnElementClick15( const VwEmptySignalArgs& p )
	{

	if( TaskNumber == 10 )
		{
		//time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );
		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
			}

	}

void HandInteractionManager::OnElementClick6( const VwEmptySignalArgs& p )
	{
	switch( value1 )
	{
		case  0:
			value1 = 1;
			break;
		case 1:
			value1 = 0;
			break;
	}
	OnChechBox();

	}
void HandInteractionManager::OnElementClick16( const VwEmptySignalArgs& p )
{
		ScalerElement = true;
}
void HandInteractionManager::OnElementClick7( const VwEmptySignalArgs& p )
	{
	//if( TaskNumber == 6 )
		{
		//time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

		switch( counter )
			{
				case 1:
					time1 = ( ( clock() - time1 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 2:
					time2 = ( ( clock() - time2 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 3:
					time3 = ( ( clock() - time3 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 4:
					time4 = ( ( clock() - time4 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 5:
					time5 = ( ( clock() - time5 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 6:
					time6 = ( ( clock() - time6 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 7:
					time7 = ( ( clock() - time7 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 8:
					time8 = ( ( clock() - time8 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 9:
					time9 = ( ( clock() - time9 ) / ( double )CLOCKS_PER_SEC );

					break;
				case 10:
					time10 = ( ( clock() - time10 ) / ( double )CLOCKS_PER_SEC );

					break;

			}
		for( VpmPullDownMenu* menu : GetMenuVector() )
			{
			menu->Hide();
			}
		ActiveMenu = false;
		ReturnTaskNumber();
		//		TaskNumber = 7;

			}



	}
void HandInteractionManager::OnElementClick8( const VwEmptySignalArgs& p )
	{
	switch( value3 )
	{
		case  0:
			value3 = 1;
			break;
		case 1:
			value3 = 0;
			break;
	}

	OnChechBox();
	}

void HandInteractionManager::OnElementClick9( const VwEmptySignalArgs& p )
	{

	switch( value4 )
	{
		case  0:
			value4 = 1;
			break;
		case 1:
			value4 = 0;
			break;
	}
	OnChechBox();
}
void HandInteractionManager::OnElementClick10( const VwEmptySignalArgs& p )
	{

	switch( value5 )
	{
	case  0:
		value5 = 1;
			break;
	case 1: 
		value5 = 0;
		break;
	}
	OnChechBox();
}

void HandInteractionManager::OnElementClick17( const VwEmptySignalArgs& p )
{
	ScalerElement = false;
}
void HandInteractionManager::OnElementClick18( const VwEmptySignalArgs& p )
	{
	ScalerElement = true;
	}

void HandInteractionManager::ThanksMassege( )
	{
	SaveTimeToIniFile( "Time" );
	ActiveMenu = false;
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D( 0, 1, 0 ), Vista::DegToRad( 0 ) );
	m_MassegeBox->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel( )->Orientation.Set( qRot );
	m_MassegeBoxText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButtonText->GetModel( )->Orientation.Set( qRot );
	m_MassegeButton->GetModel()->Position.Set( VistaVector3D( 0.0f, 0.1f, -0.3f ) );
	m_MassegeButtonText->GetModel()->Position.Set( VistaVector3D( -0.05f, 0.1f, -0.29f ) );
	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.25f, 0.2f, -0.31f ) );
	m_MassegeBox->GetModel()->Position.Set( VistaVector3D( 0.f, 0.14f, -0.32f ) );

	SetVisibilityChanged( true, true );
	m_MassegeButton->SetVisible( false );
	m_MassegeButtonText->SetVisible( false );
	m_MassegeBoxText->GetView( )->SetTextHeight( .08 );
	m_MassegeBoxText->GetView()->SetText( " Thanks for your \n participation :)  " );


	m_MassegeBoxText->GetModel()->Position.Set( VistaVector3D( -0.16f, 0.15f, -0.17f ) );
	}

void HandInteractionManager::Init( VwWidgetManager* pWidgetManager)
{
	m_pWidgetManager = pWidgetManager;
}




/*============================================================================*/
/* END OF FILE																  */
/*============================================================================*/
