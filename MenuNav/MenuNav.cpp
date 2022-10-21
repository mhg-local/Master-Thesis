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
 * $Id: MenuNav.cpp 49363 2015-04-20 14:24:47Z dz762974 $
 */


#include "MenuNav.h"
#include "Hand.h"
#include "HandInteractionManager.h"
#include "KeyboardCallbacks.h"
#include "MassegeWidget.h"

#include <VistaWidgets/Widgets/VwBackgroundWidget.h>
#include <VistaBase/VistaExceptionBase.h>
#include <VistaBase/VistaReferenceFrame.h>
#include <VistaBase/VistaVectorMath.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaUtilityMacros.h>

#include <VistaAspects/VistaPropertyAwareable.h>

#include <VistaTools/VistaIniFileParser.h>
#include <VistaTools/VistaRandomNumberGenerator.h>
#include <VistaTools/VistaFileSystemDirectory.h>

#include <VistaDataFlowNet/VdfnObjectRegistry.h>

#include <VistaKernel/DisplayManager/VistaDisplaySystem.h>
#include <VistaKernel/DisplayManager/VistaVirtualPlatform.h>
#include <VistaKernel/Cluster/VistaClusterMode.h>
#include <VistaKernel/VistaSystem.h>
#include <VistaKernel/GraphicsManager/VistaSceneGraph.h>
#include <VistaKernel/GraphicsManager/VistaGeometry.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernel/GraphicsManager/VistaGeomNode.h>
#include <VistaKernel/GraphicsManager/VistaLightNode.h>
#include <VistaKernel/DisplayManager/VistaDisplayManager.h>
#include <VistaKernel/DisplayManager/VistaWindow.h>
#include <VistaKernel/DisplayManager/VistaViewport.h>
#include <VistaKernel/DisplayManager/VistaProjection.h>
#include <VistaKernel/DisplayManager/VistaWindowingToolkit.h>
#include <VistaKernel/InteractionManager/VistaUserPlatform.h>
#include <VistaKernel/InteractionManager/VistaVirtualPlatformAdapter.h>
#include <VistaKernel/InteractionManager/VistaKeyboardSystemControl.h>
#include <VistaKernel/EventManager/VistaSystemEvent.h>
#include <VistaKernel/EventManager/VistaEventManager.h>
#include <VistaKernel/EventManager/VistaEventHandler.h>
//widget classes
#include <VistaWidgets/FocusStrategies/VwPriorityMergerFocusStrategy.h>
#include <VistaWidgets/FocusStrategies/VwAlwaysInFocusStrategy.h>
#include <VistaWidgets/FocusStrategies/VwIntenSelectFocusStrategy.h>
#include <VistaWidgets/FocusStrategies/VwProximityFocusStrategy.h>
#include <VistaWidgets/FocusStrategies/VwRaycastingFocusStrategy.h>
#include <VistaWidgets/VwFocusDispatcher.h>
#include <VistaWidgets/VwVirtualDevice.h>
#include <VistaWidgets/VwWidgetManager.h>
#include <VistaWidgets/VwWidgetManagerUpdateHandler.h>
#include <VistaWidgets/Widgets/VwPlaneWidget.h>

#include <VistaWidgets/Widgets/VwTransformWidget.h>
#include <VistaWidgets/Widgets/VwSphereWidget.h>

#include "VistaWidgets/VwWidget.h"
#include <VistaKernelOpenSGExt/VistaOpenSGMaterialTools.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernelOpenSGExt/VistaOpenSGModelOptimizer.h>
//Widget
#include <VistaWidgets/FocusHandleAspects/VwCenterFocusHandleAspect.h>
#include <VistaWidgets/FocusHandleAspects/VwPlaneFocusHandleAspect.h>
#include <VistaWidgets/SignalSystem/VwChangedFromToSignalArgs.h>
#include <VistaWidgets/Widgets/Traits/VwClickable.h>
#include <VistaWidgets/Widgets/Traits/VwFocusable.h>
#include <VistaWidgets/VwWidgetManagerUpdateHandler.h>
#include "Widgets/Views/VwColoredPlaneView.h"
#include<VistaOpenGLWidgets\Widgets\VglwCheckboxWidget.h>


