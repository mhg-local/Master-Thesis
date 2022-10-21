#pragma once


#include"../VglConfig.h"
#include"VpmElement.h"
class VGLWAPI VpmLabelElement :public VpmElement
{
public:
	VpmLabelElement();

	virtual bool NeedSecondElement() override
	{
		return false;
	}
};