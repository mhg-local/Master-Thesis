


#include"VpmCheckBoxElement.h"
#include"../Widget/VwCheckBoxWidget.h"
#include "VistaOglExt/VistaOGLUtils.h"

#include"../Widget/VwBorderWidget.h"
#include"../Widget/VwCheckBoxWidgetControl.h"

#include"../VpmGlobalConfiguration.h"
VpmCheckBoxElement::VpmCheckBoxElement()
{
	m_pCheckBox = nullptr;
}

VpmCheckBoxElement::~VpmCheckBoxElement()
{
	delete m_pCheckBox;
}

void VpmCheckBoxElement::Init()
{
	VpmElement::Init();

	m_pCheckBox = new VwCheckBoxWidget();
	m_pCheckBox->Init();


	m_pCheckBox->GetModel()->Value.Set(GetModel()->Value());
	m_pCheckBox->GetModel()->Value.GetSignal().AddSlot(this, &VpmCheckBoxElement::OnValueChanged);

	m_pCheckBox->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmCheckBoxElement::OnElementDown );
	//m_pCheckBox->GetButtonClickedSignal().AddSlot(this, &VpmCheckBoxElement::OnElementDown);
	m_pCheckBox->GetModel()->Border.Set(VpmGlobalConfiguration::BorderSize);
	AddSecondElement(m_pCheckBox );

}

void VpmCheckBoxElement::LayoutSecondElement(VistaQuaternion q, VistaVector3D pos)
{

	//correct it
	float width = GetModel()->SecondElementSpace();
	width = width <= 0 ? 0.001f : width;
	float height = (GetModel()->Height() - (VpmGlobalConfiguration::Top_Y_Padding + VpmGlobalConfiguration::Bottom_Y_Padding));

	VistaVector3D newPos(0, 0, 0);
	newPos = q.Rotate(newPos);
	newPos += pos;
	m_pCheckBox->GetModel()->Position.Set(newPos);
	m_pCheckBox->GetModel()->Orientation.Set(q);
	m_pCheckBox->GetModel()->Width.Set(width);
	m_pCheckBox->GetModel()->Height.Set(height);
}
void VpmCheckBoxElement::OnValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	m_pCheckBox->GetModel()->Value.Set(oArgs.GetNewValue());
	VpmElement::OnValueChanged(oArgs);
}
void VpmCheckBoxElement::OnCheckBoxValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	GetModel()->Value.Set(oArgs.GetNewValue());
}

void VpmCheckBoxElement::OnElementDown(const VwEmptySignalArgs& oArgs)
{
	m_pCheckBox->GetModel()->Value.Set(!m_pCheckBox->GetModel()->Value());
	VpmElement::OnElementDown(oArgs);
}
void VpmCheckBoxElement::OnEnabledChanged(const VwBoolChangedSignalArgs& oArgs)
{
	m_pCheckBox->SetEnabled(oArgs.GetNewValue());
	
	VpmElement::OnEnabledChanged(oArgs);
}
void VpmCheckBoxElement::OnVisibilityChanged(const VwEmptySignalArgs& oArgs)
{
	
	if (GetVisible())
	{
		m_pCheckBox->SetVisible(true);
		m_pCheckBox->SetEnabled(GetModel()->Enabled());
	}
	else
	{
		m_pCheckBox->SetVisible(false);
	}
	VpmElement::OnVisibilityChanged(oArgs);
}