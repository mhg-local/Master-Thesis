#pragma once
#include"../VglConfig.h"
#include"VpmElement.h"

class VwSliderWidget;
class VwBorderWidget;
class VGLWAPI VpmSliderElement :public VpmElement
{

public:
	VpmSliderElement();
	~VpmSliderElement();

	void Init();

	void SetLength(float length);
	float GetLength();

protected:
	void LayoutSecondElement(VistaQuaternion q, VistaVector3D pos) override;
	virtual bool GetLablelVisibility( ) override { return false; };

	virtual void OnValueChangedByDragging(const VwDraggableSignalArgs& oArgs);

private:

	VwSliderWidget* m_pSlider;
	VwBorderWidget*     m_pSliderBorder;

};