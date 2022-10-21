

#include"VwSliderWidgetControl.h"

#include<VistaWidgets\Widgets\VwSliderWidget.h>

VwSliderWidgetControl::VwSliderWidgetControl(VwSliderWidget* slider)
:VwWidgetControl(slider)
{

}

void VwSliderWidgetControl::SetPosition(VistaVector3D& pos)
{
	((VwSliderWidget*)GetWidget())->GetModel()->Position.Set(pos);
}

VistaVector3D VwSliderWidgetControl::GetPosition()const {
	return ((VwSliderWidget*)GetWidget())->GetModel()->Position();
}
void VwSliderWidgetControl::SetOrientation(VistaQuaternion& qOrientation) {
	((VwSliderWidget*)GetWidget())->GetModel()->Orientation.Set(qOrientation);
}
VistaQuaternion VwSliderWidgetControl::GetOrientation() const {
	return ((VwSliderWidget*)GetWidget())->GetModel()->Orientation();
}

void VwSliderWidgetControl::SetWidth(float width) {
	((VwSliderWidget*)GetWidget())->GetModel()->Width.Set(width);
}
void VwSliderWidgetControl::SetHeight(float height) {
}

float VwSliderWidgetControl::GetWidth() {
	return ((VwSliderWidget*)GetWidget())->GetModel()->Width();
}
float VwSliderWidgetControl::GetHeight() {
	return 0;
}