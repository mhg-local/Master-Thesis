#include "VpmPullDownMenu.h"
#include <VistaWidgets\Widgets\VwPlaneWidget.h>


#include"VpmGlobalConfiguration.h"

#include"Elements\VpmRadioButtonElement.h"
#include"Elements\VpmLabelElement.h"
VpmPullDownMenu::VpmPullDownMenu()

{
	m_pDownStateElement = NULL;
	m_pBackground = NULL;
	m_pActiveSubMenu = NULL;
	m_pParentMenu = NULL;
	m_iZindex = 0;
	m_bIsSubMenu = false;
	m_bIsActiveMenu = true;
	m_iPositionScroll = 0;
	m_iTotalCount = 0;
}


VpmPullDownMenu::~VpmPullDownMenu()
{
	for (const auto& oElements : m_vecElements)
	{
		delete oElements;
	}
	delete m_pBackground;
}


void VpmPullDownMenu::Show(bool withAnimation) 
{

	SetVisible(true);
	for (int i = 0;i < m_vecElements.size();i++)
	{
		m_vecElements[i]->SetVisible(true);
	}
	GetView()->GetBackgroundView()->SetVisible(false);
	GetModel()->SelectedElementIndex.Set(-1);
	m_pBackground->SetVisible(false);
	m_bIsActiveMenu = true;
	GetModel()->Position.Set(VpmGlobalConfiguration::OriginalPosition);
	/*auto menu = GetActiveMenu( );
	VistaVector3D OriginalPosition = this->GetModel()->Position() - VistaVector3D(0, menu->m_iPositionScroll,0);*/

	if( withAnimation )
		{

		this->GetModel()->Scale.Set( 0.6f );
		m_anmScale.SetDuration( 1.f );
		m_anmScale.SetStartValue( this->GetModel()->Scale() );
		m_anmScale.SetEndValue( 1 );
		m_anmScale.GetEaseCurve( )->SetType( VistaEaseCurve::CUBIC_OUT );

		m_anmScale.Start();

		m_anmPosition.SetDuration( 1.f );
		m_anmPosition.SetStartValue( this->GetModel( )->Position( ) );
		m_anmPosition.SetEndValue( VpmGlobalConfiguration::OriginalPosition );
			
		m_anmPosition.GetEaseCurve( )->SetType( VistaEaseCurve::CUBIC_OUT );

		m_anmPosition.Start( );
		}
	else
		{
		this->GetModel()->Scale.Set( 1 );
		GetModel( )->Position.Set( VpmGlobalConfiguration::OriginalPosition );
		
		m_anmPosition.Stop( );
		m_anmScale.Stop( );

		}
}

void VpmPullDownMenu::Hide( bool withAnimation )
{
  
	SetVisible(false);

	for (int i = 0;i < m_vecElements.size();i++)
	{
		m_vecElements[i]->SetVisible(false);
	}

	if ( m_pActiveSubMenu!=NULL )
	{
		m_pActiveSubMenu->Hide();
		m_pActiveSubMenu = NULL;
	}
	m_bIsActiveMenu = false;
}
VpmPullDownMenu* VpmPullDownMenu::GetActiveMenu()
	{
	auto cur = this;

	while( cur->m_pActiveSubMenu != NULL )
		{
		cur = cur->m_pActiveSubMenu;
		}
	return cur;
	}
void VpmPullDownMenu::MoveUp( bool withAnimation )
{
	auto menu = GetActiveMenu( );
	/*if( menu->m_iPositionScroll == 0 )return;
	menu->m_iPositionScroll--;*/

	VistaVector3D activeSubMenuPosition = menu->GetModel( )->Position( );
	VistaVector3D newPos( 0.f, 0.01f, 0.f );
	//VistaVector3D newPos( 0.f, 0.1f, 0.f );
	newPos = menu->GetModel()->Orientation().Rotate( newPos );
	activeSubMenuPosition += newPos;

	/*if( withAnimation )
		{

			menu->m_anmPosition.SetDuration( 2.f );
			menu->m_anmPosition.SetStartValue( menu->GetModel()->Position() );
			menu->m_anmPosition.SetEndValue( activeSubMenuPosition );
			menu->m_anmPosition.GetEaseCurve()->SetType( VistaEaseCurve::CUBIC_OUT );

			menu->m_anmPosition.Start();
		}
	else*/
		{
		menu->GetModel( )->Position.Set( activeSubMenuPosition );
		menu->m_anmPosition.Stop();
		}
}


