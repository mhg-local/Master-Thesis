
#include"../VglConfig.h"

#include"VpmBaseButtonElement.h"
#include<VistaWidgets\SignalSystem\Signals\VwEmptySignal.h>
class VwWidgetControl;

class VGLWAPI VpmSoildButtonElement :public VpmBaseButtonElement
{

public:

    VistaSystem*		m_pVistaSystem;
	int AddNewButton(VistaColor enableColor, VistaColor focusColor, VistaColor selectColor);

	virtual void ButtonUp( VwWidget*child ) override;
	virtual void ButtonDown( VwWidget* child ) override;
	
	bool IsChildOfThisElement(VwWidget*element, VwWidget*child );
	VwEmptySignal& GetButtonClickedSignal( int index );
protected:
    void OnElementDown( const VwEmptySignalArgs& oArgs ) override;
	virtual VwWidgetControl* CreateChildWidget() override;
};