#include "VpmTimer.h"


VpmTimer::VpmTimer( )
{

	m_bEnable = false;
	m_timerPeriod = 10000;
}


VpmTimer::~VpmTimer( )
{}

void VpmTimer::HandleEvent( VistaEvent *pEvent )
{
	UpdateTimer( );
}
void VpmTimer::UpdateTimer()
{
	if( m_bEnable )
	{
		if( ( VpmGlobalConfiguration::GetTime() - m_lastFire ) / 1000 >= m_timerPeriod )
		{
			VwEmptySignalArgs args( this );
			m_timerSignal.Raise(  args );
			m_lastFire = VpmGlobalConfiguration::GetTime();
	}
	}
}
void VpmTimer::StartTime( )
{
	m_lastFire = VpmGlobalConfiguration::GetTime();
	m_bEnable = true;

	
}

void VpmTimer::StopTime( )
{
	m_bEnable = false;
}
void VpmTimer::Init( )
{
	VwWidget::Init();
}
