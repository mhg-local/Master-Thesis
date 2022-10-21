

#include"VwPlaneWidgetControl.h"

#include<VistaWidgets\Widgets\VwPlaneWidget.h>

VwPlaneWidgetControl::VwPlaneWidgetControl(VwPlaneWidget* plane)
:VwWidgetControl(plane)
{

}

void VwPlaneWidgetControl::SetPosition(VistaVector3D& pos)
{
	((VwPlaneWidget*)GetWidget())->GetModel()->Position.Set(pos);
}

VistaVector3D VwPlaneWidgetControl::GetPosition()const {
	return ((VwPlaneWidget*)GetWidget())->GetModel()->Position();
}
void VwPlaneWidgetControl::SetOrientation(VistaQuaternion& qOrientation) {
	((VwPlaneWidget*)GetWidget())->GetModel()->Orientation.Set(qOrientation);
}
VistaQuaternion VwPlaneWidgetControl::GetOrientation() const {
	return ((VwPlaneWidget*)GetWidget())->GetModel()->Orientation();
}

void VwPlaneWidgetControl::SetWidth(float width) {
	((VwPlaneWidget*)GetWidget())->GetModel()->Width.Set(width);
}
void VwPlaneWidgetControl::SetHeight(float height) {
	((VwPlaneWidget*)GetWidget())->GetModel()->Height.Set(height);
}

float VwPlaneWidgetControl::GetWidth() {
	return ((VwPlaneWidget*)GetWidget())->GetModel()->Width();
}
float VwPlaneWidgetControl::GetHeight() {
	return ((VwPlaneWidget*)GetWidget())->GetModel()->Height();
}