void VpmPullDownMenu::MoveDown( bool withAnimation )
{
	auto menu = GetActiveMenu();

	/*if( menu->m_iTotalCount <= menu->m_iPositionScroll )return;
	menu->m_iPositionScroll++;*/
	VistaVector3D activeSubMenuPosition =   menu->GetModel()->Position();
	
	VistaVector3D newPos( 0.f, -0.01, 0.f );
	//VistaVector3D newPos( 0.f, -0.1f, 0.f );
	newPos = menu->GetModel()->Orientation().Rotate( newPos );
	activeSubMenuPosition += newPos;
	//if( withAnimation )
	//	{

	//	menu->m_anmPosition.SetDuration( 2.f );
	//	menu->m_anmPosition.SetStartValue(/* menu->*/GetModel( )->Position( ) );
	//	menu->m_anmPosition.SetEndValue( activeSubMenuPosition );
	//	menu->m_anmPosition.GetEaseCurve( )->SetType( VistaEaseCurve::CUBIC_OUT );
	//	menu->m_anmPosition.Start( );
	//		

	//	}
	//else
		{
		menu->GetModel( )->Position.Set( activeSubMenuPosition );
		menu->m_anmPosition.Stop();
		}
	
	
}


void VpmPullDownMenu::Init()
{
	VwWidget::Init();
	m_pBackground = new VwPlaneWidget();
	m_pBackground->Init();
	m_pBackground->GetModel()->Height.Set(GetModel()->Width());
	m_pBackground->GetModel()->Width.Set(GetModel()->Height());
	m_pBackground->GetView()->SetVisible(false);
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>(m_pBackground->GetView());
	pBackgroundView->SetVisible(false);
	GetModel()->Position.GetSignal().AddSlot(this, &VpmPullDownMenu::OnPositionChanged);
	GetModel()->Orientation.GetSignal().AddSlot(this, &VpmPullDownMenu::OnOrientationChanged);
	GetModel()->Width.GetSignal().AddSlot(this, &VpmPullDownMenu::OnLayoutChanged);
	GetModel()->Height.GetSignal().AddSlot(this, &VpmPullDownMenu::OnLayoutChanged);
	GetModel()->Scale.GetSignal().AddSlot(this, &VpmPullDownMenu::OnLayoutChanged);
	GetModel()->SelectedElementIndex.GetSignal().AddSlot(this, &VpmPullDownMenu::OnSelectedIndexChanged);
	GetModel()->Border.GetSignal().AddSlot(this, &VpmPullDownMenu::OnLayoutChanged);
	GetView()->SetBackgroundView(pBackgroundView);

	AddWidget( m_pBackground );

	/*m_pBackground->GetFocusable()->GetFocusGainedSignal().AddSlot( this, &VpmPullDownMenu::OnFocusGained );
	m_pBackground->GetFocusable( )->GetFocusLostSignal( ).AddSlot( this, &VpmPullDownMenu::OnFocusGained );*/
	m_pBackground->GetFocusGainedSignal().AddSlot(this, &VpmPullDownMenu::OnFocusGained);
	m_pBackground->GetFocusLostSignal().AddSlot(this, &VpmPullDownMenu::OnFocusLost);

}
VistaVector3D VpmPullDownMenu::GetMenuPosition()
	{
	auto lastMenu = this;
	while( true )
		{
		if( lastMenu->m_pActiveSubMenu )
			{
			lastMenu = m_pActiveSubMenu;
			}
		else
			break;
		}
	return lastMenu->GetModel()->Position();
	}
