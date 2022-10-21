/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :                               RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  KERNEL                       RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  ViSTA                          Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2013   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*
* $Id: TexturedQuadView.cpp 42467 2014-06-10 12:32:13Z tp483634 $
*/

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/
#include "GL/glew.h"

#include "VwScalerWidgetView.h"

#include <VistaKernel/VistaSystem.h>
#include <VistaKernel/GraphicsManager/VistaGraphicsManager.h>
#include <VistaKernel/GraphicsManager/VistaSceneGraph.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernel/GraphicsManager/VistaOpenGLDraw.h>
#include <VistaKernel/GraphicsManager/VistaOpenGLNode.h>

#include <VistaOGLExt/VistaTexture.h>
#include <VistaOGLExt/VistaOGLUtils.h>

#include <cassert>
/*============================================================================*/
/* MACROS AND DEFINES, CONSTANTS AND STATICS, FUNCTION-PROTOTYPES             */
/*============================================================================*/
class IntervalSelectionDraw : public IVistaOpenGLDraw
{
public:
	IntervalSelectionDraw(VwScalerWidgetView* pView)
		: m_pView(pView)
	{}

	bool Do() override
	{
		m_pView->Draw();
		return true;
	}

	bool GetBoundingBox(VistaBoundingBox &bb) override
	{
		return false;
	}


private:
	VwScalerWidgetView* m_pView;
};

/*============================================================================*/
/* CONSTRUCTORS / DESTRUCTOR                                                  */
/*============================================================================*/
VwScalerWidgetView::VwScalerWidgetView()
: m_pTransformNode(nullptr)
, m_pOpenGLNode(nullptr)
, m_pDrawCalback(nullptr)
, m_fLength(.15f)
, m_fWidth(0.01f)
, m_eState(IVwWidgetView::VIEW_STATE_ENABLED)
{
	VistaSceneGraph* pSG = GetVistaSystem()->GetGraphicsManager()->GetSceneGraph();

	m_pTransformNode = pSG->NewTransformNode(pSG->GetRoot());
	m_pDrawCalback   = new IntervalSelectionDraw( this );
	
	m_pOpenGLNode = pSG->NewOpenGLNode(m_pTransformNode, m_pDrawCalback);

	std::fill(m_apTextures.begin(), m_apTextures.end(), nullptr);

	std::fill(m_abHasTextureOwnership.begin(), m_abHasTextureOwnership.end(), false);

	m_aoColors = {VistaColor::GRAY, VistaColor::GRAY};
 	m_afInterval = {0.0f, 1.0f};
}

VwScalerWidgetView::~VwScalerWidgetView()
{
	delete m_pOpenGLNode;
	delete m_pTransformNode;
}

void VwScalerWidgetView::Update()
{

}

const VistaVector3D VwScalerWidgetView::GetPosition() const
{
	VistaVector3D value; 
	m_pTransformNode->GetTranslation(value);
	return value;
}

bool VwScalerWidgetView::SetPosition(const VistaVector3D &value)
{
	return m_pTransformNode->SetTranslation(value);
}

void VwScalerWidgetView::SetLowerBound(float f)
{
	m_fLowerBound=f;
}
void VwScalerWidgetView::SetUpperBound(float f)
{
	m_fUpperBound=f;
}

bool VwScalerWidgetView::SetTextPosition(const VistaVector3D &value)
{
	return m_pTransformNode->SetTranslation(value);
}
VistaQuaternion VwScalerWidgetView::GetOrientation() const
{
	VistaQuaternion qOrientation;
	m_pTransformNode->GetRotation(qOrientation);
	return qOrientation;
}

bool VwScalerWidgetView::SetOrientation(const VistaQuaternion& qOrientation)
{
	return m_pTransformNode->SetRotation(qOrientation);
}

void VwScalerWidgetView::SetPrecision(float f)
{
	m_fPrecision=f;
}

void VwScalerWidgetView::SetLength(float f)
{
	m_fLength = f;
}

