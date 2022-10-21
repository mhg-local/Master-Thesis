#include"VwBorderWidget.h"

#include <VistaWidgets/Widgets/VwPlaneWidget.h>
#include<VistaWidgets\Widgets\VwLineWidget.h>
#include"VwWidgetControl.h"
VwBorderWidget::VwBorderWidget()
{
	m_pEsetLine = NULL;
	m_pWestLine = NULL;
	m_pSouthLine = NULL;
	m_pNorthLine = NULL;
	m_pInternalWidget = NULL;
	m_pBackground = NULL;
}

VwBorderWidget::~VwBorderWidget()
{
	delete m_pEsetLine;
	delete m_pNorthLine;
	delete m_pSouthLine;
	delete m_pWestLine;
	delete m_pBackground;
	delete m_pInternalWidget;
}


void VwBorderWidget::Init(VwWidgetControl* control)
{
	VwWidget::Init();


	m_pInternalWidget = control;
	m_pBackground = new VwPlaneWidget();
	m_pBackground->Init();
	VwColoredPlaneView* pBackgroundView = dynamic_cast<VwColoredPlaneView*>(m_pBackground->GetView());
	m_pBackground->GetModel()->Height.Set(1);
	m_pBackground->GetModel()->Width.Set(1);
	pBackgroundView->SetColor(VistaColor(255, 255, 255, 255));
	
	m_pBackground->SetInteractionMode(INTERACTION_CLICKABLE);
	
	GetModel()->BorderSize.GetSignal().AddSlot(this, &VwBorderWidget::OnBorderSizeChanged);
	GetModel()->Width.GetSignal().AddSlot(this, &VwBorderWidget::OnWidthChanged);
	GetModel()->Height.GetSignal().AddSlot(this, &VwBorderWidget::OnHeightChanged);
	GetModel()->Position.GetSignal().AddSlot(this, &VwBorderWidget::OnPositionChanged);
	GetModel()->Orientation.GetSignal().AddSlot(this, &VwBorderWidget::OnOrientionChanged);
	//this->GetVisibilityChangedSignal().AddSlot(this, &VpmElement::OnVisibilityChanged);

	//m_pBackground->GetClickable( )->GetClickedSignal( ).AddSlot( this, &VwBorderWidget::OnElementDown );

	m_pBackground->AddWidget(control->GetWidget());

	GetView()->SetBackgroundView(pBackgroundView);

	AddWidget(m_pBackground);


	m_pEsetLine = new VwLineWidget();
	m_pEsetLine->Init();
	m_pEsetLine->SetInteractionMode( VwWidget::INTERACTION_NONE );
	((VwLineView*)m_pEsetLine->GetView())->SetColor(VistaColor(0, 0, 0, 0));
	m_pBackground->AddWidget(m_pEsetLine);

	m_pNorthLine = new VwLineWidget();
	m_pNorthLine->Init();
	m_pNorthLine->SetInteractionMode( VwWidget::INTERACTION_NONE );
	((VwLineView*)m_pNorthLine->GetView())->SetColor(VistaColor(0, 0, 0, 0));
	m_pBackground->AddWidget(m_pNorthLine);
	
	m_pWestLine = new VwLineWidget();
	m_pWestLine->Init();
	m_pWestLine->SetInteractionMode( VwWidget::INTERACTION_NONE );
	((VwLineView*)m_pWestLine->GetView())->SetColor(VistaColor(0, 0, 0, 0));
	m_pBackground->AddWidget(m_pWestLine);
	
	
	m_pSouthLine = new VwLineWidget();
	m_pSouthLine->Init();
	m_pSouthLine->SetInteractionMode( VwWidget::INTERACTION_NONE );
	((VwLineView*)m_pSouthLine->GetView())->SetColor(VistaColor(0, 0, 0, 0));
	m_pBackground->AddWidget(m_pSouthLine);


	GetVisibilityChangedSignal().AddSlot(this, &VwBorderWidget::OnVisibilityChanged);
	LayoutBorderWidget();
}


void VwBorderWidget::OnVisibilityChanged(const VwEmptySignalArgs& oArgs)
{
	if (GetVisible())
	{
		/*m_pInternalWidget->GetWidget()->SetVisible(true);
		m_pBackground->SetVisible(true);*/
		m_pEsetLine->SetVisible(true);
		m_pWestLine->SetVisible(true);
		m_pNorthLine->SetVisible(true);
		m_pSouthLine->SetVisible(true);
	}
	else
	{
	/*	m_pInternalWidget->GetWidget()->SetVisible(false);
		m_pBackground->SetVisible(false);*/
		m_pEsetLine->SetVisible(false);
		m_pWestLine->SetVisible(false);
		m_pNorthLine->SetVisible(false);
		m_pSouthLine->SetVisible(false);
	}
	
}
VwWidget* VwBorderWidget::GetWidget() const
{
	return m_pInternalWidget->GetWidget();
}
VwBorderWidget::Model* VwBorderWidget::CreateModel() const
{
	return new VwBorderWidget::Model;
}
VwBorderView* VwBorderWidget::CreateView() const
{
	return new VwBorderView;
}


VwBorderWidget::Model* VwBorderWidget::GetModel() const
{
	return static_cast<VwBorderWidget::Model*>(VwWidget::GetModel());
}
VwBorderView* VwBorderWidget::GetView() const
{

	return static_cast<VwBorderView*>(VwWidget::GetView());
}

