#include "networkmodel.h"
#include "networkdevice.h"
#include "wirelessdevice.h"
#include "wireddevice.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

using namespace dcc::network;

NetworkDevice::DeviceType parseDeviceType(const QString &type)
{
    if (type == "wireless") {
        return NetworkDevice::Wireless;
    }
    if (type == "wired") {
        return NetworkDevice::Wired;
    }

    return NetworkDevice::None;
}

NetworkModel::NetworkModel(QObject *parent)
    : QObject(parent),

      m_updateWiredInfoDelay(new QTimer(this))
{
    m_updateWiredInfoDelay->setSingleShot(true);
    m_updateWiredInfoDelay->setInterval(100);

    connect(m_updateWiredInfoDelay, &QTimer::timeout, this, &NetworkModel::updateWiredConnInfo);
}

NetworkModel::~NetworkModel()
{
    qDeleteAll(m_devices);
}

const QString NetworkModel::connectionUuidByPath(const QString &connPath) const
{
    for (const auto &list : m_connections)
    {
        for (const auto &cfg : list)
        {
            if (cfg.value("Path").toString() == connPath)
                return cfg.value("Uuid").toString();
        }
    }

    return QString();
}

const QString NetworkModel::connectionUuidByApInfo(const QString &hwAddr, const QString &ssid) const
{
    for (const auto &list : m_connections)
    {
        for (const auto &cfg : list)
        {
            if (cfg.value("HwAddress").toString() == hwAddr && cfg.value("Ssid").toString() == ssid)
                return cfg.value("Uuid").toString();
        }
    }

    return QString();
}

void NetworkModel::onVPNEnabledChanged(const bool enabled)
{
    if (m_vpnEnabled != enabled)
    {
        m_vpnEnabled = enabled;

        emit vpnEnabledChanged(m_vpnEnabled);
    }
}

void NetworkModel::onProxiesChanged(const QString &type, const QString &url, const QString &port)
{
    const ProxyConfig config = { url, port };
    const ProxyConfig old = m_proxies[type];

    if (old.url != config.url || old.port != config.port)
    {
        m_proxies[type] = config;

        emit proxyChanged(type, config);
    }
}

void NetworkModel::onAutoProxyChanged(const QString &proxy)
{
    if (m_autoProxy != proxy)
    {
        m_autoProxy = proxy;

        emit autoProxyChanged(m_autoProxy);
    }
}

void NetworkModel::onProxyMethodChanged(const QString &proxyMethod)
{
    if (m_proxyMethod != proxyMethod)
    {
        m_proxyMethod = proxyMethod;

        emit proxyMethodChanged(m_proxyMethod);
    }
}

void NetworkModel::onProxyIgnoreHostsChanged(const QString &hosts)
{
    if (hosts != m_proxyIgnoreHosts)
    {
        m_proxyIgnoreHosts = hosts;

        emit proxyIgnoreHostsChanged(m_proxyIgnoreHosts);
    }
}

void NetworkModel::onDeviceListChanged(const QString &devices)
{
    const QJsonObject data = QJsonDocument::fromJson(devices.toUtf8()).object();

    QSet<QString> devSet;
    bool hasNewDevices = false;

    for (auto it(data.constBegin()); it != data.constEnd(); ++it) {
        const auto type = parseDeviceType(it.key());
        const auto list = it.value().toArray();

        if (type == NetworkDevice::None)
            continue;

        for (auto const &l : list)
        {
            const auto info = l.toObject();
            const QString path = info.value("Path").toString();

            devSet << path;

            NetworkDevice *d = device(path);
            if (!d)
            {
                switch (type)
                {
                case NetworkDevice::Wireless:   d = new WirelessDevice(info, this);      break;
                case NetworkDevice::Wired:      d = new WiredDevice(info, this);         break;
                default:;
                }
                m_devices.append(d);
                hasNewDevices = true;

                // init device enabled status
                emit requestDeviceStatus(d->path());
            } else {
                d->updateDeviceInfo(info);
            }
        }
    }

    // remove unexist device
    QList<NetworkDevice *> removeList;
    for (auto const d : m_devices)
    {
        if (!devSet.contains(d->path()))
            removeList << d;
    }

    for (auto const r : removeList)
        m_devices.removeOne(r);
    qDeleteAll(removeList);

    emit deviceListChanged(m_devices);

    if (hasNewDevices)
        m_updateWiredInfoDelay->start();
}