//Menu include
#include<VistaOGLExt\VistaOGLUtils.h>
#include<VpmPullDownMenu.h>
#include<Elements\VpmElement.h>
#include<Elements\VpmCheckBoxElement.h>
#include<Elements\VpmRadioButtonElement.h>
#include<Elements\VpmLabelElement.h>
#include<Elements\VpmSoildButtonElement.h>
#include<Elements\VpmTextureButtonElement.h>
#include<Elements\VpmScalerElement.h>
#include<VpmGlobalConfiguration.h>
#include <VistaBase/VistaTimer.h>
#include<FocusStrategy\VwFocusStrategy.h>



//text 
#include <G:\dev\VflTextRendering\VflTextRendering\VtrFontManager.h>

//include hand

#include<VistaWidgets\Widgets\VwTextLabelWidget.h>
#include<VistaOpenGLWidgets\Widgets\VglwDynamicTextWidget.h>

#include <VistaOGLExt/VistaShaderRegistry.h>

#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>
#include <VistaInterProcComm/Concurrency/VistaMutex.h>

#include <VistaTools/VistaStreams.h>
#include <VistaTools/VistaFileSystemDirectory.h>

#include <math.h>
#include <cassert>
#include<VpmTimer.h>

/*============================================================================*/
/* MACROS AND DEFINES, CONSTANTS AND STATICS, FUNCTION-PROTOTYPES             */
/*============================================================================*/

/*============================================================================*/
/* IMPLEMENTATION                                                             */
/*============================================================================*/

MenuNav::MenuNav()
: m_pVistaSystem( new VistaSystem() )
, m_sIniFile("setup.ini")
, m_pLeftHand( nullptr )
, m_pRightHand( nullptr )
, m_pHandInteraction( nullptr )
, m_TimerText ( new VglwDynamicTextWidget( ))
, m_timer(nullptr)

{	
	Start = clock();
		
    VpmGlobalConfiguration::Init( m_pVistaSystem );
	if (!LoadConfigSettings(m_InitConstants, m_sIniFile))
	{
		vstr::err() << "Warning: Cannot read init file: " << m_sIniFile << std::endl;
		VISTA_THROW("No init file found!", 2);
	}
	m_pWidgetManager=std::make_shared< VwWidgetManager >();
	m_pHandInteraction=new HandInteractionManager(m_pWidgetManager.get());
	
	m_pHandInteraction->GetSelectionChanged( ).AddSlot( this, &MenuNav::OnSelectionChanged );
//	m_pHandInteraction->GetSelectionDisable().AddSlot( this, &MenuNav::OnSelectionChanged );
	// m_pHandInteraction->SetSelectionData( VistaVector3D( 0, 0.05f, 0.17f ), VistaQuaternion( VistaVector3D( 0, 0, 0 ), VistaVector3D( 0, 0.05f, -0.17f ) ), 0.05f, 0.17f,0.f, false );// vista system 
   m_pHandInteraction->SetSelectionData( VistaVector3D( 0, 0, 0.3 ), VistaQuaternion( VistaVector3D( 0, 0, 0 ), VistaVector3D( 0, 0, -0.3 ) ), 0.05f, 0.3f, 0.17f, true ); // Oculus 
	m_pVistaSystem->GetEventManager()->AddEventHandler( m_pHandInteraction, VistaSystemEvent::GetTypeId(), VistaSystemEvent::VSE_POSTAPPLICATIONLOOP );



}


void MenuNav::OnSelectionChanged( const VwBoolChangedSignalArgs& oArgs )
{

	m_pSelect->Update( oArgs.GetNewValue());
	m_pHandInteraction->GetDeepValueChangedSignal( ).AddSlot( this, &MenuNav::OnDeepActivated );
	//if( oArgs.GetNewValue() )
	//{
	//	for( auto elm : m_vecFingers )
	//	{
	//		elm->GetStrategy()->LockedStrategy();
	//	}
	//}
	
}
MenuNav::~MenuNav()
{
	delete m_pHandInteraction;
	delete m_pLeftHand;
	delete m_pRightHand;
	delete m_TimerText;
	for (auto& elem : m_vecFingers)
	{
		delete elem;
	}
	m_pVistaSystem->GetEventManager()->RemEventHandler( m_pHandInteraction, VistaSystemEvent::GetTypeId(), VistaSystemEvent::VSE_POSTAPPLICATIONLOOP );

	delete m_pVistaSystem;
}

void MenuNav::Run()
{
	m_pVistaSystem->Run();	
}

