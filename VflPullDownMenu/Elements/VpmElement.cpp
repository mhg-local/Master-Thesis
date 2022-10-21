
#include"VpmElement.h"

#include <VistaWidgets/Widgets/VwPlaneWidget.h>
#include<VistaWidgets\Widgets\VwTextLabelWidget.h>
#include<VistaOpenGLWidgets\Widgets\VglwDynamicTextWidget.h>

#include<VflTextRendering\VtrFontManager.h>
#include<VistaWidgets\Widgets\Views\VwOutlinedPlaneView.h>

#include"../Widget/VwBorderWidget.h"
#include"../Widget/VwPlaneWidgetControl.h"

#include"../VpmGlobalConfiguration.h"
#include"../VpmPullDownMenu.h"

#include"../Widget/VwTexturePlaneWidget.h"
#include<VistaOpenGLWidgets\Widgets\Views\VglwTexturedPlaneView.h>


VpmElement::VpmElement()
{
	m_pBackground = nullptr;
	m_pLabel = nullptr;
	m_pBorder = nullptr;
	m_pProgressBar = nullptr;
	m_pDeep = nullptr;
	m_bLoadImage = false;
	m_bHasSubMenu = false;
}

VpmElement::~VpmElement()
{
	delete m_pLabel;
	delete m_pBackground;
	delete m_pBorder;
	delete m_pProgressBar;
	delete m_pDeep;

}

void VpmElement::AddSecondElement( VwWidget* sec )
{
	m_pBackground->AddWidget( sec );
	 m_pBackground->SetInteractionMode( INTERACTION_CLICKABLE );
}

