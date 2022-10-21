
#pragma once

#include"../VglConfig.h"
#include <VistaOpenGLWidgets\Widgets\Views\VglwTexturedPlaneView.h>

#include <VistaWidgets\VwInputSlot.h>
#include <VistaWidgets\VwExchangeableViewWidget.h>
#include  <VistaWidgets\VwWidgetModel.h>
#include  <VistaWidgets\SignalSystem\Signals\VwDraggableSignal.h>
#include  <VistaWidgets\SignalSystem\Signals\VwSignals.h>
#include  <VistaWidgets\SignalSystem\Signals\VwEmptySignal.h>
#include  <VistaWidgets\VwField.h>

#include <VistaBase/VistaColor.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>
class IVwFocusHandleAspect;
class IVwCenterFocusHandleAspect;
class IVwPlaneFocusHandleAspect;

class VwFocusHandle;
class VwVirtualDevice;
class VGLWAPI VwTexturePlaneWidget :
	public VwExchangeableViewWidget<IVwWidgetView, VglwTexturedPlaneView>
{
public:
	VwTexturePlaneWidget();
	virtual ~VwTexturePlaneWidget();

	virtual void Init();

	typedef VglwTexturedPlaneView View;
	class VGLWAPI Model : public IVwWidgetModel
	{
	public:
		Model();
		virtual ~Model();

		VwField<VistaVector3D> Position;
		VwField<VistaQuaternion> Orientation;

		VwField<float> Width;
		VwField<float> Height;
	private:

	};

	virtual Model* GetModel() const;
	virtual View* GetView() const;

	virtual void Disable();
	virtual void Enable();

protected:
	virtual Model* CreateModel() const;
	virtual View* CreateView() const;

protected:
	virtual void OnOrientationChanged(const VwQuaternionChangedSignalArgs& oArgs);
	virtual void OnPositionChanged(const VwVectorChangedSignalArgs& oArgs);

	virtual void OnWidthChanged(const VwFloatChangedSignalArgs& oArgs);
	virtual void OnHeightChanged(const VwFloatChangedSignalArgs& oArgs);

	virtual void OnFocusGained(const VwEmptySignalArgs& oArgs);
	virtual void OnFocusLost(const VwEmptySignalArgs& oArgs);

	virtual void OnButtonDown(const VwEmptySignalArgs& oArgs);
	virtual void OnButtonUp(const VwEmptySignalArgs& oArgs);

	virtual void OnDragging(const VwDraggableSignalArgs& oArgs);

	void SetViewState(int eViewState);

private:
	VwFocusHandle*					m_pFocusHandle;

	IVwPlaneFocusHandleAspect*	m_pPlaneFocusHandleAspect;
	IVwCenterFocusHandleAspect*	m_pPositionFocusHandleAspect;
};
