#include "VideoPanel.h"
#include "../../include/padlock16x16-blue.xpm"
#include "EffectPanelUtils.h"

//(*InternalHeaders(VideoPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(VideoPanel)
const long VideoPanel::ID_FILEPICKERCTRL_Video_Filename = wxNewId();
const long VideoPanel::ID_STATICTEXT8 = wxNewId();
const long VideoPanel::IDD_SLIDER_Video_Starttime = wxNewId();
const long VideoPanel::ID_TEXTCTRL_Video_Starttime = wxNewId();
const long VideoPanel::ID_CHOICE_Video_DurationTreatment = wxNewId();
const long VideoPanel::ID_CHECKBOX_Video_AspectRatio = wxNewId();
const long VideoPanel::ID_CHECKBOX_SynchroniseWithAudio = wxNewId();
const long VideoPanel::ID_STATICTEXT1 = wxNewId();
const long VideoPanel::IDD_SLIDER_Video_CropLeft = wxNewId();
const long VideoPanel::ID_TEXTCTRL_Video_CropLeft = wxNewId();
const long VideoPanel::ID_STATICTEXT2 = wxNewId();
const long VideoPanel::IDD_SLIDER_Video_CropRight = wxNewId();
const long VideoPanel::ID_TEXTCTRL_Video_CropRight = wxNewId();
const long VideoPanel::ID_STATICTEXT3 = wxNewId();
const long VideoPanel::IDD_SLIDER_Video_CropTop = wxNewId();
const long VideoPanel::ID_TEXTCTRL_Video_CropTop = wxNewId();
const long VideoPanel::ID_STATICTEXT4 = wxNewId();
const long VideoPanel::IDD_SLIDER_Video_CropBottom = wxNewId();
const long VideoPanel::ID_TEXTCTRL_Video_CropBottom = wxNewId();
//*)

BEGIN_EVENT_TABLE(VideoPanel,wxPanel)
	//(*EventTable(VideoPanel)
	//*)
END_EVENT_TABLE()