void VpmPullDownMenu::ResetMenu()
	{
	auto mainMenu = GetMainMenu();
	auto curMenu = mainMenu;
	while( curMenu->m_pActiveSubMenu != NULL )
		{
		auto tmp = curMenu->m_pActiveSubMenu;
		curMenu->m_pActiveSubMenu = NULL;
		curMenu = tmp;
		tmp->m_anmPosition.Stop();
		tmp->m_anmScale.Stop();
		tmp->Hide(false );
		}
	mainMenu->m_anmPosition.Stop( );
	mainMenu->m_anmScale.Stop( );
	}
VpmPullDownMenu* VpmPullDownMenu::GetMainMenu()
	{
	auto mainMenu = this;
	while( true )
		{
		if( mainMenu->m_pParentMenu == NULL )
			break;
		else
			mainMenu = mainMenu->m_pParentMenu;
		}
	return mainMenu;
	}

bool VpmPullDownMenu::IsStateElement( VpmElement* elemnt )
	{
	return dynamic_cast< VpmLabelElement* >( elemnt ) != NULL;
	}
void VpmPullDownMenu::OnSelectedIndexChanged(const VwIntChangedSignalArgs& oArgs)
{
	int selectedIndex = oArgs.GetNewValue();
	VpmElement* element = NULL;
	bool closeMenu = false;
	if( selectedIndex != -1 )
	{
		element = m_vecElements[selectedIndex];
		if( !(HasSubMenu( element )==false && IsStateElement(element)) )
		{
			element->Select();
		}
		else{
			if( IsStateElement( element))
			closeMenu = true;
			}
	}

	for (std::size_t i = 0; i < m_vecElements.size(); ++i)
	{
		if (m_vecElements[i] != element)
		{
			m_vecElements[i]->Deselect();
		}
	}
	if (IsElementRadioButton(element))
	{
		for (std::size_t i = 0; i < m_vecElements.size(); ++i)
		{
			if (m_vecElements[i] != element)
			{
				if (IsElementRadioButton(m_vecElements[i]))
					m_vecElements[i]->GetModel()->Value.Set(0);
			}
		}
	}
	if( closeMenu )
		{
		
		VistaVector3D pos = VpmGlobalConfiguration::OriginalPosition ;//GetMenuPosition();
		auto mainMenu = GetMainMenu();
		ResetMenu();

		mainMenu->GetModel()->Position.Set( pos );
		mainMenu->GetModel()->Scale.Set( 1 );
		mainMenu->Hide(false);
		}
}
void VpmPullDownMenu::AddSubMenu(VpmElement*element, VpmPullDownMenu* subMenu)
{
	if (std::find(m_vecElements.begin(), m_vecElements.end(), element) == m_vecElements.end())
	{
		VISTA_THROW("Adding a submenu to an element that is not part of the menu is not allowed!", -1);
		return;
	}
	if (m_mpSubMenu.find(element) != m_mpSubMenu.end())
	{
		VISTA_THROW("Adding a submenu to an element that already has a sub menu is not allowed!", -1);
	}

	m_mpSubMenu[element] = subMenu;

	element->AddSubMenu();
	element->AddWidget(subMenu);
	subMenu->m_pParentMenu = this;
	subMenu->m_bIsSubMenu = true;
	subMenu->Hide();
}

VpmPullDownMenu* VpmPullDownMenu::GetSubMenu(VpmElement*element)
{
	if (m_mpSubMenu.find(element) != m_mpSubMenu.end())
	{
		return m_mpSubMenu[element];
	}
	return nullptr;
}
bool VpmPullDownMenu::HasSubMenu(VpmElement* element)
{

    if( m_mpSubMenu.find( element ) != m_mpSubMenu.end( ) )
	{
		return true;
	}
	return false;
}
void VpmPullDownMenu::RemoveSubMenu( VpmElement* element )
{
	if( HasSubMenu( element ) )
	{
		GetSubMenu( element )->m_bIsSubMenu = false;
		element->RemoveWidget( GetSubMenu( element ) );
		element->RemoveSubMenu();
		m_mpSubMenu.erase( element );

	}
	else
	{
		VISTA_THROW( "Removing a submenu from an element that not included submenu is not allowed!", -1 );
	}
}

