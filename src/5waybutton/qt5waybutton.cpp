//============================================================================
/**
 * \file   qt5waybutton.cpp
 * \author Uwe Kindler
 * \date   02.06.2010
 * \brief  Implementation of 5 way SVG button control.
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
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>
#include <QAbstractButton>
#include <QGridLayout>
#include <QBitmap>

#include "qt5waybutton.h"
#include "qtsvgpixmapcache.h"
#include "QtNavigationButton.h"



/*!
    \class Qt5WayButton

    \brief The Qt5WayButton provides a button group with SVG graphics.

    Qt5WayButton is a widget that consists of five Buttons, one on any edge
    and one in the middle of the widget. Each button is represented as a
    QAbstractButton and can be accessed with the methods \a upButton(),
    \a downButton(), \a leftButton(), \a rightButton(), \a centerButton().
    The returned buttons can then be used to connect signals and slots or to
    change properties like the checkable state.

    \section qt5waybutton_example Example Usage
    The following example shows how to create a Qt5WayButton.
    \code
    Qt5WayButton* button = new Qt5WayButton(parent);
    button->setSkin("Beryl");
    QObject::connect(button->upButton(), SIGNAL(clicked()), this, SLOT(moveUp()));
    \endcode

    \section qt5waybutton_skin Setting a Skin

    After creating a new Qt5WayButton a skin needs to be set by calling
    \a setSkin(). Without a skin set, a Qt5WayButton will not have any
    visible content. skin() returns the current skin.
    Further details about skinning the Qt5WayButton can be found in the
    widget description.
*/


//============================================================================
/*!
    Constructor of the widget with  parent as
    Parent.
*/
Qt5WayButton::Qt5WayButton(QWidget * parent)
    : QWidget(parent),
      m_MouseLeaveOpacity(1.0),
      m_RenderBackground(true),
      m_Opacity(1.0)
{
	init();
}


//============================================================================
/*!
    Destructor
*/
Qt5WayButton::~Qt5WayButton()
{
}


//============================================================================
/*!
    \internal
    Internal initalisation function
*/
void Qt5WayButton::init()
{
    QSizePolicy sp;
    sp.setHeightForWidth(true);
    setSizePolicy(sp);

    QGridLayout* grid = new QGridLayout(this);
    grid->setMargin(0);
    grid->setSpacing(0);

    m_upButton = new QtNavigationButton(this);
    m_downButton = new QtNavigationButton(this);
    m_leftButton = new QtNavigationButton(this);
    m_rightButton = new QtNavigationButton(this);
    m_centerButton = new QtNavigationButton(this);

    grid->addWidget(m_upButton, 0, 0, 1, 2);
    grid->addWidget(m_downButton, 1, 0, 1, 2);
    grid->addWidget(m_leftButton, 0, 0, 2, 1);
    grid->addWidget(m_rightButton, 0, 1, 2, 1);
    grid->addWidget(m_centerButton, 0, 0, 2, 2);

    m_rendererBase = new QtSvgPixmapCache(this);
}


//============================================================================
/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the Qt5WayButton.

    \sa skin()

*/
void Qt5WayButton::setSkin(const QString& skin)
{
    m_skin = skin;

    const QString base = ":/5waybutton/" + skin + '/';
    m_rendererBase->load(base + "background.svg");

    m_upButton->setSkin(":/5waybutton", skin, "up");
    m_downButton->setSkin(":/5waybutton", skin, "down");
    m_leftButton->setSkin(":/5waybutton", skin, "left");
    m_rightButton->setSkin(":/5waybutton", skin, "right");
    m_centerButton->setSkin(":/5waybutton", skin, "center");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();

    m_upButton->updateMask();
    m_downButton->updateMask();
    m_leftButton->updateMask();
    m_rightButton->updateMask();
    m_centerButton->updateMask();
}


//============================================================================
/*!

    This function returns the actual skin name. If no skin has been set the
    return value is "".

    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        button->setSkin("Beryl");
        qDebug() << button->skin();
    \endcode

    \sa setSkin()

*/
QString Qt5WayButton::skin() const
{
    return m_skin;
}


//============================================================================
/*!
    This function returns the actual pointer from the upButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::upButton()
{
    return m_upButton;
}


//============================================================================
/*!
    This function returns the actual pointer from the downButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::downButton()
{
    return m_downButton;
}


//============================================================================
/*!
    This function returns the actual pointer from the leftButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::leftButton()
{
    return m_leftButton;
}


//============================================================================
/*!
    This function returns the actual pointer from the rightButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::rightButton()
{
    return m_rightButton;
}


//============================================================================
/*!
    This function returns the actual pointer from the centerButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->centerButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::centerButton()
{
    return m_centerButton;
}


//============================================================================
/*!
    \overload
    The \a paintEvent() draws the Qt5WayButton and shows the actual state
    "normal", "hovered", "clicked" from the button.
*/
void Qt5WayButton::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setOpacity(m_Opacity);

    if (m_RenderBackground)
    {
    	m_rendererBase->render(&painter, m_centerButton->geometry());
    }

    m_upButton->paint(&painter);
    m_downButton->paint(&painter);
    m_leftButton->paint(&painter);
    m_rightButton->paint(&painter);
    m_centerButton->paint(&painter);
}


//============================================================================
/*!
    \overload
    To provide a minimum size hint at startup. Can be changed at runtime.
*/
QSize Qt5WayButton::minimumSizeHint() const
{
    return QSize(100, 100);
}


//============================================================================
/*!
    \overload
    To provide a size hint at startup. Can be changed at runtime.
*/
QSize Qt5WayButton::sizeHint() const
{
    return QSize(150, 150);
}


//============================================================================
/*!
    \overload
    \internal
    To update the clickable area of the Buttons on size change.
*/
void Qt5WayButton::resizeEvent(QResizeEvent* event)
{
    // update masks
    m_upButton->updateMask();
    m_downButton->updateMask();
    m_leftButton->updateMask();
    m_rightButton->updateMask();
    m_centerButton->updateMask();

    QWidget::resizeEvent(event);
}


//============================================================================
/*!
    \overload
    To be sure that the width and the height are always the same size.
*/
int Qt5WayButton::heightForWidth(int w) const
{
    return w;
}


//============================================================================
void Qt5WayButton::leaveEvent(QEvent * event)
{
	m_Opacity = m_MouseLeaveOpacity;
	update();
}


//============================================================================
void Qt5WayButton::enterEvent(QEvent * event)
{
	m_Opacity = 1.0;
	update();
}


//============================================================================
void Qt5WayButton::setMouseLeaveOpacity(double Opacity)
{
	m_MouseLeaveOpacity = Opacity;
	m_Opacity = m_MouseLeaveOpacity;
	update();
}


//============================================================================
double Qt5WayButton::mouseLeaveOpacity()
{
	return m_MouseLeaveOpacity;
}


//============================================================================
void Qt5WayButton::setBackgroundRendering(bool RenderBackground)
{
	m_RenderBackground = RenderBackground;
	update();
}


//============================================================================
bool Qt5WayButton::hasBackgroundRendering()
{
	return m_RenderBackground;
}