void VpmElement::Select()
{
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>(m_pBackground->GetView());
	pBackgroundView->SetColor(VpmGlobalConfiguration::SelectedColor);
	m_pBorder->GetView()->GetBackgroundView()->SetFocusColor(VpmGlobalConfiguration::SelectedColor);
}
void VpmElement::Deselect()
{
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>(m_pBackground->GetView());
	pBackgroundView->SetColor(VpmGlobalConfiguration::EnableColor);
	m_pBorder->GetView()->GetBackgroundView()->SetFocusColor(VpmGlobalConfiguration::EnableColor);
}
void VpmElement::Init( )
{
	VwWidget::Init();
	
	m_pBackground = new VwPlaneWidget();
	m_pBackground->Init();

	m_pBorder = new VwBorderWidget();
	m_pBorder->Init(new VwPlaneWidgetControl(m_pBackground));
	
	m_pBorder->GetModel()->Height.Set(GetModel()->Height());
	m_pBorder->GetModel()->Width.Set(GetModel()->Width());
	m_pBorder->GetModel()->Position.Set(GetModel()->Position());
	m_pBorder->GetModel()->Orientation.Set(GetModel()->Orientation());
	m_pBorder->GetModel()->BorderSize.Set(GetModel()->Border());
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>(m_pBackground->GetView());
	m_pBorder->GetView()->GetBackgroundView()->SetFocusColor(VpmGlobalConfiguration::EnableColor);
	pBackgroundView->SetColor(VpmGlobalConfiguration::EnableColor);
	


	m_pBackground->SetInteractionMode( INTERACTION_CLICKABLE );
	
		
	m_pBorder->GetClickable()->GetClickedSignal().AddSlot( this, &VpmElement::OnElementDown );
	m_pBackground->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );

	m_pBorder->GetView()->GetBackgroundView()->SetFocusColor(VpmGlobalConfiguration::FocusColor);
	pBackgroundView->SetFocusColor(VpmGlobalConfiguration::FocusColor);
	m_pBorder->GetView()->GetBackgroundView()->SetPressedColor(VpmGlobalConfiguration::PressedColor);
	pBackgroundView->SetPressedColor( VpmGlobalConfiguration::PressedColor );

	m_pImage = new VwTexturePlaneWidget();
	m_pImage->Init();

	m_pImage->SetVisible( false );
	GetView()->SetBackgroundView(pBackgroundView);
	

	AddWidget(m_pBorder);

	GetModel()->Height.GetSignal().AddSlot(this, &VpmElement::OnHieghtChanged);
	GetModel()->Width.GetSignal().AddSlot(this, &VpmElement::OnWidthChanged);

	GetModel()->Position.GetSignal().AddSlot(this, &VpmElement::OnPositionChanged);
	GetModel()->Orientation.GetSignal().AddSlot(this, &VpmElement::OnOrientationChanged);

	GetModel()->Label.GetSignal().AddSlot(this, &VpmElement::OnLabelChanged);
	GetModel()->Value.GetSignal().AddSlot(this, &VpmElement::OnValueChanged);
	GetModel()->Enabled.GetSignal().AddSlot(this, &VpmElement::OnEnabledChanged);
	GetModel()->SecondElementSpace.GetSignal().AddSlot(this, &VpmElement::OnSecondPositionChanged);
	GetModel()->Font.GetSignal().AddSlot(this, &VpmElement::OnFontChanged);
	GetModel( )->SymbolFont.GetSignal( ).AddSlot( this, &VpmElement::OnFontChanged );
	GetModel()->Border.GetSignal().AddSlot(this, &VpmElement::OnBorderChanged);

	m_pLabel = new VglwDynamicTextWidget();
	m_pLabel->Init();
	m_pLabel->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );

	
	m_pLabel->GetModel()->Text.Set(VtrString( GetModel()->Label()));
	m_pLabel->GetModel()->Height.Set(GetModel()->Height());
	m_pLabel->GetModel()->SetHorizontalAlignment(VglwDynamicTextWidget::Model::HALIGN_LEFT);
	m_pLabel->GetModel()->SetVerticalAlignment(VglwDynamicTextWidget::Model::VALIGN_MIDDLE);
	m_pLabel->GetModel()->Position.Set(GetModel()->Position());
	m_pLabel->GetView()->SetColor(VistaColor(0,0,0));
	((VglwDynamicTextView*)m_pLabel->GetView())->SetFocusColor(VistaColor(0,0,0));
	m_pLabel->GetModel()->Font.Set(GetModel()->Font());

	m_pLabel->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );

	m_pSymbolOfSubMenu = new VglwDynamicTextWidget( );
	m_pSymbolOfSubMenu->Init( );
	m_pSymbolOfSubMenu->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );
	
	m_pSymbolOfSubMenu->GetModel( )->Text.Set( VtrString( "" ) );
	m_pSymbolOfSubMenu->GetModel( )->Height.Set( GetModel( )->Height( ) );
	m_pSymbolOfSubMenu->GetModel( )->SetHorizontalAlignment( VglwDynamicTextWidget::Model::HALIGN_LEFT );
	m_pSymbolOfSubMenu->GetModel( )->SetVerticalAlignment( VglwDynamicTextWidget::Model::VALIGN_MIDDLE );
	m_pSymbolOfSubMenu->GetModel( )->Position.Set( GetModel( )->Position( ) );
	m_pSymbolOfSubMenu->GetView( )->SetColor( VistaColor( 0, 0, 0 ) );
	( ( VglwDynamicTextView* )m_pSymbolOfSubMenu->GetView( ) )->SetFocusColor( VistaColor( 0, 0, 0 ) );
	m_pSymbolOfSubMenu->GetModel( )->Font.Set( GetModel( )->SymbolFont( ) );

	m_pSymbolOfSubMenu->GetClickable()->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );
	


	m_pProgressBar = new VwPlaneWidget( );
	m_pProgressBar->Init( );
	m_pProgressBar->SetInteractionMode( InteractionMode::INTERACTION_CLICKABLE);
	m_pProgressBar->SetVisible( false );
	m_pProgressBar->GetModel( )->Position.Set( GetModel( )->Position( ) );
	m_pProgressBar->GetModel( )->Height.Set( GetModel( )->Height( ) );
	m_pProgressBar->GetModel( )->Width.Set( GetModel( )->Width( ) );

	//m_pProgressBar->GetView()->
	m_pProgressBar->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );
	m_pProgressBar->GetClickable( )->GetButtonUpSignal( ).AddSlot( this, &VpmElement::OnElementDown );

	VwColoredPlaneView* pProgressView = dynamic_cast<VwColoredPlaneView*>( m_pProgressBar->GetView( ) );
	/*pProgressView->SetCurrentColor( VpmGlobalConfiguration::ProgressColor );
	pProgressView->SetFocusColor( VpmGlobalConfiguration::ProgressColor );
	pProgressView->SetPressedColor( VpmGlobalConfiguration::ProgressColor );*/

