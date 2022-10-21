#pragma once

#include"../VglConfig.h"

#include"VpmElementView.h"

#include <VistaWidgets/VwInputSlot.h>
#include <VistaWidgets/VwExchangeableViewWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/VwField.h>

#include <VflTextRendering/VtrString.h>
#include <VflTextRendering/VtrFont.h>
#include <VistaBase/VistaColor.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>
#include<string>
#include"VpmAnimation.h"
class VwPlaneWidget;
class VglwDynamicTextWidget;
class VwBorderWidget;
class VwTexturePlaneWidget;
class VistaTexture;
class VGLWAPI VpmElement:public VwWidget {
	public:

	VpmElement();
	~VpmElement();

	virtual void Init(  );
	virtual void UpdateAnimation();
	virtual void ProgressValue(float value);
	virtual void DeepValue( float value );

	void SetImage( VistaTexture* image );
	void SetProgressVissibilityOn();
	void SetProgressVisisbilityOff();
	void Select();
	void Deselect();


	virtual void AddSubMenu();
	virtual void RemoveSubMenu();

	virtual bool Click( const VwFocusHandle* handle );
	virtual void ButtonUp( VwWidget*child );
	virtual void ButtonDown( VwWidget* child );
	bool GetByHandle( const VwFocusHandle* handle, VwWidget**childwidget );
	class Model:public IVwWidgetModel {
		public:
		Model();
		virtual ~Model() = default;

		VwField<VistaVector3D>		Position;
		VwField<VistaQuaternion>	Orientation;
		VwField<float>				Height;
		VwField<float>				Width;

		VwField<float>              SecondElementSpace;
		VwField<std::string>        Label;
		VwField<bool>				Enabled;
		VwField<int>                Value;
		VwField<float>				Border;

		VwField<VtrFont*>			Font;
		VwField<VtrFont*>           SymbolFont;

	};

	VpmAnimation<VistaColor>       m_anmColor;

	virtual Model* GetModel() const override;
	virtual VpmElementView* GetView() const override;
	VwEmptySignal&  GetElementDownSignal();
	protected:

	virtual bool GetLablelVisibility() { return true; }
	bool VpmElement::Click_Recursive( VwWidget*widget, const VwFocusHandle* handle );
	bool GetByHandle_Rec( VwWidget*widget, const VwFocusHandle* handle, VwWidget**childwidget );
	void SetLabelVisibility( bool bVisible );

	virtual void LayoutElement();
	virtual void LayoutSecondElement( VistaQuaternion q, VistaVector3D pos )
	{

	}
	void AddSecondElement( VwWidget* sec );
	virtual Model* CreateModel() const;
	virtual VpmElementView* CreateView() const;

	virtual bool NeedSecondElement()
	{
		return true;
	}


	virtual void OnValueChanged( const VwIntChangedSignalArgs& oArgs );
	virtual void OnPositionChanged( const VwVectorChangedSignalArgs& oArgs );
	virtual void OnHieghtChanged( const VwFloatChangedSignalArgs& oArgs );
	virtual void OnWidthChanged( const VwFloatChangedSignalArgs& oArgs );
	virtual void OnBorderChanged( const VwFloatChangedSignalArgs& oArgs );
	virtual void OnOrientationChanged( const VwQuaternionChangedSignalArgs& oArgs );
	virtual void OnLabelChanged( const VwStringChangedSignalArgs& oArgs );
	virtual void OnElementDown( const VwEmptySignalArgs& oArgs );
	virtual void OnDownSignal( const VwEmptySignalArgs& oArgs );
	virtual void OnUpSignal( const VwEmptySignalArgs& oArgs );
	virtual void OnEnabledChanged( const VwBoolChangedSignalArgs& oArgs );
	virtual void OnFontChanged( const VwChangedFromToSignalArgs<VtrFont*>& oArgs );
	virtual void OnVisibilityChanged( const VwEmptySignalArgs& oArgs );
	virtual void OnFocusGained( const VwEmptySignalArgs& oArgs );
	virtual void OnFocusLost( const VwEmptySignalArgs& oArgs );
	virtual void OnSecondPositionChanged( const VwFloatChangedSignalArgs& oArgs );

	virtual void OnChildClicked( VwWidget* child );
	private:
	void SetProgressValue( float ProgressValue ); 
	void SetDeepValue( float ProgressValue );

	bool  m_bLoadImage;
	bool pDepepth = false;
	bool GetImageVisibility();
	std::string      m_strLabel;
	VwEmptySignal    m_sigElementDown;
	VwPlaneWidget*	m_pBackground;
	VwBorderWidget* m_pBorder;
	VglwDynamicTextWidget* m_pLabel;
	VglwDynamicTextWidget* m_pSymbolOfSubMenu;
	bool m_bHasSubMenu;
	VwTexturePlaneWidget*  m_pImage;
	VwInputSlot<bool>*     m_pSelectInputSlot;

	VwPlaneWidget*	m_pProgressBar;
	VwPlaneWidget* m_pDeep;
	VpmAnimation<float>            m_anmProgress;
};