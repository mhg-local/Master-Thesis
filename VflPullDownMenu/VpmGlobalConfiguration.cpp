#include "VpmGlobalConfiguration.h"
#include<VflTextRendering\VtrFontManager.h>
#include <VistaKernel/VistaSystem.h>


float VpmGlobalConfiguration::BorderSize(0.0015f);
float VpmGlobalConfiguration::SecondaryElementWidthPercent(0.2f);

float VpmGlobalConfiguration::MenuWidth(0.10f);
float VpmGlobalConfiguration::MenuHeight(0.1f);

float VpmGlobalConfiguration::ElementWidth(0.35f);
float VpmGlobalConfiguration::ElementHeight(0.1f);

float VpmGlobalConfiguration::Left_X_Padding(0.04f);
float VpmGlobalConfiguration::Top_Y_Padding(0.004f);

std::string VpmGlobalConfiguration::SymbolOfSubMenu = "4";

float VpmGlobalConfiguration::Right_X_Padding( 0.025f );
float VpmGlobalConfiguration::Bottom_Y_Padding(0.004f);

VistaColor VpmGlobalConfiguration::SelectedColor(VistaColor(150, 150, 150));
VistaColor VpmGlobalConfiguration::FocusColor(VistaColor:: LIGHT_GRAY);
VistaColor VpmGlobalConfiguration::EnableColor(VistaColor(255, 255, 255, 255));
VistaColor VpmGlobalConfiguration::PressedColor(VistaColor::GRAY);

VistaColor VpmGlobalConfiguration::ProgressColor( VistaColor::GREEN );
VistaColor VpmGlobalConfiguration::DeepColor( VistaColor::RED );

float VpmGlobalConfiguration::ZDistance(0.01f);
float VpmGlobalConfiguration::Left_X_Padding_SubMenu(-0.02f);

float VpmGlobalConfiguration::ScalingCurrentMenu(1.0f);
float VpmGlobalConfiguration::ScalingPreviousMenu(0.85f);

VistaSystem* VpmGlobalConfiguration::S_pVistaSystem( nullptr );


bool VpmGlobalConfiguration::ShowProgressBar( true );

int VpmGlobalConfiguration::TotalViewElementCount = 3;
VistaVector3D VpmGlobalConfiguration::OriginalPosition = VistaVector3D( 0.f, 0.0f, 0.f );// desktop mouse
//VistaVector3D VpmGlobalConfiguration::OriginalPosition =  VistaVector3D( 0, 0, -0.3 );// Oculus
//VistaVector3D VpmGlobalConfiguration::OriginalPosition = VistaVector3D( 0.f, 0.1f, -0.17f );// desktop

void VpmGlobalConfiguration::Init( VistaSystem *pVistaSystem )
	{
	S_pVistaSystem = pVistaSystem;
	}

VistaSystem* VpmGlobalConfiguration::GetVistaSystem()
	{
	return S_pVistaSystem;
	}
VtrFont* VpmGlobalConfiguration::GetSymbolFont()
{
	if( VtrFontManager::GetInstance()->GetFont( "webdings.ttf" ) != nullptr )
	{
		return VtrFontManager::GetInstance()->GetFont( "webdings.ttf" );
	}
	return VtrFontManager::GetInstance()->GetDefaultFont();
}
double VpmGlobalConfiguration::GetTime()
	{
	if( S_pVistaSystem )
		{
		return S_pVistaSystem->GetFrameClock();
		}
	else
		{
		return 0.;
		}
	}