//////

	m_pDeep = new VwPlaneWidget( );
	m_pDeep->Init( );

		m_pDeep->SetInteractionMode( InteractionMode::INTERACTION_CLICKABLE );


	m_pDeep->SetVisible( false );
	m_pDeep->GetModel( )->Position.Set( GetModel( )->Position( ) );
	m_pDeep->GetModel( )->Height.Set( GetModel( )->Height( ) );
	m_pDeep->GetModel( )->Width.Set( GetModel( )->Width( ) );

	//m_pProgressBar->GetView()->
	m_pDeep->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );
	m_pDeep->GetClickable( )->GetButtonUpSignal( ).AddSlot( this, &VpmElement::OnElementDown );

	VwColoredPlaneView* pDeepView = dynamic_cast<VwColoredPlaneView*>( m_pDeep->GetView( ) );
	//pDeepView->SetColor( VpmGlobalConfiguration::DeepColor );
	//pDeepView->SetFocusColor( VpmGlobalConfiguration::DeepColor );
	//pDeepView->SetPressedColor( VpmGlobalConfiguration::DeepColor );



		m_pImage->SetInteractionMode( VwWidget::INTERACTION_CLICKABLE );
	
	
	m_pImage->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VpmElement::OnElementDown );
	m_pImage->GetClickable( )->GetButtonUpSignal( ).AddSlot( this, &VpmElement::OnElementDown );


	m_pBackground->GetFocusLostSignal( ).AddSlot( this, &VpmElement::OnUpSignal );
	m_pBackground->GetFocusGainedSignal().AddSlot(this,&VpmElement::OnFocusGained);
	m_pBackground->GetFocusLostSignal( ).AddSlot( this, &VpmElement::OnFocusLost );
	//m_pBackground->GetButtonDownSignal( ).AddSlot( this, &VpmElement::OnDownSignal );
	m_pBackground->GetButtonUpSignal( ).AddSlot( this, &VpmElement::OnUpSignal );
	//m_pBorder->GetButtonDownSignal( ).AddSlot( this, &VpmElement::OnDownSignal );
	m_pBorder->GetButtonUpSignal( ).AddSlot( this, &VpmElement::OnUpSignal );
	//m_pLabel->GetButtonDownSignal().AddSlot( this, &VpmElement::OnDownSignal );
	
	this->GetVisibilityChangedSignal().AddSlot(this,&VpmElement::OnVisibilityChanged);
	m_pBackground->AddWidget(m_pLabel);
	m_pBackground->AddWidget( m_pImage ); 
	m_pBackground->AddWidget( m_pSymbolOfSubMenu );
	m_pBackground->AddWidget( m_pProgressBar );
	m_pBackground->AddWidget( m_pDeep );
//OnVisibilityChanged( VwEmptySignalArgs( this ) );
}
void VpmElement::UpdateAnimation()
{
	/*if( m_anmProgress.IsStartAnimation() )
	{
		float fNewScale = m_anmProgress.GetValue();
		m_pProgressBar->GetModel()->Width.Set( fNewScale*GetModel()->Width() );
		if( m_anmProgress.GetEndValue() == fNewScale )
		{
			m_anmProgress.Stop();
			m_anmProgress.Start();
		}
	}*/
}
void VpmElement::OnSecondPositionChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutElement();
}
void VpmElement::OnFontChanged( const VwChangedFromToSignalArgs<VtrFont*>& oArgs )
{
	m_pLabel->GetModel()->Font.Set( GetModel()->Font() );
	m_pLabel->GetModel()->Font.Set( GetModel()->SymbolFont() );
	LayoutElement();
}