VpmElement* VpmPullDownMenu::GetElement(int iElement)
{
	if (iElement < GetElementNumber())
	{
		return m_vecElements[iElement];
	}
	else
	{
		VISTA_THROW("Error:index of element is out of range!", -1);
	}
}
int VpmPullDownMenu::GetElementNumber()
{
	return (int)m_vecElements.size();
}
void VpmPullDownMenu::RemoveElement(VpmElement* element)
{
	std::vector < VpmElement*>::iterator cit = std::find(m_vecElements.begin(), m_vecElements.end(), element);
	if (HasSubMenu(element))
	{
		RemoveSubMenu(element);
	}
	if (cit == m_vecElements.end())
	{
		VISTA_THROW("Error: the element is not part of the menu and cannot be removed!", -1);
	}
	m_vecElements.erase(cit);
}
VpmElement* VpmPullDownMenu::RemoveSubMenu(VpmPullDownMenu* subMenu)
{
	std::map<VpmElement*, VpmPullDownMenu*>::iterator cit, citEnd;
	VpmElement *pSubMenuElement = 0;
	cit = m_mpSubMenu.begin();
	citEnd = m_mpSubMenu.end();

	for (;cit != citEnd;++cit)
	{
		if (cit->second == subMenu)
		{
			pSubMenuElement = cit->first;
			subMenu->m_bIsSubMenu = false;
			m_mpSubMenu.erase(cit->first);
	
			break;
		}
	}
	if (!pSubMenuElement)
	{
		VISTA_THROW("Error: the sub menu cannot be removed, because it is not part of the menu!", -1);
	}

	return pSubMenuElement;
}

VpmPullDownMenu::Model* VpmPullDownMenu::GetModel() const
{
	return static_cast<VpmPullDownMenu::Model*>(VwWidget::GetModel());

}
VpmPullDownMenuView* VpmPullDownMenu::GetView() const
{
	return static_cast<VpmPullDownMenuView*>(VwWidget::GetView());
}

VpmPullDownMenu::Model* VpmPullDownMenu::CreateModel() const
{
	return new VpmPullDownMenu::Model;
}

VpmPullDownMenuView* VpmPullDownMenu::CreateView() const
{
	return new VpmPullDownMenuView;
}

float VpmPullDownMenu::GetElementWidth()
{
	return GetModel()->Width()*GetModel()->Scale();
}
float VpmPullDownMenu::GetElementHeight()
{
	float fHeightElement = 0.00001f;
	if (GetElementNumber()>0)
		fHeightElement = (GetModel()->Height()*GetModel()->Scale()) / GetElementNumber();
	return fHeightElement;
}

void VpmPullDownMenu::LayoutElements()
{
	float fTotalWidth = GetModel()->Width()*GetModel()->Scale();
	float fTotalHeight = GetModel()->Height()*GetModel()->Scale();
	
	std::size_t iNumberOfElements = m_vecElements.size();
	
	//float fHeightElement = GetElementHeight();
	//float fWidthElement =GetElementWidth();
	
	float fHeightElement = GetModel()->ElementHeight();
	float fWidthElement = GetModel()->ElementWidth();

	VistaVector3D v3Pos = GetModel()->Position();


	VistaQuaternion qOrientation = GetModel()->Orientation();
	VistaVector3D v3Position(0,0, 0.0f);
	v3Position = v3Pos - qOrientation.Rotate(v3Position);

	VistaVector3D v3ElementPosition(0, 0, 0.001f );
	v3ElementPosition = qOrientation.Rotate( v3ElementPosition);
	v3ElementPosition += v3Position;

	VistaVector3D v3ElementDirection = qOrientation.Rotate(GetElementDirection());
	v3ElementDirection *= fHeightElement;

	for (std::size_t i = 0; i < m_vecElements.size(); ++i)
	{
		VpmElement* element = m_vecElements[i];
		element->GetModel()->Position.Set(v3ElementPosition);
		element->GetModel()->Orientation.Set(qOrientation);
		element->GetModel()->Width.Set(fWidthElement);
		element->GetModel()->Height.Set(fHeightElement);
		element->GetModel()->Border.Set(GetModel()->Border()*GetModel()->Scale());
		element->GetModel()->SecondElementSpace.Set( fWidthElement*VpmGlobalConfiguration::SecondaryElementWidthPercent*GetModel()->Scale() );
		v3ElementPosition += v3ElementDirection;
	}


	m_pBackground->GetModel()->Position.Set(v3Position);
	m_pBackground->GetModel()->Height.Set(fTotalHeight);
	m_pBackground->GetModel()->Width.Set(fTotalWidth);
	m_pBackground->GetModel()->Orientation.Set(qOrientation);

}
void VpmPullDownMenu::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
	LayoutElements();
}
void VpmPullDownMenu :: OnLayoutChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutElements();
}
void VpmPullDownMenu::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
	LayoutElements();
}

