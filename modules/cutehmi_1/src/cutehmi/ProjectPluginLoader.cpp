#include "../../include/cutehmi/ProjectPluginLoader.hpp"
#include "../../include/cutehmi/IProjectPlugin.hpp"
#include "../../include/cutehmi/internal/PluginNodeData.hpp"
#include "../../include/cutehmi/internal/PluginLoader.hpp"

#include <QObject>

namespace cutehmi {

ProjectPluginLoader::ProjectPluginLoader(internal::PluginLoader * pluginLoader):
	m(new Members{pluginLoader})
{
}

ProjectNode * ProjectPluginLoader::addPluginNode(const QString & name, int reqMinor, ProjectNode & parentNode) const noexcept(false)
{
	QString binary(Plugin::NameToBinary(name));

	Plugin * plugin = (m->pluginLoader->loadPlugin(binary, reqMinor));	// Note: loadPlugin() may throw exception.
	IProjectPlugin * pluginInstance = qobject_cast<IProjectPlugin *>(plugin->instance());
	if (pluginInstance == 0)
		throw MissingInterfaceException(binary, plugin->version(), CUTEHMI_IPROJECTPLUGIN_IID);
	ProjectNode * pluginNode;
	if (!plugin->name().isEmpty())
        pluginNode = parentNode.appendChild(plugin->name(), ProjectNodeData(plugin->friendlyName()), false);
	else
        pluginNode = parentNode.appendChild(ProjectNodeData(plugin->friendlyName()), false);
	pluginNode->data().append(std::unique_ptr<DataBlock>(new internal::PluginNodeData(plugin, reqMinor)));
    pluginNode->registerExtension(plugin);
	pluginInstance->init(*pluginNode);
	return pluginNode;
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
