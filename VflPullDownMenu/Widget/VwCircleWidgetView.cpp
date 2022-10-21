

#include"VwCircleWidgetView.h"


#include <VistaKernel/VistaSystem.h>
#include <VistaKernel/GraphicsManager/VistaGraphicsManager.h>
#include <VistaKernel/GraphicsManager/VistaSceneGraph.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernel/GraphicsManager/VistaGeomNode.h>
#include <VistaKernel/GraphicsManager/VistaGeometryFactory.h>

#include <cassert>

VwCircleWidgetView::VwCircleWidgetView(
	float fRadius, float fBorder ,
	const VistaColor& oDisabledColor,
	const VistaColor& oColor,
	const VistaColor& oFocusColor,
	const VistaColor& oPressedColor)
	: m_oColor(oColor)
	, m_fBorderSize(fBorder)
	, m_oFocusColor(oFocusColor)
	, m_oDisabledColor(oDisabledColor)
	, m_oPressedColor(oPressedColor)
	, m_fRadius(fRadius)
	, m_bIsFocused(false)
	, m_bChecked(false )
	, m_eState(IVwWidgetView::VIEW_STATE_ENABLED)
{

	m_pBorderCircle = nullptr;
	m_pBorderGeometryNode = nullptr;
	m_pBorderTransformNode = nullptr;

	m_pInnerCircle = nullptr;
	m_pInnerGeometryNode = nullptr;
	m_pInnerTransformNode = nullptr;

	m_pSymbolCircle = nullptr;
	m_pSymbolGeometryNode = nullptr;
	m_pSymbolTransformNode = nullptr;

	CreateNewCircleSet();
}

void VwCircleWidgetView::CreateNewCircleSet()
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
	
	m_pBorderCircle = oGeometryFactory.CreateDisk(m_fRadius, 1024, 1, Vista::Z, m_oColor);
	m_pBorderGeometryNode = pSG->NewGeomNode(m_pBorderTransformNode, m_pBorderCircle);

	m_pInnerCircle = oGeometryFactory.CreateDisk(m_fRadius - m_fBorderSize, 1024,1, Vista::Z, m_oColor);	
	m_pInnerGeometryNode = pSG->NewGeomNode( m_pInnerTransformNode, m_pInnerCircle );

	m_pSymbolCircle = oGeometryFactory.CreateDisk(m_fRadius *0.6f, 16, 1, Vista::Z, m_oColor);
	m_pSymbolGeometryNode = pSG->NewGeomNode(m_pSymbolTransformNode, m_pSymbolCircle);

	
	SetCurrentColor();
}

VwCircleWidgetView::~VwCircleWidgetView()
{
	delete m_pInnerGeometryNode;
	delete m_pInnerTransformNode;

	delete m_pBorderGeometryNode;
	delete m_pBorderTransformNode;

	delete m_pSymbolGeometryNode;
	delete m_pSymbolTransformNode;

}


void VwCircleWidgetView::Update()
{

}

VistaVector3D VwCircleWidgetView::GetPosition() const
{
	VistaVector3D v3Position;
	m_pBorderTransformNode->GetTranslation(v3Position);
	return v3Position;
}

void VwCircleWidgetView::SetPosition(const VistaVector3D &value)
{
VistaVector3D newPos = VistaVector3D( value[0] + 0, value[1] + 0, value[2] + 0.0001f );
VistaVector3D newPos1 = VistaVector3D( value[0] + 0, value[1] + 0, value[2] + 0.0001f * 2 );

	m_pBorderTransformNode->SetTranslation(value);
	m_pSymbolTransformNode->SetTranslation(newPos1);
	m_pInnerTransformNode->SetTranslation(newPos);
}

VistaQuaternion VwCircleWidgetView::GetOrientation() const
{
	VistaQuaternion qOrientation;
	m_pBorderTransformNode->GetRotation(qOrientation);
	return qOrientation;
}

void VwCircleWidgetView::SetOrientation(const VistaQuaternion& value)
{
	m_pBorderTransformNode->SetRotation(value);
	m_pSymbolTransformNode->SetRotation(value);
	m_pInnerTransformNode->SetRotation(value);
}
float VwCircleWidgetView::GetRadius() const
{
	return m_fRadius;
}

void VwCircleWidgetView::SetRadius(float value)
{
	assert(value>0);
	m_fRadius = value;
	bool bVisible = GetVisible();
	CreateNewCircleSet();
	SetVisible(bVisible);
}


