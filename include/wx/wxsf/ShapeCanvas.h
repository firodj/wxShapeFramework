/***************************************************************
 * Name:      ShapeCanvas.h
 * Purpose:   Defines shape canvas class
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-22
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#pragma once

#include <wx/dataobj.h>
#include <wx/dnd.h>

#include "ShapeBase.h"
#include "DiagramManager.h"
#include "MultiSelRect.h"
#include "CanvasHistory.h"
#include "LineShape.h"
#include "EditTextShape.h"

#define sfDEFAULT_ME_OFFSET 5
#define sfSAVE_STATE true
#define sfDONT_SAVE_STATE false
#define sfFROM_PAINT true
#define sfFROM_ANYWHERE false

// default values
/*! \brief Default value of wxSFCanvasSettings::m_nBackgroundColor data member */
#define sfdvSHAPECANVAS_BACKGROUNDCOLOR wxColour(240, 240, 240)
/*! \brief Default value of wxSFCanvasSettings::m_nGridSize data member */
#define sfdvSHAPECANVAS_GRIDSIZE wxSize(10, 10)
/*! \brief Default value of wxSFCanvasSettings::m_nGridColor data member */
#define sfdvSHAPECANVAS_GRIDCOLOR wxColour(200, 200, 200)
/*! \brief Default value of wxSFCanvasSettings::m_CommnonHoverColor data member */
#define sfdvSHAPECANVAS_HOVERCOLOR wxColor(120, 120, 255)
/*! \brief Default value of wxSFCanvasSettings::m_nGradientFrom data member */
#define sfdvSHAPECANVAS_GRADIENT_FROM wxColour(240, 240, 240)
/*! \brief Default value of wxSFCanvasSettings::m_nGradientTo data member */
#define sfdvSHAPECANVAS_GRADIENT_TO wxColour(200, 200, 255)
/*! \brief Default value of wxSFCanvasSettings::m_nStyle data member */
#define sfdvSHAPECANVAS_STYLE wxSFShapeCanvas::sfsDEFAULT_CANVAS_STYLE

/*!
 * \brief Auxiliary serializable class encapsulating the canvas properties.
 */
class wxSFCanvasSettings : public xsSerializable
{
public:
    DECLARE_DYNAMIC_CLASS(wxSFCanvasSettings);

    wxSFCanvasSettings();

    wxColour m_nBackgroundColor;
    wxColour m_nCommonHoverColor;
	wxColour m_nGradientFrom;
	wxColour m_nGradientTo;
    wxSize m_nGridSize;
    wxColour m_nGridColor;
    wxArrayString m_arrAcceptedShapes;
    double m_nScale;
	long m_nStyle;
};

class wxSFCanvasDropTarget;

/*!
 * \brief Class encapsulating a Shape canvas. The shape canvas is window control
 * which extends the wxScrolledWindow and is responsible for displaying of shapes diagrams.
 * It also supports clipboard and drag&drop operations, undo/redo operations,
 * and graphics exporting functions.
 *
 * This class is a core framework class and provides many member functions suitable for adding,
 * removing, moving, resizing and drawing of shape objects. It can be used as it is or as a base class
 * if necessary. In that case, the default class functionality can be enhaced by overriding of
 * its virtual functions or by manual events handling. In both cases the user is responsible
 * for invoking of default event handlers/virtual functions otherwise the
 * built in functionality wont be available.
 * \sa wxSFDiagramManager
 */
class WXDLLIMPEXP_SF wxSFShapeCanvas : public wxScrolledWindow
{
public:

    friend class wxSFDiagramManager;
	friend class wxSFCanvasDropTarget;

    /*!
     * \brief Constructor
     * \param manager Pointer to shape manager
     * \param parent Parent window
     * \param id Window ID
     * \param pos Initial position
     * \param size Initial size
     * \param style Window style
     */
	wxSFShapeCanvas(wxSFDiagramManager* manager, wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL);
	/*! \brief Destructor */
	~wxSFShapeCanvas(void);

    /*! \brief Working modes */
	enum MODE
	{
	    /*! \brief The shape canvas is in ready state (no operation is pending) */
		modeREADY = 0,
        /*! \brief Some shape handle is dragged */
		modeHANDLEMOVE,
		/*! \brief Handle of multiselection tool is dragged */
		modeMULTIHANDLEMOVE,
		/*! \brief Some shape/s is/are dragged */
		modeSHAPEMOVE,
		/*! \brief Multiple shape selection is in progess */
		modeMULTISELECTION,
		/*! \brief Interactive connection creation is in progress */
		modeCREATECONNECTION,
		/*! \brief Canvas is in the Drag&Drop mode */
		modeDND
	};

