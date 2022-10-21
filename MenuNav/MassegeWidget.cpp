/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :                               RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  IntervalSelectionWidget		 RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  VistaWidgets                   Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2013   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*
* $Id: IntervalSelectionWidget.cpp 42923 2014-07-08 12:24:00Z tp483634 $
*/

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/
#include "MassegeWidget.h"
#include <VistaOpenGLWidgets\Widgets\VglwDynamicTextWidget.h>
#include <VistaOpenGLWidgets\Widgets\Views/VglwTexturedPlaneView.h>


#include <VistaWidgets/Widgets/VwTextLabelWidget.h>
//#include <VistaWidgets/Widgets/VwDraggablePlaneWidget.h>
#include <VistaWidgets/Widgets/VwPlaneWidget.h>
#include <VistaWidgets/Widgets/Traits/Constraints/VwDraggingAxisConstraint.h>

#include <VistaOGLExt/VistaOGLUtils.h>
#include <VistaOGLExt/VistaTexture.h>

#include <algorithm>
#include <cassert>
#include <cmath>
/*============================================================================*/
/* CONSTRUCTORS / DESTRUCTOR                                                  */
/*============================================================================*/
MassegeWidget::MassegeWidget( void )
	
{

}

MassegeWidget::~MassegeWidget( void )
{
}

void MassegeWidget::Init( )
{
	VwWidget::Init();

	for( auto pChild : GetChildWidgets( ) )
	{
		pChild->Init( );
	}

	InitMassegeBox();

}
void MassegeWidget::SetVisibilityChanged(bool VisibilityChanged )
{
	
	m_MassegeBox->SetVisible( VisibilityChanged );
	m_MassegeButton->SetVisible( VisibilityChanged );
	m_MassegeBoxText->SetVisible( VisibilityChanged );
	m_MassegeButtonText->SetVisible( VisibilityChanged );
	
}
void MassegeWidget::InitMassegeBox( )
{
	/// Massege Widget 
	VwPlaneWidget*  m_MassageButton = new VwPlaneWidget( );
	m_MassageButton->Init( );
	m_MassageButton->GetModel( )->Position.Set( VistaVector3D( 0.f, 0.0f, -0.16f ) );
	m_MassageButton->GetModel( )->Height.Set( .05f );
	m_MassageButton->GetModel( )->Width.Set( 0.2f );
	m_MassageButton->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );
	m_MassageButton->GetClickable( )->GetButtonUpSignal( ).AddSlot( this, &MassegeWidget::OnButtonDown );

	VwTextLabelView* m_MassageButtenText = new  VwTextLabelView;
	m_MassageButtenText->SetTextColor( VistaColor::BLACK );
	m_MassageButtenText->SetText( "Ready !!" );
	m_MassageButtenText->SetPosition( VistaVector3D( -0.05f, 0.0f, -0.16 ) );
	m_MassageButtenText->SetTextHeight( .02 );

	VwTextLabelView* m_MassageText = new  VwTextLabelView;
	m_MassageText->SetTextColor( VistaColor::BLACK );
	m_MassageText->SetText( "View on top of window can be like it" );
	m_MassageText->SetPosition( VistaVector3D( -0.2f, 0.2f, -0.16 ) );
	m_MassageText->SetTextHeight( .02 );


	VwColoredPlaneView*  MassageBox = new VwColoredPlaneView( );
	MassageBox->SetColor( VistaColor::LIGHT_GREEN );
	MassageBox->SetPosition( VistaVector3D( 0.f, 0.1f, -0.17f ) );
	MassageBox->SetWidth( .50 );
	MassageBox->SetLength( .30 );


	
}
void MassegeWidget::OnButtonDown( const VwEmptySignalArgs& oArgs )
{
	SetVisibilityChanged(false);
	VwTextLabelView* TimerText = new  VwTextLabelView;
	TimerText->SetTextColor( VistaColor::BLACK );
	float Duration = clock() / ( double )CLOCKS_PER_SEC;
	TimerText->SetText("Duration"  );
	TimerText->SetPosition( VistaVector3D( -0.05f, 0.0f, -0.16 ) );
	TimerText->SetTextHeight( .02 );


}

MassegeWidget::Model* MassegeWidget::CreateModel( ) const
{
	return new MassegeWidget::Model( );
}


MassegeWidget::Model* MassegeWidget::GetModel( ) const
{
	return static_cast< MassegeWidget::Model* >( VwWidget::GetModel( ) );
}



//VglwTexturedPlaneView* VwScalerWidget::GetRightHandleView()
//{
//	/*return dynamic_cast< VglwTexturedPlaneView* >(m_pRightHandle->GetView());*/
//}

void MassegeWidget::OnFocusGained( const VwEmptySignalArgs& oArgs )
{

}

void MassegeWidget::OnFocusLost( const VwEmptySignalArgs& oArgs )
{
	/*if(GetEnabled())
	{
	GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_ENABLED );
	}
	else
	{
	GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_DISABLED );
	}*/
}


/*============================================================================*/
/* IMPLEMENTATION                                                             */
/*============================================================================*/

MassegeWidget::Model::Model( )

{}

MassegeWidget::Model::~Model( )
{
}

/*============================================================================*/
/*  END OF FILE "IntervalSelectionWidget.cpp"					                  */
/*============================================================================*/
