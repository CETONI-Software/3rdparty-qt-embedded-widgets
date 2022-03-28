//============================================================================
/// \file   NavigationButton.cpp
/// \author Uwe Kindler
/// \date   01.06.2010
/// \brief  Implementation of NavigationButton class.
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QTouchEvent>
#include <QApplication>

#include "QtNavigationButton.h"


//============================================================================
QtNavigationButton::QtNavigationButton(QWidget* parent)
	: QAbstractButton(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_normal = new QtSvgPixmapCache(this);
	m_pressed = new QtSvgPixmapCache(this);
	m_hovered = new QtSvgPixmapCache(this);
}


//============================================================================
QtNavigationButton::~QtNavigationButton()
{
}


//============================================================================
void QtNavigationButton::setSkin(const QString& base, const QString& skin, const QString& name)
{
	const QString skin_element = base + '/' + skin + '/' + name;
	m_normal->load(skin_element + ".svg");
	m_pressed->load(skin_element + "_pressed.svg");
	m_hovered->load(skin_element + "_hover.svg");
}


//============================================================================
void QtNavigationButton::paint(QPainter* painter)
{
	if (isDown() || isChecked())
	{
		m_pressed->render(painter, geometry());
	}
	else if (underMouse() && !testAttribute(Qt::WA_AcceptTouchEvents))
	{
		m_hovered->render(painter, geometry());
	}
	else
	{
		m_normal->render(painter, geometry());
	}
}


//============================================================================
void QtNavigationButton::updateMask()
{
	QPixmap pixmap(size());
	pixmap.fill();

	QPainter painter(&pixmap);
	m_normal->render(&painter, rect());
	painter.end();

	QBitmap bitmap = pixmap.createHeuristicMask();
	setMask(bitmap);
	update();
}


//============================================================================
void QtNavigationButton::paintEvent(QPaintEvent*)
{
}


//============================================================================
void QtNavigationButton::enterEvent(QEvent*)
{
	parentWidget()->update();
}


//============================================================================
void QtNavigationButton::leaveEvent(QEvent * event)
{
	Q_UNUSED(event);
	parentWidget()->update();
}

//============================================================================
void QtNavigationButton::enableTouchEvents(bool Enable)
{
	setAttribute(Qt::WA_AcceptTouchEvents, Enable);
}


//============================================================================
void QtNavigationButton::mousePressEvent(QMouseEvent *event)
{
	QAbstractButton::mousePressEvent(event);
}


//============================================================================
void QtNavigationButton::mouseReleaseEvent(QMouseEvent *event)
{
	QAbstractButton::mouseReleaseEvent(event);
}


//============================================================================
bool QtNavigationButton::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::TouchBegin:
	case QEvent::TouchEnd:
	case QEvent::TouchUpdate:
		 return touchEvent(static_cast<QTouchEvent*>(event));
		 break;
	default:
		return QAbstractButton::event(event);
	}
	return QAbstractButton::event(event);
}


//============================================================================
bool QtNavigationButton::touchEvent(QTouchEvent* event)
{
	event->accept();
	switch (event->type())
	{
	case QEvent::TouchBegin:
		  setDown(true);
		  repaint(); //flush paint event before invoking potentially expensive operation
          QApplication::flush();
		  emit pressed();
		  break;

	case QEvent::TouchEnd:
		 setDown(false);
		 repaint(); //flush paint event before invoking potentially expensive operation
         QApplication::flush();
		 emit released();
		 break;

	default:
		return true;
	}
	return true;
}


//---------------------------------------------------------------------------
// EOF NavigationButton.cpp