    /*! \brief Search mode flags for GetShapeAtPosition function */
	enum SEARCHMODE
	{
	    /*! \brief Search for selected shapes only*/
		searchSELECTED,
		/*! \brief Search for unselected shapes only */
		searchUNSELECTED,
		/*! \brief Search for both selected and unselected shapes */
		searchBOTH
	};

    /*! \brief Flags for AlignSelected function */
	enum VALIGN
	{
	    valignNONE,
	    valignTOP,
	    valignMIDDLE,
	    valignBOTTOM
	};

    /*! \brief Flags for AlignSelected function */
	enum HALIGN
	{
	    halignNONE,
	    halignLEFT,
	    halignCENTER,
	    halignRIGHT
	};

	/*! \brief Style flags */
	enum STYLE
	{
		/*! \brief Allow multiselection box. */
		sfsMULTI_SELECTION = 1,
		/*! \brief Allow shapes' size change done via the multiselection box. */
		sfsMULTI_SIZE_CHANGE = 2,
		/*! \brief Show grid. */
		sfsGRID_SHOW = 4,
		/*! \brief Use grid. */
		sfsGRID_USE = 8,
		/*! \brief Enable Drag & Drop operations */
		sfsDND = 16,
		/*! \brief Enable Undo/Redo operations */
		sfsUNDOREDO = 32,
		/*! \brief Enable the clipboard. */
		sfsCLIPBOARD = 64,
		/*! \brief Enable mouse hovering */
		sfsHOVERING = 128,
		/*! \brief Enable highligting of shapes able to accept dragged shape(s)*/
		sfsHIGHLIGHTING = 256,
		/*! \brief Use gradient color for the canvas background */
		sfsGRADIENT_BACKGROUND = 512,
		/*! \brief Default canvas style. */
		sfsDEFAULT_CANVAS_STYLE = sfsMULTI_SELECTION | sfsMULTI_SIZE_CHANGE | sfsDND | sfsUNDOREDO | sfsCLIPBOARD | sfsHOVERING | sfsHIGHLIGHTING
	};

	// public functions

    /*!
     * \brief Get diagram manager associated with this instance of shape canvas
     * \return Pointer to diagram manager
     * \sa wxSFDiagramManager
     */
    wxSFDiagramManager* GetDiagramManager(){return m_pManager;}
    /*!
     * \brief Set diagram manager for this shape canvas
     * \param manager Pointer to diagram manager instance
     * \sa wxSFDiagramManager
     */
    void SetDiagramManager(wxSFDiagramManager* manager){m_pManager = manager;}

    /*!
     * \brief Load serialized canvas content (diagrams) from given file.
     * \param file Full file name
     */
	void LoadCanvas(const wxString& file);
    /*!
     * \brief Save  canvas content (diagrams) to given file.
     * \param file Full file name
     */
	void SaveCanvas(const wxString& file);
    /*!
     * \brief Export canvas content to BMP file.
     * \param file Full file name
     */
	void SaveCanvasToBMP(const wxString& file);

    /*!
     * \brief Start interactive connection creation.
     *
     * This function switch the cavas to a mode in which a new shape connection
     * can be created interactively (by mouse operations). Every connection must
     * start and finish in some shape object or another connection. At the end of the
     * process the OnConnectionFinished event handler is invoked so the user can
     * set needed connection properties immediately.
     *
     * Function must be called from mouse event handler and the event must be passed
     * to the function.
     * \param shapeInfo Connection type
     * \param pos Position where to start
     * \sa CreateConnection
     */
    void StartInteractiveConnection(wxClassInfo* shapeInfo, const wxPoint& pos);
    /*! \brief Abort interactive connection creation process */
	void AbortInteractiveConnection();

    /*! \brief Select all shapes in the canvas */
	void SelectAll();
	/*! \brief Deselect all shapes */
	void DeselectAll();
	/*! \brief Hide handles of all shapes */
	void HideAllHandles();
	/*!
	 * \brief Repaint the shape canvas
	 * \param erase TRUE if the canvas should be erased before repainting
	 * \param rct Refreshed region (rectangle)
	 */
	void RefreshCanvas(bool erase, wxRect rct);

