

#include"VwTexturePlaneWidgetControl.h"

#include"VwTexturePlaneWidget.h"

VwTexturePlaneWidgetControl::VwTexturePlaneWidgetControl(VwTexturePlaneWidget* plane)
:VwWidgetControl(plane)
{

}

void VwTexturePlaneWidgetControl::SetPosition(VistaVector3D& pos)
{
	((VwTexturePlaneWidget*)GetWidget())->GetModel()->Position.Set(pos);
}

VistaVector3D VwTexturePlaneWidgetControl::GetPosition()const {
	return ((VwTexturePlaneWidget*)GetWidget())->GetModel()->Position();
}
void VwTexturePlaneWidgetControl::SetOrientation(VistaQuaternion& qOrientation) {
	((VwTexturePlaneWidget*)GetWidget())->GetModel()->Orientation.Set(qOrientation);
}
VistaQuaternion VwTexturePlaneWidgetControl::GetOrientation() const {
	return ((VwTexturePlaneWidget*)GetWidget())->GetModel()->Orientation();
}

void VwTexturePlaneWidgetControl::SetWidth(float width) {
	((VwTexturePlaneWidget*)GetWidget())->GetModel()->Width.Set(width);
}
void VwTexturePlaneWidgetControl::SetHeight(float height) {
	((VwTexturePlaneWidget*)GetWidget())->GetModel()->Height.Set(height);
}

float VwTexturePlaneWidgetControl::GetWidth() {
	return ((VwTexturePlaneWidget*)GetWidget())->GetModel()->Width();
}
float VwTexturePlaneWidgetControl::GetHeight() {
	return ((VwTexturePlaneWidget*)GetWidget())->GetModel()->Height();
}