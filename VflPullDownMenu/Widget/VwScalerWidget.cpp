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
#include "VwScalerWidget.h"
#include <VistaOpenGLWidgets\Widgets\VglwDynamicTextWidget.h>
#include <VistaOpenGLWidgets\Widgets\Views/VglwTexturedPlaneView.h>
#include "VwScalerWidgetView.h"

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
VwScalerWidget::VwScalerWidget(void)
	: m_pLeftHandle(new VwPlaneWidget())
	, m_pRightHandle(new VwPlaneWidget())
	, m_pMinText(new VglwDynamicTextWidget())
	, m_pMaxText (new VglwDynamicTextWidget())

{
	m_pLeftHandle->SetView(new VglwTexturedPlaneView());
	m_pRightHandle->SetView(new VglwTexturedPlaneView());
	
	AddWidget(m_pLeftHandle);
	AddWidget(m_pRightHandle);

	AddWidget(m_pMinText);
	AddWidget(m_pMaxText);
}

VwScalerWidget::~VwScalerWidget(void)
{
	delete m_pLeftHandle;
	delete m_pRightHandle;

	delete m_pMinText;
	delete m_pMaxText;
}

void VwScalerWidget::Init()
{
	VwWidget::Init();

	for( auto pChild : GetChildWidgets( ) )
	{
		pChild->Init( );
	}
	
	InitHandle();
	InitTextLabel();
	InitSlots();
	UpdateHanldeSize();
	UpdateTextLabelSize();	


	this->GetVisibilityChangedSignal( ).AddSlot( this, &VwScalerWidget::OnVisibilityChanged );

}
void VwScalerWidget::OnButtonDown( const VwEmptySignalArgs& oArgs )
{
	if( GetEnabled( ) && GetFocusable( )->GetIsFocused( ) )
		GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_PRESSED );
	
}
void VwScalerWidget::OnVisibilityChanged( const VwEmptySignalArgs& oArgs )
{
	if( GetVisible( ) )
	{
		m_pRightHandle->SetVisible( true );
		m_pLeftHandle->SetVisible( true );
		m_pMinText->SetVisible( true );
		m_pMaxText->SetVisible( true );
	}
	else
	{
		m_pRightHandle->SetVisible( false );
		m_pLeftHandle->SetVisible( false );
		m_pMinText->SetVisible( false );
		m_pMaxText->SetVisible( false );
	}
}
void VwScalerWidget::InitHandle()
{
	m_pRightHandle->SetInteractionMode( VwWidget::INTERACTION_NONE );
	m_pLeftHandle->GetModel()->Position.GetConstraintSignal().AddSlot(this,&VwScalerWidget::LeftHandleConstraint);
	m_pRightHandle->GetModel()->Position.GetConstraintSignal().AddSlot(this,&VwScalerWidget::RightHandleConstraint);
	m_pRightHandle->GetModel()->Position.GetSignal().AddSlot(this,&VwScalerWidget::OnRightHandlePositionChanged);
	m_pLeftHandle->GetModel()->Position.GetSignal().AddSlot(this,&VwScalerWidget::OnLeftHandlePositionChanged);
	UpdateHandlePositions();
}

void VwScalerWidget::InitTextLabel()
{
	m_pMinText->GetModel()->SetHorizontalAlignment(VglwDynamicTextWidget::Model::HALIGN_RIGHT);
	m_pMaxText->GetModel()->SetHorizontalAlignment(VglwDynamicTextWidget::Model::HALIGN_LEFT);
	m_pMinText->GetView()->SetColor( VistaColor::BLACK );
	m_pMaxText->GetView( )->SetColor( VistaColor::BLACK );
	m_pMinText->SetEnabled(false);
	m_pMaxText->SetEnabled(false);
	UpdateTextLabelPosition();
	UpdateLabelText();
}