VpmElement::Model* VpmElement::GetModel() const
{
	return static_cast<VpmElement::Model*>(VwWidget::GetModel());

}
VpmElementView* VpmElement::GetView() const
{
	return static_cast<VpmElementView*>(VwWidget::GetView());
}

VpmElement::Model* VpmElement::CreateModel() const
{
	return new  VpmElement::Model;
}
void VpmElement::OnDownSignal( const VwEmptySignalArgs& oArgs )
{
	/*if( this->GetVisible() == false )return;
	float startScale = .3f;
	m_pProgressBar->GetModel( )->Width.Set( startScale * GetModel( )->Width( ) );
	m_pProgressBar->SetVisible( true );
	m_anmProgress.SetDuration(0.15);
	m_anmProgress.SetStartValue( startScale );
	m_anmProgress.SetEndValue( 2.0f );
	m_anmProgress.Start( );   */ 
}
void VpmElement::OnUpSignal( const VwEmptySignalArgs& oArgs )
{
	//m_pDeep->SetVisible( false );
}
VpmElementView* VpmElement::CreateView() const
{
	return new VpmElementView;
}
//VtrFontManager::GetInstance()->GetDefaultFont()
void VpmElement::SetImage( VistaTexture* image )
{
	m_bLoadImage = image != nullptr;
	VglwTexturedPlaneView* background = dynamic_cast< VglwTexturedPlaneView* >( m_pImage->GetView() );

	background->SetBackgroundFocusTexture( image );
	background->SetBackgroundPressedTexture( image );
	background->SetBackgroundTexture( image );
	OnVisibilityChanged(VwEmptySignalArgs(this));
	
}
void VpmElement::LayoutElement()
{
	float fTotalWidth = GetModel()->Width();
	float fTotalHeight = GetModel()->Height();
	float fBorder = m_pBorder->GetModel()->BorderSize();

	float fWidth = fTotalWidth - ( 2 * fBorder );
	fWidth = fWidth <= 0 ? 0.001f : fWidth;
	float fHeight = fTotalHeight - ( 2 * fBorder );
	fHeight = fHeight <= 0 ? 0.001f : fHeight;

	float secondElementSpace = NeedSecondElement() ? GetModel()->SecondElementSpace() : 0.0f;
	float fImageWidth = VpmGlobalConfiguration::Left_X_Padding;
	float fImageSize = VpmGlobalConfiguration::Left_X_Padding < fHeight ? VpmGlobalConfiguration::Left_X_Padding : fHeight;
	float fSymbolWidth = VpmGlobalConfiguration::Right_X_Padding;
	float fLabelWidth = fWidth - secondElementSpace - VpmGlobalConfiguration::Left_X_Padding - VpmGlobalConfiguration::Right_X_Padding;
	fLabelWidth = fLabelWidth <= 0 ? 0.001f : fLabelWidth;
	float fLabelHeight = fHeight*0.3f;

	VistaVector3D vCenter = GetModel( )->Position( );
	VistaQuaternion qOrientation = GetModel( )->Orientation( );
	VistaVector3D v3Postiton( fWidth / 2.0f, -fHeight / 2.0f, 0.0f );
	v3Postiton = vCenter - qOrientation.Rotate( v3Postiton );


	VistaVector3D progressPosition( 0, 0, 0.0001f );
	progressPosition = qOrientation.Rotate( progressPosition );
	progressPosition += vCenter;

	VistaVector3D DeepPosition( 0, 0, 0.0003f );
	DeepPosition = qOrientation.Rotate( DeepPosition );
	DeepPosition += vCenter;

	VistaVector3D imagePostion( fBorder + (fImageWidth/2.0f), -fHeight / 2.0f, 0.0004f );
	imagePostion = qOrientation.Rotate( imagePostion );
	imagePostion += v3Postiton;

	VistaVector3D labelPostion( fBorder + fImageWidth, -fBorder+((-fHeight-fLabelHeight)/2.0f), 0.0004f );
	labelPostion = qOrientation.Rotate( labelPostion );
	labelPostion += v3Postiton;

	VistaVector3D buttonPosition( fBorder + fImageWidth + fLabelWidth + ( secondElementSpace/2.0f ), -fHeight / 2.0f, 0.0004f );
	buttonPosition = qOrientation.Rotate( buttonPosition );
	buttonPosition += v3Postiton;

	VistaVector3D symbolPosition( fBorder + fImageWidth + fLabelWidth +secondElementSpace, ( -fHeight - fLabelHeight ) / 2.0f - fBorder, 0.0004f );
	symbolPosition = qOrientation.Rotate( symbolPosition );
	symbolPosition += v3Postiton;

	m_pBorder->GetModel( )->Position.Set( vCenter );
	m_pBorder->GetModel( )->Height.Set( fHeight );
	m_pBorder->GetModel( )->Width.Set( fWidth );
	m_pBorder->GetModel( )->Orientation.Set( qOrientation );
	m_pBorder->GetModel( )->BorderSize.Set( fBorder );

	m_pImage->GetModel( )->Position.Set( imagePostion );
	m_pImage->GetModel( )->Height.Set( fImageSize  );
	m_pImage->GetModel( )->Width.Set( fImageSize  );
	m_pImage->GetModel( )->Orientation.Set( qOrientation );

	m_pLabel->GetModel( )->Position.Set( labelPostion );
	m_pLabel->GetModel( )->Height.Set( fLabelHeight );
	m_pLabel->GetModel( )->Orientation.Set( qOrientation );

	m_pSymbolOfSubMenu->GetModel( )->Position.Set( symbolPosition );
	m_pSymbolOfSubMenu->GetModel( )->Height.Set( fLabelHeight );
	m_pSymbolOfSubMenu->GetModel( )->Orientation.Set( qOrientation );


	m_pDeep->GetModel( )->Position.Set( DeepPosition );
	//m_pProgressBar->GetModel( )->Height.Set( fHeight );
	//m_pProgressBar->GetModel()->Width.Set( fWidth );
	m_pDeep->GetModel( )->Orientation.Set( qOrientation );

	m_pProgressBar->GetModel( )->Position.Set( progressPosition );
	//m_pProgressBar->GetModel( )->Height.Set( fHeight );
	//m_pProgressBar->GetModel()->Width.Set( fWidth );
	m_pProgressBar->GetModel( )->Orientation.Set( qOrientation );

	LayoutSecondElement( qOrientation, buttonPosition );

	float textWidth = m_pLabel->GetModel( )->GetTextWidth( );
	std::string tmpLabel = m_strLabel;
	m_pLabel->GetModel( )->Text.Set( tmpLabel );
	while( textWidth > fLabelWidth &&tmpLabel.size( ) > 0 )
	{
		tmpLabel = tmpLabel.substr( 0, tmpLabel.size( ) - 1 );
		m_pLabel->GetModel( )->Text.Set( tmpLabel );
		textWidth = m_pLabel->GetModel( )->GetTextWidth( );
	}

}
VwEmptySignal& VpmElement::GetElementDownSignal()
{
	return m_sigElementDown;
}
void VpmElement::OnValueChanged(const VwIntChangedSignalArgs& oArgs)
{

}
void VpmElement::OnPositionChanged(const VwVectorChangedSignalArgs& oArgs)
{
	GetView()->SetPosition(oArgs.GetNewValue());
	LayoutElement();

}
void VpmElement::OnHieghtChanged(const VwFloatChangedSignalArgs& oArgs)
{ 
	GetView()->SetLength(oArgs.GetNewValue());
	LayoutElement();
}
void VpmElement::OnWidthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	GetView()->SetWidth(oArgs.GetNewValue());
	LayoutElement();
}
void VpmElement::OnBorderChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutElement();
}
void VpmElement::OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	GetView()->SetOrientation(oArgs.GetNewValue());
	LayoutElement();
}
void VpmElement::OnLabelChanged(const VwStringChangedSignalArgs& oArgs)
{
	m_strLabel = oArgs.GetNewValue();
	m_pLabel->GetModel()->Text.Set(VtrString( oArgs.GetNewValue()));

}
void VpmElement::AddSubMenu()
{
	m_pSymbolOfSubMenu->GetModel( )->Text.Set( VtrString( VpmGlobalConfiguration::SymbolOfSubMenu ) );
	m_pSymbolOfSubMenu->SetVisible( GetVisible() );
	m_bHasSubMenu = true;
	LayoutElement();
}
void VpmElement::RemoveSubMenu()
{
	m_pSymbolOfSubMenu->GetModel()->Text.Set( VtrString( "" ) );
	m_pSymbolOfSubMenu->SetVisible( false );
	m_bHasSubMenu = false;
	LayoutElement( );

}
void VpmElement::OnElementDown(const VwEmptySignalArgs& oArgs)
{
	if( GetVisible() == false )return;

	
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>( m_pBackground->GetView( ) );
	m_pBorder->GetView()->GetBackgroundView()->SetPressedColor( VpmGlobalConfiguration::PressedColor );
	pBackgroundView->SetPressedColor( VpmGlobalConfiguration::PressedColor );

	VwEmptySignalArgs oDownArgs( this );
	m_sigElementDown.Raise( oDownArgs );

	//GetModel()->Value.Set(GetModel()->Value() == 1 ? 0 : 1);
}


