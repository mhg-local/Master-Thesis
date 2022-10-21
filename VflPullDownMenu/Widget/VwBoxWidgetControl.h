

#pragma once


#include"../VglConfig.h"
#include"VwWidgetControl.h"

class VwBoxWidget;

class VGLWAPI VwBoxWidgetControl:public VwWidgetControl {
	public:
	VwBoxWidgetControl( VwBoxWidget* checkbox );
	virtual void SetPosition( VistaVector3D& pos ) override;
	virtual VistaVector3D GetPosition( ) const override;
	virtual void SetOrientation( VistaQuaternion& qOrientation ) override;
	virtual VistaQuaternion GetOrientation( ) const override;

	virtual void SetWidth( float width ) override;
	virtual void SetHeight( float height ) override;

	virtual float GetWidth( ) override;
	virtual float GetHeight( ) override;



};