#include "VwCircleWidget.h"

#include <VistaWidgets/VwFocusHandle.h>
#include <VistaWidgets/VwInputSlot.h>
#include <VistaWidgets/VwVirtualDevice.h>
#include <VistaWidgets/FocusHandleAspects/VwCenterFocusHandleAspect.h>
#include <VistaWidgets/FocusHandleAspects/VwBoxFocusHandleAspect.h>
#include <VistaWidgets/FocusHandleAspects/VwRadiusFocusHandleAspect.h>

#include <VistaWidgets/Widgets/Traits/VwDraggable.h>
#include <VistaWidgets/Widgets/Traits/VwFocusable.h>
#include <VistaWidgets/Widgets/Traits/VwClickable.h>

#include <cstddef>
VwCircleWidget::VwCircleWidget()
: m_pFocusHandle(new VwFocusHandle())
, m_pRadiusFocusHandleAspect(NULL)
, m_pPositionFocusHandleAspect(NULL)
{
}

VwCircleWidget::~VwCircleWidget(void)
{
	RemoveFocusHandle(m_pFocusHandle);
	delete m_pFocusHandle;
	delete m_pPositionFocusHandleAspect;
	delete m_pRadiusFocusHandleAspect;

}

void VwCircleWidget::Init()
{
	VwWidget::Init();
	GetModel()->Orientation.GetSignal().AddSlot(this, &VwCircleWidget::OnOrientationChanged);
	GetModel()->Position.GetSignal().AddSlot(this, &VwCircleWidget::OnPositionChanged);

	GetModel()->Radius.GetSignal().AddSlot(this, &VwCircleWidget::OnRadiusChanged);
	GetModel()->Border.GetSignal().AddSlot(this, &VwCircleWidget::OnBorderChanged);
	GetModel()->Value.GetSignal().AddSlot(this, &VwCircleWidget::OnValueChanged);
	GetView()->SetChecked( false );
	m_pPositionFocusHandleAspect = new VwFieldCenterFocusHandleAspect(
		&GetModel()->Position
		);

	m_pRadiusFocusHandleAspect = new VwFieldRadiusFocusHandleAspect(
		&GetModel()->Radius
		);


	m_pFocusHandle->AddAspect(m_pPositionFocusHandleAspect);
	m_pFocusHandle->AddAspect(m_pRadiusFocusHandleAspect);

	m_pFocusHandle->SetFocusType(VwFocusHandle::FOCUSTYPE_PRIMARY_FOCUS);

	AddFocusHandle(m_pFocusHandle);


	GetFocusGainedSignal().AddSlot(this, &VwCircleWidget::OnFocusGained);
	GetFocusLostSignal().AddSlot(this, &VwCircleWidget::OnFocusLost);

	GetClickable()->GetButtonDownSignal().AddSlot(this, &VwCircleWidget::OnButtonDown);
	GetClickable()->GetButtonUpSignal().AddSlot(this, &VwCircleWidget::OnButtonUp);
}

VwCircleWidget::Model* VwCircleWidget::GetModel() const
{
	return static_cast<VwCircleWidget::Model*>(VwWidget::GetModel());
}
VwCircleWidgetView* VwCircleWidget::GetView() const
{
	return static_cast<VwCircleWidgetView*>(VwWidget::GetView());
}
VwCircleWidget::Model* VwCircleWidget::CreateModel() const
{
	return new Model();
}

VwCircleWidgetView* VwCircleWidget::CreateView() const
{
	return new VwCircleWidgetView(GetModel()->Radius(), GetModel()->Border());
}

void VwCircleWidget::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
}

void VwCircleWidget::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
}

void VwCircleWidget::OnBorderChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetBorder(oArgs.GetNewValue());
}
void VwCircleWidget::OnRadiusChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetRadius(oArgs.GetNewValue());
}
void VwCircleWidget::OnValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	GetView()->SetChecked(oArgs.GetNewValue() != 0);
}

void VwCircleWidget::OnFocusGained(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled())
		GetView()->SetState(VwCircleWidgetView::VIEW_STATE_FOCUSED);
}

void VwCircleWidget::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled() && VwClickable::BUTTONSTATE_UP == GetClickable()->GetButtonState())
		GetView()->SetState(VwCircleWidgetView::VIEW_STATE_ENABLED);
}

void VwCircleWidget::OnButtonDown(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled() && GetFocusable()->GetIsFocused())
		GetView()->SetState(VwCircleWidgetView::VIEW_STATE_PRESSED);
}
void VwCircleWidget::OnButtonUp(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled())
	{
		if (GetFocusable()->GetIsFocused())
		{
			GetView()->SetState(VwCircleWidgetView::VIEW_STATE_FOCUSED);
		}
		else
			GetView()->SetState(VwCircleWidgetView::VIEW_STATE_ENABLED);

	}
}
/*============================================================================*/
/* MODEL CLASS IMPLEMENTATION				                                  */
/*============================================================================*/

VwCircleWidget::Model::Model()
: Position(Vista::ZeroVector)
, Orientation(Vista::UnitQuaternion)
, Border(.02f)
, Radius(0.1f)
, Value(0)
{}

VwCircleWidget::Model::~Model()
{}

