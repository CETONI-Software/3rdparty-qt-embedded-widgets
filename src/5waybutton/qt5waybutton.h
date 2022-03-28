#ifndef QT_5WAY_BUTTON_H
#define QT_5WAY_BUTTON_H
//============================================================================
/**
 * \file   qt5waybutton.h
 * \author Uwe Kindler
 * \date   02.06.2010
 * \brief  Declaration of 5 way SVG button control.
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


//============================================================================
//                          FORWARD DECLARATIONS
//============================================================================
class QtSvgPixmapCache;
class QtNavigationButton;


/**
 * @brief A 5-way button is a button that consists of 5 separate buttons.
 * This control is very well suited for control of directions, for navigation
 * of control of axis systems.
 */
class Qt5WayButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    Q_PROPERTY(double mouseLeaveOpacity READ mouseLeaveOpacity WRITE setMouseLeaveOpacity)
    Q_PROPERTY(bool backgroundRendering READ hasBackgroundRendering WRITE setBackgroundRendering)

private:
    double m_MouseLeaveOpacity;///< defines the opacity of the control if mouse leaves this control
    bool m_RenderBackground;///< set to false to get a transparent background (only the 5 buttons are visible)
    double m_Opacity;///< stores actual opacity value
    QString m_skin; ///< name of actual skin

    /** pointer to one Button **/
    QtNavigationButton* m_upButton;
    /** pointer to one Button **/
    QtNavigationButton* m_downButton;
    /** pointer to one Button **/
    QtNavigationButton* m_leftButton;
    /** pointer to one Button **/
    QtNavigationButton* m_rightButton;
    /** pointer to one Button **/
    QtNavigationButton* m_centerButton;

    /** m_rendererBase used to render the skin SVG graphics **/
    QtSvgPixmapCache *m_rendererBase;

    /**
     * @brief A kind of private constructor.
     */
    void init();

protected: // implemented from QWidget ---------------------------------------
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual int heightForWidth ( int w ) const;
    virtual void leaveEvent(QEvent * event);
    virtual void enterEvent(QEvent * event);

public: // implemented from QWidget ------------------------------------------
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public:
    explicit Qt5WayButton(QWidget * parent = 0);
    virtual ~Qt5WayButton();

    QAbstractButton * upButton();
    QAbstractButton * downButton();
    QAbstractButton * leftButton();
    QAbstractButton * rightButton();
    QAbstractButton * centerButton();

    /**
     * @brief Set a certain skin by name
     */
    void setSkin(const QString& skin);

    /**
     * @brief Returns the actual skin by name
     */
    QString skin() const;

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

private Q_SLOTS:
}; // class Qt5WayButton

#undef QSvgRenderer

#endif // QT_5WAY_BUTTON_H