void VpmPullDownMenu::OnFocusGained(const VwEmptySignalArgs& oArgs)
{
	GetView()->SetState(VpmPullDownMenuView::VIEW_STATE_FOCUSED);
	
}

void VpmPullDownMenu::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	GetView()->SetState(VpmPullDownMenuView:: VIEW_STATE_ENABLED);
	
	
}
void VpmPullDownMenu::OnBackgroundPositionchanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetModel()->Position.Set(oArgs.GetNewValue());
}

bool VpmPullDownMenu::IsElementInCurrentMenu(VpmElement*element, VpmPullDownMenu* subMenu)
{
	for( VpmElement* elemnet : subMenu->m_vecElements )
	{
		if( elemnet == element )
		{
			return true;
		}
	}
	
	/*
	for (std::size_t i = 0; i < subMenu->m_vecElements.size(); ++i)
	{
		if (subMenu->m_vecElements[i] == element)
		{
			return true;
		}
	}*/
	return false;

}
VistaVector3D VpmPullDownMenu::GetElementDirection()
{
	return Vista::YAxis;
}

void VpmPullDownMenu::Update()
{
	//if( )
	{

		if( m_anmScale.IsStartAnimation() )
		{
			float fNewScale=m_anmScale.GetValue();
			fNewScale = m_anmScale.GetEndValue( ) <= fNewScale ? m_anmScale.GetEndValue( ) : fNewScale;
			this->GetModel()->Scale.Set(fNewScale );

			if( m_anmScale.GetEndValue() == fNewScale )
			{
				m_anmScale.Stop();
			}
		}
		if( m_anmPosition.IsStartAnimation( ) )
		{
			VistaVector3D fNewPos = m_anmPosition.GetValue( );
			this->GetModel( )->Position.Set( fNewPos );

			if( m_anmPosition.GetEndValue( ) == fNewPos )
			{
				m_anmPosition.Stop( );
			}
		}
	}
	for( int i = 0; i < m_vecElements.size(); i++ )
	{
		m_vecElements[ i ]->UpdateAnimation();
	}

	VwWidget::Update();
}
void VpmPullDownMenu::BringBack( float width, float height, float scale, float baseScale, VistaVector3D curPosition,bool withAnimation )
{
	float curWidth = this->GetModel()->Width()*scale;
	float curHeight = this->GetModel()->Height()*scale;

	VistaVector3D newPos( -width + ( ( width - curWidth ) / 2.0f ), ( height - curHeight ) / 2.0f + 0.02f, -0.01f );
	newPos = GetModel()->Orientation().Rotate( newPos );
	newPos += curPosition;

   if( withAnimation )
		{

		m_anmScale.SetDuration( 1.0f );//  it was 0.15f
		m_anmScale.SetStartValue( this->GetModel()->Scale() );
		m_anmScale.SetEndValue( scale );
		m_anmScale.GetEaseCurve()->SetType( VistaEaseCurve:: CUBIC_OUT );

		m_anmScale.Start();
	
		m_anmPosition.SetDuration( 1.f );
		m_anmPosition.SetStartValue( this->GetModel()->Position() );
		m_anmPosition.SetEndValue( newPos );
		m_anmPosition.GetEaseCurve()->SetType( VistaEaseCurve::CUBIC_OUT );

		m_anmPosition.Start();
	
		}
	else
		{
		this->GetModel( )->Scale.Set( scale );
		GetModel( )->Position.Set( newPos );
		m_anmPosition.Stop();
		m_anmScale.Stop( );

		}

		if( m_pParentMenu != NULL )
		{
		m_pParentMenu->BringBack( curWidth, curHeight, scale*baseScale, baseScale, newPos, withAnimation );
		};
	
}
void VpmPullDownMenu::BringFront( VistaVector3D Position, bool withAnimation )
{
	if( withAnimation)
	
		{
		m_anmScale.SetDuration( 1.f );
		m_anmScale.SetStartValue( this->GetModel()->Scale() );
		m_anmScale.SetEndValue( 1 );
		m_anmScale.GetEaseCurve()->SetType( VistaEaseCurve::CUBIC_OUT );

		m_anmScale.Start();

		m_anmPosition.SetDuration( 1.f );
		m_anmPosition.SetStartValue( this->GetModel()->Position() );
		m_anmPosition.SetEndValue( Position );
		m_anmPosition.GetEaseCurve()->SetType( VistaEaseCurve::CUBIC_OUT );
		m_anmPosition.Start();
		}
		else{
			  this->GetModel()->Scale.Set( 1 );
			 this->GetModel()->Position.Set( Position );
			 m_anmScale.Stop();
			 m_anmPosition.Stop();
			}
	
		if( m_pParentMenu != NULL )
			m_pParentMenu->BringBack( this->GetModel()->Width(), this->GetModel()->Height(), VpmGlobalConfiguration::ScalingPreviousMenu, VpmGlobalConfiguration::ScalingPreviousMenu, Position,withAnimation );
		    

}
void VpmPullDownMenu::ShowSubMenuForElement(VpmElement* element,VpmPullDownMenu* parentMenu)
{
	
	if( HasSubMenu( element ) )
		{

			VpmPullDownMenu* selectedSubMenu = GetSubMenu( element );

			float parentScale = VpmGlobalConfiguration::ScalingPreviousMenu;
			float curScale = VpmGlobalConfiguration::ScalingCurrentMenu;



			float parentWidth = parentMenu->GetModel()->Width()*parentScale;
			VistaVector3D parentPos = parentMenu->GetModel()->Position();

			selectedSubMenu->m_iZindex = parentMenu->m_iZindex + 1;
			VistaQuaternion qOrientatiton = parentMenu->GetModel()->Orientation();


			float curWidth = parentMenu->GetModel()->Width();
			float curHeight = parentMenu->GetModel()->Height();

			VistaVector3D curMenuPos(- parentWidth / 2.0f + ( curWidth*curScale ) / 2.0f + VpmGlobalConfiguration::Left_X_Padding_SubMenu, 0, selectedSubMenu->m_iZindex*VpmGlobalConfiguration::ZDistance );
			curMenuPos = qOrientatiton.Rotate( curMenuPos );
			curMenuPos += parentPos;

			selectedSubMenu->GetModel()->Scale.Set( 0.6f );
			//selectedSubMenu->GetModel( )->Scale.Set( curScale );

			selectedSubMenu->GetModel()->Height.Set( curHeight );
			selectedSubMenu->GetModel()->Width.Set( curWidth );
			selectedSubMenu->GetModel()->Orientation.Set( qOrientatiton );
			selectedSubMenu->GetModel( )->Position.Set( parentPos );
			selectedSubMenu->GetModel()->Border.Set( parentMenu->GetModel()->Border() );


			selectedSubMenu->m_anmScale.SetDuration( 1.f );
			selectedSubMenu->m_anmScale.SetStartValue( selectedSubMenu->GetModel()->Scale() );
			selectedSubMenu->m_anmScale.SetEndValue( curScale );
			selectedSubMenu->m_anmScale.GetEaseCurve()->SetType( VistaEaseCurve::CUBIC_OUT );
			selectedSubMenu->m_anmScale.Start();
			selectedSubMenu->Show( true );

			parentMenu->BringBack( curWidth, curHeight, parentScale, parentScale, parentMenu->GetModel()->Position() );
			

		}
		else
		{
			parentMenu->GetModel()->Scale.Set( VpmGlobalConfiguration::ScalingCurrentMenu );
		}

}
int VpmPullDownMenu::GetElementIndex(VpmElement* element)
{
	int iSelectedIndex = -1;

	for (std::size_t i = 0; i < m_vecElements.size(); ++i)
	{
		if (m_vecElements[i] == element)
		{
			iSelectedIndex = static_cast<int>(i);
			break;
		}
	}
	return iSelectedIndex;
}
void VpmPullDownMenu::ShowMenu()
{
	if( GetVisible() == false )
	{
		this->Show(true);
	}
}
void VpmPullDownMenu::MoveUpMenu( )
{
	
	if( GetVisible() )
	{
		this->MoveUp( true );

	}
}


