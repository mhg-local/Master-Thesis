#pragma once
#include "../VglConfig.h"

#include "VwCircleWidgetView.h"

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
class IVwRadiusFocusHandleAspect;

class VwFocusable;
class VwClickable;

class VwFocusHandle;
class VwVirtualDevice;

class VwSignalSource;
class IVwDraggingConstraint;
/*============================================================================*/
/* CLASS DEFINITIONS                                                          */
/*============================================================================*/
class VGLWAPI VwCircleWidget
	: public VwWidget
{
public:
	VwCircleWidget();
	virtual ~VwCircleWidget();

	virtual void Init();

	class VGLWAPI Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model();

		VwField<VistaVector3D> Position;
		VwField<VistaQuaternion> Orientation;

		VwField<float> Radius;
		VwField<float> Border;

		VwField<int> Value;
	};

	virtual Model* GetModel() const;
	virtual VwCircleWidgetView* GetView() const;
protected:
	virtual Model* CreateModel() const;
	virtual VwCircleWidgetView* CreateView() const;
protected:
	virtual void OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs);
	virtual void OnPositionChanged(const VwVectorChangedSignalArgs& oArgs);

	virtual void OnRadiusChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnBorderChanged(const VwFloatChangedSignalArgs& oArgs);

	virtual void OnValueChanged(const VwIntChangedSignalArgs& oArgs);

	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);

	virtual void OnButtonDown(const VwEmptySignalArgs& oArgs);
	virtual void OnButtonUp(const VwEmptySignalArgs& oArgs);

private:
	VwFocusHandle*					m_pFocusHandle;

	IVwRadiusFocusHandleAspect*	m_pRadiusFocusHandleAspect;
	IVwCenterFocusHandleAspect*	m_pPositionFocusHandleAspect;

};
