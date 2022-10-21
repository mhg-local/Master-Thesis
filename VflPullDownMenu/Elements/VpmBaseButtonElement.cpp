

#include"VpmBaseButtonElement.h"

#include"../VglConfig.h"
#include"../VpmGlobalConfiguration.h"
#include"VpmElement.h"
#include"../Widget/VwWidgetControl.h"
#include"../Widget/VwBorderWidget.h"

VpmBaseButtonElement::VpmBaseButtonElement()
{
	
}

VpmBaseButtonElement::~VpmBaseButtonElement()
{
	for ( int i = 0; i < m_vecBorder.size(); i++ )
	{
		delete m_vecButtons[ i ]->GetWidget();
		delete m_vecButtons[ i ];
		delete m_vecBorder[ i ];

		delete m_vecSignal[ i ];
	}
	m_vecBorder.clear();
	m_vecButtons.clear();
	m_vecSignal.clear();
}
void VpmBaseButtonElement::ButtonUp( VwWidget*child )
{}
void VpmBaseButtonElement::ButtonDown( VwWidget* child )
{}
void VpmBaseButtonElement::Init()
{
	VpmElement::Init();
	SetLabelVisibility(false);
}

VwWidgetControl* VpmBaseButtonElement::AddChildButton()
{
	if ( m_vecBorder.size() < 4 )
	{

		VwWidgetControl*  button = CreateChildWidget();

		VwBorderWidget*   border = new VwBorderWidget();
		border->Init( button );

		

		m_vecButtons.emplace_back( button );
		m_vecBorder.emplace_back( border );
		m_vecSignal.emplace_back(new VwEmptySignal( ) );
		//button->GetClickable->GetClickedSignal( ).AddSlot( this, &VpmBaseButtonElement::OnElementDown );

		AddSecondElement( border);
		
		return button;
	}
	return NULL;
}

void VpmBaseButtonElement::OnButtonClick( const VwEmptySignalArgs& oArgs )
{
	VwWidget* control = ( VwWidget* )oArgs.GetSignalSource();

	int i = 0;
	for ( auto element : m_vecButtons )
	{
		if ( element->GetWidget() == control )
		{
			VwEmptySignalArgs arg( control );
			m_vecSignal[ i ]->Raise( arg );
			GetModel()->Value.Set( i );
		}
		i++;
	}
}

VwEmptySignal& VpmBaseButtonElement::GetButtonClickedSignal( int index )
{
	if ( index < m_vecSignal.size() )
	{
		return *m_vecSignal[ index ];
	}
	VISTA_THROW( "Get Out Of Range Signal", -1 );
}
void VpmBaseButtonElement::OnVisibilityChanged(const VwEmptySignalArgs& oArgs)
{

	for (auto element : m_vecButtons)
	{

		element->GetWidget()->SetVisible(GetVisible());
	}
	for (auto element : m_vecBorder)
	{

		element->SetVisible(GetVisible());
	}
	VpmElement::OnVisibilityChanged(oArgs);
}

void VpmBaseButtonElement::OnElementDown(const VwEmptySignalArgs& oArgs)
{
	VwEmptySignalArgs o(this);
	VpmElement::OnElementDown( o );
}

int  VpmBaseButtonElement::GetNumberOfButton()
{
	return m_vecBorder.size();
}
int VpmBaseButtonElement::RemoveButton(int index)
{
	if (index < GetNumberOfButton())
	{
		auto border=m_vecBorder[index];
		auto element = m_vecButtons[index];
		delete element->GetWidget();
		delete element;
		delete border;
	}
	else
	{
		VISTA_THROW("Removing out of range Button!", -1);
	}
}
void VpmBaseButtonElement::LayoutSecondElement(VistaQuaternion q, VistaVector3D pos)
{
	float fTotalWidth = GetModel()->Width();
	float fTotalHeight = GetModel()->Height();

	float scale = 1;
	float posStartX = 0;
	float tmp;
	float fElementWidth = 0;
	float fElementHeigth = fTotalHeight - VpmGlobalConfiguration::Top_Y_Padding - VpmGlobalConfiguration::Bottom_Y_Padding - 2 * GetModel()->Border();

	float fRaito = fTotalWidth / fTotalHeight;
	
	fElementWidth = fRaito*fElementHeigth;

	tmp = (fElementWidth + 2 * GetModel()->Border() + (m_vecBorder.size() + 1) * VpmGlobalConfiguration::Left_X_Padding)*m_vecBorder.size();
	if (tmp > GetModel()->Width())
	{
		scale = GetModel()->Width() / tmp;
	}
	else
	{
		posStartX = (GetModel()->Width() - tmp) / 2.0f;
	}

	//fElementHeigth *= scale;
	fElementWidth *= scale;

	VistaVector3D posCenter = GetModel()->Position();
	VistaQuaternion qOrientation = GetModel()->Orientation();
	VistaVector3D v3Pos(fTotalWidth / 2.0f, -fTotalHeight / 2.0f, 0);
	v3Pos = qOrientation.Rotate(v3Pos);
	v3Pos = posCenter - v3Pos;

	VistaVector3D dirButton = qOrientation.Rotate(Vista::XAxis);
	dirButton *= fElementWidth + (VpmGlobalConfiguration::Left_X_Padding );


	VistaVector3D posButton(VpmGlobalConfiguration::Left_X_Padding + posStartX + fElementWidth / 2.0f, -fTotalHeight / 2.0f, 0.001f);
	posButton = qOrientation.Rotate(posButton);
	posButton += v3Pos;


	for (auto element : m_vecBorder)
	{
		element->GetModel()->Position.Set(posButton);
		element->GetModel()->Orientation.Set(qOrientation);
		element->GetModel()->Height.Set(fElementHeigth);
		element->GetModel()->Width.Set(fElementWidth);
		element->GetModel()->BorderSize.Set(GetModel()->Border());

		posButton += dirButton;
	}
	
}

void VpmBaseButtonElement::OnChildClicked( VwWidget* targetWidget )
{
	for( VwWidget* child : m_vecBorder )
	{

		//Child is Clicked
		if( child == targetWidget )
		{
			
		}
	}
}