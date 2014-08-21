// This file is automatically generated, please don't edit manually.
import QtQuick 2.1
import Deepin.Widgets 1.0
import "../edit"

BaseEditSection { 
    id: sectionVpnOpenvpnAdvanced
    virtualSection: "vs-vpn-openvpn-advanced"
    
    header.sourceComponent: EditDownArrowHeader{
        text: dsTr("VPN Advanced")
    }

    content.sourceComponent: Column { 
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedVkEnablePort
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "vk-enable-port"
            text: dsTr("Customize Gateway Port")
        }
        EditLineSpinner {
            id: lineAliasVpnOpenvpnAdvancedPort
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "port"
            text: dsTr("Gateway Port")
            max: 65535
            min: 0
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedVkEnableRenegSeconds
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "vk-enable-reneg-seconds"
            text: dsTr("Customize Renegotiation Interval")
        }
        EditLineSpinner {
            id: lineAliasVpnOpenvpnAdvancedRenegSeconds
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "reneg-seconds"
            text: dsTr("Renegotiation Interval")
            max: 604800
            min: 0
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedCompLzo
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "comp-lzo"
            text: dsTr("Use LZO data compression")
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedProtoTcp
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "proto-tcp"
            text: dsTr("Use TCP connection")
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedTapDev
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "tap-dev"
            text: dsTr("Use TAP device")
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedVkEnableTunnelMtu
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "vk-enable-tunnel-mtu"
            text: dsTr("Customize Tunnel MTU")
        }
        EditLineSpinner {
            id: lineAliasVpnOpenvpnAdvancedTunnelMtu
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "tunnel-mtu"
            text: dsTr("MTU")
            max: 65535
            min: 0
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedVkEnableFragmentSize
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "vk-enable-fragment-size"
            text: dsTr("Customize UDP Fragment Size")
        }
        EditLineSpinner {
            id: lineAliasVpnOpenvpnAdvancedFragmentSize
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "fragment-size"
            text: dsTr("UDP Fragment Size")
            max: 65535
            min: 0
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedMssfix
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "mssfix"
            text: dsTr("Restrict Tunnel TCP MSS")
        }
        EditLineSwitchButton {
            id: lineAliasVpnOpenvpnAdvancedRemoteRandom
            connectionSession: sectionVpnOpenvpnAdvanced.connectionSession
            availableSections: sectionVpnOpenvpnAdvanced.availableSections
            availableKeys: sectionVpnOpenvpnAdvanced.availableKeys
            errors: sectionVpnOpenvpnAdvanced.errors
            section: "alias-vpn-openvpn-advanced"
            key: "remote-random"
            text: dsTr("Randomize Remote Hosts")
        }
    }
}
