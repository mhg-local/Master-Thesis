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
 * $Id: VwLineWidget.h 42923 2014-07-08 12:24:00Z tp483634 $
 */
#ifndef _VGLW_INTERVAL_SELECTION_WIDGET_H
#define _VGLW_INTERVAL_SELECTION_WIDGET_H
/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/

#include "VwScalerWidgetView.h"

#include <VistaWidgets/VwExchangeableViewWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/VwField.h>

#include <VistaWidgets/Widgets/Views/VwEmptyView.h>
#include <VistaWidgets/SignalSystem/Signals/VwSignals.h>
#include <VistaWidgets/SignalSystem/Signals/VwConstraintSignals.h>

#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>
/*============================================================================*/
/* MACROS AND DEFINES                                                         */
/*============================================================================*/

/*============================================================================*/
/* FORWARD DECLARATIONS                                                       */
/*============================================================================*/
class VwPlaneWidget;
class VglwTexturedPlaneView;
class VglwDynamicTextWidget;
class VglwDynamicTextView;
class VwScalerWidgetView;

class VtrFont;
/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/
class  VwScalerWidget : public VwExchangeableViewWidget<IVwWidgetView, VwScalerWidgetView>
{
public:

	VwScalerWidget();
	virtual ~VwScalerWidget();

	virtual void Init();

	typedef VwScalerWidgetView View;

	class  Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model();
		VwField<float> LowerBound;
		VwField<float> UpperBound;
		VwField<float> fLeftConstraint;
		VwField<float> fRightConsraint;
		VwField<float> BoundDelta;
		
		/** 
		 * MinValue/MaxValue specify the value range.
		 * The Lower- and UpperBound can be mapped to values
		 * within the value range using the GetSelectedInterval()-method.
		 */
		VwField<float> MinValue;
		VwField<float> MaxValue;

		VwField<VtrFont*> Font;
		VwField<float> TextSize;
		VwField<std::string> Unit;
		/**
		 * The Precision defines the number of positions after decimal point
		 * in the text-labels for the minimal/maximal-values.
		 */
		VwField<unsigned int> Precision;
		
		/**
		 * The Length and Width of the VwScalerWidget
		 * See VglwIntervalSelectionView for more infos
		 */
		VwField<float> Length;
		VwField<float> Width;

		VwField<VistaVector3D> Position;
		VwField<VistaQuaternion> Orientation;
	
	};

	virtual Model* GetModel() const;
	virtual VwScalerWidgetView* GetView() const override;

	bool GetIsFocused() const;
	bool GetIsDragging() const;
	
	VglwTexturedPlaneView* GetLeftHandleView();
	VglwTexturedPlaneView* GetRightHandleView();
		
	VglwDynamicTextView* GetMinTextLabelView();
	VglwDynamicTextView* GetMaxTextLabelView();

protected:
	virtual Model* CreateModel() const;
	virtual VwScalerWidgetView* CreateView() const override;
	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);
	virtual void OnButtonDown( const VwEmptySignalArgs& oArgs );
	
private:
	void InitHandle();

	void InitTextLabel();
	void InitSlots();

	void UpdateHanldeSize();
	void UpdateTextLabelSize();
	void UpdateHandlePositions();
	void UpdateHandlePositions(VwPlaneWidget* pHandle,float fValue);

	void UpdateLabelText();
    void UpdateTextLabelPosition();
	float HandlePositionToValue( const VistaVector3D& v3Pos);
	VistaVector3D ValueToHandlePosition( float fValue);
		
	void LeftHandleConstraint( VwVectorConstraintSignalArgs& oArgs );
	void RightHandleConstraint( VwVectorConstraintSignalArgs& oArgs );
	void OnRightHandlePositionChanged(const VwVectorChangedSignalArgs& oArgs);
	void OnLeftHandlePositionChanged(const VwVectorChangedSignalArgs& oArgs);

	void OnBoundCheck();
	void OnIntervalLowerBoundChanged(const VwFloatChangedSignalArgs& oArgs);
	void OnIntervalUpperBoundChanged(const VwFloatChangedSignalArgs& oArgs);
	void OnValueRangeChanged( const VwFloatChangedSignalArgs& oArgs );
	void OnUnitChanged( const VwStringChangedSignalArgs& oArgs );
	void OnFontChanged( const VwChangedFromToSignalArgs< VtrFont* >& oArgs );
	void OnTextSizeChanged( const VwFloatChangedSignalArgs& oArgs );
	void OnPrecisionChanged( const VwChangedFromToSignalArgs < unsigned int >& oArgs );
	void OnLengthChanged( const VwFloatChangedSignalArgs& oArgs );
	void OnWidthChanged( const VwFloatChangedSignalArgs& oArgs );
	void OnBoundDeltaChanged(const VwFloatChangedSignalArgs& oArgs);
	void OnPositionChanged( const VwVectorChangedSignalArgs& oArgs );
	void OnOrientationChanged( const VwQuaternionChangedSignalArgs& oArgs );
	void OnMinRangeChanged(const VwFloatChangedSignalArgs& oArgs);
	void OnMaxRangeChanged(const VwFloatChangedSignalArgs& oArgs);
	void OnVisibilityChanged( const VwEmptySignalArgs& oArgs );
private:
	std::array<VistaTexture*,6>	m_apTextures;
	VwPlaneWidget*	m_pLeftHandle;
	VwPlaneWidget*	m_pRightHandle;

	VglwDynamicTextWidget* m_pMinText;
	VglwDynamicTextWidget* m_pMaxText;
};
#endif // _VWLineWIDGET_H
