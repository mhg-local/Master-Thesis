#pragma once


#include"VglConfig.h"
#include<VistaBase\VistaColor.h>
#include <VflTextRendering/VtrFont.h>

class VistaSystem;

class VGLWAPI VpmGlobalConfiguration
{
public:
	static void Init( VistaSystem* pSystem );
	static VistaSystem* GetVistaSystem();



	static bool   ShowProgressBar;

	static float BorderSize;
	static float SecondaryElementWidthPercent; 

	static float Left_X_Padding;
	static float Top_Y_Padding;

	static float Right_X_Padding;
	static float Bottom_Y_Padding;

	static float ZDistance;
	static float Left_X_Padding_SubMenu;

	static float ScalingCurrentMenu;
	static float ScalingPreviousMenu;

	static float MenuWidth;
	static float MenuHeight;
	static float ElementWidth;
	static float ElementHeight;
	
	//Max Element Count in View 
	static int    TotalViewElementCount;
	static VistaVector3D OriginalPosition;

	static std::string SymbolOfSubMenu;

	static VistaColor SelectedColor;
	static VistaColor FocusColor;
	static VistaColor EnableColor;
	static VistaColor PressedColor;
	static VistaColor ProgressColor;
	static VistaColor DeepColor;

	static double GetTime( );


	static VtrFont* GetSymbolFont();

private:
	static VistaSystem* S_pVistaSystem;

};