void VwScalerWidget::InitSlots()
{
	GetModel()->LowerBound.GetSignal().AddSlot(this,&VwScalerWidget::OnIntervalLowerBoundChanged);
	GetModel()->UpperBound.GetSignal().AddSlot(this,&VwScalerWidget::OnIntervalUpperBoundChanged);
	GetModel()->MinValue.GetSignal().AddSlot(this,&VwScalerWidget::OnValueRangeChanged);
	GetModel()->MaxValue.GetSignal().AddSlot(this,&VwScalerWidget::OnValueRangeChanged);
	GetModel()->Unit.GetSignal().AddSlot(this,&VwScalerWidget::OnUnitChanged);
	GetModel()->Font.GetSignal().AddSlot(this,&VwScalerWidget::OnFontChanged);
	GetModel()->TextSize.GetSignal().AddSlot(this,&VwScalerWidget::OnTextSizeChanged);
	GetModel()->Precision.GetSignal().AddSlot(this,&VwScalerWidget::OnPrecisionChanged);
	GetModel()->Length.GetSignal().AddSlot(this,&VwScalerWidget::OnLengthChanged);
	GetModel()->Width.GetSignal().AddSlot(this,&VwScalerWidget::OnWidthChanged);
	GetModel()->Position.GetSignal().AddSlot(this,&VwScalerWidget::OnPositionChanged);
	GetModel()->Orientation.GetSignal().AddSlot(this,&VwScalerWidget::OnOrientationChanged);
	GetFocusable()->GetFocusGainedSignal().AddSlot(this,&VwScalerWidget::OnFocusGained);
	GetFocusable()->GetFocusLostSignal().AddSlot(this,&VwScalerWidget::OnFocusLost);
	
}

VwScalerWidget::Model* VwScalerWidget::CreateModel() const
{
return new VwScalerWidget::Model( );
}

VwScalerWidgetView* VwScalerWidget::CreateView() const
{
	return new VwScalerWidgetView;
}

VwScalerWidget::Model* VwScalerWidget::GetModel() const
{
	return static_cast< VwScalerWidget::Model* >(VwWidget::GetModel());
}

VwScalerWidgetView* VwScalerWidget::GetView() const
{
	return dynamic_cast< VwScalerWidgetView* >(VwWidget::GetView());
}

bool VwScalerWidget::GetIsFocused() const
{
	return m_pLeftHandle->GetFocused()
		|| m_pRightHandle->GetFocused();
}

bool VwScalerWidget::GetIsDragging() const
{
	return m_pLeftHandle->GetIsDragging()
	|| m_pRightHandle->GetIsDragging();
}

VglwTexturedPlaneView* VwScalerWidget::GetLeftHandleView()
{
	return dynamic_cast< VglwTexturedPlaneView* >(m_pLeftHandle->GetView());
}

VglwTexturedPlaneView* VwScalerWidget::GetRightHandleView()
{
	return dynamic_cast< VglwTexturedPlaneView* >(m_pRightHandle->GetView());
}

VglwDynamicTextView* VwScalerWidget::GetMinTextLabelView()
{
	return m_pMinText->GetView();
}

VglwDynamicTextView* VwScalerWidget::GetMaxTextLabelView()
{
	return m_pMaxText->GetView();
}

void VwScalerWidget::UpdateHanldeSize()
{
/*float fWidth=GetModel()->Width();

m_pLeftHandle->GetModel()->SizeZ.Set(0.5f * fWidth);
m_pRightHandle->GetModel()->SizeZ.Set(0.5f * fWidth);

m_pLeftHandle->GetModel()->SizeX.Set(fWidth);
m_pRightHandle->GetModel()->SizeX.Set(fWidth);*/
	float fWidth = GetModel()->Width();

	m_pLeftHandle->GetModel()->Height.Set( fWidth * 3 );
	m_pRightHandle->GetModel()->Height.Set( fWidth * 3 );

	m_pLeftHandle->GetModel()->Width.Set( 2.f * fWidth );
	m_pRightHandle->GetModel( )->Width.Set( 2.f * fWidth );
}

