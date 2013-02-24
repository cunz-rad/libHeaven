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

#ifndef MGV_HEAVEN_APPLICATION_H
#define MGV_HEAVEN_APPLICATION_H

#include <QObject>

#include "libHeaven/App/SecondaryWindow.hpp"

namespace Heaven
{

    class Mode;
    class PrimaryWindow;
    class View;
    class ViewFactory;
    class ApplicationPrivate;

    class HEAVEN_API Application : public QObject
    {
        Q_OBJECT
        friend class ApplicationPrivate;
    public:
        static Application* self();

    public:
        PrimaryWindow* primaryWindow() const;
        SecondaryWindows secondaryWindows() const;
        HeavenWindows allWindows() const;

        SecondaryWindow* createSecondaryWindow();
        HeavenWindow* window( const QString& handle, bool create );

    public:
        void addMode( Mode* mode );
        void removeMode( Mode* mode );
        void setCurrentMode( Mode* mode );
        Mode* findMode( const QString& name );
        Mode* currentMode();

        static QString dataPath();

        void setViewFactory( ViewFactory* factory );
        View* createView( const QString& identifer );

    public:
        QSet< View* > openViews() const;

    signals:
        void currentModeChanged( Heaven::Mode* mode );

    private slots:
        void reapplyMode();

    private:
        Application();
        static Application* sSelf;
        ApplicationPrivate* d;
    };

}

#endif
