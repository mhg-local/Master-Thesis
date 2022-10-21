

#include"VwBoxWidgetControl.h"

#include<VistaWidgets\Widgets\VwBoxWidget.h>

VwBoxWidgetControl::VwBoxWidgetControl( VwBoxWidget* box )
:VwWidgetControl( box )
{

}

void VwBoxWidgetControl::SetPosition( VistaVector3D& pos )
{
	( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Position.Set( pos );
}

VistaVector3D VwBoxWidgetControl::GetPosition( )const
{
	return ( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Position( );
}
void VwBoxWidgetControl::SetOrientation( VistaQuaternion& qOrientation )
{
	( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Orientation.Set( qOrientation );
}
VistaQuaternion VwBoxWidgetControl::GetOrientation( ) const
{
	return ( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Orientation( );
}

void VwBoxWidgetControl::SetWidth( float width )
{
	VistaVector3D diss = ( ( VwBoxWidget* )GetWidget() )->GetModel()->Dimensions();
	diss = VistaVector3D(width,diss[1],diss[2]);
	( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Dimensions.Set( diss );
}
void VwBoxWidgetControl::SetHeight( float height )
{
	VistaVector3D diss = ( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Dimensions( );
	diss = VistaVector3D( diss[0],height, diss[ 2 ] );
	( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Dimensions.Set( diss );
}

float VwBoxWidgetControl::GetWidth( )
{
	VistaVector3D diss = ( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Dimensions( );
	return diss[ 0 ];
}
float VwBoxWidgetControl::GetHeight( )
{
	VistaVector3D diss = ( ( VwBoxWidget* )GetWidget( ) )->GetModel( )->Dimensions( );
	return diss[ 1];
}