void NetworkModel::onConnectionListChanged(const QString &conns)
{
    const QJsonObject connsObject = QJsonDocument::fromJson(conns.toUtf8()).object();
    for (auto it(connsObject.constBegin()); it != connsObject.constEnd(); ++it)
    {
        const auto connList = it.value().toArray();
        m_connections[it.key()].clear();

        for (const auto &connObject : connList)
            m_connections[it.key()].append(connObject.toObject());
    }

    m_updateWiredInfoDelay->start();

    // update ppp connection info
//    for (auto *dev : m_devices)
//        if (dev->type() == NetworkDevice::Wired)
//            static_cast<WiredDevice *>(dev)->onPPPInfoChanged(m_connections["pppoe"]);

    emit connectionListChanged();
}

void NetworkModel::onActiveConnInfoChanged(const QString &conns)
{
    m_activeConnInfos.clear();

    QMap<QString, QString> activeConnInfo;

    QJsonArray activeConns = QJsonDocument::fromJson(conns.toUtf8()).array();
    for (const auto &info : activeConns)
    {
        const auto connInfo = info.toObject();

        activeConnInfo[connInfo.value("HwAddress").toString()] = connInfo.value("ConnectionName").toString();

        m_activeConnInfos.append(connInfo);
    }

    // update wireless device active ap name
    for (auto *dev : m_devices)
    {
        if (dev->type() != NetworkDevice::Wireless)
            continue;

        WirelessDevice *d = static_cast<WirelessDevice *>(dev);
        d->setActiveApName(activeConnInfo[d->hwAddr()]);
    }

    emit activeConnInfoChanged(m_activeConnInfos);
}

void NetworkModel::onActiveConnectionsChanged(const QString &conns)
{
    m_activeConnections.clear();

    const QJsonObject activeConns = QJsonDocument::fromJson(conns.toUtf8()).object();
    for (auto it(activeConns.constBegin()); it != activeConns.constEnd(); ++it)
    {
        const QJsonObject info = it.value().toObject();
        const auto uuid = info.value("Uuid").toString();
        if (!uuid.isEmpty())
            m_activeConnections << uuid;
    }

    emit activeConnectionsChanged(m_activeConnections);
}

void NetworkModel::onConnectionSessionCreated(const QString &device, const QString &sessionPath)
{
    for (const auto dev : m_devices)
    {
        if (dev->path() != device)
            continue;
        emit dev->sessionCreated(sessionPath);
        return;
    }

    emit unhandledConnectionSessionCreated(device, sessionPath);
}

void NetworkModel::onDeviceAPListChanged(const QString &device, const QString &apList)
{
    for (auto const dev : m_devices)
    {
        if (dev->type() != NetworkDevice::Wireless || dev->path() != device)
            continue;
        return static_cast<WirelessDevice *>(dev)->setAPList(apList);
    }
}

void NetworkModel::onDeviceAPInfoChanged(const QString &device, const QString &apInfo)
{
    for (auto const dev : m_devices)
    {
        if (dev->type() != NetworkDevice::Wireless || dev->path() != device)
            continue;
        return static_cast<WirelessDevice *>(dev)->updateAPInfo(apInfo);
    }
}

void NetworkModel::onDeviceAPRemoved(const QString &device, const QString &apInfo)
{
    for (auto const dev : m_devices)
    {
        if (dev->type() != NetworkDevice::Wireless || dev->path() != device)
            continue;
        return static_cast<WirelessDevice *>(dev)->deleteAP(apInfo);
    }
}


void NetworkModel::onDeviceEnableChanged(const QString &device, const bool enabled)
{
    NetworkDevice *dev = nullptr;
    for (auto const d : m_devices)
    {
        if (d->path() == device)
        {
            dev = d;
            break;
        }
    }

    if (!dev)
        return;

    dev->setEnabled(enabled);

    emit deviceEnableChanged(device, enabled);
}

bool NetworkModel::containsDevice(const QString &devPath) const
{
    return device(devPath) != nullptr;
}

NetworkDevice *NetworkModel::device(const QString &devPath) const
{
    for (auto const d : m_devices)
        if (d->path() == devPath)
            return d;

    return nullptr;
}

void NetworkModel::updateWiredConnInfo()
{
    Q_ASSERT(sender() == m_updateWiredInfoDelay);

    for (const auto &wired : m_connections["wired"])
    {
        const QString hwAddr = wired.value("HwAddress").toString();
        for (auto *dev : m_devices)
            if (dev->type() == NetworkDevice::Wired && dev->hwAddr() == hwAddr)
                static_cast<WiredDevice *>(dev)->onConnectionInfoChanged(wired);
    }
}
