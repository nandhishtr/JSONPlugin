/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#include <QVBoxLayout>
#include <QtPlugin>
#include "JsonPlugin.h"
#include "PluginServices.h"

/**
 * If the plugin doesn't load, start cube with -verbose to get detailed information.
 * If the error message "Plugin verification data mismatch" is printed, check if the
 * same compiler and Qt version have been used.
 */

using namespace cubepluginapi;
using namespace jsonvisualizerplugin;

JSONPlugin::JSONPlugin()
{
    // The constructor should be empty, use cubeOpened to initialize. If Qt widgets or
    // signals/slots are used in constructor, they have to be deleted in destructor,
    // otherwise cube may crash if the plugin is unloaded.
}

bool
JSONPlugin::cubeOpened( PluginServices* service )
{
    this->service = service;

    widget_ = new QWidget();
    qlabel_ = new QLabel( "Testing JSON Plugin" );
    QVBoxLayout* layout = new QVBoxLayout();
    widget_->setLayout( layout );
    layout->addWidget( qlabel_ );

    service->addTab( SYSTEM, this );

    connect( service, SIGNAL( treeItemIsSelected( cubepluginapi::TreeItem* ) ),
             this, SLOT( treeItemIsSelected( cubepluginapi::TreeItem* ) ) );
    return true; // initialisation is ok => plugin should be shown
}

void
JSONPlugin::cubeClosed()
{
    delete widget_;
}

/** set a version number, the plugin with the highest version number will be loaded */
void
JSONPlugin::version( int& major, int& minor, int& bugfix ) const
{
    major  = 1;
    minor  = 0;
    bugfix = 0;
}

/** unique plugin name */
QString
JSONPlugin::name() const
{
    return "JSON Visualizer";
}

QString
JSONPlugin::getHelpText() const
{
    return "Just a simple JSON Visualizer.";
}

/** widget that will be placed into the tab */
QWidget*
JSONPlugin::widget()
{
    return widget_;
}

/** tab label */
QString
JSONPlugin::label() const
{
    return "JSON Plugin";
}

/** slot, which is called if a tree item is selected */
void
JSONPlugin::treeItemIsSelected( TreeItem* item )
{
    auto systemTreeItem = service->getSystemTreeItem(0);

    QString outputString = "";
    outputString = getData(systemTreeItem, outputString);
    qlabel_->setText(outputString);
}

QString JSONPlugin::getData(cubegui::TreeItem *item, QString &outputString)
{
    outputString += QString::number(item->getValue()) + " " + item->getName() + "\n\t";

    if (!item->isLeaf())
    {
        for (auto child : item->getChildren())
        {
            getData(child, outputString);
        }
    }

    return outputString;
}
