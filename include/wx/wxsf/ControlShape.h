/***************************************************************
 * Name:      ControlShape.h
 * Purpose:   Defines GUI control shape class
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2008-04-30
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#ifndef _WXSFCONTROLSHAPE_H
#define _WXSFCONTROLSHAPE_H

#include "wx/wxsf/RectShape.h"

#define sfFIT_SHAPE_TO_CONTROL true
#define sfFIT_CONTROL_TO_SHAPE false

#define sfdvCONTROLSHAPE_CONTROLOFFSET 0
#define sfdvCONTROLSHAPE_PROCESSEVENTS wxSFControlShape::evtKEY2CANVAS | wxSFControlShape::evtMOUSE2CANVAS
#define sfdvCONTROLSHAPE_MODFILL wxBrush(*wxBLUE, wxBDIAGONAL_HATCH)
#define sfdvCONTROLSHAPE_MODBORDER wxPen(*wxBLUE, 1, wxSOLID)

class WXDLLIMPEXP_SF wxSFControlShape;

/*!
 * \brief Auxiliary class used by wxSFControlShape. All events generated by a GUI control (widget)
 * managed by parent control shape are redirected to this event sink which invokes a default event handler
 * or send a copy of the event to shape canvas if requested.
 */
class EventSink : public wxEvtHandler
{
public:
    /*! \brief Default constructor. */
    EventSink();
    /*!
     * \brief User constructor.
     * \param parent Pointer to parent control shape
     */
    EventSink(wxSFControlShape *parent);
    /*! \brief Destructor. */
    virtual ~EventSink();

    // public functions
	/*!
     * \brief Event handler used for delayed processing of a mouse button events.
	 * The handler creates new key event instance and sends it to a shape canvas for further processing.
	 * \param event Mouse event
	 */
	void _OnMouseButton(wxMouseEvent &event);
	/*!
     * \brief Event handler used for delayed processing of a mouse event (mouse movement).
	 * The handler creates new key event instance and sends it to a shape canvas for further processing.
	 * \param event Mouse event
	 */
	void _OnMouseMove(wxMouseEvent &event);
	/*!
	 * \brief Event handler used for delayed processing of a key event.
	 * The handler creates new key event instance and sends it to a shape canvas for further processing.
	 * \param event Keyboard event
	 */
	void _OnKeyDown(wxKeyEvent &event);

    /*! \brief Event handler used for adjusting the parent shape's size in accordance to size of managed GUI control. */
	void _OnSize(wxSizeEvent &event);

protected:
    // protected data members
    /*! \brief Poineter to parent contol shape. */
    wxSFControlShape *m_pParentShape;

    // protected functions
	/*!
	 * \brief Send copy of incomming event to a shape canvas.
	 * \param event Event to be send
	 */
    void SendEvent(wxEvent &event);
	/*!
	 * \brief Modify given mouse event (recalculate the event's position in accordance to parent control
	 * shape's position.
	 * \param event Mouse event to be updated;
	 */
    void UpdateMouseEvent(wxMouseEvent &event);
};

/*!
 * \brief Class encapsulates a special shape able to manage assigned GUI controls (widgets). The GUI control's
 * position and size can by modified via parent control shape. User can also specify how events incoming from the
 * managed GUI control are processed.
 *
 * Note that the managed controls use a shape canvas as their parent window so these shapes cannot be used
 * without existing and properly initialized shape canvas. Moreover, managed GUI controls are not serialized in any
 * way internaly so it is completely up to the user to provide this functionality if needed.
 */
class WXDLLIMPEXP_SF wxSFControlShape : public wxSFRectShape
{
public:
    friend class EventSink;

    XS_DECLARE_CLONABLE_CLASS(wxSFControlShape)

    /*! \brief Way of processing of GUI control's events. */
    enum EVTPROCESSING
    {
        /*! \brief Event isn't processed. */
        evtNONE = 0,
        /*! \brief Keyboard events are processed by the GUI control. */
        evtKEY2GUI = 1,
        /*! \brief Keyboard events are send to a shape canvas. */
        evtKEY2CANVAS = 2,
        /*! \brief Mouse events are processed by the GUI control. */
        evtMOUSE2GUI = 4,
        /*! \brief Mouse events are send to a shape canvas. */
        evtMOUSE2CANVAS = 8
    };

    /*! \brief Default constructor. */
    wxSFControlShape();
    /*!
     * \brief User constructor.
     * \param ctrl Pointer to managed GUI control
     * \param pos Initial position
     * \param size Initial size
     * \param manager Pointer to parent diagram manager
     */
    wxSFControlShape(wxWindow *ctrl, const wxRealPoint& pos, const wxRealPoint& size, wxSFDiagramManager* manager);
    /*!
     * \brief Copy constructor.
     * \param obj Object to copy from
     */
    wxSFControlShape(const wxSFControlShape& obj);
    /*! \brief Default destructor. */
    virtual ~wxSFControlShape();