void VwScalerWidgetView::SetTextSize(float f)
{
	m_fTextSize=f;
}
void VwScalerWidgetView::SetFont(VtrFont* f)
{
	m_fFont=f;
}
void VwScalerWidgetView::SetWidth(float f)
{
	m_fWidth = f;
}
void VwScalerWidgetView::SetBoundDelta(float f)
{
	m_fBoundDelta=f;
}
void VwScalerWidgetView::SetIntervalMin(float f)
{
	m_afInterval[0] = f-0.5f;
}
void VwScalerWidgetView::SetIntervalMax(float f)
{
	m_afInterval[1]=f+0.5f;
}

void VwScalerWidgetView::SetSliderColor(const VistaColor& rColor)
{
	m_aoColors[1] = rColor;
}
void VwScalerWidgetView::SetBackgroundColor(const VistaColor& rColor)
{
	m_aoColors[0] = rColor;
}

void VwScalerWidgetView::SetSliderLeftTexture(const std::string& strTexture)
{
	SetTexture(0, LoadTexture(strTexture), true);
}
void VwScalerWidgetView::SetSliderRightTexture(const std::string& strTexture)
{
	SetTexture(1, LoadTexture(strTexture), true);
}
void VwScalerWidgetView::SetSliderCenterTexture(const std::string& strTexture)
{
	SetTexture(2, LoadTexture(strTexture), true);
}
void VwScalerWidgetView::SetBackgroundLeftTexture(const std::string& strTexture)
{
	SetTexture(3, LoadTexture(strTexture), true);
}
void VwScalerWidgetView::SetBackgroundRightTexture(const std::string& strTexture)
{
	SetTexture(4, LoadTexture(strTexture), true);
}
void VwScalerWidgetView::SetBackgroundCenterTexture(const std::string& strTexture)
{
	SetTexture(5, LoadTexture(strTexture), true);
}

void VwScalerWidgetView::SetSliderLeftTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(0, pTexture, bTakeOnership);
}
void VwScalerWidgetView::SetSliderRightTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(1, pTexture, bTakeOnership);
}
void VwScalerWidgetView::SetSliderCenterTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(2, pTexture, bTakeOnership);
}
void VwScalerWidgetView::SetBackgroundLeftTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(3, pTexture, bTakeOnership);
}
void VwScalerWidgetView::SetBackgroundRightTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(4, pTexture, bTakeOnership);
}
void VwScalerWidgetView::SetBackgroundCenterTexture(VistaTexture* pTexture, bool bTakeOnership)
{
	SetTexture(5, pTexture, bTakeOnership);
}

bool VwScalerWidgetView::GetVisible() const
{
	return m_pOpenGLNode->GetIsEnabled();
}

void VwScalerWidgetView::SetVisible(bool bIsVisible)
{
	m_pOpenGLNode->SetIsEnabled(bIsVisible);
}

int VwScalerWidgetView::GetState() const
{
	return m_eState;
}

void VwScalerWidgetView::SetState(int eState)
{
	if(!(eState >= IVwWidgetView::VIEW_STATE_DISABLED && eState < IVwWidgetView::VIEW_STATE_LAST ))
	{
		throw std::invalid_argument(
			"eState must be in ["
			+ std::to_string(IVwWidgetView::VIEW_STATE_DISABLED)
			+ ";"
			+ std::to_string(IVwWidgetView::VIEW_STATE_LAST)
			+ ")"
			);
	}
	m_eState = eState;
}

VistaBoundingBox VwScalerWidgetView::GetBoundingBox() const
{
	return m_pOpenGLNode->GetBoundingBox();
}

