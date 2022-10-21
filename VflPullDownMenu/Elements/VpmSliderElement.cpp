#include"VpmSliderElement.h"

#include"../Widget/VwBorderWidget.h"

#include<VistaWidgets\Widgets\VwSliderWidget.h>
#include"../Widget/VwSliderWidgetControl.h"
VpmSliderElement::VpmSliderElement()
{
	m_pSlider = NULL;
}

VpmSliderElement::~VpmSliderElement()
{
	delete m_pSlider;
}
void VpmSliderElement::Init()
{
	VpmElement::Init();

	SetLabelVisibility(false);

	m_pSlider = new VwSliderWidget();
	m_pSlider->Init();


	/*m_pSliderBorder = new VwBorderWidget();
	m_pSliderBorder->Init(new VwSliderWidgetControl(m_pSlider));
	m_pSliderBorder->GetModel()->BorderSize.Set(0.001f);*/

	//check it later

	//m_pSlider->GetDraggingStoppedSignal().AddSlot(this, &VpmSliderElement::OnValueChangedByDragging);

	//m_pSlider->GetModel()->
	AddSecondElement(m_pSlider);
}

void VpmSliderElement::LayoutSecondElement(VistaQuaternion q, VistaVector3D pos)
{
	m_pSlider->GetModel()->Position.Set(GetModel()->Position());
	m_pSlider->GetModel( )->Orientation.Set( q );
	/*m_pSlider->GetModel()->Length.Set( GetModel()->Height() );
	m_pSlider->GetModel( )->Width.Set( GetModel( )->Width( ) );*/
	
}
void VpmSliderElement::OnValueChangedByDragging(const VwDraggableSignalArgs& oArgs)
{
	//Correct It!!!
//	GetModel()->Value.Set((int)m_pSlider->GetValue());
}
void VpmSliderElement::SetLength(float length)
{
	m_pSlider->GetModel()->Length.Set(length);
}
float VpmSliderElement::GetLength()
{
	return m_pSlider->GetModel()->Length();
}