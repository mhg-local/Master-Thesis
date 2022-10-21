#include "VpmPullDownMenuView.h"
#include <VistaWidgets/Widgets/Views/VwColoredPlaneView.h>


VpmPullDownMenuView::VpmPullDownMenuView()
{
	m_pBackgroundView = nullptr;
}


VpmPullDownMenuView::~VpmPullDownMenuView()
{
}


VwColoredPlaneView* VpmPullDownMenuView::GetBackgroundView() const
{
	return m_pBackgroundView;
}

void VpmPullDownMenuView::SetBackgroundView(VwColoredPlaneView* pBackgroundView)
{
	assert(pBackgroundView != nullptr);
	m_pBackgroundView = pBackgroundView;
}


float VpmPullDownMenuView::GetLength() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetLength();
}

void VpmPullDownMenuView::SetLength(float value)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetLength(value);
}

float VpmPullDownMenuView::GetWidth() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetWidth();
}

void VpmPullDownMenuView::SetWidth(float value)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetWidth(value);
}

VistaVector3D VpmPullDownMenuView::GetPosition() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetPosition();
}

void VpmPullDownMenuView::SetPosition(const VistaVector3D& value)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetPosition(value);
}

VistaQuaternion VpmPullDownMenuView::GetOrientation() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetOrientation();
}

void VpmPullDownMenuView::SetOrientation(const VistaQuaternion& value)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetOrientation(value);
}

int VpmPullDownMenuView::GetState() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetState();
}
bool VpmPullDownMenuView::GetVisible() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetVisible();
}

void VpmPullDownMenuView::SetVisible(bool value)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetVisible(value);
}

VistaBoundingBox VpmPullDownMenuView::GetBoundingBox() const
{
	assert(m_pBackgroundView != nullptr);
	return m_pBackgroundView->GetBoundingBox();
}
void VpmPullDownMenuView::SetState(int eState)
{
	assert(m_pBackgroundView != nullptr);
	m_pBackgroundView->SetState(eState);
}

