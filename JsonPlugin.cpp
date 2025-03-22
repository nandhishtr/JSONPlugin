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
#include <QScrollArea>

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

    //container widget
    QWidget* container = new QWidget();

    //layout for the inner container
    QVBoxLayout* layout = new QVBoxLayout(container);

    qlabel_ = new QLabel("JSON Plugin to display system tree data in JSON format");

    layout->addWidget(qlabel_);

    //make the container widget scrollable
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //main widget
    widget_ = new QWidget();

    //layout for main widget
    QVBoxLayout* mainLayout = new QVBoxLayout(widget_);
    mainLayout->addWidget(scrollArea);

    service->addTab(SYSTEM, this);

    connect(service, SIGNAL(treeItemIsSelected(cubepluginapi::TreeItem*)),
            this, SLOT(treeItemIsSelected(cubepluginapi::TreeItem*)));

    return true; // initialization is OK => plugin should be shown
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
    return "JSON Plugin to display system tree data in JSON format. It visualizes the tree with names and values";
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
    QJsonObject systemTreeJson = getJSONData(systemTreeItem);
    QJsonDocument document(systemTreeJson);
    QString outputString = document.toJson(QJsonDocument::Indented);
    qlabel_->setText(outputString);
}

/** returs json object created form tree data*/
QJsonObject
JSONPlugin::getJSONData(cubegui::TreeItem *item)
{
    QJsonObject jsonObject;

    //populate json object with tree object name and value
    jsonObject["value"] = item->getValue();
    jsonObject["name"] = item->getName();
    if (!item->isLeaf())
    {
        QJsonArray childJsonObjects;
        for (auto child : item->getChildren())
        {
            childJsonObjects.append(getJSONData(child));
        }
        jsonObject["children"] = childJsonObjects;
    }
    return jsonObject;
}

