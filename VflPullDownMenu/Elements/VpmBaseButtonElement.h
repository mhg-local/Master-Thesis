#pragma once

#include"../VglConfig.h"
#include"VpmElement.h"

class VwWidgetControl;
class VwBorderWidget;
class VGLWAPI VpmBaseButtonElement :public VpmElement
{
public:
	VpmBaseButtonElement();
	~VpmBaseButtonElement();

	void Init();
	int  RemoveButton(int indexButton);
	int  GetNumberOfButton();
	virtual void ButtonUp( VwWidget*child ) override;
	virtual void ButtonDown( VwWidget* child ) override;


	VwEmptySignal& GetButtonClickedSignal( int index );
protected:
	virtual VwWidgetControl* CreateChildWidget() = 0;
	void LayoutSecondElement(VistaQuaternion q, VistaVector3D pos) override;
	VwWidgetControl* AddChildButton();
	virtual void OnVisibilityChanged(const VwEmptySignalArgs& oArgs) override;


	virtual bool GetLablelVisibility( ) override { return false; };
	virtual void OnChildClicked( VwWidget*child ) override;
	virtual void OnElementDown(const VwEmptySignalArgs& oArgs) override;
	virtual void OnButtonClick( const VwEmptySignalArgs& oArgs );
	std::vector<VwWidgetControl*>  m_vecButtons;
	std::vector<VwBorderWidget*>  m_vecBorder;

	std::vector<VwEmptySignal*>    m_vecSignal;

};

