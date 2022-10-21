#pragma once

#include"../VglConfig.h"


#include <VistaWidgets/VwField.h>
#include <VistaWidgets/VwWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/SignalSystem/Signals/VwConstraintSignals.h>
#include <VistaWidgets/Widgets/Traits/VwClickable.h>
#include <VistaWidgets/Widgets/Traits/VwDraggable.h>

class VwWidgetControl
{
public:
	VwWidgetControl(VwWidget* widget);

	virtual void SetPosition(VistaVector3D& pos) = 0;
	virtual VistaVector3D GetPosition() const = 0;
	virtual void SetOrientation(VistaQuaternion& qOrientation) = 0;
	virtual VistaQuaternion GetOrientation() const = 0;

	virtual void SetWidth(float width) = 0;
	virtual void SetHeight(float height) = 0;

	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

	virtual VwWidget* GetWidget() const;
	VwClickable* GetClickable;
	VwDraggable* GetDraggable;
	VwFocusable* Getfocusable;
private:
	VwWidget* m_pWidget;

};