bool MenuNav::Init(int argc, char  *argv[])
{
	// ViSTA's standard intro message
	m_pVistaSystem->IntroMsg();

	if( !m_pVistaSystem->Init( argc, argv ) )
		return false;

	VistaWindow* pOcuWin = m_pVistaSystem->GetDisplayManager()->GetWindowByName("MAIN_WINDOW");
	if (pOcuWin)
		m_pVistaSystem->GetDisplayManager()->GetWindowingToolkit()->BindWindow(pOcuWin);

	if( m_pVistaSystem->GetDisplayManager()->GetDisplaySystem() == NULL )
	{
		vstr::errp() << "Could not create Display" << std::endl;
		return false;
	}

	VtrFontManager::GetInstance()->SetFontDirectory("res/");
	VtrFontManager::GetInstance()->Init("res/");

	m_pLeftHand = new Hand( "left_hand" );
	m_pLeftHand->SetIsLeft(true);
	m_pRightHand = new Hand( "right_hand" );
	m_pRightHand->SetIsLeft( false );
	VistaShaderRegistry::GetInstance().AddSearchDirectory("./resources/shader/");

 	VistaUserPlatform* pUserPlatform = m_pVistaSystem->GetPlatformFor(m_pVistaSystem->GetDisplayManager()->GetDisplaySystem());
 	m_pVistaSystem->GetDfnObjectRegistry()->SetObject("PLATFORM_OFFSET", nullptr, pUserPlatform->GetPlatformNode());

	m_pWidgetUpdateHandler=std::make_unique< VwWidgetManagerUpdateHandler >(
		m_pWidgetManager.get(),
		m_pVistaSystem->GetEventManager(),
		VistaSystemEvent::VSE_POSTAPPLICATIONLOOP
		);
	//InitVirtualDevice();



	CreateInteraction();
	CreateScene( );
	//m_pHandInteraction->CreateIndicator();
	InitMenu( );
	m_pHandInteraction->CreateMassege( );

	// create some basic keyboard navigation
	VistaKeyboardSystemControl* pCtrl = m_pVistaSystem->GetKeyboardSystemControl();
	pCtrl->BindAction(VISTA_KEY_DOWNARROW, new ConfigSceneTranslation(VistaVector3D(-0.01f, 0.f, 0.f), m_pVistaSystem), "translate in scene's global Z direction");
	pCtrl->BindAction(VISTA_KEY_UPARROW, new ConfigSceneTranslation(VistaVector3D(0.01f, 0.f, 0.f), m_pVistaSystem), "translate in scene's global -Z direction");
	pCtrl->BindAction(VISTA_KEY_LEFTARROW, new ConfigSceneTranslation(VistaVector3D(0.f, 0.f, -0.01f), m_pVistaSystem), "translate in scene's global X direction");
	pCtrl->BindAction(VISTA_KEY_RIGHTARROW, new ConfigSceneTranslation(VistaVector3D(0.f, 0.f, 0.01f), m_pVistaSystem), "translate in scene's global -X direction");
	pCtrl->BindAction(VISTA_KEY_PAGEUP, new ConfigSceneTranslation(VistaVector3D(0.f, 0.01f, 0.f), m_pVistaSystem), "translate in scene's global Y direction");
	pCtrl->BindAction(VISTA_KEY_PAGEDOWN, new ConfigSceneTranslation(VistaVector3D(0.f, -0.01f, 0.f), m_pVistaSystem), "translate in scene's global -Y direction");
	pCtrl->BindAction( VISTA_KEY_ESC, [this]() {

		if( m_pHandInteraction->ActiveTrainMenu )
		{
			m_pHandInteraction->ActiveTrainMenu = false;
			for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
			{
				menu->Hide( );

			}
			m_pHandInteraction->RandomTaskCreator( );
		}
			
	} );

		
	return true;
}

void MenuNav::InitMenu()
{
	VistaQuaternion qRot = VistaAxisAndAngle( VistaVector3D(0, 1, 0 ), Vista::DegToRad(0) );
	//m_pHandInteraction->CreateMenu( VistaVector3D( 0.f, 0.1f, -0.17f ), qRot );// vista system 
	//m_pHandInteraction->CreateTrainingMenu( VistaVector3D( 0.f, 0.1f, -0.17f ), qRot );// vista system 
	m_pHandInteraction->CreateMenu( VistaVector3D( 0, 0, -.3 ), qRot ); // Oculus
	m_pHandInteraction->CreateTrainingMenu(  VistaVector3D( 0, 0, -.3 ), qRot ); //oculus
   		
}
void MenuNav::OnShowMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->ShowMenu( );
	}
}

void MenuNav::OnShowTrainingMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->ShowMenu( );
	}
}
void MenuNav::OnCloseMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector() )
	{
		menu->CloseActiveSubMenu();
	}
}
void MenuNav::OnCloseTrainingMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->CloseActiveSubMenu( );
	}
}