	/*!
	 * \brief Start Drag&Drop process with shapes included in the given list
	 * \param shapes List of shapes which should be dragged
	 * \return rct Drag result
	 */
	wxDragResult DoDragDrop(ShapeList &shapes, const wxPoint& start = wxPoint(-1, -1));
    /*! \brief Copy selected shapes to the clipboard */
	void Copy();
	/*! \brief Copy selected shapes to the clipboard and remove them from the canvas */
	void Cut();
	/*! \brief Paste shapes stored in the clipboard to the canvas */
	void Paste();
	/*! \brief Perform Undo operation (if available) */
	void Undo();
	/*! \brief Perform Redo operation (if available) */
	void Redo();
	/*! \brief Function returns TRUE if some shapes can be copied to the clipboard (it means they are selected) */
	bool CanCopy();
	/*! \brief Function returns TRUE if some shapes can be cutted to the clipboard (it means they are selected) */
	bool CanCut();
	/*! \brief Function returns TRUE if some shapes can be copied from the clipboard to the canvas
	 * (it means the clipboard contains stored shapes) */
	bool CanPaste();
	/*! \brief Function returns TRUE if Undo operation can be done */
	bool CanUndo();
	/*! \brief Function returns TRUE if Redo operation can be done */
	bool CanRedo();
	/*! \brief Function returns TRUE if AlignSelected function can be invoked (if more than
	 * one shape is selected) */
	bool CanAlignSelected();

    /*! \brief Save current canvas state (for Undo/Redo operations) */
	void SaveCanvasState();
	/*! \brief Clear all stored canvas states (no Undo/Redo operations will be available) */
	void ClearCanvasHistory();

    /*!
     * \brief Convert device position to logical position.
     *
     * The function returns unscrolled unscaled canvas position.
     * \param pos Device position (for example mouse position)
     * \return Logical position
     */
	wxPoint DP2LP(const wxPoint& pos) const;
	wxRect DP2LP(const wxRect& rct) const;
    /*!
     * \brief Convert logical position to device position.
     *
     * The function returns scrolled scaled canvas position.
     * \param pos Logical position (for example shape position)
     * \return Device position
     */
	wxPoint LP2DP(const wxPoint& pos) const;
	wxRect LP2DP(const wxRect& rct) const;

	/*!
	 * \brief Get shape under current mouse cursor position (fast implementation - use everywhere
	 * it is possible instead of much slower GetShapeAtPosition()).
	 * \param mode Search mode
	 * \return Pointer to shape if found, otherwise NULL
	 * \sa SEARCHMODE, wxSFShapeCanvas::DP2LP, wxSFShapeCanvas::GetShapeAtPosition
	 */
	wxSFShapeBase* GetShapeUnderCursor(SEARCHMODE mode = searchBOTH);
	/*!
	 * \brief Get shape at given logical position
	 * \param pos Logical position
	 * \param zorder Z-order of searched shape (usefull if several shapes are located
	 * at the given position)
	 * \param mode Search mode
	 * \return Pointer to shape if found, otherwise NULL
	 * \sa SEARCHMODE, wxSFShapeCanvas::DP2LP,, wxSFShapeCanvas::GetShapeUnderCursor
	 */
	wxSFShapeBase* GetShapeAtPosition(const wxPoint& pos, int zorder = 1, SEARCHMODE mode = searchBOTH);
    /*!
     * \brief Get topmost handle at given position
     * \param pos Logical position
     * \return Pointer to shape handle object if found, otherwise NULL
     * \sa wxSFShapeCanvas::DP2LP
     */
	wxSFShapeHandle* GetTopmostHandleAtPosition(const wxPoint& pos);
	/*!
	 * \brief Get list of all shapes located at given position
	 * \param pos Logical position
	 * \param shapes Reference to shape list where pointers to
	 * all found shapes will be stored
	 * \return Number of found shapes
	 * \sa wxSFShapeCanvas::DP2LP
	 */
	int GetShapesAtPosition(const wxPoint& pos, ShapeList& shapes);
	/*!
	 * \brief Get list of shapes located inside given rectangle
	 * \param rct Examined rectangle
	 * \param shapes Reference to shape list where pointers to
	 * all found shapes will be stored
	 * \return Number of found shapes
	 */
	int GetShapesInside(const wxRect& rct, ShapeList& shapes);
	/*!
	 * \brief Get list of selected shapes.
	 * \param selection Reference to shape list where pointers to
	 * all selected shapes will be stored
	 * \return Number of selected shapes
	 */
	int GetSelectedShapes(ShapeList& selection);
    /*!
	 * \brief Get box bounding all shapes in the canvas.
	 * \return Total bounding box
	 */
	wxRect GetTotalBoundingBox() const;
    /*!
     * \brief Get bounding box of all selected shapes.
     * \return Selection bounding box
     */
	wxRect GetSelectionBB();

