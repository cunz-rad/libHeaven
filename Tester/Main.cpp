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

#include <QApplication>
#include <QPalette>

#include "libHeavenIcons/IconManager.hpp"
#include "libHeavenIcons/IconDefaultProvider.hpp"

#include "libHeavenActions/MenuBar.hpp"
#include "libHeavenActions/Menu.hpp"

#include "libBlueSky/Windows.hpp"

#include "Application.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Heaven::IconManager::self().defaultProvider()->addSearchPath(QString::fromLatin1(":/icons"));

    Application bsApp;
    BlueSky::PrimaryWindow* pw = bsApp.primaryWindow();

    QPalette p;
    p.setColor(QPalette::Base, qRgb(0xDD, 0xEE, 0xFF));
    pw->setPalette(p);
    pw->show();

    return app.exec();
}