void VpmPullDownMenu::MoveDownMenu(  )
{
	if( GetVisible( ) )
	{
		this->MoveDown( true );
	}
}

bool VpmPullDownMenu::CloseActiveSubMenu(bool withAnimation)
{
	auto activeSubMenu = m_pActiveSubMenu;
	auto preSubMenu = m_pActiveSubMenu;
	if( activeSubMenu != NULL )
	{
		while( activeSubMenu->m_pActiveSubMenu != NULL )
		{

			activeSubMenu = activeSubMenu->m_pActiveSubMenu;
		}
		preSubMenu = activeSubMenu->m_pParentMenu;
		VistaVector3D pos = VpmGlobalConfiguration::OriginalPosition;//activeSubMenu->GetModel()->Position();

		activeSubMenu->m_bIsActiveMenu = false;
		activeSubMenu->Hide();

		
		preSubMenu->m_bIsActiveMenu = true;
		preSubMenu->m_pActiveSubMenu = NULL;
		preSubMenu->GetModel()->SelectedElementIndex.Set( -1 );
		preSubMenu->BringFront( pos, withAnimation );
		
		return true;
	}
	else
	{
		m_pActiveSubMenu = NULL;
		this->GetModel()->SelectedElementIndex.Set( -1 );
		this->Hide();
		//preSubMenu->BringFront( pos, withAnimation );
		return false;
	}
}
void VpmPullDownMenu::ProgressVisible( )
{
	auto menu = GetActiveMenu( );
	for( auto element : menu->m_vecElements )
	{
	element->SetProgressVissibilityOn( );
	}
}
void VpmPullDownMenu::ProgressInvisible( )
{
	auto menu = GetActiveMenu( );
	for( auto element : menu->m_vecElements )
	{
		element->SetProgressVisisbilityOff();
	}
}

