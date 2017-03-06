#include "ServoPanel.h"

#include "EffectPanelUtils.h"
//(*InternalHeaders(ServoPanel)













//(*IdInit(ServoPanel)








BEGIN_EVENT_TABLE(ServoPanel,wxPanel)
	//(*EventTable(ServoPanel)
	//*)
END_EVENT_TABLE()

ServoPanel::ServoPanel(wxWindow* parent)
{
	//(*Initialize(ServoPanel)






































    SetName("ID_PANEL_SERVO");

    Connect(wxID_ANY, EVT_VC_CHANGED, (wxObjectEventFunction)&ServoPanel::OnVCChanged, 0, this);

    ValueCurve_Servo->GetValue()->SetLimits(0, 100);

}

ServoPanel::~ServoPanel()
{
	//(*Destroy(ServoPanel)
	//*)
}

PANEL_EVENT_HANDLERS(ServoPanel)