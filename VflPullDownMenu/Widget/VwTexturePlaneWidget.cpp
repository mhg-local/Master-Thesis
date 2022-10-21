#include "VwTexturePlaneWidget.h"

#include <VistaWidgets\VwFocusHandle.h>
#include <VistaWidgets\VwInputSlot.h>
#include <VistaWidgets\VwVirtualDevice.h>
#include <VistaWidgets\FocusHandleAspects\VwCenterFocusHandleAspect.h>
#include <VistaWidgets\FocusHandleAspects\VwPlaneFocusHandleAspect.h>

#include <VistaWidgets\Widgets\Traits\VwFocusable.h>
#include <VistaWidgets\Widgets\Traits\VwClickable.h>
#include <VistaWidgets\Widgets\Traits\VwDraggable.h>

#include <cstddef>


VwTexturePlaneWidget::VwTexturePlaneWidget()
: m_pFocusHandle(new VwFocusHandle())
, m_pPlaneFocusHandleAspect(nullptr)
, m_pPositionFocusHandleAspect(nullptr)
{

}

VwTexturePlaneWidget::~VwTexturePlaneWidget(void)
{
	RemoveFocusHandle(m_pFocusHandle);
	delete m_pPlaneFocusHandleAspect;
	delete m_pPositionFocusHandleAspect;
	delete m_pFocusHandle;
}

void VwTexturePlaneWidget::Init()
{
	VwWidget::Init();
	GetModel()->Orientation.GetSignal().AddSlot(this, &VwTexturePlaneWidget::OnOrientationChanged);
	GetModel()->Position.GetSignal().AddSlot(this, &VwTexturePlaneWidget::OnPositionChanged);
	GetModel()->Width.GetSignal().AddSlot(this, &VwTexturePlaneWidget::OnWidthChanged);
	GetModel()->Height.GetSignal().AddSlot(this, &VwTexturePlaneWidget::OnHeightChanged);

	m_pPositionFocusHandleAspect = new VwFieldCenterFocusHandleAspect(&GetModel()->Position);
	m_pPlaneFocusHandleAspect = new VwFieldPlaneFocusHandleAspect(
		&GetModel()->Orientation, &GetModel()->Width, &GetModel()->Height);

	m_pFocusHandle->AddAspect(m_pPositionFocusHandleAspect);
	m_pFocusHandle->AddAspect(m_pPlaneFocusHandleAspect);

	m_pFocusHandle->SetFocusType(VwFocusHandle::FOCUSTYPE_PRIMARY_FOCUS);

	AddFocusHandle(m_pFocusHandle);

	GetFocusGainedSignal().AddSlot(this, &VwTexturePlaneWidget::OnFocusGained);
	GetFocusLostSignal().AddSlot(this, &VwTexturePlaneWidget::OnFocusLost);

	GetClickable()->GetButtonDownSignal().AddSlot(this, &VwTexturePlaneWidget::OnButtonDown);
	GetClickable()->GetButtonUpSignal().AddSlot(this, &VwTexturePlaneWidget::OnButtonUp);

	//check later

	/*GetDraggable()->GetDraggingStartedSignal().AddSlot(this, &VwTexturePlaneWidget::OnDragging);
	GetDraggable()->GetDraggingSignal().AddSlot(this, &VwTexturePlaneWidget::OnDragging);
	GetDraggable()->GetDraggingStoppedSignal().AddSlot(this, &VwTexturePlaneWidget::OnDragging);*/
}

VwTexturePlaneWidget::Model* VwTexturePlaneWidget::GetModel() const
{
	return static_cast<VwTexturePlaneWidget::Model*>(VwWidget::GetModel());
}

VwTexturePlaneWidget::View* VwTexturePlaneWidget::GetView() const
{
	return static_cast<VwTexturePlaneWidget::View*>(VwWidget::GetView());
}

VwTexturePlaneWidget::Model* VwTexturePlaneWidget::CreateModel() const
{
	return new Model();
}

VwTexturePlaneWidget::View* VwTexturePlaneWidget::CreateView() const
{
	return new View(GetModel()->Width(), GetModel()->Height());
}

void VwTexturePlaneWidget::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
}

void VwTexturePlaneWidget::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
	if (!GetIsDragging())
	{
		GetDraggable( )->Position.Set( oArgs.GetNewValue( ) );
		//GetDraggable()->SetPosition(oArgs.GetNewValue());
	}
}

void VwTexturePlaneWidget::OnWidthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetWidth(oArgs.GetNewValue());
}

void VwTexturePlaneWidget::OnHeightChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetLength(oArgs.GetNewValue());
}

void VwTexturePlaneWidget::OnFocusGained(const VwEmptySignalArgs& oArgs)
{
	SetViewState(VwPlaneViewBase::VIEW_STATE_FOCUSED);
}

void VwTexturePlaneWidget::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	SetViewState(VwPlaneViewBase::VIEW_STATE_ENABLED);
}

void VwTexturePlaneWidget::OnButtonDown(const VwEmptySignalArgs& oArgs)
{
	SetViewState(VwPlaneViewBase::VIEW_STATE_PRESSED);
}

void VwTexturePlaneWidget::OnButtonUp(const VwEmptySignalArgs& oArgs)
{
	if (!GetEnabled())
	{
		return;
	}

	if (GetFocused())
	{
		SetViewState(VwPlaneViewBase::VIEW_STATE_FOCUSED);
	}
	else
	{
		SetViewState(VwPlaneViewBase::VIEW_STATE_ENABLED);
	}
}

void VwTexturePlaneWidget::OnDragging(const VwDraggableSignalArgs& oArgs)
{
	GetModel()->Position.Set(oArgs.GetNewPosition());
}

void VwTexturePlaneWidget::SetViewState(int eViewState)
{
	if (GetEnabled())
	{
		GetView()->SetState(eViewState);
	}
	else
	{
		GetView()->SetState(VwPlaneViewBase::VIEW_STATE_DISABLED);
	}
}

void VwTexturePlaneWidget::Disable()
{
	VwWidget::SetEnabled(false);
	SetViewState(VwPlaneViewBase::VIEW_STATE_DISABLED);
}

void VwTexturePlaneWidget::Enable()
{
	VwWidget::SetEnabled(true);
	SetViewState(VwPlaneViewBase::VIEW_STATE_ENABLED);
}

/*============================================================================*/
/* MODEL CLASS IMPLEMENTATION				                                  */
/*============================================================================*/
VwTexturePlaneWidget::Model::Model()
: Position(Vista::ZeroVector)
, Width(1.0f)
, Height(1.0f)
{}

VwTexturePlaneWidget::Model::~Model()
{}