void VpmElement::OnEnabledChanged( const VwBoolChangedSignalArgs& oArgs )
{
	m_pLabel->SetEnabled( oArgs.GetNewValue() );
	m_pImage->SetEnabled( oArgs.GetNewValue() );
	m_pBackground->SetEnabled( oArgs.GetNewValue() );
	m_pBorder->SetEnabled( oArgs.GetNewValue() );
}

void VpmElement::OnVisibilityChanged( const VwEmptySignalArgs& oArgs )
{
	if( GetVisible() )
	{
		m_pLabel->SetVisible( GetLablelVisibility() );
		m_pBorder->SetVisible( true );
		m_pImage->SetVisible( GetImageVisibility() );
		m_pSymbolOfSubMenu->SetVisible( m_bHasSubMenu );

		m_pBackground->SetVisible( true);

	}
	else
	{
		m_pLabel->SetVisible( false );
		m_pBorder->SetVisible( false );
		m_pImage->SetVisible( false );
		m_pSymbolOfSubMenu->SetVisible( false );
		m_pBackground->SetVisible( false );
	}
	m_pProgressBar->SetVisible( false );
	m_pDeep->SetVisible( false );
}
void VpmElement::OnChildClicked( VwWidget*child )
{

}
bool VpmElement::GetByHandle_Rec( VwWidget*widget, const VwFocusHandle* clickHandle, VwWidget**childwidget )
{
	for( VwFocusHandle* handle : widget->GetFocusHandles() )
	{
		// priority of click is higher than focus 
		if( handle == clickHandle &&  this->GetInteractionMode( ) > INTERACTION_FOCUSABLE )
		{
			*childwidget = widget;
			return true;
		}
	}
	//check child of widget handle
	for( VwWidget* child : widget->GetChildWidgets() )
	{
		if( dynamic_cast< VpmPullDownMenu* >( child ) == NULL )
		{

			bool b = GetByHandle_Rec( child, clickHandle, childwidget );
			if( b )
			{
				VpmElement*element = dynamic_cast< VpmElement* >( widget );
				if( element )
				{

				}
				return true;
			}
		}
	}
	return false;
}
void VpmElement::ButtonDown( VwWidget *child)
{
	if( GetVisible() == false )return;


	VwColoredPlaneView* pBackgroundView = dynamic_cast< VwColoredPlaneView* >( m_pBackground->GetView() );
	m_pBorder->GetView()->GetBackgroundView()->SetPressedColor( VpmGlobalConfiguration::PressedColor );
	pBackgroundView->SetPressedColor( VpmGlobalConfiguration::PressedColor );

	VwEmptySignalArgs oDownArgs( this );
	m_sigElementDown.Raise( oDownArgs );
	////GetModel()->Value.Set(GetModel()->Value() == 1 ? 0 : 1);

}
void VpmElement::ButtonUp( VwWidget *child )
{

}
bool VpmElement::GetByHandle( const VwFocusHandle* handle, VwWidget**childwidget )
{
	return GetByHandle_Rec( this, handle,  childwidget );
}
bool VpmElement::Click_Recursive( VwWidget*widget,const VwFocusHandle* clickHandle )
{
//	if( )
	{
		//check cuurent of widget handle
		for( VwFocusHandle* handle :widget-> GetFocusHandles() )
		{
			// priority of click is higher than focus 
			if( handle == clickHandle &&  this->GetInteractionMode( ) > INTERACTION_FOCUSABLE )
			{
				return true;
			}
		}
		//check child of widget handle
		for( VwWidget* child : widget->GetChildWidgets( ) )
		{
			if( dynamic_cast< VpmPullDownMenu* >( child ) == NULL )
			{

				bool b = Click_Recursive( child, clickHandle );
				if( b )
				{
					VpmElement* element = dynamic_cast< VpmElement* >( widget );
					if( element != NULL )
					{
						element->OnChildClicked( child );
					}
					return true;
				}
			}
		}
		return false;
	}
}
bool VpmElement::Click(const VwFocusHandle* handle )
{
	//if( m_pSelectInputSlot )
	{
		if( Click_Recursive(this,handle ))
		{
			VwEmptySignalArgs oArgs( this );
			OnElementDown( oArgs );
			return true;
		}
		return false;
	}

}
void VpmElement::SetProgressVissibilityOn( )
{
	if( GetVisible() && GetFocused() )
	{
		m_pDeep->SetVisible( false );
		//pDepepth = false;

		//m_pProgressBar->SetVisible(true);
	}
}
void VpmElement::SetProgressVisisbilityOff( )
{
	if( GetVisible( ) && GetFocused( ) )
	{
		m_pDeep->SetVisible( true );
		//pDepepth = true;
		m_pProgressBar->SetVisible( false );
	}
}
void VpmElement::ProgressValue( float  value )
{
	if( GetVisible() && GetFocused() )
	{
		this->SetProgressValue( value );
	}
}