VideoPanel::VideoPanel(wxWindow* parent)
{
	//(*Initialize(VideoPanel)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticText* StaticText1;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer42;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer42 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer42->AddGrowableCol(0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FilePicker_Video_Filename = new xlVideoFilePickerCtrl(this, ID_FILEPICKERCTRL_Video_Filename, wxEmptyString, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL_Video_Filename"));
	FlexGridSizer1->Add(FilePicker_Video_Filename, 1, wxALL|wxEXPAND, 2);
	FlexGridSizer3->Add(FlexGridSizer1, 1, wxEXPAND, 2);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Start Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer2->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Video_Starttime = new wxSlider(this, IDD_SLIDER_Video_Starttime, 0, 0, 20, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("IDD_SLIDER_Video_Starttime"));
	FlexGridSizer2->Add(Slider_Video_Starttime, 1, wxALL|wxEXPAND, 2);
	TextCtrl_Video_Starttime = new wxTextCtrl(this, ID_TEXTCTRL_Video_Starttime, _("0.0"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(40,-1)), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL_Video_Starttime"));
	FlexGridSizer2->Add(TextCtrl_Video_Starttime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer3->Add(FlexGridSizer2, 1, wxEXPAND, 2);
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer5->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Duration Treatment"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Choice_Video_DurationTreatment = new wxChoice(this, ID_CHOICE_Video_DurationTreatment, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Video_DurationTreatment"));
	Choice_Video_DurationTreatment->SetSelection( Choice_Video_DurationTreatment->Append(_("Normal")) );
	Choice_Video_DurationTreatment->Append(_("Loop"));
	Choice_Video_DurationTreatment->Append(_("Slow/Accelerate"));
	FlexGridSizer5->Add(Choice_Video_DurationTreatment, 1, wxALL|wxEXPAND, 2);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxEXPAND, 2);
	CheckBox_Video_AspectRatio = new wxCheckBox(this, ID_CHECKBOX_Video_AspectRatio, _("Maintain Aspect Ratio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Video_AspectRatio"));
	CheckBox_Video_AspectRatio->SetValue(false);
	FlexGridSizer4->Add(CheckBox_Video_AspectRatio, 1, wxALL|wxEXPAND, 2);
	CheckBox_SynchroniseWithAudio = new wxCheckBox(this, ID_CHECKBOX_SynchroniseWithAudio, _("Use sequence audio file as video file and synchronise"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_SynchroniseWithAudio"));
	CheckBox_SynchroniseWithAudio->SetValue(false);
	FlexGridSizer4->Add(CheckBox_SynchroniseWithAudio, 1, wxALL|wxEXPAND, 2);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer6->AddGrowableCol(1);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT1, _("Crop Left"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer6->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Video_CropLeft = new wxSlider(this, IDD_SLIDER_Video_CropLeft, 0, 0, 100, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("IDD_SLIDER_Video_CropLeft"));
	FlexGridSizer6->Add(Slider_Video_CropLeft, 1, wxALL|wxEXPAND, 2);
	TextCtrl_Video_CropLeft = new wxTextCtrl(this, ID_TEXTCTRL_Video_CropLeft, _("0"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(40,-1)), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL_Video_CropLeft"));
	FlexGridSizer6->Add(TextCtrl_Video_CropLeft, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT2, _("Crop Right"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer6->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Video_CropRight = new wxSlider(this, IDD_SLIDER_Video_CropRight, 100, 0, 100, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("IDD_SLIDER_Video_CropRight"));
	FlexGridSizer6->Add(Slider_Video_CropRight, 1, wxALL|wxEXPAND, 2);
	TextCtrl_Video_CropRight = new wxTextCtrl(this, ID_TEXTCTRL_Video_CropRight, _("100"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(40,-1)), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL_Video_CropRight"));
	FlexGridSizer6->Add(TextCtrl_Video_CropRight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT3, _("Crop Top"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	Slider_Video_CropTop = new wxSlider(this, IDD_SLIDER_Video_CropTop, 100, 0, 100, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("IDD_SLIDER_Video_CropTop"));
	FlexGridSizer6->Add(Slider_Video_CropTop, 1, wxALL|wxEXPAND, 2);
	TextCtrl_Video_CropTop = new wxTextCtrl(this, ID_TEXTCTRL_Video_CropTop, _("100"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(40,-1)), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL_Video_CropTop"));
	FlexGridSizer6->Add(TextCtrl_Video_CropTop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT4, _("Crop Bottom"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText5, 1, wxALL|wxALIGN_LEFT, 2);
	Slider_Video_CropBottom = new wxSlider(this, IDD_SLIDER_Video_CropBottom, 0, 0, 100, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("IDD_SLIDER_Video_CropBottom"));
	FlexGridSizer6->Add(Slider_Video_CropBottom, 1, wxALL|wxEXPAND, 2);
	TextCtrl_Video_CropBottom = new wxTextCtrl(this, ID_TEXTCTRL_Video_CropBottom, _("0"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(40,-1)), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL_Video_CropBottom"));
	FlexGridSizer6->Add(TextCtrl_Video_CropBottom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxEXPAND, 2);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND, 2);
	FlexGridSizer42->Add(FlexGridSizer3, 1, wxEXPAND, 2);
	SetSizer(FlexGridSizer42);
	FlexGridSizer42->Fit(this);
	FlexGridSizer42->SetSizeHints(this);

	Connect(ID_FILEPICKERCTRL_Video_Filename,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&VideoPanel::OnFilePicker_Video_FilenameFileChanged);
	Connect(IDD_SLIDER_Video_Starttime,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedTextCtrlFloat2);
	Connect(ID_TEXTCTRL_Video_Starttime,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedSliderFloat2);
	Connect(ID_CHECKBOX_SynchroniseWithAudio,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&VideoPanel::OnCheckBox_SynchroniseWithAudioClick);
	Connect(IDD_SLIDER_Video_CropLeft,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedTextCtrl);
	Connect(ID_TEXTCTRL_Video_CropLeft,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedSlider);
	Connect(IDD_SLIDER_Video_CropRight,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedTextCtrl);
	Connect(ID_TEXTCTRL_Video_CropRight,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedSlider);
	Connect(IDD_SLIDER_Video_CropTop,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedTextCtrl);
	Connect(ID_TEXTCTRL_Video_CropTop,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedSlider);
	Connect(IDD_SLIDER_Video_CropBottom,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedTextCtrl);
	Connect(ID_TEXTCTRL_Video_CropBottom,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&VideoPanel::UpdateLinkedSlider);
	//*)
    SetName("ID_PANEL_Video");
	TextCtrl_Video_Starttime->SetValue("0.00");
	CheckBox_Video_AspectRatio->SetValue(false);

	ValidateWindow();
}

VideoPanel::~VideoPanel()
{
	//(*Destroy(VideoPanel)
	//*)
}

void VideoPanel::addVideoTime(std::string fn, unsigned long ms) {
    std::unique_lock<std::mutex> locker(lock);
    videoTimeCache[fn] = ms;

	// If it is not correct then set it
	if (Slider_Video_Starttime->GetMax() != ms)
	{
		Slider_Video_Starttime->SetMax(ms / 10);
	}
}

PANEL_EVENT_HANDLERS(VideoPanel)

void VideoPanel::OnFilePicker_Video_FilenameFileChanged(wxFileDirPickerEvent& event) {
    std::unique_lock<std::mutex> locker(lock);
    wxFileName fn = FilePicker_Video_Filename->GetFileName();
    int i = videoTimeCache[fn.GetFullPath().ToStdString()];
    if (i > 0) {
        Slider_Video_Starttime->SetMax(i);
    } else {
        Slider_Video_Starttime->SetMax(1);
    }
}

void VideoPanel::OnCheckBox_SynchroniseWithAudioClick(wxCommandEvent& event)
{
    ValidateWindow();
}

void VideoPanel::ValidateWindow()
{
    if (CheckBox_SynchroniseWithAudio->GetValue())
    {
        Slider_Video_Starttime->Enable(false);
        TextCtrl_Video_Starttime->Enable(false);
        Choice_Video_DurationTreatment->Enable(false);
        FilePicker_Video_Filename->Enable(false);
    }
    else
    {
        Slider_Video_Starttime->Enable(true);
        TextCtrl_Video_Starttime->Enable(true);
        Choice_Video_DurationTreatment->Enable(true);
        FilePicker_Video_Filename->Enable(true);
    }
}
