#include "InitConstants.h"

#include <VistaTools/VistaIniFileParser.h>

bool LoadConfigSettings( InitConstants& initConstants, const std::string& sFileName )
{
	VistaIniFileParser iniParser;
	VistaPropertyList iniFilePropList;
	if(! iniParser.ReadProplistFromFile(sFileName, iniFilePropList))
	{
		vstr::errp() << "PropList for file " << 
			sFileName << " could not be parsed!" << std::endl;
		VISTA_THROW("No init file could be loaded!", 2);
	}

	VistaPropertyList connProperties;
	iniFilePropList.GetValue("Microphone", connProperties);
	
	connProperties.GetValue("MinClipPercentage", initConstants.m_nMinClipPercentage);
	connProperties.GetValue("MaxClipPercentage", initConstants.m_nMaxClipPercentage);
	connProperties.GetValue("ClipLevelMin", initConstants.m_nClipLevelMin);
	connProperties.GetValue("ClipLevelMax", initConstants.m_nClipLevelMax);
	connProperties.GetValue("SmoothingFactor", initConstants.m_nSmoothingFactor);
	connProperties.GetValue("SmoothedStrength", initConstants.m_nSmoothedStrength);

	
	return true;
}