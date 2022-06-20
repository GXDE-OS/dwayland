/********************************************************************
Copyright 2022  diguoliang <diguoliang@uniontech.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
#pragma once

#include <QObject>
#include <QPointer>
#include <QString>
#include <QMap>

#include <DWayland/Client/kwaylandclient_export.h>

struct wl_surface;
struct dde_globalproperty;

namespace KWayland
{

namespace Client
{

class EventQueue;
class Surface;

class KWAYLANDCLIENT_EXPORT GlobalProperty : public QObject
{
    Q_OBJECT
public:
    explicit GlobalProperty(QObject *parent = nullptr);
    virtual ~GlobalProperty();

    /**
     * Setup this Compositor to manage the @p GlobalProperty.
     * When using Registry::createGlobalProperty there is no need to call this
     * method.
     **/
    void setup(dde_globalproperty *ddeglobalproperty);

    bool isValid() const;

    operator dde_globalproperty*();
    operator dde_globalproperty*() const;
    dde_globalproperty *ddeGlobalProperty();

    /**
     * Sets the @p queue to use for bound proxies.
     **/
    void setEventQueue(EventQueue *queue);
    /**
     * @returns The event queue to use for bound proxies.
     **/
    EventQueue *eventQueue() const;

    void setProperty(const QString &module, const QString &function, wl_surface *surface, const int32_t &type, const QString &data);
    void setProperty(const QString &module, const QString &function, Surface *surface, const int32_t &type, const QString &data);
    QString getProperty(const QString &module, const QString &function);

    /**
    * Destroys the data hold by this GlobalProperty.
    * This method is supposed to be used when the connection to the Wayland
    * server goes away. If the connection is not valid any more, it's not
    * possible to call release any more as that calls into the Wayland
    * connection and the call would fail.
    *
    * This method is automatically invoked when the Registry which created this
    * GlobalProperty gets destroyed.
    **/
    void destroy();

Q_SIGNALS:
    /**
     * This signal is emitted right before the interface is released.
     **/
    void interfaceAboutToBeReleased();
    /**
     * This signal is emitted right before the data is destroyed.
     **/
    void interfaceAboutToBeDestroyed();

    /**
     * The corresponding global for this interface on the Registry got removed.
     *
     * This signal gets only emitted if the GlobalProperty got created by
     * Registry::createGlobalProperty
     *
     * @since 5.5
     **/
    void removed();

private:
    class Private;
    QScopedPointer<Private> d;
};

}

}
