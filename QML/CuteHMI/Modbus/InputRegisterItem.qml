import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

Item
{
	id: root

	implicitWidth: 50.0
	implicitHeight: 50.0

	property var delegate: parent
	property alias device: inputRegisterController.device
	property alias address: inputRegisterController.address
	property alias encoding: inputRegisterController.encoding
	property alias valueScale: inputRegisterController.valueScale
	property alias busy: inputRegisterController.busy
	property alias value: inputRegisterController.value
	property alias controller: inputRegisterController

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: inputRegisterController.busy
	}

	InputRegisterController
	{
		id: inputRegisterController
	}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.