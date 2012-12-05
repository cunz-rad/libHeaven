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

#include <QDateTime>

#include "HIGenSource.h"

HIGenSource::HIGenSource( const HIDModel& model, const QString& fileName, const QString& baseName )
    : HIGeneratorBase( model, fileName )
    , mBaseName( baseName )
{
}

void HIGenSource::writeSetProperties( HICObject* obj, const char* whitespace, const char* prefix )
{
    foreach( QString pname, obj->propertyNames() )
    {
        if( pname.startsWith( L'_' ) )
        {
            continue;
        }
        HICProperty p = obj->getProperty( pname );

        out() << whitespace << prefix << obj->name() << "->set" << pname << "( ";

        switch( p.type() )
        {
        case HICP_String:
            out() << "QLatin1String( \"" << latin1Encode( p.value().toString() ) << "\" )";
            break;

        case HICP_TRString:
            out() << "trUtf8( \"" << utf8Encode( p.value().toString() ) << "\" )";
            break;

        case HICP_Boolean:
            out() << ( p.value().toBool() ? "true" : "false" );
            break;

        default:
            out() << "WTF?";
        }

        out() << " );\n";
    }

    switch( obj->type() )
    {
    case HACO_Action:
        if( obj->hasProperty( QLatin1String( "_ConnectTo" ), HICP_String ) )
        {
            HICProperty p = obj->getProperty( QLatin1String( "_ConnectTo" ) );

            QString slot = p.value().toString();
            const char* signal = "triggered()";
            if( slot.contains( QLatin1String( "(bool)" ) ) )
            {
                signal = "toggled(bool)";
            }

            QByteArray receiver = "parent";
            if( obj->hasProperty( QLatin1String( "_ConnectContext" ), HICP_String ) )
            {
                HICProperty p2 = obj->getProperty( QLatin1String( "_ConnectContext" ) );
                receiver = p2.value().toString().toLocal8Bit();
            }

            out() << whitespace << "QObject::connect( " << prefix << obj->name() << ", SIGNAL(" << signal
                  << "), " << receiver << ", SLOT(" << slot << ") );\n";
        }
        break;

    default:
        break;
    }

}

bool HIGenSource::run()
{
    out() << "/**********************************************************************************\n"
             "*\n"
             "* This file is generated by HIC, the Heaven Interface Compiler\n"
             "*\n"
             "* Any modifications will be lost on the next gererator run. You've been warned.\n"
             "*\n"
             "* " << QDateTime::currentDateTime().toString( Qt::ISODate ) << "\n"
             "*\n"
             "**********************************************************************************/\n"
             "\n"
             "#include <QApplication>\n"
             "#include <QObject>\n"
             "\n"
             "#include \"" << mBaseName << "\"\n\n";

    foreach( HICObject* uiObject, model().allObjects( HACO_Ui ) )
    {
        QString ctx;

        if( uiObject->hasProperty( QLatin1String( "TrContext" ), HICP_String ) )
        {
            ctx = uiObject->getProperty( QLatin1String( "TrContext" ) ).value().toString();
        }

        if( ctx.isEmpty() )
        {
            ctx = uiObject->name();
        }

        out() << "QString "<< uiObject->name() << "::" << "trUtf8( const char* sourceText )\n"
                 "{\n"
                 "\treturn QApplication::translate( \"" << latin1Encode( ctx ) << "\", sourceText, "
                    "NULL"
                    #if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
                    ", QCoreApplication::UnicodeUTF8"
                    #endif
                    " );\n"
                 "}\n"
                 "\n";

        out() << "void " << uiObject->name() << "::" << "setupActions( QObject* parent )\n"
                 "{\n"
                 "\t//Setup the actions\n\n";

        foreach( HICObject* actionObject, uiObject->content( HACO_Action ) )
        {
            out() << "\tact" << actionObject->name() << " = new Heaven::Action( parent );\n";
            writeSetProperties( actionObject, "\t", "act" );
            out() << "\n";
        }

        foreach( HICObject* actionObject, uiObject->content( HACO_WidgetAction ) )
        {
            out() << "\twac" << actionObject->name() << " = new Heaven::WidgetAction( parent );\n";
            writeSetProperties( actionObject, "\t", "wac" );
            out() << "\n";
        }

        out() << "\t//Setup Mergeplaces\n\n";
        foreach( HICObject* mpObject, uiObject->content( HACO_MergePlace ) )
        {
            out() << "\tmp" << mpObject->name() << " = new Heaven::MergePlace( parent );\n"
                     "\tmp" << mpObject->name() << "->setName( QByteArray( \"" <<
                     latin1Encode( mpObject->name() ) << "\" ) );\n";
            writeSetProperties( mpObject, "\t", "mp" );
            out() << "\n";
        }

        out() << "\t//Setup containers\n\n";
        foreach( HICObject* menuObject, uiObject->content( HACO_Menu ) )
        {
            out() << "\tmenu" << menuObject->name() << " = new Heaven::Menu( parent );\n";
            writeSetProperties( menuObject, "\t", "menu" );
            out() << "\n";
        }
        foreach( HICObject* menuObject, uiObject->content( HACO_MenuBar ) )
        {
            out() << "\tmb" << menuObject->name() << " = new Heaven::MenuBar( parent );\n";
            writeSetProperties( menuObject, "\t", "mb" );
            out() << "\n";
        }
        foreach( HICObject* menuObject, uiObject->content( HACO_ToolBar ) )
        {
            out() << "\ttb" << menuObject->name() << " = new Heaven::ToolBar( parent );\n";
            writeSetProperties( menuObject, "\t", "tb" );
            out() << "\n";
        }
        foreach( HICObject* menuObject, uiObject->content( HACO_Container ) )
        {
            out() << "\tac" << menuObject->name() << " = new Heaven::ActionContainer( parent );\n";
            writeSetProperties( menuObject, "\t", "ac" );
            out() << "\n";
        }

        out() << "\t//Give containers some content\n\n";

        foreach( HICObject* object, uiObject->content() )
        {
            const char* prefix = "";
            switch( object->type() )
            {
            case HACO_Invalid:
            case HACO_Action:
            case HACO_MergePlace:
            case HACO_Ui:
            case HACO_Separator:
            case HACO_WidgetAction:
                continue;

            case HACO_Menu:
                prefix = "\tmenu";
                break;

            case HACO_MenuBar:
                prefix = "\tmb";
                break;

            case HACO_ToolBar:
                prefix = "\ttb";
                break;

            case HACO_Container:
                prefix = "\tac";
                break;
            }

            foreach( HICObject* child, object->content() )
            {
                switch( child->type() )
                {
                case HACO_Separator:
                    out() << prefix << object->name() << "->addSeparator();\n";
                    break;

                case HACO_Action:
                    out() << prefix << object->name() << "->add( act" << child->name() << " );\n";
                    break;

                case HACO_WidgetAction:
                    out() << prefix << object->name() << "->add( wac" << child->name() << " );\n";
                    break;

                case HACO_Container:
                    out() << prefix << object->name() << "->add( ac" << child->name() << " );\n";
                    break;

                case HACO_MergePlace:
                    out() << prefix << object->name() << "->add( mp" << child->name() << " );\n";
                    break;

                case HACO_Menu:
                    out() << prefix << object->name() << "->add( menu" << child->name() << " );\n";
                    break;

                default:
                    out() << "\t\tWTF?";
                }
            }

            out() << "\n";
        }

        out() << "}\n\n";
    }

    return true;
}
