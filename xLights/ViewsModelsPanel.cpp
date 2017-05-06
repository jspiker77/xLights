#include "ViewsModelsPanel.h"

//(*InternalHeaders(ViewsModelsPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "../include/model-16.xpm"
#include "../include/timing-16.xpm"
#include "../include/eye-16.xpm"
#include "../include/eye-16_gray.xpm"
#include <wx/xml/xml.h>
#include "sequencer/SequenceElements.h"
#include "xLightsMain.h"
#include "SequenceViewManager.h"
#include <wx/dnd.h>

// This event is fired when a model is dropped between lists
wxDEFINE_EVENT(EVT_VMDROP, wxCommandEvent);

class VMDropSource : public wxDropSource
{
    ViewsModelsPanel* _window;
    bool _nonModels;
    bool _models;

public:

    VMDropSource(ViewsModelsPanel* window, bool models, bool nonModels) : wxDropSource(window)
    {
        _window = window;
        _nonModels = nonModels;
        _models = models;
    }

    virtual bool GiveFeedback(wxDragResult effect) override
    {
        int sx;
        int sy;
        _window->GetScreenPosition(&sx, &sy);
        wxPoint point = wxGetMousePosition() - wxPoint(sx, sy);

        if (_models)
        {
            if (_window->ListCtrlModels->GetRect().Contains(point) ||
                _window->ListCtrlNonModels->GetRect().Contains(point))
            {
                _window->SetCursor(wxCursor(wxCURSOR_HAND));
            }
            else
            {
                _window->SetCursor(wxCursor(wxCURSOR_NO_ENTRY));
            }
        }
        else if (_nonModels)
        {
            if (_window->ListCtrlModels->GetRect().Contains(point))
            {
                _window->SetCursor(wxCursor(wxCURSOR_HAND));
            }
            else
            {
                _window->SetCursor(wxCursor(wxCURSOR_NO_ENTRY));
            }
        }
        else
        {
            return false;
        }

        return true;
    }
};

#define TIMING_IMAGE 2
#define MODEL_IMAGE 3

//(*IdInit(ViewsModelsPanel)
const long ViewsModelsPanel::ID_STATICTEXT3 = wxNewId();
const long ViewsModelsPanel::ID_LISTCTRL1 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON3 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON4 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON5 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON6 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON9 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON10 = wxNewId();
const long ViewsModelsPanel::ID_STATICTEXT1 = wxNewId();
const long ViewsModelsPanel::ID_LISTCTRL_VIEWS = wxNewId();
const long ViewsModelsPanel::ID_BUTTON1 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON2 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON7 = wxNewId();
const long ViewsModelsPanel::ID_BUTTON8 = wxNewId();
const long ViewsModelsPanel::ID_STATICTEXT2 = wxNewId();
const long ViewsModelsPanel::ID_LISTCTRL_MODELS = wxNewId();
const long ViewsModelsPanel::ID_SCROLLEDWINDOW1 = wxNewId();
const long ViewsModelsPanel::ID_PANEL1 = wxNewId();
//*)

const long ViewsModelsPanel::ID_MODELS_UNDO = wxNewId();
const long ViewsModelsPanel::ID_MODELS_HIDEALL = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SHOWALL = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SELECTALL = wxNewId();
const long ViewsModelsPanel::ID_MODELS_HIDEUNUSED = wxNewId();
const long ViewsModelsPanel::ID_MODELS_REMOVEUNUSED = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SORT = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SORTBYNAME = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SORTBYNAMEGM = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SORTBYTYPE = wxNewId();
const long ViewsModelsPanel::ID_MODELS_SORTMODELSUNDERTHISGROUP = wxNewId();
const long ViewsModelsPanel::ID_MODELS_BUBBLEUPGROUPS = wxNewId();

BEGIN_EVENT_TABLE(ViewsModelsPanel,wxPanel)
	//(*EventTable(ViewsModelsPanel)
	//*)
    EVT_COMMAND(wxID_ANY, EVT_LISTITEM_CHECKED, ViewsModelsPanel::OnListCtrlItemCheck)
    EVT_COMMAND(wxID_ANY, EVT_VMDROP, ViewsModelsPanel::OnDrop)
END_EVENT_TABLE()

