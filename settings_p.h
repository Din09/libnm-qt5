/*
Copyright 2011 Ilia Kats <ilia-kats@gmx.net>

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
*/

#ifndef NMQT_SETTINGS_P_H
#define NMQT_SETTINGS_P_H

#include <QObject>
#include <QDBusObjectPath>

#include "dbus/nm-settingsinterface.h"
#include "settings.h"

class QDBusPendingCallWatcher;

namespace NetworkManager
{

class SettingsPrivate : public NetworkManager::SettingsNotifier
{
    Q_OBJECT
    friend class NetworkManagerPrivate;
public:
    SettingsPrivate();
    Connection::List listConnections();
    NetworkManager::Connection::Ptr findConnectionByUuid(const QString &uuid);
    QString hostname() const;
    bool canModify() const;
    QString addConnection(const NMVariantMapMap &);
    void saveHostname(const QString &);
    Connection::Ptr findRegisteredConnection(const QString &);

    QMap<QString, Connection::Ptr> connections;
    bool m_canModify;
    QString m_hostname;
    OrgFreedesktopNetworkManagerSettingsInterface iface;
protected Q_SLOTS:
    void onConnectionAdded(const QDBusObjectPath &);
    void onConnectionRemoved(const QString &);
    void propertiesChanged(const QVariantMap &properties);
    void onConnectionAddArrived(QDBusPendingCallWatcher *);
    void initNotifier();
protected:
    void daemonUnregistered();
    void init();
};

}


#endif