void MenuNav::OnMoveUpMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->MoveUpMenu( );
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->MoveUpMenu( );
	}

}
void MenuNav::OnVisibleProgress( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->ProgressVisible( );
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->ProgressVisible( );
	}

}
void MenuNav::OnInvisibleProgress( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->ProgressInvisible( );
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->ProgressInvisible( );
	}

}


void MenuNav::OnMoveDownMenu( const VwEmptySignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->MoveDownMenu();
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->MoveDownMenu( );
	}
}
void MenuNav::OnProgressActivated( const VwFloatChangedSignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->ProgressiveValue( oArgs.GetNewValue() );
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->ProgressiveValue( oArgs.GetNewValue( ) );
	}
}

void MenuNav::OnDeepActivated( const VwFloatChangedSignalArgs& oArgs )
{
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{
		menu->DeepValue( oArgs.GetNewValue( ) );
	}
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuTrainingVector( ) )
	{
		menu->DeepValue( oArgs.GetNewValue( ) );
	}
}


void MenuNav::CreateInteraction( )
{
	// create input devices (fingers)
	m_pSelect = new VwInputSlot<bool>( );
	
	std::string aFingers[ 4 ] = { "Index", "Middle", "Ring", "Pinky" };
	Finger* pFinger;

	for( auto elem : aFingers )
	{
		pFinger = new Finger;
		pFinger->Init( m_pWidgetManager.get(), m_pSelect, "Hand0Finger" + elem, m_pHandInteraction );
		m_vecFingers.push_back( pFinger );

		pFinger = new Finger;
		pFinger->Init( m_pWidgetManager.get(), m_pSelect, "Hand1Finger" + elem, m_pHandInteraction );
		m_vecFingers.push_back( pFinger );
	}
	m_pHandInteraction->GetCloseMenuSignal( ).AddSlot( this, &MenuNav::OnCloseMenu );
	m_pHandInteraction->GetCloseTrainingMenuSignal( ).AddSlot( this, &MenuNav::OnCloseTrainingMenu );
	m_pHandInteraction->GetShowMenuSignal( ).AddSlot( this, &MenuNav::OnShowMenu );
	m_pHandInteraction->GetShowTrainingMenuSignal( ).AddSlot( this, &MenuNav::OnShowTrainingMenu );
	m_pHandInteraction->GetMoveDownSignal( ).AddSlot( this, &MenuNav::OnMoveDownMenu );
	m_pHandInteraction->GetMoveUpSignal( ).AddSlot( this, &MenuNav::OnMoveUpMenu ); 
	m_pHandInteraction->getProgressInvisible( ).AddSlot( this, &MenuNav::OnInvisibleProgress );
	m_pHandInteraction->getProgressVisible( ).AddSlot( this, &MenuNav::OnVisibleProgress );
	m_pHandInteraction->GetProgressValueChangedSignal( ).AddSlot( this, &MenuNav::OnProgressActivated );



	m_pHandInteraction->Init( m_pWidgetManager.get( ) );
	m_pHandInteraction->RegisterHand( m_pRightHand,
	{ m_vecFingers[ 0 ]->GetInputSlot( ),
	m_vecFingers[ 2 ]->GetInputSlot( ),
	m_vecFingers[ 4 ]->GetInputSlot( ),
	m_vecFingers[ 6 ]->GetInputSlot( ) },
	{ m_vecFingers[ 0 ]->GetVirtualDevice( ),
	m_vecFingers[ 2 ]->GetVirtualDevice( ),
	m_vecFingers[ 4 ]->GetVirtualDevice( ),
	m_vecFingers[ 6 ]->GetVirtualDevice( ) }
	);
	m_pHandInteraction->RegisterHand( m_pLeftHand,
	{ m_vecFingers[ 1 ]->GetInputSlot( ),
	m_vecFingers[ 3 ]->GetInputSlot( ),
	m_vecFingers[ 5 ]->GetInputSlot( ),
	m_vecFingers[ 7 ]->GetInputSlot( ) },
	{ m_vecFingers[ 1 ]->GetVirtualDevice( ),
	m_vecFingers[ 3 ]->GetVirtualDevice( ),
	m_vecFingers[ 5 ]->GetVirtualDevice( ),
	m_vecFingers[ 7 ]->GetVirtualDevice( ) }
	);

}
MenuNav::Finger::Finger()
{};

