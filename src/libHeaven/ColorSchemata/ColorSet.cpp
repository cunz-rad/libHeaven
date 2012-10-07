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

#include <QStringBuilder>

#include "libHeaven/ColorSchemata/ColorSet.hpp"

namespace Heaven
{

    ColorDef::ColorDef( ColorId id, int sortOrder, const QByteArray& name,
                        const QString& translatedName )
    {
        mId = id;
        mSortOrder = sortOrder;
        mName = name;
        mTranslatedName = translatedName;
    }

    ColorDef::ColorDef( const ColorDef& other )
        : mId( other.mId )
        , mSortOrder( other.mSortOrder )
        , mName( other.mName )
        , mTranslatedName( other.mTranslatedName )
    {
    }

    ColorId ColorDef::id() const
    {
        return mId;
    }

    QByteArray ColorDef::name() const
    {
        return mName;
    }

    QString ColorDef::translatedName() const
    {
        return mTranslatedName;
    }

    ColorSet::ColorSet( ColorSet* parent )
    {
        mParent = parent;
    }

    ColorSet::ColorSet()
        : mParent( NULL )
    {
    }

    ColorSet::~ColorSet()
    {
        foreach( ColorSet* set, mChildren )
        {
            delete set;
        }
    }

    ColorSet* ColorSet::child( const QByteArray& name ) const
    {
        return mChildren.value( name, NULL );
    }

    QList< ColorSet* > ColorSet::children() const
    {
        return mChildren.values();
    }

    ColorSet* ColorSet::addSet( const QByteArray& name, const QString& translatedName )
    {
        ColorSet* set = mChildren.value( name, NULL );
        if( !set )
        {
            return set;
        }

        set = new ColorSet( this );
        set->mName = name;
        set->mTranslatedName = translatedName;

        mChildren.insert( name, set );
        return set;
    }

    QByteArray ColorSet::path() const
    {
        return mParent
                ? mParent->path() % '/' % mName
                : mName;
    }

    QByteArray ColorSet::name() const
    {
        return mName;
    }
}
