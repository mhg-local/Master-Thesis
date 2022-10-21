#pragma once

#include"../VglConfig.h"

#include<VistaWidgets\VwWidgetView.h>

#include <VistaBase/VistaColor.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>


class VistaTransformNode;
class VistaGeomNode;
class VistaGeometry;

class VGLWAPI VwCircleWidgetView :public IVwWidgetView
{
public:
	VwCircleWidgetView::VwCircleWidgetView(	float fRadius=0.25f,float fBorder=0.001f,
		const VistaColor& oDisabledColor = VistaColor::GRAY,
		const VistaColor& oColor = VistaColor::BLACK,
		const VistaColor& oFocusColor = VistaColor::BLUE,
		const VistaColor& oPressedColor = VistaColor::DARK_GREEN);
	virtual ~VwCircleWidgetView();

	enum
	{
		VIEW_STATE_LAST = IVwWidgetView::VIEW_STATE_LAST
	};

	virtual void Update();

	VistaVector3D GetPosition() const;
	void SetPosition(const VistaVector3D& value);

	VistaQuaternion GetOrientation() const;
	void SetOrientation(const VistaQuaternion& value);

	float GetRadius() const;
	void SetRadius(float value);


	float GetBorder() const;
	void SetBorder(float value);
	VistaColor GetDisabledColor() const;
	void SetDisabledColor(const VistaColor& value);

	VistaColor GetColor() const;
	void SetColor(const VistaColor& value);

	VistaColor GetFocusColor() const;
	void SetFocusColor(const VistaColor& value);

	VistaColor GetPressedColor() const;
	void SetPressedColor(const VistaColor& value);

	void SetChecked(bool checked);
	bool GetChecked();

	virtual int GetState() const;
	virtual void SetState(int eState);


	virtual bool GetVisible() const;
	virtual void SetVisible(bool value);
	virtual VistaBoundingBox GetBoundingBox() const;
protected:
	void SetCurrentColor();
private:

	void CreateNewCircleSet();

	VistaTransformNode*		m_pBorderTransformNode;
	VistaGeomNode*			m_pBorderGeometryNode;
	VistaGeometry*			m_pBorderCircle;

	VistaTransformNode*		m_pInnerTransformNode;
	VistaGeomNode*			m_pInnerGeometryNode;
	VistaGeometry*			m_pInnerCircle;

	VistaTransformNode*		m_pSymbolTransformNode;
	VistaGeomNode*			m_pSymbolGeometryNode;
	VistaGeometry*			m_pSymbolCircle;

	float					m_fRadius;
	float					m_fBorderSize;
	VistaColor				m_oDisabledColor;
	VistaColor				m_oColor;
	VistaColor				m_oFocusColor;
	VistaColor				m_oPressedColor;
	bool					m_bIsFocused;
	int						m_eState;

	bool                    m_bChecked;



};