void VwBorderWidget::LayoutBorderWidget()
{
	float width = GetModel()->Width();
	float height = GetModel()->Height();
	float borderSize = GetModel()->BorderSize();

	float fInternalWidth = width - (borderSize * 2);
	float fInternalHeight = height - (borderSize * 2);

	VistaVector3D vCenter = GetModel()->Position();
	VistaQuaternion qOrientation = GetModel()->Orientation();

	VistaVector3D v3Position(width/2, height/2, 0.0f);
	v3Position= vCenter - qOrientation.Rotate(v3Position);

	VistaVector3D internalPostition( 0, 0, 0.0002f );
	internalPostition = vCenter - qOrientation.Rotate(internalPostition);


	VistaVector3D vNWPos( 0, 0, 0.0001f );
	vNWPos = v3Position + qOrientation.Rotate(vNWPos);

	VistaVector3D vNEPos( width, 0, 0.0001f );
	vNEPos = v3Position + qOrientation.Rotate(vNEPos);

	VistaVector3D vSEPos( width, height, 0.0001f );
	vSEPos = v3Position + qOrientation.Rotate(vSEPos);

	VistaVector3D vSWPos( 0, height, 0.0001f );
	vSWPos = v3Position + qOrientation.Rotate(vSWPos);

	m_pInternalWidget->SetPosition(internalPostition);
	m_pInternalWidget->SetWidth(fInternalWidth);
	m_pInternalWidget->SetHeight(fInternalHeight);
	m_pInternalWidget->SetOrientation(qOrientation);

	//correct it
	m_pEsetLine->GetModel()->Width.Set(borderSize);
	m_pEsetLine->GetModel()->EndPoint.Set(vSEPos);
	m_pEsetLine->GetModel()->StartPoint.Set(vNEPos);
	
	//m_pEsetLine->GetModel()->Orientation.Set(qOrientation);

	m_pWestLine->GetModel()->Width.Set(borderSize);
	m_pWestLine->GetModel()->StartPoint.Set(vSWPos);
	m_pWestLine->GetModel()->EndPoint.Set(vNWPos);
	//m_pWestLine->GetModel()->Orientation.Set(qOrientation);

	m_pNorthLine->GetModel()->Width.Set(borderSize);
	m_pNorthLine->GetModel()->StartPoint.Set(vNWPos);
	m_pNorthLine->GetModel()->EndPoint.Set(vNEPos);
	//m_pNorthLine->GetModel()->Orientation.Set(qOrientation);

	m_pSouthLine->GetModel()->Width.Set(borderSize);
	m_pSouthLine->GetModel()->StartPoint.Set(vSEPos);
	m_pSouthLine->GetModel()->EndPoint.Set(vSWPos);
	//m_pSouthLine->GetModel()->Orientation.Set(qOrientation);

	m_pBackground->GetModel()->Position.Set(internalPostition-VistaVector3D(0,0,0.001f));
	m_pBackground->GetModel()->Width.Set(width);
	m_pBackground->GetModel()->Height.Set(height);
	m_pBackground->GetModel()->Orientation.Set(qOrientation);
}

//VwEmptySignal&  VwBorderWidget::GetFocusGainedSignal() {
//	return m_pBackground->GetFocusable()->GetFocusGainedSignal();
//}
//VwEmptySignal&  VwBorderWidget::GetFocusLostSignal() {
//	return m_pBackground->GetFocusable()->GetFocusLostSignal();
//}
//VwEmptySignal&  VwBorderWidget::GetButtonDownSignal() {
//	return m_pBackground->GetClickable()->GetButtonDownSignal();// GetButtonDownSignal();
//}
//VwEmptySignal&  VwBorderWidget::GetButtonUpSignal() {
//	return m_pBackground->GetClickable()->GetButtonUpSignal();// GetButtonUpSignal();
//}
VwEmptySignal&  VwBorderWidget::FocusGainedSignal( )
{
	return m_pBackground->GetFocusable( )->GetFocusGainedSignal( );
}
VwEmptySignal&  VwBorderWidget::FocusLostSignal( )
{
	return m_pBackground->GetFocusable( )->GetFocusLostSignal( );
}
VwEmptySignal&  VwBorderWidget::ButtonDownSignal( )
{
	return m_pBackground->GetClickable( )->GetButtonDownSignal( );// GetButtonDownSignal();
}
VwEmptySignal&  VwBorderWidget::ButtonUpSignal( )
{
	return m_pBackground->GetClickable( )->GetButtonUpSignal( );// GetButtonUpSignal();
}
VwEmptySignal&  VwBorderWidget::GetButtonClickedSignal(){

	return m_pBackground->GetClickable()->GetClickedSignal(); //  GetClickedSignal();
}

void VwBorderWidget::OnPositionChanged(const VwVectorChangedSignalArgs&oARgs)
{
	LayoutBorderWidget();
}
void VwBorderWidget::OnBorderSizeChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutBorderWidget();
}
void VwBorderWidget::OnOrientionChanged(const VwQuaternionChangedSignalArgs& oArgs)
{
	LayoutBorderWidget();
}
void VwBorderWidget::OnWidthChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutBorderWidget();
}
void VwBorderWidget::OnHeightChanged(const VwFloatChangedSignalArgs& oArgs)
{
	LayoutBorderWidget();
}
VwBorderWidget::Model::Model():
	Position(Vista::ZeroVector),
	Width(.01f),
	Height(0.01f),
	BorderSize(.0001f)
{
}