ViewsModelsPanel::ViewsModelsPanel(xLightsFrame *frame, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) : _xlFrame(frame)
{
	//(*Initialize(ViewsModelsPanel)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	MainSizer = new wxFlexGridSizer(1, 1, 0, 0);
	MainSizer->AddGrowableCol(0);
	MainSizer->AddGrowableRow(0);
	Panel_Sizer = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer9 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer9->AddGrowableCol(0);
	FlexGridSizer9->AddGrowableRow(0);
	ScrolledWindowViewsModels = new wxScrolledWindow(Panel_Sizer, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
	ScrollWindowSizer = new wxFlexGridSizer(0, 3, 0, 0);
	ScrollWindowSizer->AddGrowableCol(2);
	ScrollWindowSizer->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(1);
	StaticText3 = new wxStaticText(ScrolledWindowViewsModels, ID_STATICTEXT3, _("Available:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	ListCtrlNonModels = new wxListCtrl(ScrolledWindowViewsModels, ID_LISTCTRL1, wxDefaultPosition, wxSize(150,-1), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
	ListCtrlNonModels->SetMinSize(wxSize(150,-1));
	FlexGridSizer2->Add(ListCtrlNonModels, 1, wxALL|wxEXPAND, 0);
	ScrollWindowSizer->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	Button_AddAll = new wxButton(ScrolledWindowViewsModels, ID_BUTTON3, _(">>"), wxDefaultPosition, wxSize(32,30), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer5->Add(Button_AddAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Button_AddSelected = new wxButton(ScrolledWindowViewsModels, ID_BUTTON4, _(">"), wxDefaultPosition, wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer5->Add(Button_AddSelected, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Button_RemoveSelected = new wxButton(ScrolledWindowViewsModels, ID_BUTTON5, _("<"), wxDefaultPosition, wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer5->Add(Button_RemoveSelected, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Button_RemoveAll = new wxButton(ScrolledWindowViewsModels, ID_BUTTON6, _("<<"), wxDefaultPosition, wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer5->Add(Button_RemoveAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Button_MoveUp = new wxButton(ScrolledWindowViewsModels, ID_BUTTON9, _("^"), wxDefaultPosition, wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	FlexGridSizer5->Add(Button_MoveUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_MoveDown = new wxButton(ScrolledWindowViewsModels, ID_BUTTON10, _("v"), wxDefaultPosition, wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON10"));
	FlexGridSizer5->Add(Button_MoveDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ScrollWindowSizer->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(1);
	FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableRow(0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer7->AddGrowableCol(0);
	FlexGridSizer7->AddGrowableRow(1);
	StaticText1 = new wxStaticText(ScrolledWindowViewsModels, ID_STATICTEXT1, _("View:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer7->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	ListCtrlViews = new wxCheckedListCtrl(ScrolledWindowViewsModels, ID_LISTCTRL_VIEWS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTCTRL_VIEWS"));
	ListCtrlViews->SetMinSize(wxDLG_UNIT(ScrolledWindowViewsModels,wxSize(40,-1)));
	FlexGridSizer7->Add(ListCtrlViews, 1, wxALL|wxEXPAND, 0);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
	Button_AddView = new wxButton(ScrolledWindowViewsModels, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer8->Add(Button_AddView, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Button_DeleteView = new wxButton(ScrolledWindowViewsModels, ID_BUTTON2, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer8->Add(Button_DeleteView, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ButtonRename = new wxButton(ScrolledWindowViewsModels, ID_BUTTON7, _("Rename"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer8->Add(ButtonRename, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ButtonClone = new wxButton(ScrolledWindowViewsModels, ID_BUTTON8, _("Clone"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	FlexGridSizer8->Add(ButtonClone, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer6->Add(FlexGridSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(FlexGridSizer6, 1, wxALL|wxEXPAND, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	FlexGridSizer4->AddGrowableRow(1);
	StaticText2 = new wxStaticText(ScrolledWindowViewsModels, ID_STATICTEXT2, _("Added:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	ListCtrlModels = new wxCheckedListCtrl(ScrolledWindowViewsModels, ID_LISTCTRL_MODELS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL_MODELS"));
	ListCtrlModels->SetMinSize(wxDLG_UNIT(ScrolledWindowViewsModels,wxSize(60,-1)));
	FlexGridSizer4->Add(ListCtrlModels, 1, wxALL|wxEXPAND, 0);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxEXPAND, 5);
	ScrollWindowSizer->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 0);
	ScrolledWindowViewsModels->SetSizer(ScrollWindowSizer);
	ScrollWindowSizer->Fit(ScrolledWindowViewsModels);
	ScrollWindowSizer->SetSizeHints(ScrolledWindowViewsModels);
	FlexGridSizer9->Add(ScrolledWindowViewsModels, 1, wxALL|wxEXPAND, 5);
	Panel_Sizer->SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(Panel_Sizer);
	FlexGridSizer9->SetSizeHints(Panel_Sizer);
	MainSizer->Add(Panel_Sizer, 1, wxEXPAND, 0);
	SetSizer(MainSizer);
	MainSizer->Fit(this);
	MainSizer->SetSizeHints(this);

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlNonModelsBeginDrag);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlNonModelsItemSelect);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlNonModelsKeyDown);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_AddAllClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_AddSelectedClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_RemoveSelectedClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_RemoveAllClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_MoveUpClick);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_MoveDownClick);
	Connect(ID_LISTCTRL_VIEWS,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlViewsItemSelect);
	Connect(ID_LISTCTRL_VIEWS,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlViewsItemDClick);
	Connect(ID_LISTCTRL_VIEWS,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlViewsKeyDown);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_AddViewClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButton_DeleteViewClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButtonRenameClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ViewsModelsPanel::OnButtonCloneClick);
	Connect(ID_LISTCTRL_MODELS,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&ViewsModelsPanel::OnListView_ViewItemsBeginDrag);
	Connect(ID_LISTCTRL_MODELS,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&ViewsModelsPanel::OnListView_ViewItemsItemSelect);
	Connect(ID_LISTCTRL_MODELS,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&ViewsModelsPanel::OnListCtrlModelsItemRClick);
	Connect(ID_LISTCTRL_MODELS,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&ViewsModelsPanel::OnListView_ViewItemsKeyDown);
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&ViewsModelsPanel::OnLeftUp);
	Connect(wxEVT_SIZE,(wxObjectEventFunction)&ViewsModelsPanel::OnResize);
	//*)

    Connect(wxID_ANY, EVT_VMDROP, (wxObjectEventFunction)&ViewsModelsPanel::OnDrop);

    ListCtrlViews->SetImages((char**)eye_16, (char**)eye_16_gray);

    _numViews = 0;
    _numModels = 0;
    _numNonModels = 0;
    _sequenceElements = nullptr;
    _mainViewsChoice = nullptr;

    ListCtrlModels->SetImages((char**)eye_16, (char**)eye_16_gray);
    ListCtrlModels->AddImage((char**)timing_16);
    ListCtrlModels->AddImage((char**)model_16);

    _imageList = new wxImageList(16, 16, true);
    _imageList->Add(wxIcon((char**)timing_16));
    _imageList->Add(wxIcon((char**)model_16));

    MyTextDropTarget *mdt = new MyTextDropTarget(this, ListCtrlModels, "Model");
    ListCtrlModels->SetDropTarget(mdt);

    mdt = new MyTextDropTarget(this, ListCtrlNonModels, "NonModel");
    ListCtrlNonModels->SetDropTarget(mdt);

    ValidateWindow();
}

ViewsModelsPanel::~ViewsModelsPanel()
{
	//(*Destroy(ViewsModelsPanel)
	//*)

    //for (int i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
    //{
    //    Element* e = (Element*)ListCtrlNonModels->GetItemData(i);
    //    if (e != nullptr && e->GetType() == ELEMENT_TYPE_MODEL && e->GetSequenceElements() == nullptr)
    //    {
    //        delete e;
    //        ListCtrlNonModels->SetItemPtrData(i, (wxUIntPtr)nullptr);
    //    }
    //}

    delete _imageList;
}

void ViewsModelsPanel::PopulateModels(const std::string& selectModels)
{
    ListCtrlModels->Freeze();
    ListCtrlNonModels->Freeze();

    int topM = ListCtrlModels->GetTopItem();
    int topN = ListCtrlNonModels->GetTopItem();

    int itemSize = 0;
    if (ListCtrlModels->GetItemCount() > 0)
    {
        wxRect rect;
        ListCtrlModels->GetItemRect(0, rect);
        itemSize = rect.GetHeight();
    }
    else
    {
        // need to add something so i can measure it

        ListCtrlModels->AppendColumn("Test");
        ListCtrlModels->InsertItem(0, "Test");

        wxRect rect;
        ListCtrlModels->GetItemRect(0, rect);
        itemSize = rect.GetHeight();
    }
    wxASSERT(itemSize != 0);

    int visibileM = ListCtrlModels->GetRect().GetHeight() / itemSize - 1;
    int visibileN = ListCtrlNonModels->GetRect().GetHeight() / itemSize - 1;

    for (int i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
    {
        Element* e = (Element*)ListCtrlNonModels->GetItemData(i);
        if (e != nullptr && e->GetType() == ELEMENT_TYPE_MODEL && e->GetSequenceElements() == nullptr)
        {
            delete e;
            ListCtrlNonModels->SetItemPtrData(i, (wxUIntPtr)nullptr);
        }
    }

    ListCtrlNonModels->ClearAll();
    ListCtrlNonModels->SetImageList(_imageList, wxIMAGE_LIST_SMALL);

    wxListItem nm0;
    nm0.SetId(0);
    nm0.SetImage(-1);
    nm0.SetText(_(""));
    nm0.SetAlign(wxLIST_FORMAT_CENTER);
    ListCtrlNonModels->InsertColumn(0, nm0);

    wxListItem nm1;
    nm1.SetId(1);
    nm1.SetText(_("Timing/Model"));
    ListCtrlNonModels->InsertColumn(1, nm1);

    ListCtrlModels->ClearAll();

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_(""));
    col0.SetAlign(wxLIST_FORMAT_CENTER);
    ListCtrlModels->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(1);
    col1.SetText(_(""));
    col1.SetAlign(wxLIST_FORMAT_CENTER);
    ListCtrlModels->InsertColumn(1, col1);

    wxListItem col2;
    col2.SetId(2);
    col2.SetText(_("Timing/Model"));
    ListCtrlModels->InsertColumn(2, col2);

    _numModels = 0;
    _numNonModels = 0;
    int current_view = _sequenceElements->GetCurrentView();
    for (int i = 0; i < _sequenceElements->GetElementCount(); i++)
    {
        Element* elem = _sequenceElements->GetElement(i);
        if (elem->GetType() == ELEMENT_TYPE_TIMING)
        {
            TimingElement *te = dynamic_cast<TimingElement*>(elem);
            if (current_view == MASTER_VIEW || _sequenceElements->TimingIsPartOfView(te, current_view))
            {
                AddTimingToList(elem);
            }
            else
            {
                AddTimingToNotList(elem);
            }
        }
    }

    if (current_view > 0)
    {
        _sequenceViewManager->SetSelectedView(current_view);
        SequenceView * view = _sequenceViewManager->GetSelectedView();
        if (view != nullptr)
        {
            _sequenceElements->AddMissingModelsToSequence(view->GetModelsString());
            auto models = view->GetModels();
            for (auto it = models.begin(); it != models.end(); ++it)
            {
                Element* elem = _sequenceElements->GetElement(*it);
                AddModelToList(elem);
            }

            // add everything that isnt in the view
            for (int i = 0; i < _sequenceElements->GetElementCount(); i++)
            {
                Element* elem = _sequenceElements->GetElement(i);
                if (elem->GetType() == ELEMENT_TYPE_MODEL && std::find(models.begin(), models.end(), elem->GetName()) == models.end())
                {
                    AddModelToNotList(elem);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < _sequenceElements->GetElementCount(); i++)
        {
            Element* elem = _sequenceElements->GetElement(i);
            if (elem->GetType() == ELEMENT_TYPE_MODEL)
            {
                AddModelToList(elem);
            }
        }

        for (wxXmlNode* e = _modelGroups->GetChildren(); e != nullptr; e = e->GetNext())
        {
            if (e->GetName() == "modelGroup")
            {
                wxString name = e->GetAttribute("name");
                if (!_sequenceElements->ElementExists(name.ToStdString(), 0))
                {
                    ModelElement *me = new ModelElement(name.ToStdString());
                    AddModelToNotList(me);
                }
            }
        }

        for (wxXmlNode* e = _models->GetChildren(); e != nullptr; e = e->GetNext())
        {
            if (e->GetName() == "model")
            {
                wxString name = e->GetAttribute("name");
                if (!_sequenceElements->ElementExists(name.ToStdString(), 0))
                {
                    ModelElement *me = new ModelElement(name.ToStdString());
                    AddModelToNotList(me);
                }
            }
        }
    }

    if (ListCtrlModels->GetItemCount() > 0) {
        if (topM + visibileM - 1< ListCtrlModels->GetItemCount())
        {
            ListCtrlModels->EnsureVisible(topM + visibileM - 1);
        }
        ListCtrlModels->EnsureVisible(topM);
    }
    if (ListCtrlNonModels->GetItemCount() > 0) {
        if (topN + visibileN - 1< ListCtrlNonModels->GetItemCount())
        {
            ListCtrlNonModels->EnsureVisible(topN + visibileN - 1);
        }
        ListCtrlNonModels->EnsureVisible(topN);
    }
    
    if (selectModels != "")
    {
        wxArrayString models = wxSplit(selectModels, ',');

        for (auto it = models.begin(); it != models.end(); ++it)
        {
            SelectItem(ListCtrlModels, it->ToStdString(), 2, true);
        }
    }

    ListCtrlNonModels->SetColumnWidth(0, wxLIST_AUTOSIZE);
    if (ListCtrlNonModels->GetColumnWidth(0) < 22) {
        ListCtrlNonModels->SetColumnWidth(0, 22);
    }
    ListCtrlNonModels->SetColumnWidth(1, wxLIST_AUTOSIZE);

    ListCtrlModels->SetColumnWidth(0, wxLIST_AUTOSIZE);
    ListCtrlModels->SetColumnWidth(1, wxLIST_AUTOSIZE);
    if (ListCtrlModels->GetColumnWidth(0) < 28) {
        ListCtrlModels->SetColumnWidth(0, 28);
    }
    if (ListCtrlModels->GetColumnWidth(1) < 22) {
        ListCtrlModels->SetColumnWidth(1, 22);
    }
    ListCtrlModels->SetColumnWidth(2, wxLIST_AUTOSIZE);

    ListCtrlModels->Thaw();
    ListCtrlNonModels->Thaw();
    ListCtrlModels->Refresh();
    ListCtrlNonModels->Refresh();
}

bool ViewsModelsPanel::IsModelAGroup(const std::string& modelname) const
{
    for (auto it = _modelGroups->GetChildren(); it != nullptr; it = it->GetNext())
    {
        if (it->GetName() == "modelGroup" && it->GetAttribute("name") == modelname)
        {
            return true;
        }
    }
    return false;
}

wxArrayString ViewsModelsPanel::GetGroupModels(const std::string& group) const
{
    wxArrayString res;

    for (auto it = _modelGroups->GetChildren(); it != nullptr; it = it->GetNext())
    {
        if (it->GetName() == "modelGroup" && it->GetAttribute("name") == group)
        {
            res = wxSplit(it->GetAttribute("models"), ',');
            break;
        }
    }

    return res;
}

std::string ViewsModelsPanel::GetModelType(const std::string& modelname) const
{
    for (auto it = _models->GetChildren(); it != nullptr; it = it->GetNext())
    {
        if (it->GetAttribute("name") == modelname)
        {
            return it->GetAttribute("DisplayAs").ToStdString();
        }
    }
    return "";
}

bool ViewsModelsPanel::IsItemSelected(wxListCtrl* ctrl, int item)
{
    return ctrl->GetItemState(item, wxLIST_STATE_SELECTED) == wxLIST_STATE_SELECTED;
}

bool ViewsModelsPanel::SelectItem(wxListCtrl* ctrl, int item, bool select)
{
    return ctrl->SetItemState(item, select ? wxLIST_STATE_SELECTED : 0, wxLIST_STATE_SELECTED);
}

bool ViewsModelsPanel::SelectItem(wxListCtrl* ctrl, const std::string& item, int col, bool select)
{
    for (int i = 0; i < ctrl->GetItemCount(); ++i)
    {
        if (ctrl->GetItemText(i, col).ToStdString() == item)
        {
            return ctrl->SetItemState(i, select ? wxLIST_STATE_SELECTED : 0, wxLIST_STATE_SELECTED);
        }
    }
    return false;
}

void ViewsModelsPanel::OnListView_ViewItemsBeginDrag(wxListEvent& event)
{
    if (ListCtrlModels->GetSelectedItemCount() == 0) return;

    _dragRowModel = true;
    _dragRowNonModel = false;

    wxString drag = "Model";
    for (size_t i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        if (IsItemSelected(ListCtrlModels, i))
        {
            drag += "," + ListCtrlModels->GetItemText(i, 1);
        }
    }

    wxTextDataObject my_data(drag);
    VMDropSource dragSource(this, true, false);
    dragSource.SetData(my_data);
    dragSource.DoDragDrop(wxDrag_DefaultMove);
    SetCursor(wxCURSOR_ARROW);

    ValidateWindow();
}

void ViewsModelsPanel::OnListView_ViewItemsItemSelect(wxListEvent& event)
{
    ValidateWindow();
}

void ViewsModelsPanel::OnListView_ViewItemsKeyDown(wxListEvent& event)
{
    auto key = event.GetKeyCode();
    if (key == WXK_LEFT || key == WXK_DELETE || key == WXK_NUMPAD_DELETE)
    {
        RemoveSelectedModels();
    }
    ValidateWindow();
}

void ViewsModelsPanel::RemoveSelectedModels()
{
    if (_seqData->NumFrames() == 0) return;

    SaveUndo();

    if (_sequenceElements->GetCurrentView() == MASTER_VIEW)
    {
        bool hasEffects = false;
        for (size_t i = 0; i < ListCtrlModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlModels, i))
            {
                Element* e = (Element*)ListCtrlModels->GetItemData(i);
                if (e->HasEffects())
                {
                    hasEffects = true;
                    break;
                }
            }
        }

        if (!hasEffects || wxMessageBox("Delete all effects and layers for the selected model(s)?", "Confirm Delete?", wxICON_QUESTION | wxYES_NO) == wxYES)
        {
            for (size_t i = 0; i < ListCtrlModels->GetItemCount(); ++i)
            {
                if (IsItemSelected(ListCtrlModels, i))
                {
                    // Got a selected item so handle it
                    Element* e = (Element*)ListCtrlModels->GetItemData(i);
                    _sequenceElements->DeleteElement(e->GetName());
                }
            }
        }
    }
    else
    {
        for (size_t i = 0; i < ListCtrlModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlModels, i))
            {
                // Got a selected item so handle it
                Element* e = (Element*)ListCtrlModels->GetItemData(i);
                if (e->GetType() == ELEMENT_TYPE_MODEL)
                {
                    _sequenceElements->DeleteElementFromView(e->GetName(), _sequenceElements->GetCurrentView());
                }
                else
                {
                    _sequenceElements->DeleteTimingFromView(e->GetName(), _sequenceElements->GetCurrentView());
                    _sequenceElements->SetTimingVisibility(_sequenceElements->GetViewName(_sequenceElements->GetCurrentView()));
                }
            }
        }
        UpdateModelsForSelectedView();
    }

    MarkViewsChanged();
    PopulateModels();

    // Update Grid
    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::AddSelectedModels(int pos)
{
    if (_seqData->NumFrames() == 0) return;

    SaveUndo();

    int p = pos;

    std::string type = "model";
    int current_view = _sequenceElements->GetCurrentView();

    if (p == -1)
    {
        p = _sequenceElements->GetElementCount();
    }
    else
    {
        if (_sequenceViewManager->GetSelectedViewIndex() != MASTER_VIEW)
        {
            p -= GetTimingCount();
            if (p < 0) p = 0;
        }
    }

    wxArrayString addedModels;
    for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
    {
        if (IsItemSelected(ListCtrlNonModels, i))
        {
            addedModels.push_back(ListCtrlNonModels->GetItemText(i, 1));
        }
    }

    if (current_view == MASTER_VIEW)
    {
        int selcnt = 0;

        for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlNonModels, i))
            {
                Element* ee = (Element*)ListCtrlNonModels->GetItemData(i);
                if (ee != nullptr && ee->GetType() != ELEMENT_TYPE_TIMING)
                {
                    Element* e = _sequenceElements->AddElement(p + selcnt, ListCtrlNonModels->GetItemText(i, 1).ToStdString(), type, true, false, false, false);
                    if (e != nullptr)
                    {
                        e->AddEffectLayer();
                    }
                    selcnt++;
                }
            }
        }
    }
    else
    {
        int selcnt = 0;
        auto view = _sequenceViewManager->GetSelectedView();
        for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlNonModels, i))
            {
                Element* ee = (Element*)ListCtrlNonModels->GetItemData(i);
                if (ee != nullptr && ee->GetType() != ELEMENT_TYPE_TIMING)
                {
                    view->AddModel(ListCtrlNonModels->GetItemText(i, 1).ToStdString(), p + selcnt);
                    selcnt++;
                }
            }
        }

        _sequenceElements->AddMissingModelsToSequence(view->GetModelsString());
        for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlNonModels, i))
            {
                Element* e = _sequenceElements->GetElement(ListCtrlNonModels->GetItemText(i, 1).ToStdString());
                if (e != nullptr && e->GetType() != ELEMENT_TYPE_TIMING)
                {
                    e->SetVisible(true);
                }
            }
        }

        std::string modelsString = _sequenceElements->GetViewModels(view->GetName());
        _sequenceElements->PopulateView(modelsString, current_view);

        std::vector<std::string> timings;
        for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlNonModels, i))
            {
                Element* ee = (Element*)ListCtrlNonModels->GetItemData(i);
                if (ee != nullptr && ee->GetType() == ELEMENT_TYPE_TIMING)
                {
                    timings.push_back(ListCtrlNonModels->GetItemText(i, 1).ToStdString());
                }
            }
        }

        if (timings.size() > 0)
        {
            _sequenceElements->AddViewToTimings(timings, view->GetName());
        }

        _sequenceElements->SetTimingVisibility(view->GetName());
    }

    MarkViewsChanged();
    PopulateModels(wxJoin(addedModels, ',').ToStdString());

    // Update Grid
    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::OnButton_AddAllClick(wxCommandEvent& event)
{
    for (int i = 0; i < ListCtrlNonModels->GetItemCount(); i++)
    {
        ListCtrlNonModels->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    AddSelectedModels();

    ValidateWindow();
}

void ViewsModelsPanel::OnButton_AddSelectedClick(wxCommandEvent& event)
{
    AddSelectedModels();

    ValidateWindow();
}

void ViewsModelsPanel::OnButton_RemoveSelectedClick(wxCommandEvent& event)
{
    RemoveSelectedModels();

    ValidateWindow();
}

void ViewsModelsPanel::OnButton_RemoveAllClick(wxCommandEvent& event)
{
    for (int i = 0; i < ListCtrlModels->GetItemCount(); i++)
    {
        ListCtrlModels->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    RemoveSelectedModels();

    ValidateWindow();
}

void ViewsModelsPanel::Clear()
{
    ListCtrlModels->ClearAll();
    ListCtrlNonModels->ClearAll();
    ListCtrlViews->ClearAll();
}

void ViewsModelsPanel::Initialize()
{
    if (_seqData->NumFrames() == 0) {
        Clear();
        return;
    }

    PopulateViews();
    PopulateModels();

    // ensure the selected view exists ... this can happen if the user creates views but doesnt save them
    if (_sequenceViewManager->GetView(_sequenceElements->GetCurrentView()) == nullptr) _sequenceElements->SetCurrentView(0);

    SelectView(_sequenceElements->GetViewName(_sequenceElements->GetCurrentView()));
    ValidateWindow();
    wxSizeEvent se;
    OnResize(se);
}

void ViewsModelsPanel::SetSequenceElementsModelsViews(SequenceData* seqData, SequenceElements* sequenceElements, wxXmlNode* modelsNode, wxXmlNode* modelGroupsNode, SequenceViewManager* sequenceViewManager)
{
    _sequenceElements = sequenceElements;
    _seqData = seqData;
    _models = modelsNode;
    _sequenceViewManager = sequenceViewManager;
    _modelGroups = modelGroupsNode;
}

void ViewsModelsPanel::ValidateWindow()
{
    if (ListCtrlNonModels->GetItemCount() > 0)
    {
        Button_AddAll->Enable(true);
    }
    else
    {
        Button_AddAll->Enable(false);
    }

    if (ListCtrlModels->GetItemCount() > 0)
    {
        Button_RemoveAll->Enable(true);
    }
    else
    {
        Button_RemoveAll->Enable(false);
    }

    if (ListCtrlNonModels->GetSelectedItemCount() == 0)
    {
        Button_AddSelected->Enable(false);
    }
    else
    {
        Button_AddSelected->Enable(true);
    }

    if (ListCtrlModels->GetSelectedItemCount() == 0)
    {
        Button_RemoveSelected->Enable(false);
    }
    else
    {
        Button_RemoveSelected->Enable(true);
    }

    if (ListCtrlViews->GetSelectedItemCount() == 0)
    {
        ButtonClone->Enable(false);
    }
    else
    {
        ButtonClone->Enable(true);
    }
    if (ListCtrlViews->GetSelectedItemCount() == 0 || _sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        Button_DeleteView->Enable(false);
        ButtonRename->Enable(false);
    }
    else
    {
        Button_DeleteView->Enable(true);
        ButtonRename->Enable(true);
    }

    if (GetSelectedModelCount() > 0)
    {
        Button_MoveUp->Enable(true);
        Button_MoveDown->Enable(true);
    }
    else
    {
        Button_MoveUp->Enable(false);
        Button_MoveDown->Enable(false);
    }
}

void ViewsModelsPanel::UpdateModelsForSelectedView()
{
    int current_view = _sequenceElements->GetCurrentView();
    if (current_view != MASTER_VIEW)
    {
        wxString viewName = ListCtrlViews->GetItemText(current_view, 1);
        wxString models = "";
        for (int i = 0; i < _sequenceElements->GetElementCount(current_view); i++)
        {
            Element* elem = _sequenceElements->GetElement(i, current_view);
            if (elem->GetType() == ELEMENT_TYPE_MODEL)
            {
                if (models != "")
                {
                    models += ",";
                }
                models += elem->GetName();
            }
        }

        SequenceView* view = _sequenceViewManager->GetView(viewName.ToStdString());
        view->SetModels(models.ToStdString());
    }
    PopulateModels();
}

#pragma region View List
void ViewsModelsPanel::OnListCtrlViewsItemSelect(wxListEvent& event)
{
    int index = event.m_itemIndex;
    SelectView(ListCtrlViews->GetItemText(index, 1).ToStdString());
}

void ViewsModelsPanel::OnListCtrlItemCheck(wxCommandEvent& event)
{
    //int index = event.m_itemIndex;
    //SelectView(ListCtrlViews->GetItemText(index, 1).ToStdString());
    Element* e = (Element*)event.GetClientData();
    if (e == nullptr)
    {
        auto sv = _sequenceViewManager->GetSelectedView();

        int selected = 0;
        const int itemCount = ListCtrlViews->GetItemCount();
        for (int i = 0; i<itemCount; i++)
        {
            if (ListCtrlViews->IsChecked(i))
            {
                selected++;
            }
        }

        if (selected == 0)
        {
            SelectView(sv->GetName());
        }
        else if (selected == 2)
        {
            for (int i = 0; i < itemCount; i++)
            {
                if (ListCtrlViews->IsChecked(i))
                {
                    if (sv->GetName() == ListCtrlViews->GetItemText(i, 1))
                    {
                        ListCtrlViews->SetChecked(i, false);
                    }
                    else
                    {
                        SelectView(ListCtrlViews->GetItemText(i, 1).ToStdString());
                    }
                }
            }
        }
        else
        {
            bool found = false;
            for (int i = 0; i < itemCount; i++)
            {
                if (ListCtrlViews->IsChecked(i))
                {
                    if (!found)
                    {
                        found = true;
                        SelectView(ListCtrlViews->GetItemText(i, 1).ToStdString());
                    }
                    else
                    {
                        ListCtrlViews->SetChecked(i, false);
                    }
                }
            }
        }
    }
    else
    {
        e->SetVisible(!e->GetVisible());
    }

    MarkViewsChanged();

    // Update Grid
    _xlFrame->DoForceSequencerRefresh();
    ValidateWindow();
}

void ViewsModelsPanel::SelectView(const std::string& view)
{
    if (_seqData->NumFrames() == 0) return;

    if (view != _sequenceViewManager->GetSelectedView()->GetName())
    {
        ClearUndo();
    }

    ListCtrlViews->SetChecked(_sequenceElements->GetCurrentView(), false);
    int selected_view = GetViewIndex(view);
    if (selected_view > 0)
    {
        std::string modelsString = _sequenceElements->GetViewModels(view);
        _sequenceElements->AddMissingModelsToSequence(modelsString);
        _sequenceElements->PopulateView(modelsString, selected_view);
    }
    _sequenceViewManager->SetSelectedView(selected_view);
    _sequenceElements->SetCurrentView(selected_view);
    _sequenceElements->SetTimingVisibility(view);
    PopulateModels();
    ListCtrlViews->SetChecked(_sequenceElements->GetCurrentView(), true);
    _mainViewsChoice->SetStringSelection(view);

    _xlFrame->DoForceSequencerRefresh();
    ValidateWindow();
}

int ViewsModelsPanel::GetViewIndex(const wxString& name)
{
    return _sequenceViewManager->GetViewIndex(name.ToStdString());
}

void ViewsModelsPanel::MarkViewsChanged()
{
    wxCommandEvent eventRgbEffects(EVT_RGBEFFECTS_CHANGED);
    wxPostEvent(GetParent(), eventRgbEffects);
}

// This gives the panel a pointer to the view choice box on the sequencer tab
void ViewsModelsPanel::SetViewChoice(wxChoice* choice)
{
    _mainViewsChoice = choice;

    // this directs events from sequencer tab
    _mainViewsChoice->Connect(wxEVT_CHOICE, (wxObjectEventFunction)&ViewsModelsPanel::OnViewSelect, nullptr, this);
}

void ViewsModelsPanel::OnViewSelect(wxCommandEvent &event) {
    SelectView(_mainViewsChoice->GetString(_mainViewsChoice->GetSelection()).ToStdString());
    ValidateWindow();
}

void ViewsModelsPanel::PopulateViews()
{
    ListCtrlViews->ClearAll();
    if (_mainViewsChoice != nullptr) {
        _mainViewsChoice->Clear();
    }

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_(""));
    col0.SetWidth(30);
    col0.SetAlign(wxLIST_FORMAT_CENTER);
    ListCtrlViews->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(1);
    col1.SetText(_("View"));
    ListCtrlViews->InsertColumn(1, col1);

    _numViews = 0;
    auto views = _sequenceViewManager->GetViews();
    for (auto it = views.begin(); it != views.end(); ++it)
    {
        bool isChecked = _sequenceViewManager->GetSelectedView() == *it;
        AddViewToList((*it)->GetName(), isChecked);
        if (isChecked)
        {
            ListCtrlViews->SetChecked(0, false);
        }
    }
    ListCtrlViews->SetColumnWidth(0, wxLIST_AUTOSIZE);
    if (ListCtrlViews->GetColumnWidth(0) < 30) {
        ListCtrlViews->SetColumnWidth(0, 30);
    }
    ListCtrlViews->SetColumnWidth(1, wxLIST_AUTOSIZE);
    _mainViewsChoice->SetSelection(_sequenceViewManager->GetSelectedViewIndex());
}

void ViewsModelsPanel::AddViewToList(const wxString& viewName, bool isChecked)
{
    wxListItem li;
    li.SetId(_numViews);
    ListCtrlViews->InsertItem(li);
    ListCtrlViews->SetItem(_numViews, 1, viewName);
    ListCtrlViews->SetChecked(_numViews, isChecked);
    _numViews++;

    _mainViewsChoice->Append(viewName);
}

void ViewsModelsPanel::OnButton_AddViewClick(wxCommandEvent& event)
{
    if (_seqData->NumFrames() == 0) return;

    std::string viewName = "";
    int DlgResult = wxID_OK;

    do
    {
        wxTextEntryDialog dialog(this, _("Enter Name for View"), _("Create View"));
        DlgResult = dialog.ShowModal();
        viewName = dialog.GetValue().Trim().ToStdString();
    } while (DlgResult == wxID_OK && (viewName == "" || _sequenceViewManager->GetView(viewName) != nullptr));

    if (DlgResult != wxID_OK) return;

    _sequenceViewManager->AddView(viewName);
    AddViewToList(viewName, true);
    _sequenceElements->AddView(viewName);
    SelectView(viewName);
    MarkViewsChanged();
    PopulateViews();
    ValidateWindow();
}

wxString ViewsModelsPanel::GetMasterViewModels() const
{
    wxArrayString models;
    for (int i = 0; i < _sequenceElements->GetElementCount(); i++)
    {
        Element* elem = _sequenceElements->GetElement(i);
        if (elem->GetType() == ELEMENT_TYPE_MODEL)
        {
            models.push_back(elem->GetName());
        }
    }
    return wxJoin(models, ',');
}

void ViewsModelsPanel::OnButtonCloneClick(wxCommandEvent& event)
{
    if (_seqData->NumFrames() == 0) return;

    int itemIndex = ListCtrlViews->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    std::string oldName = _sequenceElements->GetViewName(itemIndex);

    std::string newName = "Copy Of " + oldName;
    int DlgResult = wxID_OK;

    do
    {
        wxTextEntryDialog dialog(this, _("Enter Name for View"), _("Create View"), newName);
        DlgResult = dialog.ShowModal();
        newName = dialog.GetValue().Trim().ToStdString();
    } while (DlgResult == wxID_OK && (newName == "" || _sequenceViewManager->GetView(newName) != nullptr));

    if (DlgResult != wxID_OK) return;

    SequenceView* view = _sequenceViewManager->AddView(newName);
    if (itemIndex == MASTER_VIEW)
    {
        wxArrayString models;
        for (int i = 0; i < _sequenceElements->GetElementCount(); i++)
        {
            Element* elem = _sequenceElements->GetElement(i);
            if (elem->GetType() == ELEMENT_TYPE_MODEL)
            {
                models.push_back(elem->GetName());
            }
        }
        view->SetModels(wxJoin(models, ',').ToStdString());
    }
    else
    {
        view->SetModels(_sequenceViewManager->GetView(oldName)->GetModelsString());
    }

    AddViewToList(newName, true);
    _sequenceElements->AddView(newName);

    std::vector<std::string> timings;
    for (int i = 0; i < _sequenceElements->GetElementCount(itemIndex); i++)
    {
        Element* elem = _sequenceElements->GetElement(i);
        if (elem->GetType() == ELEMENT_TYPE_TIMING)
        {
            timings.push_back(elem->GetName());
        }
    }
    _sequenceElements->AddViewToTimings(timings, view->GetName());
    _sequenceElements->SetTimingVisibility(view->GetName());

    SelectView(newName);
    MarkViewsChanged();
    PopulateViews();
    ValidateWindow();
}

void ViewsModelsPanel::OnListCtrlViewsItemDClick(wxListEvent& event)
{
    if (_seqData->NumFrames() == 0) return;
    if (event.GetIndex() > 0)
    {
        RenameView(event.GetIndex());
    }
}

void ViewsModelsPanel::RenameView(int itemIndex)
{
    std::string oldName = _sequenceElements->GetViewName(itemIndex);

    std::string newName = oldName;
    int DlgResult = wxID_OK;

    do
    {
        wxTextEntryDialog dialog(this, _("Enter Name for View"), _("Create View"), newName);
        DlgResult = dialog.ShowModal();
        newName = dialog.GetValue().Trim().ToStdString();
    } while (DlgResult == wxID_OK && (newName == "" || _sequenceViewManager->GetView(newName) != nullptr));

    if (DlgResult != wxID_OK || oldName == newName) return;

    _sequenceViewManager->RenameView(oldName, newName);

    MarkViewsChanged();
    PopulateViews();
    ValidateWindow();
}

void ViewsModelsPanel::OnButtonRenameClick(wxCommandEvent& event)
{
    if (_seqData->NumFrames() == 0) return;

    int itemIndex = ListCtrlViews->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    RenameView(itemIndex);
}

void ViewsModelsPanel::DeleteSelectedView()
{
    if (_seqData->NumFrames() == 0) return;

    int result = wxMessageBox("Are you sure you want to delete this View?", "Confirm Deletion", wxOK | wxCANCEL | wxCENTER);
    if (result != wxOK) return;

    ListCtrlViews->Freeze();
    long itemIndex = -1;

    for (;;) {
        itemIndex = ListCtrlViews->GetNextItem(itemIndex,
            wxLIST_NEXT_ALL,
            wxLIST_STATE_SELECTED);

        if (itemIndex == -1) break;

        // Got a selected item so handle it
        if (itemIndex > 0)  // don't delete master view
        {
            _sequenceElements->RemoveView(itemIndex);
            wxString name = _sequenceElements->GetViewName(itemIndex);
            _sequenceViewManager->DeleteView(name.ToStdString());

            ListCtrlViews->DeleteItem(itemIndex);
            _numViews--;
            break;
        }
        itemIndex = -1; // reset to delete next item which may have same index
    }
    ListCtrlViews->Thaw();
    ListCtrlViews->Refresh();
    _sequenceElements->SetCurrentView(MASTER_VIEW);
    SelectView("Master View");
    MarkViewsChanged();
    PopulateViews();
    ValidateWindow();
}

void ViewsModelsPanel::OnButton_DeleteViewClick(wxCommandEvent& event)
{
    DeleteSelectedView();
}
#pragma endregion

void ViewsModelsPanel::OnResize(wxSizeEvent& event)
{
    // a minimum size is cached deep inside someplace, reset them all
    ListCtrlViews->SetMinSize(wxSize(-1, -1));
    ListCtrlNonModels->SetMinSize(wxSize(150, -1));
    ListCtrlModels->SetMinSize(wxSize(-1, -1));
    Panel_Sizer->SetMinSize(wxSize(-1, -1));
    Panel_Sizer->GetSizer()->SetMinSize(-1, -1);
    ScrolledWindowViewsModels->SetVirtualSize(-1, -1);
    ScrolledWindowViewsModels->SetClientSize(-1, -1);
    ScrolledWindowViewsModels->SetMinSize(wxSize(-1, -1));
    ScrollWindowSizer->SetMinSize(wxSize(-1, -1));

    wxSize s = GetSize();
    Panel_Sizer->SetSize(s);
    Panel_Sizer->SetMaxSize(s);
    Panel_Sizer->Refresh();

    s -= wxSize(10, 10); //account for the border
    ScrolledWindowViewsModels->SetSize(s);
    ScrolledWindowViewsModels->SetMaxSize(s);

    ScrolledWindowViewsModels->FitInside();
    ScrolledWindowViewsModels->SetScrollRate(5, 5);
    ScrolledWindowViewsModels->Refresh();
}

void ViewsModelsPanel::OnLeftUp(wxMouseEvent& event)
{
    _xlFrame->DoForceSequencerRefresh();
    ValidateWindow();
}

#pragma region Non Models

void ViewsModelsPanel::AddTimingToNotList(Element* timing)
{
    if (timing != nullptr)
    {
        wxListItem li;
        li.SetId(_numNonModels);
        li.SetText(_(""));
        ListCtrlNonModels->InsertItem(li, 0);
        ListCtrlNonModels->SetItemPtrData(_numNonModels, (wxUIntPtr)timing);
        ListCtrlNonModels->SetItem(_numNonModels, 1, timing->GetName());

        _numNonModels++;
    }
}

void ViewsModelsPanel::AddModelToNotList(Element* model)
{
    if (model != nullptr)
    {
        wxListItem li;
        li.SetId(_numNonModels);
        li.SetText(_(""));
        if (IsModelAGroup(model->GetName()))
        {
            ListCtrlNonModels->InsertItem(li, 1);
        }
        else
        {
            ListCtrlNonModels->InsertItem(li, -1);
        }
        ListCtrlNonModels->SetItemPtrData(_numNonModels, (wxUIntPtr)model);
        ListCtrlNonModels->SetItem(_numNonModels, 1, model->GetName());

        _numNonModels++;
    }
}

void ViewsModelsPanel::OnListCtrlNonModelsItemSelect(wxListEvent& event)
{
    ValidateWindow();
}

void ViewsModelsPanel::OnListCtrlNonModelsBeginDrag(wxListEvent& event)
{
    if (ListCtrlNonModels->GetSelectedItemCount() == 0) return;

    _dragRowModel = false;
    _dragRowNonModel = true;

    wxString drag = "NonModel";
    for (size_t i = 0; i < ListCtrlNonModels->GetItemCount(); ++i)
    {
        if (IsItemSelected(ListCtrlNonModels, i))
        {
            drag += "," + ListCtrlNonModels->GetItemText(i, 1);
        }
    }

    wxTextDataObject my_data(drag);
    VMDropSource dragSource(this, false, true);
    dragSource.SetData(my_data);
    dragSource.DoDragDrop(wxDrag_DefaultMove);
    SetCursor(wxCURSOR_ARROW);

    ValidateWindow();
}

void ViewsModelsPanel::OnListCtrlNonModelsKeyDown(wxListEvent& event)
{
    if (event.GetKeyCode() == WXK_RIGHT)
    {
        AddSelectedModels();
    }
    ValidateWindow();
}

#pragma endregion Non Models

#pragma region Models

void ViewsModelsPanel::OnListCtrlModelsItemRClick(wxListEvent& event)
{
    ListCtrlModels->SetFocus();

    int items = ListCtrlModels->GetItemCount();
    int models = items - GetTimingCount();
    bool isGroup = false;
    if (event.GetIndex() != -1)
    {
        isGroup = IsModelAGroup(ListCtrlModels->GetItemText(event.GetIndex(), 2).ToStdString());
    }

    wxMenu mnu;
    mnu.Append(ID_MODELS_UNDO, "Undo")->Enable(_undo.size() > 0);
    mnu.Append(ID_MODELS_HIDEALL, "Hide All")->Enable(items > 0);
    mnu.Append(ID_MODELS_HIDEUNUSED, "Hide Unused")->Enable(items > 0);
    mnu.Append(ID_MODELS_SHOWALL, "Show All")->Enable(items > 0);
    mnu.Append(ID_MODELS_REMOVEUNUSED, "Remmove Unused")->Enable(items > 0);
    mnu.Append(ID_MODELS_SELECTALL, "Select All")->Enable(items >0);

    wxMenu* mnuSort = new wxMenu();

    mnuSort->Append(ID_MODELS_SORTBYNAME, "By Name")->Enable(models > 0);
    mnuSort->Append(ID_MODELS_SORTBYNAMEGM, "By Name But Groups At Top")->Enable(models > 0);
    mnuSort->Append(ID_MODELS_SORTBYTYPE, "By Type")->Enable(models > 0);
    mnuSort->Append(ID_MODELS_SORTMODELSUNDERTHISGROUP, "Models Under This Group")->Enable(isGroup);
    mnuSort->Append(ID_MODELS_BUBBLEUPGROUPS, "Bubble Up Groups")->Enable(models > 0);

    mnuSort->Connect(wxEVT_MENU, (wxObjectEventFunction)&ViewsModelsPanel::OnModelsPopup, nullptr, this);

    mnu.Append(ID_MODELS_SORT, "Sort", mnuSort, "");
    mnu.Connect(wxEVT_MENU, (wxObjectEventFunction)&ViewsModelsPanel::OnModelsPopup, nullptr, this);

    PopupMenu(&mnu);
    ListCtrlModels->SetFocus();
}

void ViewsModelsPanel::OnModelsPopup(wxCommandEvent &event)
{
    int id = event.GetId();
    int item = ListCtrlModels->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (id == ID_MODELS_HIDEALL)
    {
        ShowAllModels(false);
    }
    else if (id == ID_MODELS_UNDO)
    {
        Undo();
    }
    else if (id == ID_MODELS_SHOWALL)
    {
        ShowAllModels(true);
    }
    else if (id == ID_MODELS_SELECTALL)
    {
        SelectAllModels();
    }
    else if (id == ID_MODELS_HIDEUNUSED)
    {
        HideUnusedModels();
    }
    else if (id == ID_MODELS_REMOVEUNUSED)
    {
        RemoveUnusedModels();
    }
    else if (id == ID_MODELS_SORTBYNAME)
    {
        SortModelsByName();
    }
    else if (id == ID_MODELS_SORTBYNAMEGM)
    {
        SortModelsByNameGM();
    }
    else if (id == ID_MODELS_SORTBYTYPE)
    {
        SortModelsByType();
    }
    else if (id == ID_MODELS_SORTMODELSUNDERTHISGROUP)
    {
        SortModelsUnderThisGroup(item);
    }
    else if (id == ID_MODELS_BUBBLEUPGROUPS)
    {
        SortModelsBubbleUpGroups();
    }
    ValidateWindow();
}

void ViewsModelsPanel::ShowAllModels(bool show)
{
    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        ListCtrlModels->SetChecked(i, show);
        ((Element*)ListCtrlModels->GetItemData(i))->SetVisible(show);
    }
    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::HideUnusedModels()
{
    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        Element* element = (Element*)ListCtrlModels->GetItemData(i);
        if (!element->HasEffects())
        {
            ListCtrlModels->SetChecked(i, false);
            ((Element*)ListCtrlModels->GetItemData(i))->SetVisible(false);
        }
    }
    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::RemoveUnusedModels()
{
    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        Element* element = (Element*)ListCtrlModels->GetItemData(i);
        if (!element->HasEffects())
        {
            SelectItem(ListCtrlModels, i, true);
        }
        else
        {
            SelectItem(ListCtrlModels, i, false);
        }
    }
    RemoveSelectedModels();
    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::SelectAllModels()
{
    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        SelectItem(ListCtrlModels, i, true);
    }
}

void ViewsModelsPanel::SortModelsByName()
{
    SaveUndo();

    SequenceView* view = _sequenceViewManager->GetSelectedView();
    wxString models;
    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        models = GetMasterViewModels();
    }
    else
    {
        models = view->GetModelsString();
    }

    wxArrayString modelArray = wxSplit(models, ',');
    modelArray.Sort();

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(modelArray);
    }
    else
    {
        view->SetModels(wxJoin(modelArray, ',').ToStdString());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();

    _xlFrame->DoForceSequencerRefresh();
}

wxArrayString ViewsModelsPanel::MergeStringArrays(const wxArrayString& arr1, const wxArrayString& arr2)
{
    wxArrayString res = arr1;

    for (auto it = arr2.begin(); it != arr2.end(); ++it)
    {
        res.push_back(*it);
    }

    return res;
}

void ViewsModelsPanel::SetMasterViewModels(const wxArrayString& models)
{
    for (int i = 0; i < models.size(); ++i)
    {
        int index = _sequenceElements->GetElementIndex(models[i].ToStdString(), MASTER_VIEW);
        if (index < 0)
        {
            _sequenceElements->AddElement(i + GetTimingCount(), models[i].ToStdString(), "model", true, false, false, false);
        }
        else
        {
            _sequenceElements->MoveSequenceElement(index, i + GetTimingCount(), MASTER_VIEW);
        }
    }
}

void ViewsModelsPanel::SortModelsByNameGM()
{
    SaveUndo();

    SequenceView* view = _sequenceViewManager->GetSelectedView();

    wxString models;
    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        models = GetMasterViewModels();
    }
    else
    {
        models = view->GetModelsString();
    }

    wxArrayString modelArray = wxSplit(models, ',');

    wxArrayString groups;
    wxArrayString modelsOnly;

    for (auto it = modelArray.begin(); it != modelArray.end(); ++it)
    {
        if (IsModelAGroup(it->ToStdString()))
        {
            groups.push_back(*it);
        }
        else
        {
            modelsOnly.push_back(*it);
        }
    }

    groups.Sort();
    modelsOnly.Sort();

    modelArray = MergeStringArrays(groups, modelsOnly);

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(modelArray);
    }
    else
    {
        view->SetModels(wxJoin(modelArray, ',').ToStdString());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();

    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::SortModelsByType()
{
    SaveUndo();

    SequenceView* view = _sequenceViewManager->GetSelectedView();
    wxString models;
    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        models = GetMasterViewModels();
    }
    else
    {
        models = view->GetModelsString();
    }

    wxArrayString modelArray = wxSplit(models, ',');

    wxArrayString groups;
    std::map<std::string, wxArrayString> typeModels;

    for (auto it = modelArray.begin(); it != modelArray.end(); ++it)
    {
        if (IsModelAGroup(it->ToStdString()))
        {
            groups.push_back(*it);
        }
        else
        {
            std::string type = GetModelType(it->ToStdString());
            if (typeModels.find(type) == typeModels.end())
            {
                wxArrayString arr;
                arr.push_back(*it);
                typeModels[type] = arr;
            }
            else
            {
                typeModels[type].push_back(*it);
            }
        }
    }

    modelArray = groups;

    for (auto it = typeModels.begin(); it != typeModels.end(); ++it)
    {
        modelArray = MergeStringArrays(modelArray, it->second);
    }

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(modelArray);
    }
    else
    {
        view->SetModels(wxJoin(modelArray, ',').ToStdString());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();

    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::SortModelsUnderThisGroup(int groupIndex)
{
    SaveUndo();

    SequenceView* view = _sequenceViewManager->GetSelectedView();
    wxString models;
    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        models = GetMasterViewModels();
    }
    else
    {
        models = view->GetModelsString();
    }

    wxArrayString modelArray = wxSplit(models, ',');

    std::string group = modelArray[groupIndex - GetTimingCount()].ToStdString();

    wxArrayString groupModels = GetGroupModels(group);

    for (auto it = groupModels.rbegin(); it != groupModels.rend(); ++it)
    {
        if (std::find(modelArray.begin(), modelArray.end(), *it) != modelArray.end())
        {
            modelArray.erase(std::find(modelArray.begin(), modelArray.end(), *it));
            auto groupit = std::find(modelArray.begin(), modelArray.end(), group);
            ++groupit;
            modelArray.insert(groupit, *it);
        }
    }

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(modelArray);
    }
    else
    {
        view->SetModels(wxJoin(modelArray, ',').ToStdString());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();

    _xlFrame->DoForceSequencerRefresh();
}

void ViewsModelsPanel::SortModelsBubbleUpGroups()
{
    SaveUndo();

    SequenceView* view = _sequenceViewManager->GetSelectedView();
    wxString models;
    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        models = GetMasterViewModels();
    }
    else
    {
        models = view->GetModelsString();
    }

    wxArrayString modelArray = wxSplit(models, ',');

    wxArrayString groups;
    wxArrayString modelsOnly;

    for (auto it = modelArray.begin(); it != modelArray.end(); ++it)
    {
        if (IsModelAGroup(it->ToStdString()))
        {
            groups.push_back(*it);
        }
        else
        {
            modelsOnly.push_back(*it);
        }
    }

    modelArray = MergeStringArrays(groups, modelsOnly);

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(modelArray);
    }
    else
    {
        view->SetModels(wxJoin(modelArray, ',').ToStdString());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();

    _xlFrame->DoForceSequencerRefresh();
}

int ViewsModelsPanel::GetTimingCount()
{
    int timings = 0;

    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        Element* t = (Element*)ListCtrlModels->GetItemData(i);
        if (t->GetType() == ELEMENT_TYPE_TIMING)
        {
            timings++;
        }
        else
        {
            break;
        }
    }

    return timings;
}

void ViewsModelsPanel::AddTimingToList(Element* timing)
{
    if (timing != nullptr)
    {
        wxListItem li;
        li.SetId(_numModels);
        ListCtrlModels->InsertItem(li);
        ListCtrlModels->SetItemPtrData(_numModels, (wxUIntPtr)timing);
        ListCtrlModels->SetItem(_numModels, 2, timing->GetName());
        ListCtrlModels->SetChecked(_numModels, timing->GetVisible());
        ListCtrlModels->SetItemColumnImage(_numModels, 1, TIMING_IMAGE);
        _numModels++;
    }
}

void ViewsModelsPanel::AddModelToList(Element* model)
{
    if (model != nullptr)
    {
        wxListItem li;
        li.SetId(_numModels);
        ListCtrlModels->InsertItem(li);
        ListCtrlModels->SetItemPtrData(_numModels, (wxUIntPtr)model);
        ListCtrlModels->SetItem(_numModels, 2, model->GetName());
        ListCtrlModels->SetChecked(_numModels, model->GetVisible());
        // Need to solve this ... I think we only want images for groups.
        if (IsModelAGroup(model->GetName()))
        {
            ListCtrlModels->SetItemColumnImage(_numModels, 1, MODEL_IMAGE);
        }
        _numModels++;
    }
}

void ViewsModelsPanel::OnListCtrlViewsKeyDown(wxListEvent& event)
{
    auto key = event.GetKeyCode();
    if ((key == WXK_DELETE || key == WXK_NUMPAD_DELETE) && Button_DeleteView->IsEnabled())
    {
        DeleteSelectedView();
    }
}

#pragma endregion Models

#pragma region Drag and Drop

wxDragResult MyTextDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    static int MINSCROLLDELAY = 10;
    static int STARTSCROLLDELAY = 300;
    static int scrollDelay = STARTSCROLLDELAY;
    static wxLongLong lastTime = wxGetUTCTimeMillis();

    if (wxGetUTCTimeMillis() - lastTime < scrollDelay)
    {
        // too soon to scroll again
    }
    else
    {
        if (_type == "Model" && _list->GetItemCount() > 0)
        {
            int flags = wxLIST_HITTEST_ONITEM;
            int lastItem = _list->HitTest(wxPoint(x, y), flags, nullptr);

            for (int i = 0; i < _list->GetItemCount(); ++i)
            {
                if (i == lastItem)
                {
                    _list->SetItemState(i, wxLIST_STATE_DROPHILITED, wxLIST_STATE_DROPHILITED);
                }
                else
                {
                    _list->SetItemState(i, 0, wxLIST_STATE_DROPHILITED);
                }
            }

            wxRect rect;
            _list->GetItemRect(0, rect);
            int itemSize = rect.GetHeight();

            if (y < 2 * itemSize)
            {
                // scroll up
                if (_list->GetTopItem() > 0)
                {
                    lastTime = wxGetUTCTimeMillis();
                    _list->EnsureVisible(_list->GetTopItem()-1);
                    scrollDelay = scrollDelay / 2;
                    if (scrollDelay < MINSCROLLDELAY) scrollDelay = MINSCROLLDELAY;
                }
            }
            else if (y > _list->GetRect().GetHeight() - itemSize)
            {
                // scroll down
                if (lastItem >= 0 && lastItem < _list->GetItemCount())
                {
                    _list->EnsureVisible(lastItem+1);
                    lastTime = wxGetUTCTimeMillis();
                    scrollDelay = scrollDelay / 2;
                    if (scrollDelay < MINSCROLLDELAY) scrollDelay = MINSCROLLDELAY;
                }
            }
            else
            {
                scrollDelay = STARTSCROLLDELAY;
            }
        }
    }

    return wxDragMove;
}

bool MyTextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
    long mousePos = x;
    mousePos = mousePos << 16;
    mousePos += y;
    wxCommandEvent event(EVT_VMDROP);
    event.SetString(data); // this is the dropped string
    event.SetExtraLong(mousePos); // this is the mouse position packed into a long

    wxArrayString parms = wxSplit(data, ',');

    if (parms[0] == "NonModel")
    {
        if (_type == "Model")
        {
            event.SetInt(0);
            wxPostEvent(_owner, event);
            return true;
        }
    }
    else if (parms[0] == "Model")
    {
        if (_type == "Model")
        {
            event.SetInt(1);
            wxPostEvent(_owner, event);
            return true;
        }
        else if (_type == "NonModel")
        {
            event.SetInt(2);
            wxPostEvent(_owner, event);
            return true;
        }
    }

    return false;
}

void ViewsModelsPanel::OnDrop(wxCommandEvent& event)
{
    wxArrayString parms = wxSplit(event.GetString(), ',');
    int x = event.GetExtraLong() >> 16;
    int y = event.GetExtraLong() & 0xFFFF;

    switch(event.GetInt())
    {
    case 0:
        // Non model dropped into models (an add)
        {
            int flags = wxLIST_HITTEST_ONITEM;
            long index = ListCtrlModels->HitTest(wxPoint(x, y), flags, nullptr);
            AddSelectedModels(index);
        }
        break;
    case 1:
        // Model dropped into models (a reorder)
        {
            int flags = wxLIST_HITTEST_ONITEM;
            long index = ListCtrlModels->HitTest(wxPoint(x, y), flags, nullptr);

            MoveSelectedModelsTo(index);
        }
        break;
    case 2:
        // Model dropped into non model (a remove)
        RemoveSelectedModels();
        break;
    default:
        break;
    }
}

#pragma endregion Drag and Drop

#pragma region Undo

void ViewsModelsPanel::SaveUndo()
{
    wxArrayString undo;
    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        undo.push_back(ListCtrlModels->GetItemText(i, 2).ToStdString());
    }
    std::string to = wxJoin(undo, ',').ToStdString();
    if (undo.size() > 0 && undo.back() != to)
    {
        _undo.push_back(to);
    }
}

