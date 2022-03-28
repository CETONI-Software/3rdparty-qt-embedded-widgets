//============================================================================
/**
 * \file   qt6waybutton.cpp
 * \author Uwe Kindler
 * \date   02.06.2010
 * \brief  Implementation of 6 way SVG button control.
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
#include <QPropertyAnimation>

#include "qt6waybutton.h"
#include "qt6waynavbutton.h"
#include "qtsvgpixmapcache.h"
#include "QtNavigationButton.h"

#include <iostream>



//============================================================================
/*!
    Constructor of the widget with  parent as
    Parent.
*/
Qt6WayButton::Qt6WayButton(QWidget * parent)
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
Qt6WayButton::~Qt6WayButton()
{
}


//============================================================================
/*!
    \internal
    Internal initalisation function
*/
void Qt6WayButton::init()
{
    QSizePolicy sp;
    sp.setHeightForWidth(true);
    setSizePolicy(sp);

    QGridLayout* grid = new QGridLayout(this);
    grid->setMargin(0);
    grid->setSpacing(0);

    m_Buttons.append(new Qt6WayNavButton(UP, this));
    m_Buttons.append(new Qt6WayNavButton(DOWN, this));
    m_Buttons.append(new Qt6WayNavButton(LEFT, this));
    m_Buttons.append(new Qt6WayNavButton(RIGHT, this));
    m_Buttons.append(new Qt6WayNavButton(CENTER_UP, this));
    m_Buttons.append(new Qt6WayNavButton(CENTER_DOWN, this));

    grid->addWidget(m_Buttons[UP], 0, 0, 1, 2);
    grid->addWidget(m_Buttons[DOWN], 1, 0, 1, 2);
    grid->addWidget(m_Buttons[LEFT], 0, 0, 2, 1);
    grid->addWidget(m_Buttons[RIGHT], 0, 1, 2, 1);
    grid->addWidget(m_Buttons[CENTER_UP], 0, 0, 1, 2);
    grid->addWidget(m_Buttons[CENTER_DOWN], 1, 0, 1, 2);

    m_rendererBase = new QtSvgPixmapCache(this);
    this->setupOpacityAnimation();
}


//============================================================================
void Qt6WayButton::setupOpacityAnimation()
{
    m_OpacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_OpacityAnimation->setDuration(200);
    m_OpacityAnimation->setStartValue(1.0);
}


//============================================================================
/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the Qt6WayButton.

    \sa skin()

*/
void Qt6WayButton::setSkin(const QString& skin)
{
    static const char* SkinElement[6] =
    {
		 "up", "down", "left", "right", "center_up", "center_down"
    };
	m_skin = skin;

    const QString base = ":/6waybutton/" + skin + '/';
    m_rendererBase->load(base + "background.svg");

    for (int i = 0; i < 6; ++i)
    {
    	m_Buttons[i]->setSkin(":/6waybutton", skin, SkinElement[i]);
    }

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();

    for (int i = 0; i < 6; ++i)
    {
    	m_Buttons[i]->updateMask();
    }
}


//============================================================================
/*!

    This function returns the actual skin name. If no skin has been set the
    return value is "".

    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        button->setSkin("Beryl");
        qDebug() << button->skin();
    \endcode

    \sa setSkin()

*/
QString Qt6WayButton::skin() const
{
    return m_skin;
}


//============================================================================
/*!
    This function returns the actual pointer from the upButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt6WayButton::upButton()
{
    return m_Buttons[UP];
}


//============================================================================
/*!
    This function returns the actual pointer from the downButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt6WayButton::downButton()
{
    return m_Buttons[DOWN];
}


//============================================================================
/*!
    This function returns the actual pointer from the leftButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt6WayButton::leftButton()
{
    return m_Buttons[LEFT];
}


//============================================================================
/*!
    This function returns the actual pointer from the rightButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt6WayButton::rightButton()
{
    return m_Buttons[RIGHT];
}


//============================================================================
/*!
    This function returns the actual pointer from the centerButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt6WayButton * button = new Qt6WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->centerButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt6WayButton::centerUpButton()
{
    return m_Buttons[CENTER_UP];
}


//============================================================================
QAbstractButton * Qt6WayButton::centerDownButton()
{
    return m_Buttons[CENTER_DOWN];
}


//============================================================================
/*!
    \overload
    The \a paintEvent() draws the Qt6WayButton and shows the actual state
    "normal", "hovered", "clicked" from the button.
*/
void Qt6WayButton::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setOpacity(m_Opacity);

    if (m_RenderBackground)
    {
    	m_rendererBase->render(&painter, this->geometry());
    }

    for (int i = 0; i < 6; ++i)
    {
    	m_Buttons[i]->paint(&painter);
    }
}


