/*
 * libHeaven - A Qt-based ui framework for strongly modularized applications
 * Copyright (C) 2012 Sascha Cunz <sascha@babbelbox.org>
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

#ifndef MGV_HEAVEN_UIOBJECT_PRIVATE_HPP
#define MGV_HEAVEN_UIOBJECT_PRIVATE_HPP

#include <QObject>
#include <QSet>

#include "libHeaven/Heaven.hpp"
#include "libHeaven/HeavenPrivate.hpp"

namespace Heaven
{

    class UiContainer;

    class UiObjectPrivate : public QObject
    {
        friend class UiContainer;
        Q_OBJECT
    protected:
        UiObjectPrivate( QObject* owner );
        ~UiObjectPrivate();

    public:
        virtual UiObjectTypes type() const = 0;

    protected:
        void addedToContainer( UiContainer* container );
        void removeFromContainer( UiContainer* container );
        void removedFromContainer( UiContainer* container );

        QObject* owner() const;

    private:
        QObject*                mOwner;
        QSet< UiContainer* >    mContainers;
    };

}

#endif