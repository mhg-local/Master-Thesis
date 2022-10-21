

#pragma once


#include"../VglConfig.h"
#include"VwWidgetControl.h"

class VglwCheckboxWidget;

class VGLWAPI VwCheckBoxWidgetControl :public VwWidgetControl
{
public:
	VwCheckBoxWidgetControl(VglwCheckboxWidget* checkbox);
	virtual void SetPosition(VistaVector3D& pos) override;
	virtual VistaVector3D GetPosition() const override;
	virtual void SetOrientation(VistaQuaternion& qOrientation) override;
	virtual VistaQuaternion GetOrientation() const override;

	virtual void SetWidth(float width) override;
	virtual void SetHeight(float height) override;

	virtual float GetWidth() override;
	virtual float GetHeight() override;

	

};