    // member data accessors
    /*!
     * \brief Set managed GUI control.
     * \param ctrl Pointer to existing manager GUI control
     * \param fit TRUE if the control shape should be resized in accordance to the given GUI control
     */
    void SetControl(wxWindow * ctrl, bool fit = sfFIT_SHAPE_TO_CONTROL);
    /*!
     * \brief Get pointer to managed GUI control.
     * \return Pointer to the GUI control
     */
    wxWindow * GetControl() { return m_pControl; }
    /*!
     * \brief Set a way how GUI control's events are processed.
     * \param mask Event processing
     * \sa EVTPROCESSING
     */
    void SetEventProcessing(int mask){m_nProcessEvents = mask;}
    /*!
     * \brief Get a way how GUI control's events are processed.
     * \return Combination of EVTPROCESSING flags
     * \sa EVTPROCESSING
     */
    int GetEventProcessing(){return m_nProcessEvents;}
    /*!
     * \brief Set control shape's background style used during its modification.
     * \param brush Reference to used brush
     */
    void SetModFill(const wxBrush& brush){m_ModFill = brush;}
    /*!
     * \brief Get control shape's background style used during its modification.
     * \return Used brush
     */
    wxBrush GetModFill(){return m_ModFill;}
    /*!
     * \brief Set control shape's border styl used during its modification.
     * \param pen Reference to used pen
     */
    void SetModBorder(const wxPen& pen){m_ModBorder = pen;}
    /*!
     * \brief Get control shape's border styl used during its modification.
     * \return Used pen
     */
    wxPen GetModBorder(){return m_ModBorder;}
    /*!
     * \brief Set control shape's offset (a gap between the shape's border and managed GUI control).
     * \param offset Offset size
     */
    void SetControlOffset(int offset){m_nControlOffset = offset;}
    /*!
     * \brief Get control shape's offset (a gap between the shape's border and managed GUI control).
     * \return Offset size
     */
    int GetControlOffset(){return m_nControlOffset;}

    // public virtual functions

    /*!
	 * \brief Scale the shape size by in both directions. The function can be overrided if necessary
     * (new implementation should call default one ore scale shape's children manualy if neccesary).
     * \param x Horizontal scale factor
     * \param y Vertical scale factor
     * \param children TRUE if the shape's children shoould be scaled as well, otherwise the shape will be updated after scaling via Update() function.
     */
	virtual void Scale(double x, double y, bool children = sfWITHCHILDREN);
	/*!
	 * \brief Move the shape to the given absolute position. The function can be overrided if necessary.
	 * \param x X coordinate
	 * \param y Y coordinate
	 */
	virtual void MoveTo(double x, double y);
	/*!
	 * \brief Move the shape by the given offset. The function can be overrided if neccessary.
	 * \param x X offset
	 * \param y Y offset
	 */
	virtual void MoveBy(double x, double y);

    /*! \brief Resize the shape to bound all child shapes. The function can be overrided if neccessary. */
	virtual void FitToChildren();

	/*!
	 * \brief Event handler called at the begining of the shape dragging process.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \sa wxSFShapeCanvas
	 */
	virtual void OnBeginDrag(const wxPoint& pos);
	/*!
	 * \brief Event handler called during the shape dragging process.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \param pos Current mouse position
	 * \sa wxSFShapeCanvas
	 */
	virtual void OnDragging(const wxPoint& pos);
	/*!
	 * \brief Event handler called at the end of the shape dragging process.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \param pos Current mouse position
	 * \sa wxSFShapeCanvas
	 */
	virtual void OnEndDrag(const wxPoint& pos);
	/*!
	 * \brief Event handler called when the user started to drag the shape handle.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \param handle Reference to dragged handle
	 */
	virtual void OnBeginHandle(wxSFShapeHandle& handle);
	/*!
	 * \brief Event handler called during dragging of the shape handle.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \param handle Reference to dragged handle
	 */
	virtual void OnHandle(wxSFShapeHandle& handle);
	/*!
	 * \brief Event handler called when the user finished dragging of the shape handle.
	 * The function can be overrided if necessary.
	 *
	 * The function is called by the framework (by the shape canvas).
	 * Default implementation does nothing.
	 * \param handle Reference to dragged handle
	 */
	virtual void OnEndHandle(wxSFShapeHandle& handle);

protected:

    // protected data members

    /*! \brief Pointer to manager data control. */
    wxWindow * m_pControl;
    /*! \brief Events processing mask */
    int m_nProcessEvents;

    /*! \brief Brush used during the shape's modification. */
    wxBrush m_ModFill;
    /*! \brief Pen used during the shape's modification. */
    wxPen m_ModBorder;
    /*! \brief Offset between the shape and managed GUI control. */
    int m_nControlOffset;

    // protected functions
    /*! \brief Update size and position of the managed control according to the parent shape. */
    void UpdateControl();
    /*! \brief Update size of the shape position according to the managed control. */
    void UpdateShape();

private:

    // private data members

    /*! \brief Pointer to parent window. */
    wxWindow * m_pPrevParent;
    /*! \brief Pointer to event sink.*/
    EventSink * m_pEventSink;
    /*! \brief Previous canvas style. */
    long m_nPrevStyle;
    /*! \brief Previously used shape's brush. */
    wxBrush m_PrevFill;
    /*! \brief Previously used shape's pen. */
    wxPen m_PrevBorder;

    // private functions
	 /*! \brief Initialize serializable properties. */
	void MarkSerializableDataMembers();

};

#endif //_WXSFCONTROLSHAPE_H