void VwScalerWidget::UpdateTextLabelSize()
{
	float fWidth=GetModel()->Width();

	m_pMinText->GetModel()->Height.Set(0.5f * fWidth);
	m_pMaxText->GetModel()->Height.Set(0.5f * fWidth);
}

void VwScalerWidget::UpdateHandlePositions(VwPlaneWidget* pHandle,float fValue)
{
	VistaVector3D v3Handle(GetModel()->Length() * (fValue - 0.5f), 0.0f, 0.0005f);
	VistaQuaternion qOri=GetModel()->Orientation();
	if(!pHandle->GetFocused())
		pHandle->GetModel()->Position.Set(qOri.Rotate(v3Handle) + GetModel()->Position());
	pHandle->GetModel()->Orientation.Set(GetModel()->Orientation());
}

void VwScalerWidget::UpdateHandlePositions()
{
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	float fUpperValue=(GetModel()->UpperBound() - GetModel()->MinValue()) / fScale;
	float fLowerValue=(GetModel()->LowerBound() - GetModel()->MinValue()) / fScale;
	UpdateHandlePositions(m_pRightHandle, fUpperValue);
	UpdateHandlePositions(m_pLeftHandle, fLowerValue);
}

void VwScalerWidget::OnFocusGained(const VwEmptySignalArgs& oArgs)
{
GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_FOCUSED );
}

void VwScalerWidget::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	if(GetEnabled())
	{
	GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_ENABLED );
	}
	else
	{
	GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_DISABLED );
	}
}

void VwScalerWidget::UpdateTextLabelPosition()
{
 	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	float fLowerValue=(GetModel()->LowerBound() - GetModel()->MinValue()) / fScale;
	float fUpperValue=(GetModel()->UpperBound() - GetModel()->MinValue()) / fScale;

	
	VistaVector3D v3LeftLabelPos(GetModel()->Length() * (fLowerValue - 0.5f), GetModel()->Width(), 0.0f);
	VistaVector3D v3RightLabelPos(GetModel()->Length() * (fUpperValue - 0.5f), GetModel()->Width(), 0.0f);
	VistaQuaternion qOri=GetModel()->Orientation();
	v3LeftLabelPos=qOri.Rotate(v3LeftLabelPos);
	v3RightLabelPos=qOri.Rotate(v3RightLabelPos);
	m_pMinText->GetModel( )->Position.Set( v3LeftLabelPos + GetModel( )->Position( )+VistaVector3D( 0.f, 0.01f, 0.f ) );
	m_pMaxText->GetModel( )->Position.Set( v3RightLabelPos + GetModel( )->Position( ) + VistaVector3D( 0.f, 0.01f, 0.f ) );
	m_pMinText->GetModel()->Orientation.Set(GetModel()->Orientation());
	m_pMaxText->GetModel()->Orientation.Set(GetModel()->Orientation());
	
}

float VwScalerWidget::HandlePositionToValue(const VistaVector3D& v3Pos)
{
	VistaVector3D v3Dir=v3Pos - GetModel()->Position();
	VistaQuaternion qOri=GetModel()->Orientation();
	qOri.Invert();
	v3Dir=qOri.Rotate(v3Dir);
	float fValue=((v3Dir[0]) / GetModel()->Length()) + .5f;

	
	return  fValue;	
}

VistaVector3D VwScalerWidget::ValueToHandlePosition(float fValue)
{
	VistaVector3D v3Handle(GetModel()->Length() * (fValue - 0.5f), 0.0f, 0.0005f);
	VistaQuaternion qOri=GetModel()->Orientation();
	return qOri.Rotate(v3Handle) + GetModel()->Position();
}