	/*!
	 * \brief Align selected shapes in given directions.
	 *
	 * Shapes will be aligned according to most far shape in appropriate direction.
	 * \param halign Horizontal alignment
	 * \param valign Vertical alignment
	 */
	void AlignSelected(HALIGN halign, VALIGN valign);

    /*!
     * \brief Set canvas style.
	 *
	 * Default value is sfsMULTI_SELECTION | sfsMULTI_SIZE_CHANGE | sfsDND | sfsUNDOREDO | sfsCLIPBOARD | sfsHOVERING | sfsHIGHLIGHTING
     * \param style Combination of the canvas styles
     * \sa STYLE
     */
    inline void SetStyle(long style){m_Settings.m_nStyle = style;}
    /*! \brief Get current canvas style. */
    inline long GetStyle(){return m_Settings.m_nStyle;}
	/*! \brief Add new style flag. */
    inline void AddStyle(STYLE style){m_Settings.m_nStyle |= style;}
	/*! \brief Remove given style flag. */
    inline void RemoveStyle(STYLE style){m_Settings.m_nStyle &= ~style;}
	/*! \brief Check whether given style flag is used. */
    inline bool ContainsStyle(STYLE style){return (m_Settings.m_nStyle & style) != 0;}

	// public members accessors
	/*!
	 * \brief Set canvas background color.
	 * \param col Background color
	 */
	void SetCanvasColour(const wxColour& col){m_Settings.m_nBackgroundColor = col;}
	/*!
	 * \brief Get canvas background color.
	 * \return Background color
	 */
	wxColour GetCanvasColour() const {return m_Settings.m_nBackgroundColor;}
	/*!
	 * \brief Set starting gradient color.
	 * \param col Color
	 */
	void SetGradientFrom(const wxColour& col){m_Settings.m_nGradientFrom = col;}
	/*!
	 * \brief Get starting gradient color.
	 * \return Color
	 */
	wxColour GetGradientFrom() const {return m_Settings.m_nGradientFrom;}
	/*!
	 * \brief Set ending gradient color.
	 * \param col Color
	 */
	void SetGradientTo(const wxColour& col){m_Settings.m_nGradientTo = col;}
	/*!
	 * \brief Get ending gradient color.
	 * \return Color
	 */
	wxColour GetGradientTo() const {return m_Settings.m_nGradientTo;}
	/*!
	 * \brief Get grid size.
	 * \return Grid size
	 */
	wxSize GetGrid() const {return m_Settings.m_nGridSize;}
	/*!
	 * \brief Set grid size.
	 * \param grid Grid size.
	 */
	void SetGrid(wxSize grid){m_Settings.m_nGridSize = grid;}
	/*!
	 * \brief Set grid color.
	 * \param col Grid color.
	 */
	void SetGridColour(const wxColour& col){m_Settings.m_nGridColor = col;}
	/*!
	 * \brief Get grid color.
	 * \return Grid color
	 */
	wxColour GetGridColour() const {return m_Settings.m_nGridColor;}
	/*!
	 * \brief Set canvas scale.
	 * \param scale Scale value.
	 */
	void SetScale(double scale);
	/*!
	 * \brief Get canvas scale.
	 * \return Canvas scale
	 */
	double GetScale(){return m_Settings.m_nScale;}
	/*!
	 * \brief Get canvas workind mode.
	 * \return Working mode
	 * \sa MODE
	 */
	MODE GetMode(){return m_nWorkingMode;}
	/*!
	 * \brief Set default hover color.
	 * \param col Hover color.
	 */
	void SetHoverColour(const wxColour& col);
	/*!
	 * \brief Get default hover color.
	 * \return Hover color
	 */
	wxColour GetHoverColour() const {return m_Settings.m_nCommonHoverColor;}
	/*!
	 * \brief Get canvas hostory manager.
	 * \return Reference to the canvas history manager
	 * \sa wxSFCanvasHistory
	 */	
	wxSFCanvasHistory& GetHistoryManager(){return m_CanvasHistory;}

