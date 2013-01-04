/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#ifndef EVENTSEDITOR_H
#define EVENTSEDITOR_H

//(*Headers(EventsEditor)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/statbmp.h>
#include <wx/scrolbar.h>
//*)
#include <wx/ribbon/page.h>
#include <wx/ribbon/buttonbar.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"
#include "GDCore/Events/Event.h"
#include "GDCore/IDE/EventsEditorItemsAreas.h"
#include "GDCore/IDE/EventsEditorSelection.h"
namespace gd { class ExternalEvents; }
namespace gd { class LayoutEditorCanvas; }
class SearchEvents;
class Game;
class Scene;
class SceneCanvas;
namespace gd { class BaseEvent; }
class EventsEditor;

/**
 * \brief Lightweight internal class to get refresh order
 */
class InternalEventsEditorRefreshCallbacks : public GDpriv::EventsEditorRefreshCallbacks
{
public:
    InternalEventsEditorRefreshCallbacks(EventsEditor * editor_) : editor(editor_) {};
    virtual ~InternalEventsEditorRefreshCallbacks() {};

    virtual void Refresh();

    EventsEditor * editor;
};

/**
 * \brief A complete events editor
 */
class EventsEditor: public wxPanel
{
public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent window
     * \param game Game the events belongs to
     * \param scene Scene to be used to get objects, variables... The events are not necessarily the events of this scene
     * \param events The events to be edited
     * \param gd::MainFrameWrapper gd::MainFrameWrapper object to be used so as to communicate with the editor.
     */
    EventsEditor(wxWindow* parent, Game & game, Scene & scene, std::vector < gd::BaseEventSPtr > * events_, gd::MainFrameWrapper & mainFrameWrapper_ );
    virtual ~EventsEditor();

    /**
     * Launch immediate refresh of events
     */
    void Refresh();

    /**
     * Scroll view to reach an event.
     */
    void ScrollToEvent(gd::BaseEventSPtr event);

    /**
     * Called when events are changed. Can be called from an external class such as SearchEvents dialog.
     *
     * \param updateHistory true if history must be updated
     * \param noNeedForSceneRecompilation set this to false if the changes does not imply that a scene events compilation must be made ( For example, when a comment is edited. )
     */
    void ChangesMadeOnEvents(bool updateHistory = true, bool noNeedForSceneRecompilation = false);

    /**
     * Return a reference to the class used to manage selection.
     */
    EventsEditorSelection & GetSelection() { return selection; };

    static void CreateRibbonPage(wxRibbonPage * page);
    void ConnectEvents();

    /**
     * Declare a LayoutEditorCanvas to be associated with this events editor.
     * Used to check if profiling is enabled.
     */
    void SetAssociatedLayoutCanvas(gd::LayoutEditorCanvas * layoutCanvas_) { layoutCanvas = layoutCanvas_; };
    gd::LayoutEditorCanvas * GetAssociatedLayoutCanvas() { return layoutCanvas; };

    /**
     * Notify events editor that we're editing external events.
     * Calling this method do _not_ change events in editor. It is only used to notify others layouts/external events that changed have been made to these external events.
     */
    void SetExternalEvents(gd::ExternalEvents * externalEvents_) {externalEvents = externalEvents_; };

    //(*Declarations(EventsEditor)
    wxStaticText* addSubEventBt;
    wxStaticText* addEventBt;
    wxMenuItem* redoMenu;
    wxMenuItem* MenuItem5;
    wxMenuItem* toggleActivation;
    wxMenuItem* eventPasteMenu;
    wxMenuItem* MenuItem1;
    wxMenuItem* eventCutMenu;
    wxScrollBar* scrollBar;
    wxStaticBitmap* addInstrIcon;
    wxMenu eventsContextMenu;
    wxMenuItem* undoMenu;
    wxStaticBitmap* addEventIcon;
    wxStaticText* addMoreBt;
    wxMenuItem* deleteMenu;
    wxStaticBitmap* addMoreIcon;
    wxTextCtrl* liveEdit;
    wxPanel* liveEditingPanel;
    wxPanel* eventContextPanel;
    wxPanel* listContextPanel;
    wxMenuItem* MenuItem6;
    wxMenu eventTypesMenu;
    wxPanel* eventsPanel;
    wxStaticText* addInstrBt;
    wxMenuItem* eventCopyMenu;
    wxMenu multipleContextMenu;
    wxBitmapButton* parameterEditBt;
    wxStaticBitmap* addSubEventIcon;
    //*)
    SearchEvents * searchDialog;

protected:

    //(*Identifiers(EventsEditor)
    static const long ID_TEXTCTRL1;
    static const long ID_BITMAPBUTTON1;
    static const long ID_PANEL2;
    static const long ID_STATICBITMAP1;
    static const long ID_STATICTEXT1;
    static const long ID_STATICBITMAP2;
    static const long ID_STATICTEXT2;
    static const long ID_STATICBITMAP3;
    static const long ID_STATICTEXT3;
    static const long ID_PANEL3;
    static const long ID_STATICBITMAP4;
    static const long ID_STATICTEXT4;
    static const long ID_PANEL4;
    static const long ID_PANEL1;
    static const long ID_SCROLLBAR1;
    static const long deleteMenuItem;
    static const long toggleActivationMenuItem;
    static const long copyMenuItem;
    static const long cutMenuItem;
    static const long ID_MENUITEM4;
    static const long ID_MENUITEM5;
    static const long ID_MENUITEM6;
    static const long ID_MENUITEM7;
    static const long ID_MENUITEM11;
    static const long ID_MENUITEM12;
    //*)
    static const long idRibbonEvent;
    static const long idRibbonCom;
    static const long idRibbonSubEvent;
    static const long idRibbonSomeEvent;
    static const long idRibbonDelEvent;
    static const long idRibbonUndo;
    static const long idRibbonRedo;
    static const long idRibbonCopy;
    static const long idRibbonCut;
    static const long idRibbonPaste;
    static const long idRibbonTemplate;
    static const long idRibbonCreateTemplate;
    static const long idRibbonHelp;
    static const long idSearchReplace;
    static const long idRibbonProfiling;
    static const long idRibbonFoldAll;
    static const long idRibbonUnFoldAll;

    static wxRibbonButtonBar * insertRibbonBar;
    static wxRibbonButtonBar * deleteRibbonBar;
    static wxRibbonButtonBar * clipboardRibbonBar;
    static wxRibbonButtonBar * templateRibbonBar;
    static wxRibbonButtonBar * undoRibbonBar;
    std::vector < std::pair<long, std::string> > idForEventTypesMenu;

private:

    //(*Handlers(EventsEditor)
    void OneventsPanelPaint(wxPaintEvent& event);
    void OneventsPanelLeftUp(wxMouseEvent& event);
    void OneventsPanelKeyDown(wxKeyEvent& event);
    void OneventsPanelKeyUp(wxKeyEvent& event);
    void OneventsPanelEraseBackground(wxEraseEvent& event);
    void OneventsPanelLeftDown(wxMouseEvent& event);
    void OneventsPanelMouseMove(wxMouseEvent& event);
    void OnscrollBarScroll(wxScrollEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnliveEditTextEnter(wxCommandEvent& event);
    void OneventsPanelMouseWheel(wxMouseEvent& event);
    void OnliveEditText(wxCommandEvent& event);
    void OnaddEventBtClick(wxCommandEvent& event);
    void OnaddSubEventBtClick(wxCommandEvent& event);
    void OnaddMoreBtClick(wxCommandEvent& event);
    void OndeleteMenuSelected(wxCommandEvent& event);
    void OneventCopyMenuSelected(wxCommandEvent& event);
    void OneventCutMenuSelected(wxCommandEvent& event);
    void OneventPasteMenuSelected(wxCommandEvent& event);
    void OnundoMenuSelected(wxCommandEvent& event);
    void OnredoMenuSelected(wxCommandEvent& event);
    void OneventsPanelMouseLeave(wxMouseEvent& event);
    void OnaddInstrBtClick(wxCommandEvent& event);
    void OneventsPanelLeftDClick(wxMouseEvent& event);
    void OnlistContextPanelPaint(wxPaintEvent& event);
    void OneventContextPanelPaint(wxPaintEvent& event);
    void OnparameterEditBtClick(wxCommandEvent& event);
    void OneventsPanelMiddleUp(wxMouseEvent& event);
    void OneventsPanelRightUp(wxMouseEvent& event);
    void OntoggleActivationSelected(wxCommandEvent& event);
    void OnPanel1LeftDown(wxMouseEvent& event);
    void OnaddEventIconPnlPaint(wxPaintEvent& event);
    void OnaddMoreIconPnlPaint(wxPaintEvent& event);
    void OnaddMoreIconPnlLeftDown(wxMouseEvent& event);
    void OnaddSubEventIconPnlPaint(wxPaintEvent& event);
    void OnaddSubEventIconPnlLeftDown(wxMouseEvent& event);
    void OnaddEventIconPnlLeftDown(wxMouseEvent& event);
    void OnaddInstrIconPnlPaint(wxPaintEvent& event);
    void OnaddInstrIconPnlLeftDown(wxMouseEvent& event);
    void OnaddEventIconPnlMouseEnter(wxMouseEvent& event);
    void OnaddEventIconPnlMouseLeave(wxMouseEvent& event);
    void OnaddSubEventIconPnlMouseEnter(wxMouseEvent& event);
    void OnaddSubEventIconPnlMouseLeave(wxMouseEvent& event);
    void OnaddMoreIconPnlMouseLeave(wxMouseEvent& event);
    void OnaddMoreIconPnlMouseEnter(wxMouseEvent& event);
    void OnaddInstrIconPnlMouseEnter(wxMouseEvent& event);
    void OnaddInstrIconPnlMouseLeave(wxMouseEvent& event);
    void OneventContextPanelEraseBackground(wxEraseEvent& event);
    void OnlistContextPanelEraseBackground(wxEraseEvent& event);
    //*)
    void UpdateRibbonBars();
    void OnHelpBtClick(wxCommandEvent& event);
    void OnTemplateBtClick(wxCommandEvent& event);
    void OnCreateTemplateBtClick(wxCommandEvent& event);
    void OnSearchBtClick(wxCommandEvent& event);
    void OnProfilingBtClick(wxCommandEvent& event);
    void OnAddCustomEventFromMenuSelected(wxCommandEvent& event);
    void OnRibbonAddEventBtClick(wxRibbonButtonBarEvent& evt);
    void OnRibbonAddCommentBtClick(wxRibbonButtonBarEvent& evt);
    void OnRibbonAddSubEventSelected(wxRibbonButtonBarEvent& evt);
    void OnRibbonAddCustomEventFromMenu(wxRibbonButtonBarEvent& evt);
    void OnRibbonFoldAll(wxRibbonButtonBarEvent& evt);
    void OnRibbonUnFoldAll(wxRibbonButtonBarEvent& evt);
    void HandleSelectionAfterClick(int x, int y, bool allowLiveEditingParameters = true);

    void AddEvent(EventItem & previousEventItem);
    void AddSubEvent(EventItem & parentEventItem);
    void AddCustomEventFromMenu(unsigned int menuID, EventItem & previousEventItem);

    void RecomputeAllEventsWidth(std::vector < boost::shared_ptr<gd::BaseEvent> > & eventsToRefresh);
    void DeleteSelection();

    void EndLiveEditing();

    /**
     * Draw events.
     * \param wxDC where events are drawn
     * \param Events to be drawn
     * \param x position where draw events
     * \param y position where draw events
     * \param optional event that will be searched for. If event is found, it will be selected and scrollbar set to view this event
     */
    unsigned int DrawEvents(wxDC & dc, std::vector < boost::shared_ptr< gd::BaseEvent > > & events, int x, int y, boost::shared_ptr< gd::BaseEvent > scrollTo = boost::shared_ptr< gd::BaseEvent >() );

    /**
     * Tool function.
     */
    void FoldEventListAndSubEvents(std::vector<boost::shared_ptr<gd::BaseEvent> > & list, bool fold);

    Game & game;

    Scene & scene; ///< Scene is required, even if it is a empty useless scene.
    gd::ExternalEvents * externalEvents; ///< Events editor can be used to edit external events

    std::vector < gd::BaseEventSPtr > * events; ///< Events modified are not necessarily the events of the scene
    gd::MainFrameWrapper & mainFrameWrapper;
    gd::LayoutEditorCanvas * layoutCanvas;

    EventsEditorItemsAreas itemsAreas; ///< Areas management
    EventsEditorSelection selection; ///<Selection management and input

    unsigned int conditionColumnWidth; ///< Size of the conditions column
    bool isResizingColumns; ///< True if user is resizeing column
    unsigned int leftMargin; ///< Margin size at the left of events

    wxBitmap foldBmp;
    wxBitmap unfoldBmp;
    bool hideContextPanelsLabels;

    ParameterItem liveEditedParameter; ///< Filled with information about parameter which is currently edited, if any.
    InstructionItem liveEditedAssociatedInstruction; ///< Filled with information about instruction of parameter which is currently edited, if any.
    bool liveEditingChangesMade; ///< Used to known if user changed something when live editing the parmameter.

    bool ctrlKeyDown;

    std::vector < std::vector < gd::BaseEventSPtr > > history; ///<Changes history
    std::vector < std::vector < gd::BaseEventSPtr > > redoHistory;
    std::vector < gd::BaseEventSPtr > latestState; ///< Necessary to keep track of what changed

    bool profilingActivated;

    InternalEventsEditorRefreshCallbacks refreshCallback; ///< Used to allow external objects to request the editor to refresh

    DECLARE_EVENT_TABLE()
};

#endif