void ViewsModelsPanel::Undo()
{
    if (_undo.size() == 0) return;

    std::string undo = _undo.back();
    _undo.pop_back();

    std::vector<std::string> timings;
    wxArrayString models;

    wxArrayString arr = wxSplit(undo, ',');

    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        Element* e = _sequenceElements->GetElement(it->ToStdString());
        if (e == nullptr)
        {
            // this cant be undone
        }
        else
        {
            if (e->GetType() == ELEMENT_TYPE_TIMING)
            {
                timings.push_back(it->ToStdString());
            }
            else
            {
                models.push_back(*it);
            }
        }
    }

    if (_sequenceViewManager->GetSelectedViewIndex() == MASTER_VIEW)
    {
        SetMasterViewModels(models);
    }
    else
    {
        _sequenceViewManager->GetSelectedView()->SetModels(wxJoin(models, ',').ToStdString());
    }

    _sequenceElements->DeleteTimingsFromView(_sequenceViewManager->GetSelectedViewIndex());
    if (timings.size() > 0)
    {
        _sequenceElements->AddViewToTimings(timings, _sequenceViewManager->GetSelectedView()->GetName());
    }

    SelectView(_sequenceViewManager->GetSelectedView()->GetName());
    MarkViewsChanged();
    PopulateModels();
    _xlFrame->DoForceSequencerRefresh();
    ValidateWindow();
}