void VwScalerWidgetView::Draw()
 {
// 
// 	VistaOGLUtils::CheckForOGLError(__FILE__,__LINE__);
	if( GetVisible() ==false)return;
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glColor4fv(&m_aoColors[0][0]);
		
	
	DrawQuad(m_apTextures[0],-0.5f*m_fLength-0.5f*m_fWidth,-0.5f*m_fLength,-0.0001f);
	DrawQuad(m_apTextures[1],+0.5f*m_fLength,+0.5f*m_fLength+0.5f*m_fWidth,-0.0001f);
	DrawQuad(m_apTextures[2],-0.5f*m_fLength,+0.5f*m_fLength,-0.0001f);
	
	glColor4fv(&m_aoColors[1][0]);
	
	DrawQuad(m_apTextures[3], 
		m_fLength*(m_afInterval[0] - 0.5f) - 0.5f*m_fWidth,
		m_fLength*(m_afInterval[0] - 0.5f),
		0.0001f);
	DrawQuad(m_apTextures[4],
		m_fLength*(m_afInterval[1] - 0.5f), 
		m_fLength*(m_afInterval[1] - 0.5f) + 0.5f*m_fWidth, 
		0.0001f);
	DrawQuad(m_apTextures[5], 
		m_fLength*(m_afInterval[0] - 0.5f), 
		m_fLength*(m_afInterval[1] - 0.5f), 
		0.0001f);

/*	VistaOGLUtils::CheckForOGLError(__FILE__,__LINE__);*/

	glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);
	
		glColor3f(1.0f, 1.0f, 1.0f);
		glColor4fv(&m_aoColors[0][0]);
		
	
		DrawQuad(m_apTextures[0],-0.5f*m_fLength-0.5f*m_fWidth,-0.5f*m_fLength,-0.0001f);
		DrawQuad(m_apTextures[1],+0.5f*m_fLength,+0.5f*m_fLength+0.5f*m_fWidth,-0.0001f);
		DrawQuad(m_apTextures[2],-0.5f*m_fLength,+0.5f*m_fLength,-0.0001f);
	
		glColor4fv(&m_aoColors[1][0]);
	
		DrawQuad(m_apTextures[3], 
			m_fLength*(m_afInterval[0] - 0.5f) - 0.5f*m_fWidth,
			m_fLength*(m_afInterval[0] - 0.5f),
			0.0001f);
		DrawQuad(m_apTextures[4],
			m_fLength*(m_afInterval[1] - 0.5f), 
			m_fLength*(m_afInterval[1] - 0.5f) + 0.5f*m_fWidth, 
			0.0001f);
		DrawQuad(m_apTextures[5], 
			m_fLength*(m_afInterval[0] - 0.5f), 
			m_fLength*(m_afInterval[1] - 0.5f), 
			0.0001f);

}

void VwScalerWidgetView::DrawQuad(VistaTexture* pTexture, float fMin, float fMax, float fZ )
{
	if (pTexture)
	{
		pTexture->Enable();
		pTexture->Bind();
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fMin, -0.5f*m_fWidth, fZ);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fMin, +0.5f*m_fWidth, fZ);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fMax, +0.5f*m_fWidth, fZ);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fMax, -0.5f*m_fWidth, fZ);
	glEnd();

	if (pTexture)
	{
		pTexture->Unbind();
		pTexture->Disable();
	}
}

VistaTexture* VwScalerWidgetView::LoadTexture(const std::string& strTexture)
{
	VistaTexture* pTexture = VistaOGLUtils::LoadTextureFromTga(strTexture);

	if (pTexture)
	{
		pTexture->Bind();
		pTexture->SetWrapS(GL_CLAMP_TO_EDGE);
		pTexture->SetWrapT(GL_CLAMP_TO_EDGE);
		pTexture->SetMagFilter(GL_LINEAR_MIPMAP_LINEAR);
		pTexture->SetMinFilter(GL_LINEAR);
		pTexture->Unbind();
	}

	return pTexture;
}
void VwScalerWidgetView::SetTexture(int iIndex, VistaTexture* pTexture, bool bTakeOnership)
{
	if (m_abHasTextureOwnership[iIndex])
		delete m_apTextures[iIndex];

	m_apTextures[iIndex]            = pTexture;
	m_abHasTextureOwnership[iIndex] = bTakeOnership;
}

/*============================================================================*/
/*  END OF FILE "TexturedQuadView.cpp"									      */
/*============================================================================*/
