/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      Header   :                               RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :                               RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :                                 Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2013   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*                                                                            */
/*    THIS SOFTWARE IS PROVIDED 'AS IS'. ANY WARRANTIES ARE DISCLAIMED. IN    */
/*    NO CASE SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DAMAGES.    */
/*    REDISTRIBUTION AND USE OF THE NON MODIFIED TOOLKIT IS PERMITTED. OWN    */
/*    DEVELOPMENTS BASED ON THIS TOOLKIT MUST BE CLEARLY DECLARED AS SUCH.    */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/*      CLASS DEFINITIONS:                                                    */
/*                                                                            */
/*        - ...               :   ...                                         */
/*                                                                            */
/*============================================================================*/
/*
 * $Id: VwLineView.h 42467 2014-06-10 12:32:13Z tp483634 $
 */
#ifndef _VGLW_INTERVAL_SELECTION_VIEW_H
#define _VGLW_INTERVAL_SELECTION_VIEW_H
/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/

#include <VistaWidgets/VwWidgetView.h>

#include <VistaBase/VistaColor.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>

#include <array>
/*============================================================================*/
/* MACROS AND DEFINES                                                         */
/*============================================================================*/

/*============================================================================*/
/* FORWARD DECLARATIONS                                                       */
/*============================================================================*/
class VistaTransformNode;
class VistaOpenGLNode;
class VistaTexture;
class IntervalSelectionDraw;
class VtrFont;
/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/

/**
 * Background:
 *               Width/2          Length           Width/2
 *                _/\_   ___________/\___________   _/\_
 *               /    \ /                        \ /    \
 *	       ,-   +------+--------------------------+------+
 *	      |     |      |                          |      |
 *	      |     | Left-|                          |Right-|
 * Width <      | tex- |      CenterTexture       | tex- |
 *        |     | ture |                          | ture |
 *        |     |      |                          |      |
 *         `-   +------+--------------------------+------+
 *              
 * Slider:
 *                  Width/2    Length*(Max-Min)   Width/2
 *                    _/\_   ________/\_________   _/\_
 *                   /    \ /                   \ /    \
 *	       ,-       +------+---------------------+------+
 *	      |         |      |                     |      |
 *	      |         | Left-|                     |Right-|
 * Width <          | tex- |    CenterTexture    | tex- |
 *        |         | ture |                     | ture |
 *        |         |      |                     |      |
 *         `-       +------+---------------------+------+  
 */
class VwScalerWidgetView : public IVwWidgetView// @TODO: use most narrow Interface
{
public:
	enum
	{
		VIEW_STATE_LAST = IVwWidgetView::VIEW_STATE_LAST
	};
	VwScalerWidgetView();
	virtual ~VwScalerWidgetView();

	virtual void Update();

	const VistaVector3D GetPosition() const;
	bool SetPosition(const VistaVector3D &value);
	void SetLowerBound(float f);
	void SetUpperBound(float f);
	bool SetTextPosition(const VistaVector3D &value);

	VistaQuaternion GetOrientation() const;
	bool SetOrientation(const VistaQuaternion& qOrientation);

	void SetLength(float f);
	void SetWidth(float f);
	void SetBoundDelta(float f);
	void SetIntervalMin(float f);
	void SetIntervalMax(float f);
	void SetPrecision(float f);
	void SetTextSize(float f);
	void SetFont(VtrFont* f);

	void SetSliderColor(const VistaColor& rColor);
	void SetBackgroundColor(const VistaColor& rColor);

	void SetSliderLeftTexture(const std::string& strTexture);
	void SetSliderRightTexture(const std::string& strTexture);
	void SetSliderCenterTexture(const std::string& strTexture);
	void SetBackgroundLeftTexture(const std::string& strTexture);
	void SetBackgroundRightTexture(const std::string& strTexture);
	void SetBackgroundCenterTexture(const std::string& strTexture);

	void SetSliderLeftTexture(VistaTexture*, bool bTakeOnership = false);
	void SetSliderRightTexture(VistaTexture*, bool bTakeOnership = false);
	void SetSliderCenterTexture(VistaTexture*, bool bTakeOnership = false);
	void SetBackgroundLeftTexture(VistaTexture*, bool bTakeOnership = false);
	void SetBackgroundRightTexture(VistaTexture*, bool bTakeOnership = false);
	void SetBackgroundCenterTexture(VistaTexture*, bool bTakeOnership = false);

	virtual int GetState() const;
	virtual void SetState(int eState);

	/**
	 * @copydoc	IVwWidgetView::GetIsVisible()
	 */
	virtual bool GetVisible() const;
	/**
	 * @copydoc	IVwWidgetView::SetIsVisible(bool)
	 */
	virtual void SetVisible(bool bIsVisible);
	/**
	 * @copydoc IVwWidgetView::GetBoundingBox()
	 */
	virtual VistaBoundingBox GetBoundingBox() const;

	void Draw();

private:
	void DrawQuad(VistaTexture* pTexture, float fMin, float fMax, float fZ);

	VistaTexture* LoadTexture(const std::string& strTexture);
	void SetTexture( int iIndex, VistaTexture* pTexture, bool bTakeOnership );

private:
	VistaTransformNode*		m_pTransformNode;
	VistaOpenGLNode*		m_pOpenGLNode;
	IntervalSelectionDraw*	m_pDrawCalback;

	std::array<VistaColor, 2>		m_aoColors;

	std::array<VistaTexture*, 6>	m_apTextures;
	std::array<bool, 6>				m_abHasTextureOwnership;

	float m_fLength;
	float m_fPrecision;
	float m_fWidth;
	float m_fTextSize;
	float m_fLowerBound;
	float m_fUpperBound;
	float m_fBoundDelta;
	
	VtrFont* m_fFont;
	std::array<float, 2>	m_afInterval;

	int m_eState;
};

/*============================================================================*/
/* LOCAL VARS AND FUNCS                                                       */
/*============================================================================*/

/*============================================================================*/
/* END OF FILE "VwLineView.h"                                                 */
/*============================================================================*/

#endif // _VWLINEVIEW_H