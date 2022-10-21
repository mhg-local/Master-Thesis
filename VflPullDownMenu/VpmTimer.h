#pragma once
#include"VglConfig.h"
#include"VpmGlobalConfiguration.h"
#include <VistaWidgets\VwField.h>
#include <VistaWidgets\VwWidget.h>
#include <VistaWidgets\VwWidgetModel.h>
#include <VistaWidgets\SignalSystem\Signals\VwConstraintSignals.h>
#include<vector>
#include"VpmAnimation.h"
class VwPlaneWidget;


class VGLWAPI VpmTimer:public VwWidget {
	public:
	VpmTimer();
	~VpmTimer( );
	virtual void HandleEvent( VistaEvent *pEvent );
	void Init();
	void UpdateTimer( );
	VwEmptySignal& GetTimerSignal()	{return m_timerSignal;}
	
	void StartTime( );
	void StopTime();
	void SetTimePeriod( int period )
	{
		m_timerPeriod = period;
	}
	protected :
	virtual IVwWidgetModel* CreateModel() const
	{
		return nullptr;
	}
	virtual IVwWidgetView* CreateView() const
	{
		return nullptr;
	}
	private:
	VwEmptySignal m_timerSignal;

	int m_timerPeriod;
	double m_lastFire = 0;
	bool m_bEnable;
};