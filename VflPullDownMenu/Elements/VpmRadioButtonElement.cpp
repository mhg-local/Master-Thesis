


#include"VpmRadioButtonElement.h"
#include"../Widget/VwCircleWidget.h"
#include "VistaOglExt/VistaOGLUtils.h"

#include"../VpmGlobalConfiguration.h"


#include<VistaWidgets\Widgets\VwSphereWidget.h>
#include<VistaWidgets\Widgets\Views\VwSolidSphereView.h>
VpmRadioButtonElement::VpmRadioButtonElement()
{
	m_RadioButton = nullptr;
}

VpmRadioButtonElement::~VpmRadioButtonElement()
{
	delete m_RadioButton;
}

void VpmRadioButtonElement::Init()
{
	VpmElement::Init();

	m_RadioButton = new VwCircleWidget();
	//m_RadioButton = new VwSphereWidget();
	m_RadioButton->Init();
	m_RadioButton->GetModel()->Border.Set(VpmGlobalConfiguration::BorderSize);
	m_RadioButton->GetModel()->Value.Set(GetModel()->Value());
	m_RadioButton->GetModel()->Value.GetSignal().AddSlot(this, &VpmRadioButtonElement::OnRadioValueChanged);

	m_RadioButton->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmRadioButtonElement::OnElementDown );
	//m_RadioButton->GetButtonClickedSignal().AddSlot(this, &VpmRadioButtonElement::OnElementDown);
	AddSecondElement(m_RadioButton);

}
float VpmRadioButtonElement::GetRadius(float width, float height)
{
	float f= width < height ? width : height;
	return (f <= 0 ? 0.000001f : f)/2.0f;
}
void VpmRadioButtonElement::LayoutSecondElement(VistaQuaternion q, VistaVector3D pos)
{
	float fRadius = GetRadius(GetModel()->SecondElementSpace() - (VpmGlobalConfiguration::Right_X_Padding), (GetModel()->Height() - (VpmGlobalConfiguration::Top_Y_Padding + VpmGlobalConfiguration::Bottom_Y_Padding)));
	VistaVector3D newPos(-VpmGlobalConfiguration::Right_X_Padding/2,0,0);
	newPos = q.Rotate(newPos);
	newPos += pos;
	m_RadioButton->GetModel()->Position.Set(pos);
	m_RadioButton->GetModel()->Orientation.Set(q);
	m_RadioButton->GetModel()->Radius.Set(fRadius);
}

VwSolidSphereView* VpmRadioButtonElement::GetRadioButtonView()
{
	return dynamic_cast< VwSolidSphereView* >( m_RadioButton->GetView() );
}
void VpmRadioButtonElement::OnRadioValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	GetModel()->Value.Set(oArgs.GetNewValue());
}
void VpmRadioButtonElement::OnValueChanged(const VwIntChangedSignalArgs& oArgs)
{
	m_RadioButton->GetModel()->Value.Set(oArgs.GetNewValue());
	VpmElement::OnValueChanged(oArgs);
}

void VpmRadioButtonElement::OnElementDown(const VwEmptySignalArgs& oArgs)
{
	m_RadioButton->GetModel()->Value.Set(1);
	VpmElement::OnElementDown(oArgs);
}
void VpmRadioButtonElement::OnEnabledChanged(const VwBoolChangedSignalArgs& oArgs)
{
	m_RadioButton->SetEnabled(oArgs.GetNewValue());
	VpmElement::OnEnabledChanged(oArgs);
}
void VpmRadioButtonElement::OnVisibilityChanged(const VwEmptySignalArgs& oArgs)
{

	if (GetVisible())
	{
		m_RadioButton->SetVisible(true);
		m_RadioButton->SetEnabled(GetModel()->Enabled());
	}
	else
	{
		m_RadioButton->SetVisible(false);
	}
	VpmElement::OnVisibilityChanged(oArgs);
}