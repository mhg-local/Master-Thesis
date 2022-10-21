

#include"VpmSoildButtonElement.h"
#include"../Widget/VwPlaneWidgetControl.h"
#include"../Widget/VwBorderWidget.h"
#include<VistaWidgets\Widgets\VwPlaneWidget.h>
#include<VistaWidgets\Widgets\Views\VwColoredPlaneView.h>
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

VwWidgetControl* VpmSoildButtonElement::CreateChildWidget()
{
	VwPlaneWidget* plane = new VwPlaneWidget();
	plane->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );
	plane->Init();
	plane->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmSoildButtonElement::OnElementDown );
	return new VwPlaneWidgetControl(plane);
}
void VpmSoildButtonElement::ButtonUp( VwWidget*child )
{
	int index = 0;
	for( VwBorderWidget* cntrl : m_vecBorder )
	{
		if( IsChildOfThisElement( ( VwWidget* )cntrl, child ) )
		{
			VwPlaneWidget* plane = dynamic_cast< VwPlaneWidget* >( cntrl->GetWidget() );

			VwColoredPlaneView* background = dynamic_cast< VwColoredPlaneView* >( plane->GetView( ) );
			if( GetFocused() )
			{
				background->SetState( IVwWidgetView::VIEW_STATE_FOCUSED) ;
			}
			else
				background->SetState( IVwWidgetView::VIEW_STATE_ENABLED );

			VwEmptySignalArgs oThis(this);
			GetButtonClickedSignal( index ).Raise( oThis );
			break;
		}
		index++;
	}
}
bool VpmSoildButtonElement::IsChildOfThisElement( VwWidget*element, VwWidget*child )
{
	if( element == child )
	{
		return true;
	}
	for( VwWidget*e : element->GetChildWidgets() )
	{
		if( IsChildOfThisElement( e, child ) )
		{
			return true;
		}
	}
	return false;
}

void VpmSoildButtonElement::OnElementDown( const VwEmptySignalArgs& oArgs )
{
	VpmElement::OnElementDown( oArgs );
}
VwEmptySignal& VpmSoildButtonElement::GetButtonClickedSignal( int index )
{
	if( index < m_vecSignal.size( ) )
	{
		return *m_vecSignal[ index ];
	}
	VISTA_THROW( "Get Out Of Range Signal", -1 );
}
void VpmSoildButtonElement::ButtonDown( VwWidget* child )
{


	for( VwBorderWidget* cntrl : m_vecBorder )
	{
		if(IsChildOfThisElement((VwWidget*)cntrl,child))
		{

			VwEmptySignalArgs o( this );
			VpmElement::OnElementDown( o );

			VwPlaneWidget* plane = dynamic_cast< VwPlaneWidget* >( cntrl->GetWidget() );
			VwColoredPlaneView* background = dynamic_cast< VwColoredPlaneView* >( plane->GetView( ) );
			
			background->SetState( IVwWidgetView::VIEW_STATE_PRESSED );

			break;
		}
		
	}
}

int VpmSoildButtonElement::AddNewButton(VistaColor enableColor, VistaColor focusColor, VistaColor selectColor)
{

	auto newElement=AddChildButton();
	if ( newElement != NULL )
	{

		VwColoredPlaneView* background = dynamic_cast< VwColoredPlaneView* >( newElement->GetWidget()->GetView() );
			
		//m_pVistaSystem->GetGraphicsManager( )->SetBackgroundColor( VistaColor::BLACK );
		
		background->SetFocusColor( focusColor );
		background->SetPressedColor( selectColor );
		background->SetColor( enableColor );

		LayoutElement();
		return GetNumberOfButton();
	}
	return -1;
}

