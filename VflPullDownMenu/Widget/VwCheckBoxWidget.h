#pragma once
#include "../VglConfig.h"

#include "VwCheckBoxWidgetView.h"

#include <VistaWidgets/VwInputSlot.h>
#include <VistaWidgets/VwExchangeableViewWidget.h>
#include <VistaWidgets/VwWidgetModel.h>
#include <VistaWidgets/SignalSystem/Signals/VwDraggableSignal.h>
#include <VistaWidgets/SignalSystem/Signals/VwSignals.h>
#include <VistaWidgets/VwField.h>

#include <VistaBase/VistaColor.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>

class IVwFocusHandleAspect;
class IVwCenterFocusHandleAspect;
class IVwPlaneFocusHandleAspect;

class VwFocusable;
class VwClickable;

class VwFocusHandle;
class VwVirtualDevice;

class VwSignalSource;
class IVwDraggingConstraint;
/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/
class VGLWAPI VwCheckBoxWidget
	: public VwWidget
{
public:
	VwCheckBoxWidget();
	virtual ~VwCheckBoxWidget();

	virtual void Init();

	class VGLWAPI Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model();

		VwField<VistaVector3D> Position;
		VwField<VistaQuaternion> Orientation;

		VwField<float> Width;
		VwField<float> Height;
		VwField<float> Border;

		VwField<int> Value;
	};

	virtual Model* GetModel() const;
	virtual VwCheckBoxWidgetView* GetView() const;
protected:
	virtual Model* CreateModel() const;
	virtual VwCheckBoxWidgetView* CreateView() const;
protected:
	virtual void OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs);
	virtual void OnPositionChanged(const VwVectorChangedSignalArgs& oArgs);

	virtual void OnWidthChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnHeightChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnBorderChanged(const VwFloatChangedSignalArgs& oArgs);

	virtual void OnValueChanged(const VwIntChangedSignalArgs& oArgs);

	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);

	virtual void OnButtonDown(const VwEmptySignalArgs& oArgs);
	virtual void OnButtonUp(const VwEmptySignalArgs& oArgs);

private:
	VwFocusHandle*					m_pFocusHandle;
	IVwPlaneFocusHandleAspect*		m_pPlaneFocusHandleAspect;
	IVwCenterFocusHandleAspect*		m_pPositionFocusHandleAspect;

};