void ViewsModelsPanel::ClearUndo()
{
    _undo.clear();
}

#pragma endregion Undo

void ViewsModelsPanel::OnButton_MoveDownClick(wxCommandEvent& event)
{
    if (GetSelectedModelCount() == 0) return;

    SaveUndo();
    bool itemsMoved = false;

    wxArrayString movedModels;
    int selcnt = 0;

    for (int i = ListCtrlModels->GetItemCount()-1; i >= 0; --i)
    {
        if (IsItemSelected(ListCtrlModels, i) && ((Element*)ListCtrlModels->GetItemData(i))->GetType() != ELEMENT_TYPE_TIMING)
        {
            itemsMoved = true;
            int from = i;
            int to = i + 2;
            if (to > ListCtrlModels->GetItemCount()) return;

            movedModels.push_back(ListCtrlModels->GetItemText(i, 2));
            from -= GetTimingCount();

            to -= GetTimingCount();

            // not sure why we need to do this with the master only
            if (_sequenceViewManager->GetSelectedViewIndex() == 0)
            {
                from += GetTimingCount();
                to += GetTimingCount();
            }

            _sequenceElements->MoveSequenceElement(from, to, _sequenceViewManager->GetSelectedViewIndex());
            SelectItem(ListCtrlModels, i, false);

            selcnt++;
            i++;
        }
    }

    if (itemsMoved)
    {
        MarkViewsChanged();
        UpdateModelsForSelectedView();
        PopulateModels(wxJoin(movedModels, ',').ToStdString());
        _xlFrame->DoForceSequencerRefresh();
    }
}

