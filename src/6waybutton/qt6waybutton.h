#ifndef QT_6WAY_BUTTON_H
#define QT_6WAY_BUTTON_H
//============================================================================
/**
 * \file   qt6waybutton.h
 * \author Uwe Kindler
 * \date   02.06.2010
 * \brief  Declaration of 6 way SVG button control.
 */
/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/
//============================================================================


//============================================================================
//                              INCLUDES
//============================================================================
#include <QRect>
#include <QAbstractButton>
#include <QList>


//============================================================================
//                       FORWARD DECLARATIONS
//============================================================================
class QtSvgPixmapCache;
class QtNavigationButton;
class QPropertyAnimation;
class Qt6WayNavButton;


/*!
    \class Qt6WayButton

    \brief The Qt6WayButton provides a button group with SVG graphics.

    Qt6WayButton is a widget that consists of six Buttons, one on any edge
    and two in the middle of the widget. Each button is represented as a
    QAbstractButton and can be accessed with the methods \a upButton(),
    \a downButton(), \a leftButton(), \a rightButton(), \a centerUpButton(),
    \a centerDownButton.
    The returned buttons can then be used to connect signals and slots or to
    change properties like the checkable state.

    \section qt6waybutton_example Example Usage
    The following example shows how to create a Qt6WayButton.
    \code
    Qt6WayButton* button = new Qt6WayButton(parent);
    button->setSkin("Black");
    connect(button, SIGNAL(clicked(Qt6WayNavButton*), this, SLOT(onNavButtonClicked(Qt6WayNavButton*)));
    \endcode

    \section qt6waybutton_skin Setting a Skin

    After creating a new Qt6WayButton a skin needs to be set by calling
    \a setSkin(). Without a skin set, a Qt6WayButton will not have any
    visible content. skin() returns the current skin.
    Further details about skinning the Qt6WayButton can be found in the
    widget description.

    \section qt6waybutton_signal Signals
    There are two different ways of handling signals emitted by individual
    buttons of a Qt6WayButton. The individual buttons (i.e. downButton()) can
    be used directly to connect signals and slots. The second way is to use
    the signals of the Qt6WayButton (clicked(), pressed(), released()). These
    signals are emitted for each individual button and the sender button is
    passed as the first argument of the signal. By using the Qt6WayButton
    signals it is much more easier to handle the signals of all buttons in
    a single slot.
*/
class Qt6WayButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    Q_PROPERTY(double mouseLeaveOpacity READ mouseLeaveOpacity WRITE setMouseLeaveOpacity)
    Q_PROPERTY(bool backgroundRendering READ hasBackgroundRendering WRITE setBackgroundRendering)
    Q_PROPERTY(double opacity READ opacity WRITE setOpacity)

public:
    explicit Qt6WayButton(QWidget * parent = 0);
    virtual ~Qt6WayButton();

    QAbstractButton* upButton();
    QAbstractButton* downButton();
    QAbstractButton* leftButton();
    QAbstractButton* rightButton();
    QAbstractButton* centerUpButton();
    QAbstractButton* centerDownButton();

    void setSkin(const QString& skin);
    QString skin() const;

    /**
     * @brief This enumerates the 6 buttons in this 6-way navigation button
     */
    enum eButtonId
    {
    	UP = 0,        //!< UP
    	DOWN,      //!< DOWN
    	LEFT,      //!< LEFT
    	RIGHT,     //!< RIGHT
    	CENTER_UP, //!< CENTER_UP
    	CENTER_DOWN//!< CENTER_DOWN
    };

    /**
     * @brief This enumerates the 3 axes that are represented by 2 buttons.
     */
    enum eAxisId
    {
    	X_AXIS = 0,//!< X axis comprising of LEFT & RIGHT button
    	Y_AXIS,//!< Y axis comprising of UP & DOWN button
    	Z_AXIS,//!< Z_AXIS comprising of CENTER_UP & CENTER_DOWN button
    };

    /**
     * @brief This enumerates the two directions that are represented by the
     * 2 button of an axis.
     */
    enum eDirection
    {
    	DIRECTION_NEGATIVE = -1,///< UP, LEFT and CENTER_UP button
    	DIRECTION_POSITIVE =  1///< DOWN, RIGHT and CENTER_DOWN button
    };

    /**
     * @brief Sets the opacity of the control that will get set if mouse leaves
     * this control.
     * This feature is useful i.e if you layer this control on top of a image
     * display or a graphics scene and you would like to fade the control out
     * if mouse leaves the control
     * @param Opacity The valid range of opacity is from 1.0 (completely opaque)
     *                to 0.0 (completely transparent).
     */
    void setMouseLeaveOpacity(double Opacity);

    /**
     * @brief Returns the opacity value on mouse leave events.
     * @see setMouseLeaveOpacity()
     */
    double mouseLeaveOpacity();

    /**
     * @brief Enables / disables background rendering for this control.
     * The background.svg image of the skin will get rendered only if
     * background rendering is true.
     */
    void setBackgroundRendering(bool RenderBackground);

    /**
     * @brief This property holds whether background rendering is enabled for
     * the widget.
     */
    bool hasBackgroundRendering();

    /**
     * @brief Returns the current opacity.
     */
    double opacity();

    /**
     * @brief Sets the current opacity of the control.
     * @param Opacity The valid range of opacity is from 1.0 (completely opaque)
     *                to 0.0 (completely transparent).
     */
    void setOpacity(double Opacity);

    /**
     * @brief Returns a list of all button.
     */
    QList<QtNavigationButton*>& buttons();

    /**
     * Enables / disables support for touch events
     */
    void enableTouchEvents(bool Enable);

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual int heightForWidth ( int w ) const;
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent * event);
	void onButtonClicked(Qt6WayNavButton* Button, bool Checked);
	void onButtonPressed(Qt6WayNavButton* Button);
	void onButtonReleased(Qt6WayNavButton* Button);
	friend class Qt6WayNavButton;

private:
    double m_MouseLeaveOpacity;///< defines the opacity of the control if mouse leaves this control
    bool m_RenderBackground;///< set to false to get a transparent background (only the 5 buttons are visible)
    double m_Opacity;///< stores actual opacity value
    QPropertyAnimation* m_OpacityAnimation;///< fade control in and out

    void init();

    /**
     * @brief Setup the fade in / fade out effect
     */
    void setupOpacityAnimation();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    /** name of actual skin **/
    QString m_skin;

    /** List of all navigation buttons **/
    QList<QtNavigationButton*> m_Buttons;


    /** m_rendererBase used to render the skin SVG graphics **/
    QtSvgPixmapCache *m_rendererBase;

signals:
	/**
	 * @brief This signal is emitted when one of the navigation buttons is
	 * activated (i.e. pressed
	 * down then released while the mouse cursor is inside the button).
	 * This signal passes the the navigation button out of the 6 navigation
	 * buttons that caused this event as the first signal parameter.
	 */
	void clicked(Qt6WayNavButton* Sender, bool Checked = false);

	/**
	 * @brief This signal is emitted when one of the navigation buttons is
	 * pressed down.
	 * This signal passes the the navigation button out of the 6 navigation
	 * buttons that caused this event.
	 */
	void pressed(Qt6WayNavButton* Sender);

	/**
	 * @brief This signal is emitted when the one of the navigation buttons
	 * is released
	 * This signal passes the the navigation button out of the 6 navigation
	 * buttons that caused this event.
	 */
	void released(Qt6WayNavButton* Sender);
}; // class Qt6WayButton

#undef QSvgRenderer

//----------------------------------------------------------------------------
#endif // QT_6WAY_BUTTON_H
