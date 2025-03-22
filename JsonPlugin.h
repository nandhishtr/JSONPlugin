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


#ifndef TESTPLUGIN1_H
#define TESTPLUGIN1_H
#include <QWidget>
#include <QLabel>
#include "PluginServices.h"
#include "CubePlugin.h"
#include "TabInterface.h"

namespace jsonvisualizerplugin
{
class JSONPlugin : public QObject, public cubepluginapi::CubePlugin, cubepluginapi::TabInterface
{
    Q_OBJECT
    Q_INTERFACES( cubepluginapi::CubePlugin )
    Q_PLUGIN_METADATA( IID "JSONPluginPlugin" ) // unique plugin name

public:
    JSONPlugin();

    // CubePlugin implementation
    virtual bool
    cubeOpened( cubepluginapi::PluginServices* service );
    virtual void
    cubeClosed();
    virtual QString
    name() const;
    virtual void
    version( int& major,
             int& minor,
             int& bugfix ) const;
    virtual QString
    getHelpText() const;

    // TabInterface implementation
    virtual QString
    label() const;
    virtual QWidget*
    widget();

private slots:
    void
    treeItemIsSelected( cubepluginapi::TreeItem* item );

private:
    QWidget*                       widget_;
    QLabel*                        qlabel_;
    cubepluginapi::PluginServices* service;
    QJsonObject getJSONData(cubepluginapi::TreeItem* item);

    // TabInterface interface
};
}

#endif // TESTPLUGIN1_H
