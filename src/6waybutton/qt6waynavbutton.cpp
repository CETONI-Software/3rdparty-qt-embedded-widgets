//============================================================================
/// \file   qt6waynavbutton.cpp
/// \author Uwe Kindler
/// \date   03.06.2010
/// \brief  Implementation of navigation button for Qt6WayNavButton
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include "qt6waynavbutton.h"

struct stButtonIdMapping
{
	Qt6WayButton::eAxisId AxisId;
	Qt6WayButton::eDirection Direction;
};

static const stButtonIdMapping ButtonIdMappingTbl[6] =
{
	 {Qt6WayButton::Y_AXIS, Qt6WayButton::DIRECTION_NEGATIVE},
	 {Qt6WayButton::Y_AXIS, Qt6WayButton::DIRECTION_POSITIVE},
	 {Qt6WayButton::X_AXIS, Qt6WayButton::DIRECTION_NEGATIVE},
	 {Qt6WayButton::X_AXIS, Qt6WayButton::DIRECTION_POSITIVE},
	 {Qt6WayButton::Z_AXIS, Qt6WayButton::DIRECTION_NEGATIVE},
	 {Qt6WayButton::Z_AXIS, Qt6WayButton::DIRECTION_POSITIVE},
};

//============================================================================
Qt6WayNavButton::Qt6WayNavButton(Qt6WayButton::eButtonId ButtonId,
    Qt6WayButton* parent) :
	QtNavigationButton(parent), m_ButtonId(ButtonId), m_Parent(parent)
{
	connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked(bool)));
	connect(this, SIGNAL(pressed()), this, SLOT(onPressed()));
	connect(this, SIGNAL(released()), this, SLOT(onReleased()));
}

//============================================================================
void Qt6WayNavButton::onClicked(bool Checked)
{
	m_Parent->onButtonClicked(this, Checked);
}


//============================================================================
void Qt6WayNavButton::onPressed()
{
	m_Parent->onButtonPressed(this);
}


//============================================================================
void Qt6WayNavButton::onReleased()
{
	m_Parent->onButtonReleased(this);
}


//============================================================================
Qt6WayButton::eButtonId Qt6WayNavButton::buttonId() const
{
	return m_ButtonId;
}


//============================================================================
Qt6WayButton::eAxisId Qt6WayNavButton::axisId() const
{
	return ButtonIdMappingTbl[m_ButtonId].AxisId;
}


//============================================================================
Qt6WayButton::eDirection Qt6WayNavButton::direction() const
{
	return ButtonIdMappingTbl[m_ButtonId].Direction;
}

//---------------------------------------------------------------------------
// EOF qt6waynavbutton.cpp