int ViewsModelsPanel::GetSelectedModelCount()
{
    int count = 0;

    for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
    {
        if (IsItemSelected(ListCtrlModels, i) && ((Element*)ListCtrlModels->GetItemData(i))->GetType() != ELEMENT_TYPE_TIMING)
        {
            count++;
        }
    }

    return count;
}

void ViewsModelsPanel::MoveSelectedModelsTo(int indexTo)
{
    SaveUndo();
    bool itemsMoved = false;

    wxArrayString movedModels;
    int selcnt = 0;
        for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlModels, i) && ((Element*)ListCtrlModels->GetItemData(i))->GetType() != ELEMENT_TYPE_TIMING)
            {
                movedModels.push_back(ListCtrlModels->GetItemText(i, 2));
                int from = i - GetTimingCount();
                int to = -1;
                // we are moving this one
                itemsMoved = true;
                if (indexTo == -1)
                {
                    // moving to the end
                    to = _sequenceElements->GetElementCount(_sequenceViewManager->GetSelectedViewIndex());
                }
                else
                {
                    to = indexTo + selcnt - GetTimingCount();
                }

                // not sure why we need to do this with the master only
                if (_sequenceViewManager->GetSelectedViewIndex() == 0)
                {
                    from += GetTimingCount();
                    to += GetTimingCount();
                }

                if (from < to)
                {
                    from -= selcnt;
                    to -= selcnt;
                }

                _sequenceElements->MoveSequenceElement(from, to, _sequenceViewManager->GetSelectedViewIndex());
                SelectItem(ListCtrlModels, i, false);

                selcnt++;
                i--;
            }
        }

    if (itemsMoved)
    {
        MarkViewsChanged();
        UpdateModelsForSelectedView();
        PopulateModels(wxJoin(movedModels, ',').ToStdString());
        _xlFrame->DoForceSequencerRefresh();
    }
}