void VpmPullDownMenu::ProgressiveValue( float prgValue )
{
	auto menu=GetActiveMenu();
	for( auto element : menu->m_vecElements )
	{
		element->ProgressValue( prgValue );
	}
}

void VpmPullDownMenu::DeepValue( float prgValue )
{
	auto menu = GetActiveMenu( );
	for( auto element : menu->m_vecElements )
	{
		element->DeepValue( prgValue );

	}
}
void VpmPullDownMenu::OnElementDown( const VwEmptySignalArgs& oArgs )
{
	int iSelectedIndex = -1;
	VpmElement* selectedElement = ( VpmElement* )oArgs.GetSignalSource();
	VpmPullDownMenu* selectedmenu = ( VpmPullDownMenu* )oArgs.GetSignalSource();
	VpmPullDownMenu* selectedSubMenu = GetSubMenu( selectedElement );
	//bool checkElementInActiveMenu = IsElementInCurrentMenu( selectedElement, GetMainMenu() );
	if( selectedmenu = m_pActiveSubMenu )
	{
		return;
	}
	if( m_pActiveSubMenu != selectedSubMenu )
		{
		VistaVector3D pos = this->GetModel()->Position();
			if( m_pActiveSubMenu != NULL )
			{
				pos = m_pActiveSubMenu->GetModel()->Position() ;
				m_pActiveSubMenu->m_bIsActiveMenu = false;
				m_pActiveSubMenu->Hide();
				
			}
			
			this->BringFront( pos );
			m_pActiveSubMenu = selectedSubMenu;
			
		}
		if( selectedSubMenu != NULL )
		{
			selectedSubMenu->m_bIsActiveMenu = true;
		}
		else
		{
			this->m_bIsActiveMenu = true;
		}

		//Group Radio Button Like!;
		if( IsElementRadioButton( selectedElement ) )
		for( auto element : m_vecElements )
		{
			if( element != selectedElement )
			{
				if( IsElementRadioButton( element ) )
				{
					element->GetModel()->Value.Set( 0 );
				}
			}
		}

		ShowSubMenuForElement( selectedElement, this );
		iSelectedIndex = GetElementIndex( selectedElement );
		GetModel()->SelectedElementIndex.Set( iSelectedIndex );

	
	
}

