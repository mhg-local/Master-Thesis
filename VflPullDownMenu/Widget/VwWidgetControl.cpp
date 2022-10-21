

#include"VwWidgetControl.h"


VwWidgetControl::VwWidgetControl(VwWidget* pWidget)
{
	m_pWidget = pWidget;
}


VwWidget* VwWidgetControl::GetWidget() const
{
	return m_pWidget;
}