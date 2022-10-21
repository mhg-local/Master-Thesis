

#include"VwCheckBoxWidgetView.h"


#include <VistaKernel/VistaSystem.h>
#include <VistaKernel/GraphicsManager/VistaGraphicsManager.h>
#include <VistaKernel/GraphicsManager/VistaSceneGraph.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernel/GraphicsManager/VistaGeomNode.h>
#include <VistaKernel/GraphicsManager/VistaGeometryFactory.h>

#include <cassert>

VwCheckBoxWidgetView::VwCheckBoxWidgetView(
	float fWidth,float fHeight, float fBorder,
	const VistaColor& oDisabledColor,
	const VistaColor& oColor,
	const VistaColor& oFocusColor,
	const VistaColor& oPressedColor)
	: m_oColor(oColor)
	, m_fBorderSize(fBorder)
	, m_oFocusColor(oFocusColor)
	, m_oDisabledColor(oDisabledColor)
	, m_oPressedColor(oPressedColor)
	, m_fWidth(fWidth)
	, m_fHeight(fHeight)
	, m_bIsFocused(false)
	, m_eState(IVwWidgetView::VIEW_STATE_ENABLED)
{

	m_pBorderRect = nullptr;
	m_pBorderGeometryNode = nullptr;
	m_pBorderTransformNode = nullptr;

	m_pInnerRect = nullptr;
	m_pInnerGeometryNode = nullptr;
	m_pInnerTransformNode = nullptr;

	m_pSymbolRect = nullptr;
	m_pSymbolGeometryNode = nullptr;
	m_pSymbolTransformNode = nullptr;

	CreateNewRectSet();
}

void VwCheckBoxWidgetView::CreateNewRectSet()
{
	VistaSceneGraph* pSG = GetVistaSystem()->GetGraphicsManager()->GetSceneGraph();
	VistaGeometryFactory oGeometryFactory(pSG);

	if (m_pBorderGeometryNode != nullptr)
	{
		pSG->DeleteLeaf(m_pBorderGeometryNode);
		m_pBorderGeometryNode = nullptr;

		pSG->DeleteLeaf(m_pInnerGeometryNode);
		m_pInnerGeometryNode = nullptr;

		pSG->DeleteLeaf(m_pSymbolGeometryNode);
		m_pSymbolGeometryNode = nullptr;
	}
	if (m_pBorderTransformNode == nullptr)
	{
		m_pBorderTransformNode = pSG->NewTransformNode(pSG->GetRoot());
		m_pInnerTransformNode = pSG->NewTransformNode(pSG->GetRoot());
		m_pSymbolTransformNode = pSG->NewTransformNode(pSG->GetRoot());
	}
	auto localWitdh = m_fWidth < 2 * m_fBorderSize ? (m_fBorderSize * 2 + 0.001f) : m_fWidth;


	m_pBorderRect = oGeometryFactory.CreatePlane( localWitdh, localWitdh, 1, 1, Vista::Z, m_oColor );
	m_pBorderGeometryNode = pSG->NewGeomNode(m_pBorderTransformNode, m_pBorderRect);

	m_pInnerRect = oGeometryFactory.CreatePlane( localWitdh - ( 2 * m_fBorderSize ), localWitdh - ( 2 * m_fBorderSize ), 1, 1, Vista::Z, m_oColor );
	m_pInnerGeometryNode = pSG->NewGeomNode( m_pInnerTransformNode, m_pInnerRect );

	m_pSymbolRect = oGeometryFactory.CreatePlane( localWitdh*0.6f, localWitdh *0.6f, 1, 1, Vista::Z, m_oColor );
	m_pSymbolGeometryNode = pSG->NewGeomNode(m_pSymbolTransformNode, m_pSymbolRect);

	SetCurrentColor();
	//SetVisible();
}

VwCheckBoxWidgetView::~VwCheckBoxWidgetView()
{
	delete m_pInnerGeometryNode;
	delete m_pInnerTransformNode;

	delete m_pBorderGeometryNode;
	delete m_pBorderTransformNode;

	delete m_pSymbolGeometryNode;
	delete m_pSymbolTransformNode;

}


void VwCheckBoxWidgetView::Update()
{

}

VistaVector3D VwCheckBoxWidgetView::GetPosition() const
{
	VistaVector3D v3Position;
	m_pBorderTransformNode->GetTranslation(v3Position);
	return v3Position;
}

void VwCheckBoxWidgetView::SetPosition( const VistaVector3D &value )
	{
	VistaVector3D newPos = VistaVector3D( value[0] + 0, value[1] + 0, value[2] + 0.0001f );
	VistaVector3D newPos1 = VistaVector3D( value[0] + 0, value[1] + 0, value[2] + 0.0001f*2 );

	m_pInnerTransformNode->SetTranslation( newPos );
	m_pBorderTransformNode->SetTranslation( value );
	m_pSymbolTransformNode->SetTranslation( newPos1 );

	}

VistaQuaternion VwCheckBoxWidgetView::GetOrientation() const
{
	VistaQuaternion qOrientation;
	m_pBorderTransformNode->GetRotation(qOrientation);
	return qOrientation;
}