float VwCircleWidgetView::GetBorder() const
{
	return m_fBorderSize;
}

void VwCircleWidgetView::SetBorder(float value)
{
	//assert(value>0);
	m_fBorderSize = value;
	bool bVisible = GetVisible();
	CreateNewCircleSet();
	SetVisible(bVisible);
}

VistaColor VwCircleWidgetView::GetDisabledColor() const
{
	return m_oDisabledColor;
}

void VwCircleWidgetView::SetDisabledColor(const VistaColor& value)
{
	m_oDisabledColor = value;
	SetCurrentColor();
}

VistaColor VwCircleWidgetView::GetColor() const
{
	return m_oColor;
}

void VwCircleWidgetView::SetColor(const VistaColor& value)
{
	m_oColor = value;
	SetCurrentColor();
}

VistaColor VwCircleWidgetView::GetFocusColor() const
{
	return m_oFocusColor;
}

void VwCircleWidgetView::SetFocusColor(const VistaColor& value)
{
	m_oFocusColor = value;
	SetCurrentColor();
}

VistaColor VwCircleWidgetView::GetPressedColor() const
{
	return m_oPressedColor;
}

void VwCircleWidgetView::SetChecked(bool checked)
{
	m_bChecked = checked;
	SetVisible(GetVisible());
}
bool VwCircleWidgetView::GetChecked()
{
	return m_bChecked;
}

void VwCircleWidgetView::SetPressedColor(const VistaColor& value)
{
	m_oPressedColor = value;
	SetCurrentColor();
}

void VwCircleWidgetView::SetCurrentColor()
{
	switch (m_eState)
	{
	case VwCircleWidgetView::VIEW_STATE_DISABLED:
	{
													m_pBorderCircle->SetColor(m_oDisabledColor);
													m_pSymbolCircle->SetColor(m_oDisabledColor);
													m_pInnerCircle->SetColor(VistaColor(1 - m_oDisabledColor.GetRed(), 1 - m_oDisabledColor.GetGreen(), 1 - m_oDisabledColor.GetBlue()));
													break;
	}
	case VwCircleWidgetView::VIEW_STATE_ENABLED:
	{
												   m_pBorderCircle->SetColor(m_oColor);
												   m_pSymbolCircle->SetColor(m_oColor);
												   m_pInnerCircle->SetColor(VistaColor(1 - m_oColor.GetRed(), 1 - m_oColor.GetGreen(), 1 - m_oColor.GetBlue()));
												   break;
	}
	case VwCircleWidgetView::VIEW_STATE_FOCUSED:
	{
												   m_pBorderCircle->SetColor(m_oFocusColor);
												   m_pSymbolCircle->SetColor(m_oFocusColor);

												   m_pInnerCircle->SetColor(VistaColor(1 - m_oFocusColor.GetRed(), 1 - m_oFocusColor.GetGreen(), 1 - m_oFocusColor.GetBlue()));
												   break;
	}
	case VwCircleWidgetView::VIEW_STATE_PRESSED:
	{
												   m_pBorderCircle->SetColor(m_oPressedColor);
												   m_pSymbolCircle->SetColor(m_oPressedColor);

												   m_pInnerCircle->SetColor(VistaColor(1 - m_oPressedColor.GetRed(), 1 - m_oPressedColor.GetGreen(), 1 - m_oPressedColor.GetBlue()));
												   break;
	}
	default:
	{
			   assert(false);
			   break;
	}
	}
}

bool VwCircleWidgetView::GetVisible() const
{
	return m_pBorderGeometryNode->GetIsEnabled();
}

void VwCircleWidgetView::SetVisible(bool value)
{
	m_pBorderGeometryNode->SetIsEnabled(value);
	m_pInnerGeometryNode->SetIsEnabled(value);
	m_pSymbolGeometryNode->SetIsEnabled(value&m_bChecked);
}

int VwCircleWidgetView::GetState() const
{
	return m_eState;
}

void VwCircleWidgetView::SetState(int eState)
{
	assert(eState >= VwCircleWidgetView::VIEW_STATE_DISABLED && eState < VwCircleWidgetView::VIEW_STATE_LAST);
	m_eState = eState;
	SetCurrentColor();
}

VistaBoundingBox VwCircleWidgetView::GetBoundingBox() const
{
	return m_pBorderGeometryNode->GetBoundingBox();
}