//============================================================================
/*!
    \overload
    To provide a minimum size hint at startup. Can be changed at runtime.
*/
QSize Qt6WayButton::minimumSizeHint() const
{
    return QSize(100, 100);
}


//============================================================================
/*!
    \overload
    To provide a size hint at startup. Can be changed at runtime.
*/
QSize Qt6WayButton::sizeHint() const
{
    return QSize(150, 150);
}


//============================================================================
/*!
    \overload
    \internal
    To update the clickable area of the Buttons on size change.
*/
void Qt6WayButton::resizeEvent(QResizeEvent* event)
{
    for (int i = 0; i < 6; ++i)
    {
    	m_Buttons[i]->updateMask();
    }

    QWidget::resizeEvent(event);
}


//============================================================================
/*!
    \overload
    To be sure that the width and the height are always the same size.
*/
int Qt6WayButton::heightForWidth(int w) const
{
    return w;
}


//============================================================================
void Qt6WayButton::leaveEvent(QEvent * event)
{
	m_OpacityAnimation->setDirection(QAbstractAnimation::Forward);
	m_OpacityAnimation->start();
}


//============================================================================
void Qt6WayButton::enterEvent(QEvent * event)
{
	m_OpacityAnimation->setDirection(QAbstractAnimation::Backward);
	m_OpacityAnimation->start();
}


//============================================================================
void Qt6WayButton::setMouseLeaveOpacity(double Opacity)
{
	m_MouseLeaveOpacity = Opacity;
	setOpacity(m_MouseLeaveOpacity);
	m_OpacityAnimation->setEndValue(m_MouseLeaveOpacity);
}


//============================================================================
double Qt6WayButton::mouseLeaveOpacity()
{
	return m_MouseLeaveOpacity;
}


//============================================================================
void Qt6WayButton::setBackgroundRendering(bool RenderBackground)
{
	m_RenderBackground = RenderBackground;
	update();
}


//============================================================================
bool Qt6WayButton::hasBackgroundRendering()
{
	return m_RenderBackground;
}


//============================================================================
double Qt6WayButton::opacity()
{
	return m_Opacity;
}


//============================================================================
void Qt6WayButton::setOpacity(double Opacity)
{
	m_Opacity = Opacity;
	update();
}


//============================================================================
QList<QtNavigationButton*>& Qt6WayButton::buttons()
{
	return m_Buttons;
}


//============================================================================
void Qt6WayButton::onButtonClicked(Qt6WayNavButton* Button, bool Checked)
{
	emit clicked(Button, Checked);
}


//============================================================================
void Qt6WayButton::onButtonPressed(Qt6WayNavButton* Button)
{
	if (testAttribute(Qt::WA_AcceptTouchEvents))
	{
		m_OpacityAnimation->setDirection(QAbstractAnimation::Backward);
		m_OpacityAnimation->start();
	}
	emit pressed(Button);
}


//============================================================================
void Qt6WayButton::onButtonReleased(Qt6WayNavButton* Button)
{
	if (testAttribute(Qt::WA_AcceptTouchEvents))
	{
		m_OpacityAnimation->setDirection(QAbstractAnimation::Forward);
		m_OpacityAnimation->start();
	}
	emit released(Button);
}


//============================================================================
void Qt6WayButton::enableTouchEvents(bool Enable)
{
	setAttribute(Qt::WA_AcceptTouchEvents, Enable);
	for (auto& Button : m_Buttons)
	{
		Button->enableTouchEvents(Enable);
	}
}


