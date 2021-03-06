#ifndef LIGHTNINGPANEL_H
#define LIGHTNINGPANEL_H

//(*Headers(LightningPanel)
#include <wx/panel.h>
class wxTextCtrl;
class wxChoice;
class wxFlexGridSizer;
class wxBitmapButton;
class wxSlider;
class wxStaticText;
class wxCheckBox;
//*)

#include "../ValueCurveButton.h"

class LightningPanel: public wxPanel
{
	public:

		LightningPanel(wxWindow* parent);
		virtual ~LightningPanel();

		//(*Declarations(LightningPanel)
		wxBitmapButton* BitmapButton20;
		wxTextCtrl* TextCtrl86;
		wxTextCtrl* TextCtrl88;
		wxTextCtrl* TextCtrl89;
		ValueCurveButton* BitmapButton_Number_SegmentsVC;
		wxStaticText* StaticText205;
		wxCheckBox* CheckBox_ForkedLightning;
		wxStaticText* StaticText210;
		wxSlider* Slider_Lightning_TopY;
		wxStaticText* StaticText208;
		wxChoice* CHOICE_Lightning_Direction;
		wxStaticText* StaticText1;
		wxBitmapButton* BitmapButton26;
		wxBitmapButton* BitmapButton27;
		wxBitmapButton* BitmapButton25;
		wxBitmapButton* BitmapButton28;
		wxBitmapButton* BitmapButton22;
		wxStaticText* StaticText207;
		ValueCurveButton* BitmapButton_Lightning_TopYVC;
		wxBitmapButton* BitmapButton23;
		wxSlider* Slider_Lightning_BOTY;
		wxSlider* Slider_Lightning_TopX;
		wxSlider* Slider_Number_Segments;
		wxTextCtrl* TextCtrl90;
		ValueCurveButton* BitmapButton_Lightning_TopXVC;
		wxSlider* Slider_Lightning_BOTX;
		wxStaticText* StaticText203;
		wxStaticText* StaticText209;
		wxStaticText* StaticText206;
		wxSlider* Slider_Number_Bolts;
		ValueCurveButton* BitmapButton_Number_BoltsVC;
		//*)

	protected:

		//(*Identifiers(LightningPanel)
		static const long ID_STATICTEXT25;
		static const long ID_SLIDER_Number_Bolts;
		static const long ID_VALUECURVE_Number_Bolts;
		static const long IDD_TEXTCTRL_Number_Bolts;
		static const long ID_BITMAPBUTTON38;
		static const long ID_STATICTEXT26;
		static const long ID_SLIDER_Number_Segments;
		static const long ID_VALUECURVE_Number_Segments;
		static const long IDD_TEXTCTRL_Number_Segments;
		static const long ID_BITMAPBUTTON40;
		static const long ID_STATICTEXT60;
		static const long ID_CHECKBOX_ForkedLightning;
		static const long ID_BITMAPBUTTON41;
		static const long ID_STATICTEXT64;
		static const long ID_SLIDER_Lightning_TopX;
		static const long ID_VALUECURVE_Lightning_TopX;
		static const long IDD_TEXTCTRL_Lightning_TopX;
		static const long ID_BITMAPBUTTON42;
		static const long ID_STATICTEXT67;
		static const long ID_SLIDER_Lightning_TopY;
		static const long ID_VALUECURVE_Lightning_TopY;
		static const long IDD_TEXTCTRL_Lightning_TopY;
		static const long ID_BITMAPBUTTON43;
		static const long ID_STATICTEXT70;
		static const long ID_SLIDER_Lightning_BOTX;
		static const long IDD_TEXTCTRL_Lightning_BOTX;
		static const long ID_BITMAPBUTTON45;
		static const long ID_STATICTEXT73;
		static const long ID_SLIDER_Lightning_BOTY;
		static const long IDD_TEXTCTRL_Lightning_BOTY;
		static const long ID_BITMAPBUTTON52;
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_Lightning_Direction;
		//*)

	public:

		//(*Handlers(LightningPanel)
    void UpdateLinkedSliderFloat(wxCommandEvent& event);
    void UpdateLinkedTextCtrlFloat(wxScrollEvent& event);
    void UpdateLinkedTextCtrl360(wxScrollEvent& event);
    void UpdateLinkedSlider360(wxCommandEvent& event);
    void UpdateLinkedTextCtrl(wxScrollEvent& event);
    void UpdateLinkedSlider(wxCommandEvent& event);
    void OnLockButtonClick(wxCommandEvent& event);
    void UpdateLinkedTextCtrlVC(wxScrollEvent& event);
    void UpdateLinkedTextCtrlFloatVC(wxScrollEvent& event);
    void OnVCButtonClick(wxCommandEvent& event);
    void OnVCChanged(wxCommandEvent& event);
    void UpdateLinkedSliderFloat2(wxCommandEvent& event);
    void UpdateLinkedTextCtrlFloat2(wxScrollEvent& event);
    //*)

		DECLARE_EVENT_TABLE()
};
#endif
