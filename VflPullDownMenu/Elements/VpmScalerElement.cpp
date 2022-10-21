#include"VpmScalerElement.h"

#include"..\VpmGlobalConfiguration.h"
#include"../Widget/VwBorderWidget.h"

//#include<VistaOpenGLWidgets\Widgets\VglwIntervalSelectionWidget.h>
#include "../Widget/VwScalerWidget.h"

#include<VistaOpenGLWidgets\Widgets\Views\VglwTexturedPlaneView.h>
#include<VistaOpenGLWidgets\Widgets\Views\VglwMultiLineTextView.h>
//#include<VistaOpenGLWidgets\Widgets\Views\VglwIntervalSelectionView.h>
#include "../Widget/VwScalerWidgetView.h"

#include"../Widget/VwScalerWidgetControl.h"
VpmScalerElement::VpmScalerElement()
{
	m_pScaler = NULL;
}

VpmScalerElement::~VpmScalerElement()
{
	delete m_pScaler;

	delete m_pScalerBorder;
}
void VpmScalerElement::Init()
{
	VpmElement::Init();

	SetLabelVisibility(false);

	m_pScaler = new VwScalerWidget( );
	m_pScaler->Init();

	//m_pScaler->GetModel()->Width.Set( GetModel()->Height()*0.4f );
	//m_pScaler->GetModel()->Length.Set( GetModel()->Width() - 2 * VpmGlobalConfiguration::Left_X_Padding );
	m_pScaler->GetModel( )->Position.Set( GetModel( )->Position( ) );
	m_pScaler->GetModel()->Orientation.Set( GetModel()->Orientation() );
	m_pScaler->GetModel( )->LowerBound.GetSignal( ).AddSlot( this, &VpmScalerElement::OnScalerValueChanged );
	m_pScaler->GetModel( )->UpperBound.GetSignal( ).AddSlot( this, &VpmScalerElement::OnScalerValueChanged );
	//m_pScaler->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmScalerElement::OnElementDown );
	
	//m_pScaler->GetButtonClickedSignal().AddSlot(this,&VpmScalerElement::OnElementDown);
	
	AddSecondElement(m_pScaler);

	
}
void  VpmScalerElement::OnScalerValueChanged( const VwFloatChangedSignalArgs& oArgs )
{
	VwEmptySignalArgs arg( this );
	m_sgScalerValueChanged.Raise( arg );
	
	if( oArgs.GetNewValue() > 5 )
	{
		VwEmptySignalArgs o( this );
		VpmElement::OnElementDown( o );
		
	}
}
void VpmScalerElement::OnElementDown(const VwEmptySignalArgs& oArgs)
{
	//VpmElement::OnElementDown(oArgs);
	
}
void VpmScalerElement::SetMaxValue(float fMax)
{
	m_pScaler->GetModel()->MaxValue.Set(fMax);
}
void VpmScalerElement::SetMinValue(float fMin)
{
	m_pScaler->GetModel()->MinValue.Set(fMin);
}

VwEmptySignal& VpmScalerElement::GetIntervalValueChangedSignal()
{
	return m_sgScalerValueChanged;
}

VwScalerWidgetView*  VpmScalerElement::GetSliderView( ) const
{
	return m_pScaler->GetView();
}
VglwTexturedPlaneView* VpmScalerElement::GetLeftHandelView()
{
   return m_pScaler->GetLeftHandleView();// GetLeftHandelView();
}
VglwTexturedPlaneView* VpmScalerElement::GetRightHandelView()
{
return m_pScaler->GetRightHandleView();// GetRightHandelView();
}


void VpmScalerElement::GetSelectedInterval(float&fLower, float&fUpper)
{
	fLower = m_pScaler->GetModel()->LowerBound();
	fUpper = m_pScaler->GetModel()->UpperBound();
}
void VpmScalerElement::LayoutSecondElement(VistaQuaternion q, VistaVector3D pos)
{
       
	m_pScaler->GetModel()->Font.Set(GetModel()->Font());
	m_pScaler->GetModel()->Position.Set( VistaVector3D( GetModel()->Position()[ 0 ], GetModel()->Position()[ 1 ], pos[ 2 ] ) );
	m_pScaler->GetModel( )->Orientation.Set( q );
	m_pScaler->GetModel()->Width.Set( GetModel()->Height()*0.25f );
	m_pScaler->GetModel()->Length.Set( GetModel()->Width() - 3 * VpmGlobalConfiguration::Left_X_Padding ); 

}

void VpmScalerElement::SetFont(VtrFont* font)
{
	m_pScaler->GetModel()->Font.Set( font );
}


void VpmScalerElement::SetUnit( std::string unit )
{
	m_pScaler->GetModel( )->Unit.Set( unit );
}
void VpmScalerElement::SetPrecision( int precision )
{

	m_pScaler->GetModel( )->Precision.Set( precision );
}
void VpmScalerElement::OnVisibilityChanged( const VwEmptySignalArgs& oArgs )
{
	if( GetVisible() )
		{
		m_pScaler->SetVisible( true );
		m_pScaler->SetEnabled( GetModel()->Enabled() );
		}
	else
		{
		m_pScaler->SetVisible( false );
		}
	VpmElement::OnVisibilityChanged( oArgs );
}

void VpmScalerElement::OnEnabledChanged( const VwBoolChangedSignalArgs& oArgs )
{
	m_pScaler->SetEnabled( oArgs.GetNewValue( ) );

	VpmElement::OnEnabledChanged( oArgs );
}
