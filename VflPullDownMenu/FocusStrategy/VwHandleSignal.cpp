#include"VwHandleSignal.h"


#include<VwFocusHandle.h>



VwHandleSignalArgs::VwHandleSignalArgs( void* pSource, VwFocusHandle*pHandle ):VwSignalArgs( pSource )
{
	m_pHandle = pHandle;
	m_bContinue = new bool;
}
VwHandleSignalArgs::VwHandleSignalArgs( void* pSource, const VwHandleSignalArgs& oArgs ) : VwSignalArgs( pSource )
{
	m_pHandle = oArgs.m_pHandle;
	m_bContinue = new bool;
	*m_bContinue = oArgs.GetContinue();
}
VwHandleSignalArgs::~VwHandleSignalArgs()
{
	delete m_bContinue;
}
bool VwHandleSignalArgs::GetContinue() const
{
	return *m_bContinue;
}
void VwHandleSignalArgs::SetContinue( bool bContinue ) const
{
	*m_bContinue = bContinue;
}

VwFocusHandle* VwHandleSignalArgs::GetHandle( ) const
{
	return m_pHandle;
}




