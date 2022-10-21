#pragma once
#include"../VglConfig.h"
#include"VpmElement.h"


class VwCheckBoxWidget;
class VwBorderWidget;

class VGLWAPI VpmCheckBoxElement :public VpmElement
{
public:
	VpmCheckBoxElement();
	virtual ~VpmCheckBoxElement();
	void Init();
protected:

	void LayoutSecondElement(VistaQuaternion q, VistaVector3D pos) override;
	void OnValueChanged(const VwIntChangedSignalArgs& oArgs) override;
	void OnCheckBoxValueChanged(const VwIntChangedSignalArgs& oArgs);
	void OnElementDown(const VwEmptySignalArgs& oArgs) override;
	void OnEnabledChanged(const VwBoolChangedSignalArgs& oArgs) override;
	void OnVisibilityChanged(const VwEmptySignalArgs& oArgs) override;

private:
	VwCheckBoxWidget* m_pCheckBox;
};