MenuNav::Finger::~Finger()
{
	delete m_pVirtualDevice;
	delete m_pFocusStrategy;
	delete m_pPose;
};


void MenuNav::Finger::OnHandleClicked( const VwHandleSignalArgs& oArgs )
{
	// check 
	bool flag = false;
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{

		if( menu->Click( oArgs.GetHandle( ) ) )
		{
			flag = true;
			break;
		}

	}
	if( flag )
	{
		oArgs.SetContinue( !flag );
	}
}

void MenuNav::Finger::OnHandleButtonDown( const VwHandleSignalArgs& oArgs )
{
// check 
	bool flag = false;
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{

		if( menu->ButtonDown( oArgs.GetHandle( ) ) )
		{
			flag = true;
			break;
		}
		
	}
	if( flag )
	{
		oArgs.SetContinue( !flag );
	}
}

void MenuNav::Finger::OnHandleButtonUp( const VwHandleSignalArgs& oArgs )
{
	// check 
	bool flag = false;
	for( VpmPullDownMenu* menu : m_pHandInteraction->GetMenuVector( ) )
	{

		if( menu->ButtonUp( oArgs.GetHandle( ) ) )
		{
			flag = true;
			break;
		}

	}
	if( flag )
	{
		oArgs.SetContinue( !flag );
	}
	
}
void MenuNav::Finger::Init(VwWidgetManager* pWidgetManager, VwInputSlot<bool>* pSelect, const std::string& strVirtualDeviceName,HandInteractionManager*handInteraction)
{
	m_pPose = new VwInputSlot<VistaTransformMatrix>();
	m_pFocusStrategy = new VwFocusStrategy( );
	m_pHandInteraction = handInteraction;

	m_pFocusStrategy->GetButtonDownSignal( ).AddSlot( this, &MenuNav::Finger::OnHandleButtonDown );
	m_pFocusStrategy->GetButtonUpSignal( ).AddSlot( this, &MenuNav::Finger::OnHandleButtonUp );
	m_pFocusStrategy->GetClickSignal( ).AddSlot( this, &MenuNav::Finger::OnHandleClicked );
	
	m_pFocusStrategy->SetPoseInputSlot(m_pPose);
	m_pFocusStrategy->SetSelectInputSlot( pSelect );
	
	m_pFocusStrategy->SetFocusRadius( 1.2f );
	VwPriorityMergerFocusStrategy* pMerger = new VwPriorityMergerFocusStrategy;
	VwGenericAlwaysInFocusStrategy* pAlways = new VwGenericAlwaysInFocusStrategy;

	pMerger->AddStrategy( pAlways );
	pMerger->AddStrategy( m_pFocusStrategy );
	m_pVirtualDevice = new VwVirtualDevice(strVirtualDeviceName);
	m_pVirtualDevice->AddInputSlot("Pose", m_pPose);
	m_pVirtualDevice->AddInputSlot("Select", pSelect);
	m_pVirtualDevice->GetFocusDispatcher()->SetRootStrategy(pMerger);
	pWidgetManager->AddVirtualDevice(m_pVirtualDevice);


}

VwVirtualDevice* MenuNav::Finger::GetVirtualDevice() const
{
  
	return m_pVirtualDevice;
}

void MenuNav::CreateScene()
{
	VistaSceneGraph* pSG = m_pVistaSystem->GetGraphicsManager()->GetSceneGraph();

	m_pTransform = pSG->NewTransformNode( pSG->GetRoot() );

	// create a light

	VistaPointLight* pLight = pSG->NewPointLight( pSG->GetRoot() );
	pLight->SetPosition( VistaVector3D( 5, 24, 17 ) );
	pLight->SetAmbientColor( 0.2f, 0.2f, 0.2f );
	pLight->SetDiffuseColor( 0.625f, 0.625f, 0.6f );
	pLight->SetSpecularColor( 0.9f, 0.9f, 0.9f );


	// setup hands
	Hand::DfnNodeCreate* pCreate = new Hand::DfnNodeCreate();
	pCreate->AddHand( m_pLeftHand );
	pCreate->AddHand( m_pRightHand );
	VdfnNodeFactory::GetSingleton()->SetNodeCreator( "HandObject", pCreate );

    m_pLeftHand->CreateSimpleVisualization( pSG->GetRoot( ), pSG, VistaColor::WHITE );
	m_pRightHand->CreateSimpleVisualization( pSG->GetRoot( ), pSG, VistaColor::WHITE );
	
	
	
}

/*============================================================================*/
/*  END OF FILE							                                      */
/*============================================================================*/


