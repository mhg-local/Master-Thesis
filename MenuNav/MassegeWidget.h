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
#ifndef _VGLW_MassegeWidget_H
#define _VGLW_MassegeWidget_H
/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/



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
class  MassegeWidget: public VwExchangeableViewWidget<IVwWidgetView>
{
public:

MassegeWidget( );
virtual ~MassegeWidget( );

	virtual void Init();

	typedef VwScalerWidgetView View;

	class  Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model();
		
	
	};

	virtual Model* GetModel() const;


protected:
	virtual Model* CreateModel() const;
	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);

private:
	void InitMassegeBox();
	virtual void OnButtonDown( const VwEmptySignalArgs& oArgs );
	void SetVisibilityChanged( bool VisibilityChanged );
private:

	
	VwPlaneWidget*	m_MassegeBox;
	VwPlaneWidget*	m_MassegeButton;

	VglwDynamicTextWidget* m_MassegeBoxText;
	VglwDynamicTextWidget* m_MassegeButtonText;
	clock_t   Time;

};
#endif // _VWLineWIDGET_H