bool VpmPullDownMenu::ButtonUp( const VwFocusHandle* handle )
	{
	VpmElement* element = NULL;
	VwWidget*   widget = NULL;
	if( GetElementOfHandle( this, handle, &element, &widget ) )
		{
		if( element == m_pDownStateElement )
			{
			m_pDownStateElement->ButtonUp( widget );
			m_pDownStateElement = NULL;

			}
		return true;
		}
	return false;
	}
bool VpmPullDownMenu::ButtonDown( const VwFocusHandle* handle )
	{
	VpmElement* element = NULL;
	VwWidget*   widget = NULL;

	if( GetElementOfHandle( this, handle, &element, &widget ) )
		{
		element->ButtonDown( widget );
		m_pDownStateElement = element;
		return true;
		}
	return false;
	}
bool VpmPullDownMenu::GetElementOfHandle( VpmPullDownMenu* menu, const VwFocusHandle* handle ,VpmElement**elementofHandle,VwWidget** childOfElement)
{
	//current Menu Elememt
	int index = 0;
	for( VpmElement* elemnet : menu->m_vecElements )
	{
		// check handel of element
		if( elemnet->GetByHandle( handle, childOfElement ) )
		{
			*elementofHandle = elemnet;
			return true;
		}
		index++ ;
	}
	// To check clicked subMenu's elements 
	if( menu->m_pActiveSubMenu != NULL )
	{
		return  menu->m_pActiveSubMenu->GetElementOfHandle( menu->m_pActiveSubMenu, handle, elementofHandle, childOfElement );
	}
	return false;
}



bool VpmPullDownMenu::ClickMenu( VpmPullDownMenu* menu,const VwFocusHandle* handle )
{
	//current Menu Elememt
	for( VpmElement* elemnet : menu->m_vecElements )
	{
		// check handel of element
		if( elemnet->Click( handle ) )
				return true;
		
		
	}
	// To check clicked subMenu's elements 
	if( menu->m_pActiveSubMenu != NULL )
	{
		return ClickMenu( menu->m_pActiveSubMenu, handle );
	}
	
	return false;
}
bool VpmPullDownMenu::Click(const VwFocusHandle* handle )
{
	bool b= ClickMenu( this, handle );
	return b;
}
bool VpmPullDownMenu::IsElementRadioButton(VpmElement* element)
{
	return element!=0 &&((dynamic_cast<VpmRadioButtonElement*>(element))!=NULL);
}
void VpmPullDownMenu::AddWigetToBackground(VpmElement*element)
{

	AddWidget(element);
}




VpmPullDownMenu::Model::Model()
    : SelectedElementIndex( -1 )
   , ElementHeight( VpmGlobalConfiguration::ElementHeight )
	, ElementWidth(VpmGlobalConfiguration::ElementWidth )
	, Width(VpmGlobalConfiguration::MenuWidth)
	, Height(VpmGlobalConfiguration::MenuHeight)
	, Position(Vista::ZeroVector)
	, Border(VpmGlobalConfiguration::BorderSize)
	, Scale(VpmGlobalConfiguration::ScalingCurrentMenu)
	/*, Orientation(VistaAxisAndAngle(VistaVector3D(0, 1, 0), Vista::DegToRad(10)))*/
{

}