void VpmElement::DeepValue( float  value )
{
	if( GetVisible( ) && GetFocused( ))
	{
		this->SetDeepValue( value );
	}
}

void VpmElement::SetDeepValue( float DeepValue )
{
	//m_pDeep->SetVisible( true );
	m_pDeep->GetModel( )->Width.Set( DeepValue * GetModel( )->Width( ) );

}
void VpmElement::SetProgressValue( float ProgressValue )
{
	//m_pProgressBar->SetVisible( true );
	m_pProgressBar->GetModel()->Width.Set( ProgressValue * GetModel()->Width() );
}

bool VpmElement::GetImageVisibility(  )
{
	return VpmGlobalConfiguration::Left_X_Padding > 0 && m_bLoadImage;
}
void VpmElement::SetLabelVisibility(bool bLabelVisibile)
{
	m_pLabel->SetVisible(false);
}

void VpmElement::OnFocusGained( const VwEmptySignalArgs& oArgs )
{
  m_pProgressBar->SetVisible( GetVisible() && VpmGlobalConfiguration::ShowProgressBar );
  m_pDeep->SetVisible( false );
}
void VpmElement::OnFocusLost(const VwEmptySignalArgs& oArgs)
{
	m_pProgressBar->SetVisible( false );
	m_pDeep->SetVisible( false );
}

VpmElement::Model::Model():
Label( "" ),
Height( VpmGlobalConfiguration::MenuHeight ),
Position( Vista::ZeroVector ),
Width( VpmGlobalConfiguration::MenuWidth ),
SecondElementSpace( VpmGlobalConfiguration::MenuWidth*VpmGlobalConfiguration::SecondaryElementWidthPercent ),
Enabled( true ),
Value( 0 ),
Font( VtrFontManager::GetInstance()->GetDefaultFont() ),
SymbolFont(VpmGlobalConfiguration::GetSymbolFont()),
Border( VpmGlobalConfiguration::BorderSize )

{

}
