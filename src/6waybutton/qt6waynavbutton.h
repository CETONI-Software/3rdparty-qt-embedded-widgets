#ifndef qt6waynavbuttonH
#define qt6waynavbuttonH
//============================================================================
/// \file   qt6waynavbutton.h
/// \author Uwe Kindler
/// \date   03.06.2010
/// \brief  Declaration of navigation button for qt6waybutton.
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include "QtNavigationButton.h"
#include "qt6waybutton.h"


/**
 * @brief Private helper class which is used by qt6waybutton for propagation
 * of navigation button events.
 *
 * The Qt6WayNavButton offers some functionality that make it easy to handle
 * the signals of all buttons in a single slot. The Qt6WayNavButton has three
 * functions to identify the button type (UP, DOWN, LEFT, RIGHT, CENTER_UP and
 * CENTER_DOWN), the type of the axis a certain button belongs to (X_AXIS,
 * Y_AXIS or Z_AXIS) and the direction type (DIRECTION_POSITIVE or
 * DIRECTION_NEGATIVE.
 */
class Qt6WayNavButton : public QtNavigationButton
{
    Q_OBJECT
private:
	Qt6WayButton::eButtonId m_ButtonId;///< button identifier
	Qt6WayButton* m_Parent;///< pointer to the Qt6WayButton class that owns this navigation button

private slots:
	/**
	 * @brief Calls onButtonClicked() of the Qt6WayButton class and passed its
	 * button ID.
	 */
	void onClicked(bool Checked);

	/**
	 * @brief Calls onButtonPressed() of the Qt6WayButton class and passed its
	 * button ID.
	 */
	void onPressed();

	/**
	 * @brief Calls onButtonReleased() of the Qt6WayButton class and passed its
	 * button ID.
	 */
	void onReleased();

public:
	/**
	 * @brief Create an navigation button and registers the owner of this button
	 * and the type identifier.
	 * @param ButtonId Identifies the button type (UP, DOWN, LEFT...)
	 * @param parent The Qt6WayButton that owns this navigation button
	 * @return
	 */
	Qt6WayNavButton(Qt6WayButton::eButtonId ButtonId, Qt6WayButton* parent);

	/**
	 * @brief Returns the button identifier of this navigation button
	 */
	Qt6WayButton::eButtonId buttonId() const;

	/**
	 * @brief Returns the axis identifier of this button.
	 * The axis identifier makes it easy to determine the axis a button belongs
	 * to. Each axis is build up of two buttons. (i.e. X_AXIS consists of
	 * buttons LEFT and RIGHT).
	 */
	Qt6WayButton::eAxisId axisId() const;

	/**
	 * @brief Returns the direction identifier of this button.
	 * This function enables the identification of the direction of the button
	 * that is clicked on a certain axis. (i.e. the CENTER_UP button is the
	 * button with DIRECTION_NEGATIVE on the Z_AXIS).
	 */
	Qt6WayButton::eDirection direction() const;
};

//---------------------------------------------------------------------------
#endif // qt6waynavbuttonH