void VwCheckBoxWidgetView::SetOrientation(const VistaQuaternion& value)
{
	m_pBorderTransformNode->SetRotation(value);
	m_pSymbolTransformNode->SetRotation(value);
	m_pInnerTransformNode->SetRotation(value);
}
float VwCheckBoxWidgetView::GetWidth() const
{
	return m_fWidth;
}

void VwCheckBoxWidgetView::SetWidth(float value)
{
	assert(value > 0);
	bool bVisible = GetVisible();
	m_fWidth = value;
	CreateNewRectSet();
	SetVisible(bVisible);
}
float VwCheckBoxWidgetView::GetHeight() const
{
	return m_fHeight;
}

void VwCheckBoxWidgetView::SetHeight(float value)
{
	assert(value > 0);
	bool bVisible = GetVisible();
	m_fHeight = value;
	CreateNewRectSet();
	SetVisible(bVisible);
}

float VwCheckBoxWidgetView::GetBorder() const
{
	return m_fBorderSize;
}

void VwCheckBoxWidgetView::SetBorder(float value)
{
	//assert(value>0);
	bool bVisible = GetVisible();
	m_fBorderSize = value;
	CreateNewRectSet();
	SetVisible(bVisible);
}

VistaColor VwCheckBoxWidgetView::GetDisabledColor() const
{
	return m_oDisabledColor;
}

void VwCheckBoxWidgetView::SetDisabledColor(const VistaColor& value)
{
	m_oDisabledColor = value;
	SetCurrentColor();
}

VistaColor VwCheckBoxWidgetView::GetColor() const
{
	return m_oColor;
}

void VwCheckBoxWidgetView::SetColor(const VistaColor& value)
{
	m_oColor = value;
	SetCurrentColor();
}

VistaColor VwCheckBoxWidgetView::GetFocusColor() const
{
	return m_oFocusColor;
}

void VwCheckBoxWidgetView::SetFocusColor(const VistaColor& value)
{
	m_oFocusColor = value;
	SetCurrentColor();
}

VistaColor VwCheckBoxWidgetView::GetPressedColor() const
{
	return m_oPressedColor;
}

void VwCheckBoxWidgetView::SetChecked(bool checked)
{
	m_bChecked = checked;
	SetVisible(GetVisible());
}
bool VwCheckBoxWidgetView::GetChecked()
{
	return m_bChecked;
}

void VwCheckBoxWidgetView::SetPressedColor(const VistaColor& value)
{
	m_oPressedColor = value;
	SetCurrentColor();
}

void VwCheckBoxWidgetView::SetCurrentColor()
{
	switch (m_eState)
	{
	case VwCheckBoxWidgetView::VIEW_STATE_DISABLED:
	{
													m_pBorderRect->SetColor(m_oDisabledColor);
													m_pSymbolRect->SetColor(m_oDisabledColor);
													m_pInnerRect->SetColor(VistaColor(1 - m_oDisabledColor.GetRed(), 1 - m_oDisabledColor.GetGreen(), 1 - m_oDisabledColor.GetBlue()));
													break;
	}
	case VwCheckBoxWidgetView::VIEW_STATE_ENABLED:
	{
												   m_pBorderRect->SetColor(m_oColor);
												   m_pSymbolRect->SetColor(m_oColor);
												   m_pInnerRect->SetColor(VistaColor(1 - m_oColor.GetRed(), 1 - m_oColor.GetGreen(), 1 - m_oColor.GetBlue()));
												   break;
	}
	case VwCheckBoxWidgetView::VIEW_STATE_FOCUSED:
	{
												   m_pBorderRect->SetColor(m_oFocusColor);
												   m_pSymbolRect->SetColor(m_oFocusColor);

												   m_pInnerRect->SetColor(VistaColor(1 - m_oFocusColor.GetRed(), 1 - m_oFocusColor.GetGreen(), 1 - m_oFocusColor.GetBlue()));
												   break;
	}
	case VwCheckBoxWidgetView::VIEW_STATE_PRESSED:
	{
												   m_pBorderRect->SetColor(m_oPressedColor);
												   m_pSymbolRect->SetColor(m_oPressedColor);

												   m_pInnerRect->SetColor(VistaColor(1 - m_oPressedColor.GetRed(), 1 - m_oPressedColor.GetGreen(), 1 - m_oPressedColor.GetBlue()));
												   break;
	}
	default:
	{
			   assert(false);
			   break;
	}
	}
}

bool VwCheckBoxWidgetView::GetVisible() const
{
return m_pInnerGeometryNode->GetIsEnabled( );
}

void VwCheckBoxWidgetView::SetVisible(bool value)
{
	m_pBorderGeometryNode->SetIsEnabled(value);
	m_pInnerGeometryNode->SetIsEnabled(value);
	m_pSymbolGeometryNode->SetIsEnabled(value&m_bChecked);
}

int VwCheckBoxWidgetView::GetState() const
{
	return m_eState;
}

void VwCheckBoxWidgetView::SetState(int eState)
{
	assert(eState >= VwCheckBoxWidgetView::VIEW_STATE_DISABLED && eState < VwCheckBoxWidgetView::VIEW_STATE_LAST);
	m_eState = eState;
	SetCurrentColor();
}

VistaBoundingBox VwCheckBoxWidgetView::GetBoundingBox() const
{
	return m_pBorderGeometryNode->GetBoundingBox();
}



