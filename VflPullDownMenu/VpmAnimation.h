
#pragma once
#include "VglConfig.h"

#include "VpmGlobalConfiguration.h"

#include <VistaBase/VistaVector3D.h>

#include<VistaMath/VistaEaseCurve.h>
template <class T>
class VGLWAPI VpmAnimation
{
public:
	VpmAnimation() :
		m_pEaseCurve(new VistaEaseCurve()),
		m_dStartUpOffset(0.),
		m_dDuration(0.),
		m_dStartTime(0.),
		m_tStartValue(T()),
		m_tEndValue(T()),
		m_bStartAnimation(false )
	{ }

	VpmAnimation(const VpmAnimation<T> &oOther) :
		m_dStartUpOffset(oOther.m_dStartUpOffset),
		m_dDuration(oOther.m_dDuration),
		m_dStartTime(oOther.m_dStartTime),
		m_tStartValue(oOther.m_tStartValue),
		m_tEndValue(oOther.m_tEndValue)
	{
		m_pEaseCurve = new VistaEaseCurve(oOther.m_pEaseCurve);
	}

	virtual ~VpmAnimation()
	{
		delete m_pEaseCurve;
	}

	bool IsStartAnimation()
	{
		return m_bStartAnimation;
	}
	void Stop()
	{
		m_bStartAnimation = false;
	}
	void Start()
	{
		m_dStartTime = VpmGlobalConfiguration::GetTime();
		m_bStartAnimation = true;
	}

	double GetProgress() const
	{
		if ( m_dDuration == 0.f )
		{
			return 1.f;
		}
		else
		{
			double fDuration = VpmGlobalConfiguration::GetTime() 
				- ( m_dStartTime + m_dStartUpOffset );
			return m_pEaseCurve->GetValue(Clamp(fDuration / m_dDuration, 0., 1.));
		}
	}

	T GetValue() const
	{
		return static_cast<T>(
			m_tStartValue + GetProgress() * (m_tEndValue - m_tStartValue));
	}

	void SetStartUpOffset(double val)
	{
		m_dStartUpOffset = val;
	}

	double GetStartUpOffset() const
	{
		return m_dStartUpOffset;
	}

	void SetDuration(double val)
	{
		m_dDuration = val;
	}

	double GetDuration() const
	{
		return m_dDuration;
	}

	VistaEaseCurve * GetEaseCurve() const
	{
		return m_pEaseCurve;
	}

	void SetStartValue(T val)
	{
		m_tStartValue = val;
	}

	T GetStartValue() const
	{
		return m_tStartValue;
	}

	void SetEndValue(T val)
	{
		m_tEndValue = val;
	}

	T GetEndValue() const
	{
		return m_tEndValue;
	}

	bool GetIsRunning() const
	{
		return GetProgress() < 1.f;
	}

private:
	double Clamp(double dValue, double dLower, double dUpper) const
	{
		return dValue < dLower ? dLower : (dValue > dUpper ? dUpper : dValue);
	}

private:
bool m_bStartAnimation;
	double
		m_dStartUpOffset,
		m_dDuration,
		m_dStartTime;

	T	m_tStartValue,
		m_tEndValue;

	VistaEaseCurve	*m_pEaseCurve;

};
  
template <>
VistaVector3D VpmAnimation<VistaVector3D>::GetValue() const;

