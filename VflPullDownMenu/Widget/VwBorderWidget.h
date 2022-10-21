#pragma once

#include"../VglConfig.h"


#include <VistaWidgets/VwField.h>
#include <VistaWidgets/VwWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/SignalSystem/Signals/VwConstraintSignals.h>

#include"VwBorderView.h"

class VwPlaneWidget;
class VwLineWidget;
class VwWidgetControl;


class VGLWAPI VwBorderWidget :public VwWidget
{
public:
	VwBorderWidget();
	~VwBorderWidget();

	void Init(VwWidgetControl*);

	class Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model() = default;

		VwField<float>				BorderSize;
		VwField<VistaVector3D>		Position;
		VwField<VistaQuaternion>	Orientation;
		VwField<float>				Height;
		VwField<float>				Width;

	};
	VwWidget*  GetWidget() const;

	virtual Model* GetModel() const override;
	virtual VwBorderView* GetView() const override;


	/*virtual VwEmptySignal& GetFocusGainedSignal() override;
	virtual VwEmptySignal& GetFocusLostSignal() override;
	virtual VwEmptySignal& GetButtonDownSignal() override;
	virtual VwEmptySignal& GetButtonUpSignal() override;*/
	virtual VwEmptySignal& GetButtonClickedSignal();
	virtual VwEmptySignal& FocusGainedSignal( ) ;
	virtual VwEmptySignal& FocusLostSignal( ) ;
	virtual VwEmptySignal& ButtonDownSignal( ) ;
	virtual VwEmptySignal& ButtonUpSignal( ) ;


protected:

	virtual Model* CreateModel() const;
	virtual VwBorderView* CreateView() const;

	//virtual void OnElementDown( const VwEmptySignalArgs& oArgs ) ;
	virtual void OnPositionChanged(const VwVectorChangedSignalArgs&oARgs);
	virtual void OnBorderSizeChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnOrientionChanged(const VwQuaternionChangedSignalArgs& oArgs);
	virtual void OnWidthChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnHeightChanged(const VwFloatChangedSignalArgs& oArgs);

	virtual void OnVisibilityChanged(const VwEmptySignalArgs& oArgs);

private:
	void LayoutBorderWidget();


	VwPlaneWidget* m_pBackground;
	VwWidgetControl* m_pInternalWidget;
	VwLineWidget*  m_pEsetLine;
	VwLineWidget*  m_pWestLine;
	VwLineWidget*  m_pSouthLine;
	VwLineWidget*  m_pNorthLine;
};