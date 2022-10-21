#pragma once


#include"../VglConfig.h"
#include"VpmElement.h"

class VwCircleWidget;
class VwSphereWidget;
class VwSolidSphereView;
class VGLWAPI VpmRadioButtonElement :public VpmElement
{
public:
	VpmRadioButtonElement();
	virtual ~VpmRadioButtonElement();
	void Init();


	VwSolidSphereView* GetRadioButtonView();
protected:

	void LayoutSecondElement(VistaQuaternion q, VistaVector3D pos) override;
	void OnRadioValueChanged(const VwIntChangedSignalArgs& oArgs);
	void OnValueChanged(const VwIntChangedSignalArgs& oArgs) override;
	void OnElementDown(const VwEmptySignalArgs& oArgs) override;
	void OnEnabledChanged(const VwBoolChangedSignalArgs& oArgs) override;
	void OnVisibilityChanged(const VwEmptySignalArgs& oArgs) override;

private:

	float GetRadius(float width, float height);
	VwCircleWidget* m_RadioButton;
	//VwSphereWidget* m_RadioButton;
};