void VwScalerWidget::LeftHandleConstraint(VwVectorConstraintSignalArgs& oArgs)
{
	
	if(!m_pLeftHandle->GetFocused())
			return;
	float fValue=HandlePositionToValue(oArgs.GetNewValue()); 
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	float fUpper=(GetModel()->UpperBound() - GetModel()->MinValue()) / fScale;
		
	if(fValue > (fUpper - GetModel()->BoundDelta()))
	{
		fValue=fUpper - GetModel()->BoundDelta();
 	}
	else if(fValue < 0.0f)
	{
		fValue=0.0f;
	}
	oArgs.SetNewValue(ValueToHandlePosition(fValue));

}

void VwScalerWidget::RightHandleConstraint(VwVectorConstraintSignalArgs& oArgs)
{
	
	if(!m_pRightHandle->GetFocused())
			return;
	
	float fValue=HandlePositionToValue(oArgs.GetNewValue());
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	float fLower=(GetModel()->LowerBound() - GetModel()->MinValue()) / fScale;

	if(fValue > 1.0f)
	{
		fValue=1.0;
	}
	else if(fValue < (fLower + GetModel()->BoundDelta()))
	{
		fValue=fLower + GetModel()->BoundDelta();
	}
	oArgs.SetNewValue(ValueToHandlePosition(fValue));
 }

void VwScalerWidget::OnRightHandlePositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	OnBoundCheck();
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	GetModel()->UpperBound.Set((HandlePositionToValue(oArgs.GetNewValue()) * fScale) + GetModel()->MinValue());
	if( GetEnabled( ) && GetFocusable( )->GetIsFocused( ) )
		GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_PRESSED );
	
	
}
void VwScalerWidget::OnLeftHandlePositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	OnBoundCheck();
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	GetModel()->LowerBound.Set((HandlePositionToValue(oArgs.GetNewValue()) * fScale) + GetModel()->MinValue());
	if( GetEnabled( ) && GetFocusable( )->GetIsFocused( ) )
		GetView( )->SetState( VwScalerWidgetView::VIEW_STATE_PRESSED );
	
}

void VwScalerWidget::OnIntervalLowerBoundChanged(const VwFloatChangedSignalArgs& oArgs)
{
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	UpdateHandlePositions(m_pLeftHandle,(oArgs.GetNewValue() - GetModel()->MinValue()) / fScale);
		
	InitTextLabel();
	UpdateTextLabelPosition();

	std::ostringstream os;
	os<<std::fixed;
	os.precision(GetModel()->Precision());
	os<<GetModel()->LowerBound()<<GetModel()->Unit();
	m_pMinText->GetModel()->Text.Set(os.str());
}

void VwScalerWidget::OnIntervalUpperBoundChanged(const VwFloatChangedSignalArgs& oArgs)
{
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	UpdateHandlePositions(m_pRightHandle, (oArgs.GetNewValue() - GetModel()->MinValue()) / fScale);
	
	InitTextLabel();
	UpdateTextLabelPosition();

	std::ostringstream os;
	os << std::fixed;
	os.precision(GetModel()->Precision());
	os<<GetModel()->UpperBound()<<GetModel()->Unit();
    m_pMaxText->GetModel()->Text.Set(os.str());
}

void VwScalerWidget::OnValueRangeChanged(const VwFloatChangedSignalArgs& oArgs)
{
	UpdateHandlePositions();
	
}

void VwScalerWidget::OnUnitChanged(const VwStringChangedSignalArgs& oArgs)
{
	UpdateLabelText();
}

void VwScalerWidget::OnFontChanged(const VwChangedFromToSignalArgs< VtrFont* >& oArgs)
{
	m_pMinText->GetModel()->Font.Set(oArgs.GetNewValue());
	m_pMaxText->GetModel()->Font.Set(oArgs.GetNewValue());
	m_pMinText->GetModel()->SetVerticalAlignment(VglwDynamicTextWidget::Model::VALIGN_BASELINE);
	m_pMaxText->GetModel()->SetVerticalAlignment(VglwDynamicTextWidget::Model::VALIGN_BASELINE);
	GetView()->SetFont(GetModel()->Font());
}

