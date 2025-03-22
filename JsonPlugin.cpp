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
    QString txt = item->getName() + " " + QString::number( item->getValue() );
    qlabel_->setText( txt );
    auto systemTreeItem = service->getSystemTreeItem(0);
    // QString txt2 = systemTreeItem->getLabel(); //both give same thing
    // QString txt3 = systemTreeItem->getName();
    // auto txt4 = systemTreeItem->getAbsoluteValue();
    // QString valueAsString = QString::number(txt4);
    // auto test = systemTreeItem->getValueObject();
    // auto qv = systemTreeItem->convertToQVariant();
    // QJsonValue::fromVariant(qv);
    // auto yes = systemTreeItem->isTopLevelItem();
    // if (yes){
    // }

    QString outputString = "";

    auto yes = systemTreeItem->getChildren();
    auto depth = systemTreeItem->getDepth();
    outputString = QString::number(depth) + " " + QString::number(systemTreeItem->getValue()) + systemTreeItem->getName();
    for (auto item : yes)
    {
        outputString += "\n";
        outputString +=  QString::number(item->getValue()) + " " + item->getName() + " ";
        outputString += "is leaf: " + QString::number(item->isLeaf()) + "\n\t";
        auto finalchildren = item->getChildren();
        for (auto child: finalchildren) {
            outputString += QString::number(child->getValue()) + " " + child->getName() + " ";
            outputString += "is leaf: " + QString::number(child->isLeaf()) + "\n\t";
        }
    }
    qlabel_->setText(outputString);


}
