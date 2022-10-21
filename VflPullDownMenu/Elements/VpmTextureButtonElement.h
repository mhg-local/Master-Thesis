
#include"../VglConfig.h"

#include"VpmBaseButtonElement.h"

class VwWidgetControl;
class VistaTexture;
class VGLWAPI VpmTextureButtonElement :public VpmBaseButtonElement
{

public:
	int AddNewButton(VistaTexture* enableTexture, VistaTexture*focusTexture, VistaTexture* selectTexture);
protected:
	virtual VwWidgetControl* CreateChildWidget() override;

};