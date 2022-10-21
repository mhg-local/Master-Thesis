#include "VwCheckBoxWidget.h"

#include <VistaWidgets/VwFocusHandle.h>
#include <VistaWidgets/VwInputSlot.h>
#include <VistaWidgets/VwVirtualDevice.h>
#include <VistaWidgets/FocusHandleAspects/VwCenterFocusHandleAspect.h>
#include <VistaWidgets/FocusHandleAspects/VwPlaneFocusHandleAspect.h>

#include <VistaWidgets/Widgets/Traits/VwDraggable.h>
#include <VistaWidgets/Widgets/Traits/VwFocusable.h>
#include <VistaWidgets/Widgets/Traits/VwClickable.h>

#include <cstddef>
VwCheckBoxWidget::VwCheckBoxWidget()
: m_pFocusHandle(new VwFocusHandle())
, m_pPlaneFocusHandleAspect(NULL)
, m_pPositionFocusHandleAspect(NULL)
{
}

VwCheckBoxWidget::~VwCheckBoxWidget(void)
{
	RemoveFocusHandle(m_pFocusHandle);
	delete m_pFocusHandle;
	delete m_pPositionFocusHandleAspect;
	delete m_pPlaneFocusHandleAspect;

}

void VwCheckBoxWidget::Init()
{
	VwWidget::Init();
	GetModel()->Orientation.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnOrientationChanged);
	GetModel()->Position.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnPositionChanged);

	GetModel()->Width.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnWidthChanged);
	GetModel()->Height.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnHeightChanged);
	GetModel()->Border.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnBorderChanged);
	GetModel()->Value.GetSignal().AddSlot(this, &VwCheckBoxWidget::OnValueChanged);
	GetView()->SetChecked( false );
	m_pPositionFocusHandleAspect = new VwFieldCenterFocusHandleAspect(&GetModel()->Position);
	m_pPlaneFocusHandleAspect = new VwFieldPlaneFocusHandleAspect(
		&GetModel()->Orientation, &GetModel()->Width, &GetModel()->Height);

	m_pFocusHandle->AddAspect(m_pPositionFocusHandleAspect);
	m_pFocusHandle->AddAspect(m_pPlaneFocusHandleAspect);

	m_pFocusHandle->SetFocusType(VwFocusHandle::FOCUSTYPE_PRIMARY_FOCUS);

	AddFocusHandle(m_pFocusHandle);


	GetFocusGainedSignal().AddSlot(this, &VwCheckBoxWidget::OnFocusGained);
	GetFocusLostSignal().AddSlot(this, &VwCheckBoxWidget::OnFocusLost);

	GetClickable()->GetButtonDownSignal().AddSlot(this, &VwCheckBoxWidget::OnButtonDown);
	GetClickable()->GetButtonUpSignal().AddSlot(this, &VwCheckBoxWidget::OnButtonUp);
}

VwCheckBoxWidget::Model* VwCheckBoxWidget::GetModel() const
{
	return static_cast<VwCheckBoxWidget::Model*>(VwWidget::GetModel());
}
VwCheckBoxWidgetView* VwCheckBoxWidget::GetView() const
{
	return static_cast<VwCheckBoxWidgetView*>(VwWidget::GetView());
}
VwCheckBoxWidget::Model* VwCheckBoxWidget::CreateModel() const
{
	return new Model();
}

VwCheckBoxWidgetView* VwCheckBoxWidget::CreateView() const
{
	return new VwCheckBoxWidgetView(GetModel()->Width(),GetModel()->Height(), GetModel()->Border());
}

void VwCheckBoxWidget::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
}

void VwCheckBoxWidget::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
}

void VwCheckBoxWidget::OnBorderChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetBorder(oArgs.GetNewValue());
}
void VwCheckBoxWidget::OnWidthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetWidth(oArgs.GetNewValue());
}
void VwCheckBoxWidget::OnHeightChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetHeight(oArgs.GetNewValue());
}
void VwCheckBoxWidget::OnValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	GetView()->SetChecked(oArgs.GetNewValue() != 0);
}

void VwCheckBoxWidget::OnFocusGained(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled())
		GetView()->SetState(VwCheckBoxWidgetView::VIEW_STATE_FOCUSED);
}

void VwCheckBoxWidget::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled() && VwClickable::BUTTONSTATE_UP == GetClickable()->GetButtonState())
		GetView()->SetState(VwCheckBoxWidgetView::VIEW_STATE_ENABLED);
}

void VwCheckBoxWidget::OnButtonDown(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled() && GetFocusable()->GetIsFocused())
		GetView()->SetState(VwCheckBoxWidgetView::VIEW_STATE_PRESSED);
}
void VwCheckBoxWidget::OnButtonUp(const VwEmptySignalArgs& oArgs)
{
	if (GetEnabled())
	{
		if (GetFocusable()->GetIsFocused())
		{
			GetView()->SetState(VwCheckBoxWidgetView::VIEW_STATE_FOCUSED);
		}
		else
			GetView()->SetState(VwCheckBoxWidgetView::VIEW_STATE_ENABLED);

	}
}
/*============================================================================*/
/* MODEL CLASS IMPLEMENTATION				                                  */
/*============================================================================*/

VwCheckBoxWidget::Model::Model()
: Position(Vista::ZeroVector)
, Orientation(Vista::UnitQuaternion)
, Border(.02f)
, Width(0.1f)
, Height(0.1f)
, Value(0)
{}

VwCheckBoxWidget::Model::~Model()
{}