	/*!
	 * \brief Update given position so it will fit canvas grid (if enabled).
	 * \param pos Position which should be updated
	 * \return Updated position
	 */
	wxPoint FitPositionToGrid(const wxPoint& pos);
	/*! \brief Update size of multi selection rectangle */
	void UpdateMultieditSize();
	/*! \brief Update scroll window virtual size so it can display all shape canvas */
	void UpdateVirtualSize();
	/*! \brief Move all shapes so none of it will be located in negative position */
	void MoveShapesFromNegatives();
    /*!
     * \brief Validate selection (remove redundantly selected shapes etc...).
     * \param selection List of selected shapes that should be validated
     */
	void ValidateSelection(ShapeList& selection);

	/*!
	 * \brief Function responsible for drawing of the canvas's content to given DC.
	 * \param dc Reference to device context where the shapes will be drawn to
	 */
	void DrawContent(wxSFScaledPaintDC& dc, bool fromPaint);

    /*!
     * \brief Get reference to multiselection box
     * \return Reference to multiselection box object
     */
    wxSFMultiSelRect& GetMultiselectionBox(){return m_shpMultiEdit;}

	// public virtual event handlers
    /*!
     * \brief Event handler call when the canvas is clicked by
	 * the left mouse button. The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnLeftDown
     */
	virtual void OnLeftDown(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the canvas is double-clicked by
	 * the left mouse button. The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnLeftDoubleClick
     */
	virtual void OnLeftDoubleClick(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the left mouse button is released.
     * The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnLeftUp
     */
	virtual void OnLeftUp(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the canvas is clicked by
	 * the right mouse button. The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnRightDown
     */
	virtual void OnRightDown(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the canvas is double-clicked by
	 * the right mouse button. The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnRightDoubleClick
     */
	virtual void OnRightDoubleClick(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the right mouse button is released.
     * The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnRightUp
     */
	virtual void OnRightUp(wxMouseEvent& event);
    /*!
     * \brief Event handler call when the mouse pointer is moved.
     * The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Mouse event
     * \sa _OnMouseMove
     */
	virtual void OnMouseMove(wxMouseEvent& event);
    /*!
     * \brief Event handler call when any key is pressed.
     * The function can be overrided if necessary.
     *
     * The function is called by the framework and provides basic functionality
     * needed for proper management of displayed shape. It is necessary to call
     * this function from overrided methods if the default canvas behaviour
     * should be preserved.
     * \param event Keyboard event
     * \sa _OnKeyDown
     */
	virtual void OnKeyDown(wxKeyEvent& event);

    /*!
     * \brief Event handler call when any editable text shape is changed.
     * The function can be overrided if necessary.
     *
     * The function is called by the framework and its default implementation
     * generates wxEVT_SF_TEXT_CHANGE event.
     * \param text Changed wxSFEditTestShape object
     */
	virtual void OnTextChange(wxSFEditTextShape* text);
	/*!
	 * \brief Event handler called after successfull conection creation. The function
	 * can be overrided if necessary. The default implementation
     * generates wxEVT_SF_LINE_DONE event.
	 * \param connection Pointer to new connection object
	 * \sa StartInteractiveConnection
	 */
	virtual void OnConnectionFinished(wxSFLineShape* connection);

	/*!
	 * \brief Function is called by the framework after any dragged shapes
	 * are dropped to the canvas. The default implementation
     * generates wxEVT_SF_ON_DROP event.
	 * \param x X-coordinate of a position the data was dropped to
	 * \param y Y-coordinate of a position the data was dropped to
	 * \param def Drag result
	 * \param data Pointer to a data object encapsulating dropped data
	 * \sa wxSFCanvasDropTarget
	 */
	virtual void OnDrop(wxCoord x, wxCoord y, wxDragResult def, const ShapeList& dropped);

protected:

	// protected data members
	MODE m_nWorkingMode;

	wxSFCanvasSettings m_Settings;

	// protected functions

private:

	// private data members

	wxSFMultiSelRect m_shpMultiEdit;
	bool m_fCanSaveStateOnMouseUp;

	/*! \brief Flag used for determination whether the D&D operation has started and ended in one canvas instance */
	bool m_fDnDStartedHere;
	/*! \brief Started position of current D&D operation */
	wxPoint m_nDnDStartedAt;
	/*! \brief Custom data format object (used for the clipboard and D&D operations */
	wxDataFormat m_formatShapes;

	/*! \brief Canvas history manager */
	wxSFCanvasHistory m_CanvasHistory;

	/*! \brief Pointer to parent data (shapes) manager */
    wxSFDiagramManager* m_pManager;

	/*! \brief Pointer to currently selected shape handle */
	wxSFShapeHandle* m_pSelectedHandle;
	/*! \brief Pointer to new line shape under constuction */
	wxSFLineShape* m_pNewLineShape;
	/*! \brief Pointer to topmost unselected shape under the mouse cursor */
	wxSFShapeBase *m_pUnselectedShapeUnderCursor;
	/*! \brief Pointer to topmost selected shape under the mouse cursor */
	wxSFShapeBase *m_pSelectedShapeUnderCursor;
	/*! \brief Pointer to topmost shape under the mouse cursor */
	wxSFShapeBase *m_pTopmostShapeUnderCursor;

	/*! \brief Current list of all shapes in the canvas updated during mouse movement */
	ShapeList m_lstCurrentShapes;

	// private functions

	/*! \brief Close and delete all opened text editing controls actualy used by editable text shapes */
	void DeleteAllTextCtrls();
	/*! \brief Validate selection so the shapes in the given list can be processed by the clipboard functions */
	void ValidateSelectionForClipboard(ShapeList& list);
	/*! \brief Create wxMemoryBuffer from given wxString */
	wxMemoryBuffer CreateMembufferFromString(const wxString& str);

	// private event handlers
	/*!
	 * \brief Event handler called when the canvas should be repainted.
	 * \param event Paint event
	 */
	void OnPaint(wxPaintEvent& event);
	/*!
	 * \brief Event handler called when the canvas should be erased.
	 * \param event Erase event
	 */
	void OnEraseBackground(wxEraseEvent& event);
	/*!
	 * \brief Event handler called when the mouse pointer leaves the canvas window.
	 * \param event Mouse event
	 */
	void OnLeaveWindow(wxMouseEvent& event);
	/*!
	 * \brief Event handler called when the mouse pointer enters the canvas window.
	 * \param event Mouse event
	 */
	void OnEnterWindow(wxMouseEvent& event);
	/*!
	 * \brief Event handler called when the canvas size has changed.
	 * \param event Size event
	 */
	void OnResize(wxSizeEvent& event);

	// original private event handlers
	/*!
	 * \brief Original private event handler called when the canvas is clicked by
	 * left mouse button. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnLeftDown
	 */
	void _OnLeftDown(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the canvas is double-clicked by
	 * left mouse button. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnLeftDoubleClick
	 */
	void _OnLeftDoubleClick(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the left mouse button
	 * is release above the canvas. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnLeftUp
	 */
	void _OnLeftUp(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the canvas is clicked by
	 * right mouse button. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnRightDown
	 */
	void _OnRightDown(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the canvas is double-clicked by
	 * right mouse button. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnRightDoubleClick
	 */
	void _OnRightDoubleClick(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the right mouse button
	 * is release above the canvas. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnRightUp
	 */
	void _OnRightUp(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when the mouse pointer is moving above
	 * the canvas. The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Mouse event
	 * \sa wxSFShapeCanvas::OnMouseMove
	 */
	void _OnMouseMove(wxMouseEvent& event);
	/*!
	 * \brief Original private event handler called when any key is pressed.
	 * The handler calls user-overridable event handler function
	 * and skips the event for next possible processing.
	 * \param event Keyboard event
	 * \sa wxSFShapeCanvas::OnKeyDown
	 */
	void _OnKeyDown(wxKeyEvent& event);

	/*!
	 * \brief Function is called by associated wxSFCanvasDropTarget after any dragged shapes
	 * are dropped to the canvas.
	 * \param x X-coordinate of a position the data was dropped to
	 * \param y Y-coordinate of a position the data was dropped to
	 * \param def Drag result
	 * \param data Pointer to a data object encapsulating dropped data
	 * \sa wxSFCanvasDropTarget
	 */
	void _OnDrop(wxCoord x, wxCoord y, wxDragResult def, wxDataObject *data);

	DECLARE_EVENT_TABLE();
};

/*!
 * \brief Auxiliary class encapsulating shape drop target.
 */
class wxSFCanvasDropTarget : public wxDropTarget
{
	friend class wxSFShapeCanvas;

protected:
	wxSFCanvasDropTarget(wxDataObject *data, wxSFShapeCanvas *parent);
	virtual ~wxSFCanvasDropTarget();

	virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

	wxSFShapeCanvas *m_pParentCanvas;
};