void ViewsModelsPanel::OnButton_MoveUpClick(wxCommandEvent& event)
{
    if (GetSelectedModelCount() == 0) return;

    SaveUndo();
    bool itemsMoved = false;

    wxArrayString movedModels;
    int selcnt = 0;

        for (int i = 0; i < ListCtrlModels->GetItemCount(); ++i)
        {
            if (IsItemSelected(ListCtrlModels, i) && ((Element*)ListCtrlModels->GetItemData(i))->GetType() != ELEMENT_TYPE_TIMING)
            {
                itemsMoved = true;
                int from = i;
                int to = i - 1;
                if (to < GetTimingCount()) return;

                movedModels.push_back(ListCtrlModels->GetItemText(i, 2));
                from -= GetTimingCount();
                to -= GetTimingCount();

                // not sure why we need to do this with the master only
                if (_sequenceViewManager->GetSelectedViewIndex() == 0)
                {
                    from += GetTimingCount();
                    to += GetTimingCount();
                }

                _sequenceElements->MoveSequenceElement(from, to, _sequenceViewManager->GetSelectedViewIndex());
                SelectItem(ListCtrlModels, i, false);

                selcnt++;
            }
        }

    if (itemsMoved)
    {
        MarkViewsChanged();
        UpdateModelsForSelectedView();
        PopulateModels(wxJoin(movedModels, ',').ToStdString());
        _xlFrame->DoForceSequencerRefresh();
    }
}