#pragma once
#include"../VglConfig.h"
#include"VpmElement.h"

//class VglwIntervalSelectionWidget;
class VwScalerWidget;
class VwBorderWidget;
//class VglwIntervalSelectionView;
class  VwScalerWidgetView;
class VglwMultiLineTextView;
class VglwTexturedPlaneView;
class VGLWAPI VpmScalerElement:public VpmElement {

public:
	VpmScalerElement();
	~VpmScalerElement();

	void Init();



	void SetMaxValue( float maxValue );
	void SetMinValue( float minValue );

	void SetUnit( std::string unit );
	void SetPrecision( int precision );
	void SetFont( VtrFont* font );

	void GetSelectedInterval( float& fLowerValue, float& fUpperValue );

	virtual VwScalerWidgetView* GetSliderView( ) const;
	VglwTexturedPlaneView* GetLeftHandelView();
	VglwTexturedPlaneView* GetRightHandelView();
	VglwTexturedPlaneView* GetCenterHandelView();

	/*VglwDynamicTextView*  GetMinTextLabelView( );
	VglwDynamicTextView * GetMaxTextLabelView( );*/


	VwEmptySignal& GetIntervalValueChangedSignal();
protected:
	virtual bool GetLablelVisibility() override { return false; };
	void LayoutSecondElement( VistaQuaternion q, VistaVector3D pos ) override;
	virtual void OnElementDown( const VwEmptySignalArgs& oArgs ) override;
	virtual void OnScalerValueChanged( const VwFloatChangedSignalArgs& oArgs );
	void OnVisibilityChanged( const VwEmptySignalArgs& oArgs ) override;
	void OnEnabledChanged( const VwBoolChangedSignalArgs& oArgs ) override;


private:
	VwEmptySignal m_sgScalerValueChanged;
//	VglwIntervalSelectionWidget* m_pScaler;
	VwScalerWidget* m_pScaler;
	VwBorderWidget*     m_pScalerBorder;

	};