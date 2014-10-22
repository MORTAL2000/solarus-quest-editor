/*
 * Copyright (C) 2014 Christopho, Solarus - http://www.solarus-games.org
 *
 * Solarus Quest Editor is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solarus Quest Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "enum_traits.h"
#include <QMenu>

template<typename E>
class EnumTraits;

/**
 * @brief Creates a menu with all values of the enum.
 * @param checkable How checkable actions should be.
 * @return The created menu. It has no parent.
 */
template<typename E>
QMenu* EnumMenus<E>::create_menu(EnumMenuCheckableOption checkable) {

  QMenu* menu = new QMenu();
  QList<QAction*> actions = create_actions(menu, checkable);
  for (QAction* action : actions) {
    menu->addAction(action);
  }
  return menu;
}

/**
 * @brief Creates actions corresponding to all values of the enum.
 * @param parent Parent of actions to create. They will be added to this widget.
 * @param checkable How checkable actions should be.
 * @param The created actions. They have no parent.
 */
template<typename E>
QList<QAction*> EnumMenus<E>::create_actions(QWidget* parent, EnumMenuCheckableOption checkable) {

  QList<QAction*> actions;
  for (const E& value : EnumTraits<E>::get_values()) {
    const QIcon& icon = EnumTraits<E>::get_icon(value);
    const QString& text = EnumTraits<E>::get_friendly_name(value);
    QAction* action = new QAction(icon, text, parent);
    action->setData(static_cast<int>(value));
    if (checkable != EnumMenuCheckableOption::NON_CHECKABLE) {
      action->setCheckable(true);
    }
    if ((int)value == 2) action->setChecked(true);
    parent->addAction(action);
    actions << action;
  }
  return actions;
}
