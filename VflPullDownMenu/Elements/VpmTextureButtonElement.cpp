

#include"VpmTextureButtonElement.h"
#include"../Widget/VwTexturePlaneWidgetControl.h"
#include"../Widget/VwTexturePlaneWidget.h"
#include<VistaOpenGLWidgets\Widgets\Views\VglwTexturedPlaneView.h>

VwWidgetControl* VpmTextureButtonElement::CreateChildWidget()
{
	VwTexturePlaneWidget* plane = new VwTexturePlaneWidget();
	plane->Init();

	return new VwTexturePlaneWidgetControl(plane);
}

int VpmTextureButtonElement::AddNewButton(VistaTexture* enableTexture, VistaTexture*focusTexture, VistaTexture* selectTexture)
{

	VwWidgetControl* newElement = AddChildButton();
	if ( newElement != NULL )
	{
		VglwTexturedPlaneView* background = dynamic_cast< VglwTexturedPlaneView* >( newElement->GetWidget()->GetView() );

		background->SetBackgroundFocusTexture( focusTexture );
		background->SetBackgroundPressedTexture( selectTexture );
		background->SetBackgroundTexture( enableTexture );

		LayoutElement();
		return GetNumberOfButton();
	}
	return -1;
}