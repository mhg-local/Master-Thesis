#pragma once
#include"VglConfig.h"
#include"VpmPullDownMenuView.h"
#include"Elements\VpmElement.h"
#include"VpmGlobalConfiguration.h"
#include <VistaWidgets\VwField.h>
#include <VistaWidgets\VwWidget.h>
#include <VistaWidgets\VwWidgetModel.h>
#include <VistaWidgets\SignalSystem\Signals\VwConstraintSignals.h>
#include<vector>
#include"VpmAnimation.h"
class VwPlaneWidget;


class VGLWAPI VpmPullDownMenu :public VwWidget
{
public:
	VpmPullDownMenu();
	~VpmPullDownMenu();


	virtual void Init();
	virtual void Update( );

	virtual bool CloseActiveSubMenu(bool withAnimation=true);
	virtual void ShowMenu();

	virtual void MoveUpMenu();
	virtual void MoveDownMenu();


	bool Click(const VwFocusHandle* handle );
	bool ButtonDown( const VwFocusHandle*handle );
	bool ButtonUp( const VwFocusHandle*handle );
	class VGLWAPI Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model() = default;
		VwField<float>              Border;
		VwField<int>				SelectedElementIndex;
		VwField<float>				Scale;
		VwField<VistaVector3D>		Position;
		VwField<VistaQuaternion>	Orientation;
		VwField<float>				Height;
		VwField<float>				Width;
		VwField<float>				ElementHeight;
		VwField<float>				ElementWidth;
	};
	virtual Model*GetModel() const override;
	virtual VpmPullDownMenuView*GetView() const override;

	template< class TElement = VpmElement >
	TElement* AddElement(std::string label);


	VpmElement*GetElement(int iIndex);

	int GetElementNumber();

	void Show(bool withAnimation=true);
	void Hide( bool withAnimation=true );
	void MoveUp( bool withAnimation = true );
	void MoveDown( bool withAnimation = true );

	void AddSubMenu(VpmElement* element, VpmPullDownMenu*subMenu);
	void RemoveSubMenu(VpmElement*element);
	VpmElement* RemoveSubMenu(VpmPullDownMenu*element);
	VpmPullDownMenu* GetSubMenu(VpmElement* element);
	VpmPullDownMenu*  GetActiveMenu( );

	bool HasSubMenu(VpmElement* element);

	void ProgressiveValue( float prgValue ); 
	void ProgressVisible( );
	void ProgressInvisible( );
	void DeepValue( float prgValue );
	void RemoveElement(VpmElement* element);
protected:
    
	virtual void OnElementDown(const VwEmptySignalArgs& oArgs);
	virtual void OnSelectedIndexChanged(const VwIntChangedSignalArgs&oArgs);
	virtual void OnLayoutChanged(const VwFloatChangedSignalArgs& oArgs);

	virtual void OnPositionChanged(const VwVectorChangedSignalArgs& oArgs);
	virtual void OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs);

	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);

	virtual void OnBackgroundPositionchanged(const VwVectorChangedSignalArgs& oArgs);


	virtual Model* CreateModel() const;
	virtual VpmPullDownMenuView* CreateView() const;

	float GetElementWidth();
	float GetElementHeight();

	VistaVector3D GetMenuPosition();
	void          ResetMenu();
	VpmPullDownMenu* GetMainMenu();
private:

	bool IsStateElement( VpmElement*elemnet );
	void BringBack( float width, float height, float scale, float baseScale, VistaVector3D curPosition,bool withAnimation=true );
	void BringFront( VistaVector3D Position, bool withAnimation = true );
	

	//VistaVector3D m_pMainPosition;
	bool m_bIsActiveMenu;
	bool m_bIsSubMenu;

    bool  GetElementOfHandle( VpmPullDownMenu*menu, const VwFocusHandle*handle, VpmElement** element, VwWidget**childOfElement );

	bool ClickMenu( VpmPullDownMenu* menu,const VwFocusHandle* handle );
	bool  IsElementRadioButton(VpmElement* element);
	bool IsElementInCurrentMenu( VpmElement*element, VpmPullDownMenu* subMenu );
	void AddWigetToBackground(VpmElement*element);
	void ShowSubMenuForElement( VpmElement*element,  VpmPullDownMenu* curMenu );

	int GetElementIndex(VpmElement* element);
	VistaVector3D GetElementDirection();

	int m_iZindex;
	
	int m_iTotalCount;
	int m_iPositionScroll;


	std::map<VpmElement*, VpmPullDownMenu*>  m_mpSubMenu;
	VwPlaneWidget*	m_pBackground;
	std::vector<VpmElement*> m_vecElements;



	VpmElement*                    m_pDownStateElement;
	VpmPullDownMenu*               m_pParentMenu;
	VpmPullDownMenu*               m_pActiveSubMenu;



	VpmAnimation<float>            m_anmScale;
	VpmAnimation<VistaVector3D>    m_anmPosition;
	
	
	void LayoutElements();
};
template< class TElement >
TElement * VpmPullDownMenu::AddElement( std::string Label )
{
	VpmElement* element = new TElement();
	element->Init();

	m_vecElements.emplace_back( element );
	element->RemoveSubMenu();
	element->GetModel()->Height.Set( GetElementHeight() );
	element->GetModel()->Width.Set( GetElementWidth() );
	element->GetModel()->Orientation.Set( GetModel()->Orientation() );
	element->GetModel()->SecondElementSpace.Set( VpmGlobalConfiguration::SecondaryElementWidthPercent*GetElementWidth() );
	element->GetModel()->Label.Set( Label );
	element->GetElementDownSignal().AddSlot( this, &VpmPullDownMenu::OnElementDown );
	element->SetVisible( GetVisible() );
	AddWigetToBackground( element );

	int count = GetElementNumber();
	if( count > VpmGlobalConfiguration::TotalViewElementCount )
	{
		m_iTotalCount = count - VpmGlobalConfiguration::TotalViewElementCount;
	}
	else
	{
		m_iTotalCount = 0;
	}
	LayoutElements();

	return ( TElement* )element;
}

