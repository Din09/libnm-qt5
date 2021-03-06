/*
Copyright 2008,2010 Will Stephenson <wstephenson@kde.org>

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

#ifndef NMQT_NETWORKMANAGER_P_H
#define NMQT_NETWORKMANAGER_P_H

#include <QDBusServiceWatcher>
#include <QMap>

#include "dbus/nm-managerinterface.h"
#include "device.h"
#include "activeconnection.h"

#include "manager.h"

namespace NetworkManager {

class Device;
class ActiveConnection;

class NetworkManagerPrivate : public NetworkManager::Notifier
{
    Q_OBJECT
public:
    static const QString DBUS_SERVICE;
    static const QString DBUS_DAEMON_PATH;
    static const QString DBUS_SETTINGS_PATH;

    NetworkManagerPrivate();
    ~NetworkManagerPrivate();
    QDBusServiceWatcher watcher;
    OrgFreedesktopNetworkManagerInterface iface;
    uint nmState;
    bool m_isWirelessEnabled;
    bool m_isWirelessHardwareEnabled;
    bool m_isWwanEnabled;
    bool m_isWwanHardwareEnabled;
    bool m_isWimaxEnabled;
    bool m_isWimaxHardwareEnabled;
    QString m_version;

    // to store NetworkManager's version.
    int m_x;
    int m_y;
    int m_z;
    void parseVersion(const QString &version);
    int compareVersion(const QString &version);
    int compareVersion(const int x, const int y, const int z) const;

    bool m_isNetworkingEnabled;
    QMap<QString, ActiveConnection::Ptr> m_activeConnections;
    ActiveConnection::Ptr findRegisteredActiveConnection(const QString &);
    // manage device children
    Device::Ptr findRegisteredNetworkInterface(const QString &uni);
    Device::Ptr createNetworkInterface(const QString &uni);
    QMap<QString, Device::Ptr> networkInterfaceMap;
    // for frontend to call
    QString version() const;
    NetworkManager::Status status() const;
    Device::List networkInterfaces();
    Device::Ptr findNetworkInterface(const QString &uni);
    Device::Ptr findDeviceByIpIface(const QString &iface);
    bool isNetworkingEnabled() const;
    bool isWirelessEnabled() const;
    bool isWirelessHardwareEnabled() const;
    bool isWwanEnabled() const;
    bool isWwanHardwareEnabled() const;
    bool isWimaxEnabled() const;
    bool isWimaxHardwareEnabled() const;
    QDBusPendingReply<QDBusObjectPath> activateConnection(const QString &connectionUni, const QString &interfaceUni, const QString &connectionParameter);
    QDBusPendingReply<QDBusObjectPath, QDBusObjectPath> addAndActivateConnection(const NMVariantMapMap &connection, const QString &interfaceUni, const QString &connectionParameter);
    void deactivateConnection(const QString &activeConnection);
    ActiveConnection::List activeConnections();
    QStringList activeConnectionsPaths() const;
    QDBusPendingReply<QString, QString> getLogging();
    Device::Types supportedInterfaceTypes() const;
    void setNetworkingEnabled(bool enabled);
    void setWirelessEnabled(bool enabled);
    void setWwanEnabled(bool enabled);
    void setWimaxEnabled(bool enabled);
    void sleep(bool sleep);
    void setLogging(NetworkManager::LogLevel, NetworkManager::LogDomains);
    NMStringMap permissions();
protected Q_SLOTS:
    void init();
    void onDeviceAdded(const QDBusObjectPath &state);
    void onDeviceRemoved(const QDBusObjectPath &state);
    void propertiesChanged(const QVariantMap &changedProperties);
    void daemonRegistered();
    void daemonUnregistered();
private:
    void stateChanged(uint state);
    static NetworkManager::Status convertNMState(uint state);

};
}
#endif

