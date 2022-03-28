#ifndef NavigationButtonH
#define NavigationButtonH
//============================================================================
/// \file   NavigationButton.h
/// \author Uwe Kindler
/// \date   01.06.2010
/// \brief  Declaration of NavigationButton class
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <QAbstractButton>
#include "qtsvgpixmapcache.h"

class QTouchEvent;

/**
 * @brief Private helper class which is used for the region and events of the
 * multi way navigation button and spin buttons.
 */
class QtNavigationButton : public QAbstractButton
{
	Q_OBJECT
private:
    QtSvgPixmapCache *m_normal;
    QtSvgPixmapCache *m_pressed;
    QtSvgPixmapCache *m_hovered;

protected:
    /**
     * Implemented to sacrifice pure virtual
     */
    virtual void paintEvent(QPaintEvent*);

    /**
     * @brief Calls update of parent widget for hover effect.
     */
    virtual void enterEvent(QEvent*);

    /**
     * @brief Calls update of parent widget to end hover effect.
     */
    virtual void leaveEvent(QEvent * event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual bool event(QEvent* event);
    bool touchEvent(QTouchEvent* event);

public:
	/**
	 * @brief Create navigation button with parent
	 */
    QtNavigationButton(QWidget* parent);

    /**
     * @brief Virtual destructor
     */
    virtual ~QtNavigationButton();

    /**
     * @brief Set a new skin
     * @param base Base directory of the skin in the resource file
     * @param skin Name of the skin
     * @param name Name of the skin element
     */
    void setSkin(const QString& base, const QString& skin, const QString& name);

    /**
     * @brief Paints navigation button
     */
    void paint(QPainter* painter);

    /**
     * @brief Update heuristic mask of this button
     */
    void updateMask();

    /**
     * Enables / disables touch events
     */
    void enableTouchEvents(bool Enable);
}; // class QtNavigationButton

//---------------------------------------------------------------------------
#endif // NavigationButtonH
