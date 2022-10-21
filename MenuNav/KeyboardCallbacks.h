#include <VistaAspects/VistaExplicitCallbackInterface.h>
#include <VistaKernel/DisplayManager/VistaVirtualPlatform.h>
#include <VistaKernel/VistaSystem.h>
#include <VistaKernel/DisplayManager/VistaDisplayManager.h>
#include <VistaKernel/DisplayManager/VistaDisplaySystem.h>

#include "MenuNav.h"

class ConfigSceneTranslation : public IVistaExplicitCallbackInterface
{
public:
	ConfigSceneTranslation(VistaVector3D v3Direction, VistaSystem* pVistaSystem)
		: m_v3Direction(v3Direction)
		, m_pVistaSystem(pVistaSystem)
	{}

	bool Do()
	{
		VistaVirtualPlatform* pPlatform = m_pVistaSystem->GetDisplayManager()->GetDisplaySystem(0)->GetReferenceFrame();
		pPlatform->SetTranslation(pPlatform->GetTranslation() + m_v3Direction);
		/*m_pTest->Translate(m_v3Direction);*/
		return true;
	}

private:
	VistaVector3D m_v3Direction;
	VistaSystem* m_pVistaSystem;
};