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

#ifndef MGV_HEAVEN_APPLICATION_H
#define MGV_HEAVEN_APPLICATION_H

#include <QObject>

#include "libHeaven/HeavenApi.hpp"

namespace Heaven
{

    class Mode;
    class PrimaryWindow;
    class ApplicationPrivate;

    class HEAVEN_API Application : public QObject
    {
        Q_OBJECT
    public:
        static Application* self();

    public:
        PrimaryWindow* primaryWindow() const;

    public:
        void addMode( Mode* mode );
        void removeMode( Mode* mode );
        void setCurrentMode( Mode* mode );
        Mode* findMode( const QString& name );
        Mode* currentMode();

    private:
        Application();
        static Application* sSelf;
        ApplicationPrivate* d;
    };

}

#endif