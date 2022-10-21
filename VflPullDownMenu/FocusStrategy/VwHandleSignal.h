#pragma once

#include "../VglConfig.h"

#include<SignalSystem\VwSignal.h>
#include "SignalSystem\VwSignalArgs.h"

class VwSignalSource;
class VwFocusHandle;


class VGLWAPI VwHandleSignalArgs: public VwSignalArgs {
	public:
		VwHandleSignalArgs( void* pSource, VwFocusHandle*pHandle );
		VwHandleSignalArgs( void* pSource, const VwHandleSignalArgs& oArgs );
		virtual ~VwHandleSignalArgs( );

		void SetContinue( bool bContinue ) const;
		bool GetContinue() const;
		VwFocusHandle* GetHandle() const;
	private:
	VwFocusHandle* m_pHandle;
	bool*           m_bContinue;

};

typedef VwSignal<const VwHandleSignalArgs&> VwHandleSignal;


