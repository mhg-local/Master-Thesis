

#include"VwCheckBoxWidgetControl.h"

#include<VistaOpenGLWidgets\Widgets\VglwCheckboxWidget.h>

VwCheckBoxWidgetControl::VwCheckBoxWidgetControl(VglwCheckboxWidget* checkbox)
:VwWidgetControl(checkbox)
{

}

void VwCheckBoxWidgetControl::SetPosition(VistaVector3D& pos)
{
	((VglwCheckboxWidget*)GetWidget())->GetModel()->Position.Set(pos);
}

VistaVector3D VwCheckBoxWidgetControl::GetPosition()const {
	return ((VglwCheckboxWidget*)GetWidget())->GetModel()->Position();
}
void VwCheckBoxWidgetControl::SetOrientation(VistaQuaternion& qOrientation) {
	((VglwCheckboxWidget*)GetWidget())->GetModel()->Orientation.Set(qOrientation);
}
VistaQuaternion VwCheckBoxWidgetControl::GetOrientation() const {
	return ((VglwCheckboxWidget*)GetWidget())->GetModel()->Orientation();
}

void VwCheckBoxWidgetControl::SetWidth(float width) {
	((VglwCheckboxWidget*)GetWidget())->GetModel()->Width.Set(width);
}
void VwCheckBoxWidgetControl::SetHeight(float height) {
	((VglwCheckboxWidget*)GetWidget())->GetModel()->Height.Set(height);
}

float VwCheckBoxWidgetControl::GetWidth() {
	return ((VglwCheckboxWidget*)GetWidget())->GetModel()->Width();
}
float VwCheckBoxWidgetControl:: GetHeight() {
	return ((VglwCheckboxWidget*)GetWidget())->GetModel()->Height();
}