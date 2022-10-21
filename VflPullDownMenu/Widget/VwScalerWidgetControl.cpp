

#include"VwScalerWidgetControl.h"

//#include<VistaOpenGLWidgets\Widgets\VglwIntervalSelectionWidget.h>
#include"VwScalerWidget.h"

VwScalerWidgetControl::VwScalerWidgetControl( VwScalerWidget* scaler )
:VwWidgetControl(scaler)
{

}

void VwScalerWidgetControl::SetPosition(VistaVector3D& pos)
{
( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Position.Set( pos );
}

VistaVector3D VwScalerWidgetControl::GetPosition()const {
	return ( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Position( );
}
void VwScalerWidgetControl::SetOrientation(VistaQuaternion& qOrientation) {
	( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Orientation.Set( qOrientation );
}
VistaQuaternion VwScalerWidgetControl::GetOrientation() const {
	return ( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Orientation( );
}

void VwScalerWidgetControl::SetWidth(float width) {
	( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Width.Set( width );
}
void VwScalerWidgetControl::SetHeight(float height) {
	
}
void VwScalerWidgetControl::SetLength( float length )
{
	( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Width.Set( length );
}

float VwScalerWidgetControl::GetWidth() {
	return ( ( VwScalerWidget* )GetWidget( ) )->GetModel( )->Width( );
}
float VwScalerWidgetControl::GetHeight() {
	return 0;
}