/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>
#include <QAbstractButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QBitmap>

#include "qtsvgspinbutton.h"
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


/*!
    Constructor of the widget with  parent as
    Parent.
*/
QtSvgSpinButton::QtSvgSpinButton(QWidget * parent)
    : QWidget(parent)
{
    init();
}
/*!
    Destructor
*/
QtSvgSpinButton::~QtSvgSpinButton()
{
}
/*!
    \internal
    Internal initalisation function
*/
void QtSvgSpinButton::init()
{
    QSizePolicy sp;
    sp.setHeightForWidth(true);
    setSizePolicy(sp);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_upButton = new QtNavigationButton(this);
    m_downButton = new QtNavigationButton(this);

    layout->addWidget(m_upButton);
    layout->addWidget(m_downButton);
}
/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        QtSvgSpinButton * button = new QtSvgSpinButton(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the QtSvgSpinButton.

    \sa skin()

*/
void QtSvgSpinButton::setSkin(const QString& skin)
{
    m_skin = skin;

    const QString base = ":/svgspinbutton/" + skin + '/';

    m_upButton->setSkin(":/svgspinbutton", skin, "up");
    m_downButton->setSkin(":/svgspinbutton", skin, "down");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();

    m_upButton->updateMask();
    m_downButton->updateMask();
}

/*!

    This function returns the actual skin name. If no skin has been set the
    return value is "".

    \code
        QtSvgSpinButton * button = new QtSvgSpinButton(this);
        button->setSkin("Beryl");
        qDebug() << button->skin();
    \endcode

    \sa setSkin()

*/
QString QtSvgSpinButton::skin() const
{
    return m_skin;
}

/*!
    This function returns the actual pointer from the upButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        QtSvgSpinButton * button = new QtSvgSpinButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * QtSvgSpinButton::upButton()
{
    return m_upButton;
}

/*!
    This function returns the actual pointer from the downButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        QtSvgSpinButton * button = new QtSvgSpinButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * QtSvgSpinButton::downButton()
{
    return m_downButton;
}


/*!
    \overload
    The \a paintEvent() draws the QtSvgSpinButton and shows the actual state
    "normal", "hovered", "clicked" from the button.
*/
void QtSvgSpinButton::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    m_upButton->paint(&painter);
    m_downButton->paint(&painter);
}

/*!
    \overload
    To provide a minimum size hint at startup. Can be changed at runtime.
*/
QSize QtSvgSpinButton::minimumSizeHint() const
{
    return QSize(20, 20);
}

/*!
    \overload
    To provide a size hint at startup. Can be changed at runtime.
*/
QSize QtSvgSpinButton::sizeHint() const
{
	return QSize(m_upButton->sizeHint().width(), m_upButton->sizeHint().height()
		+ m_downButton->sizeHint().height());
}

/*!
    \overload
    \internal
    To update the clickable area of the Buttons on size change.
*/
void QtSvgSpinButton::resizeEvent(QResizeEvent* event)
{
    // update masks
    m_upButton->updateMask();
    m_downButton->updateMask();

    QWidget::resizeEvent(event);
}

/*!
    \overload
    To be sure that the width and the height are always the same size.
*/
int QtSvgSpinButton::heightForWidth(int w) const
{
    return w;
}