void VwScalerWidget::OnTextSizeChanged(const VwFloatChangedSignalArgs& oArgs)
{
	m_pMinText->GetModel()->Height.Set(GetModel()->TextSize());
	m_pMaxText->GetModel()->Height.Set(GetModel()->TextSize());
	GetView()->SetTextSize(GetModel()->TextSize());
}

void VwScalerWidget::OnPrecisionChanged(const VwChangedFromToSignalArgs < unsigned int > & oArgs)
{
	UpdateLabelText();
	GetView()->SetPrecision(GetModel()->Precision());
}

void VwScalerWidget::UpdateLabelText()
{
	std::ostringstream osMin;
	osMin<<std::fixed;
	osMin.precision(GetModel()->Precision());
	osMin<<GetModel()->LowerBound()<<GetModel()->Unit();

	std::ostringstream osMax;
	osMax<<std::fixed;
	osMax.precision(GetModel()->Precision());
	osMax<<GetModel()->UpperBound()<<GetModel()->Unit();
	auto MinValueSignal = std::stoi( osMin.str( ) );
	if( MinValueSignal >= 5 )
	{
		
	}

	m_pMinText->GetModel()->Text.Set(osMin.str());
	m_pMaxText->GetModel()->Text.Set(osMax.str());
}

void VwScalerWidget::OnLengthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetLength(GetModel()->Length());
	float fScale=GetModel()->MaxValue() - GetModel()->MinValue();
	float fUpperValue=(GetModel()->UpperBound() - GetModel()->MinValue()) / fScale;
	float fLowerValue=(GetModel()->LowerBound() - GetModel()->MinValue()) / fScale;
	UpdateHandlePositions(m_pLeftHandle, fLowerValue);
	UpdateHandlePositions(m_pRightHandle, fUpperValue);
	UpdateTextLabelPosition();	
}

void VwScalerWidget::OnWidthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetWidth(GetModel()->Width());
	UpdateHanldeSize();
	UpdateTextLabelSize();
	UpdateTextLabelPosition();
}

void VwScalerWidget::OnBoundDeltaChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetBoundDelta(GetModel()->BoundDelta());
	UpdateHanldeSize();
	UpdateTextLabelSize();
	UpdateTextLabelPosition();
}

void VwScalerWidget::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
	UpdateHandlePositions();
	UpdateTextLabelPosition();
}

void VwScalerWidget::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
	UpdateHandlePositions();
	UpdateTextLabelPosition( );
}

void VwScalerWidget::OnBoundCheck()
{
	if(GetModel()->LowerBound() < GetModel()->MinValue())
	{
		GetModel()->LowerBound.Set(GetModel()->MinValue());
	}
	if(GetModel()->LowerBound() > GetModel()->MaxValue())
	{
		GetModel()->LowerBound.Set(GetModel()->MinValue());
	}
	if(GetModel()->UpperBound() < GetModel()->MinValue())
	{
		GetModel()->UpperBound.Set(GetModel()->MaxValue());
	}
	if(GetModel()->UpperBound() > GetModel()->MaxValue())
	{
		GetModel()->UpperBound.Set(GetModel()->MaxValue());
	}
}
/*============================================================================*/
/* IMPLEMENTATION                                                             */
/*============================================================================*/

VwScalerWidget::Model::Model()
: LowerBound( 1 )
, UpperBound( 10 )
,BoundDelta(0.05f)

, MinValue( 1 )
, MaxValue( 10 )
, Unit("")
, Font()
, TextSize(0.4f)
, Precision(0)

,Length(.12f)
,Width( 0.02f )

,Position()
,Orientation()
{}

VwScalerWidget::Model::~Model()
{
}

/*============================================================================*/
/*  END OF FILE "IntervalSelectionWidget.cpp"					                  */
/*============================================================================*/
