import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_termobot_1"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "TermoBOT"

	description: "Settings for TermoBOT interface module."

	author: "Wojciech Zygmuntowicz"

	copyright: "Wojciech Zygmuntowicz"

	license: "Mozzarella Public License, v. alpha"

    files: [
        "include/cutehmi/termobot/ContactsModel.hpp",
        "include/cutehmi/termobot/internal/common.hpp",
        "include/cutehmi/termobot/logging.hpp",
        "include/cutehmi/termobot/metadata.hpp",
        "src/cutehmi/termobot/ContactsModel.cpp",
        "src/cutehmi/termobot/DatabaseConnectionData.hpp",
        "src/cutehmi/termobot/DatabaseThread.cpp",
        "src/cutehmi/termobot/DatabaseThread.hpp",
        "src/cutehmi/termobot/Service.cpp",
        "src/cutehmi/termobot/Service.hpp",
        "src/cutehmi/termobot/logging.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.hpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.cpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.hpp",
        "src/cutehmi/termobot/plugin/TermobotNodeData.cpp",
        "src/cutehmi/termobot/plugin/TermobotNodeData.hpp",
    ]

    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.sql" }

    Depends { name: "cutehmi.libpq" }

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

    Depends { name: "cutehmi_xml_1" }
    cutehmi_xml_1.reqMinor: 0

    Depends { name: "cutehmi_services_1" }
    cutehmi_services_1.reqMinor: 0
}
