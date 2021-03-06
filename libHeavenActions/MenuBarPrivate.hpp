/*
 * libHeaven - A Qt-based ui framework for strongly modularized applications
 * Copyright (C) 2012-2013 Sascha Cunz <sascha@babbelbox.org>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License (Version 2) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MGV_HEAVEN_MENUBAR_PRIVATE_H
#define MGV_HEAVEN_MENUBAR_PRIVATE_H

#include <QSet>

class QMenuBar;

#include "libHeavenActions/MenuBar.hpp"
#include "libHeavenActions/UiContainer.hpp"

namespace Heaven
{

    class MenuBarPrivate : public UiContainer
    {
        Q_OBJECT
    public:
        MenuBarPrivate( MenuBar* owner );
        ~MenuBarPrivate();

    public:
        QMenuBar* createQMenuBar( QWidget* forParent );
        QMenuBar* getOrCreateQMenuBar( QWidget* forParent );

    private slots:
        void qmenubarDestroyed();
        void reemergeGuiElement();

    public:
        void setContainerDirty( bool value = true );
        UiObjectTypes type() const;

    public:
        bool                mRebuildQueued;
        QSet< QMenuBar* >   mMenuBars;
    };
}

#endif
