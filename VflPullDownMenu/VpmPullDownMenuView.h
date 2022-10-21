#pragma once

/*============================================================================*/
#include "VglConfig.h"

#include <VistaWidgets/Widgets/Views/VwPlaneViewBase.h>

#include <VistaMath/VistaBoundingBox.h>
#include <VistaBase/VistaColor.h>

class VwColoredPlaneView;

class VpmPullDownMenuView :public VwPlaneViewBase
{
public:
	enum
	{
		VIEW_STATE_LAST = VwPlaneViewBase::VIEW_STATE_LAST
	};

	VpmPullDownMenuView();
	~VpmPullDownMenuView();



	//virtual float GetLength() const override;
	//virtual void SetLength(float value) override;

	//virtual float GetWidth() const override;
	//virtual void SetWidth(float value) override;

	//virtual VistaVector3D GetPosition() const override;
	//virtual void SetPosition(const VistaVector3D& value) override;

	//virtual VistaQuaternion GetOrientation() const override;
	//virtual void SetOrientation(const VistaQuaternion& value) override;

	virtual float GetLength() const ;
	virtual void SetLength( float value ) ;

	virtual float GetWidth() const;
	virtual void SetWidth( float value ) ;

	virtual VistaVector3D GetPosition() const ;
	virtual void SetPosition( const VistaVector3D& value ) ;

	virtual VistaQuaternion GetOrientation() const;
	virtual void SetOrientation( const VistaQuaternion& value ) ;

	virtual int GetState() const override;
	virtual void SetState(int eState) override;


	virtual bool GetVisible() const override;
	virtual void SetVisible(bool value) override;

	virtual VistaBoundingBox GetBoundingBox() const override;


	virtual VwColoredPlaneView* GetBackgroundView() const;
	virtual void SetBackgroundView(VwColoredPlaneView* pBackgroundView);
private:
	VwColoredPlaneView*				m_pBackgroundView;
};

