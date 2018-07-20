//#include "../../../../include/cutehmi/termobot/Service.hpp"
#include "../../../../include/cutehmi/termobot/internal/common.hpp"

//#include <cutehmi/services/ServiceRegistry.hpp>

#include <cutehmi/Exception.hpp>

#include "PluginNodeData.hpp"
#include "ProjectPlugin.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

void ProjectPlugin::init(ProjectNode &node) {
    std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
    node.registerExtension(pluginNodeData->xmlBackendPlugin());
    node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader &xmlReader, ProjectNode &node) {
  CUTEHMI_LOG_DEBUG("Plugin " CUTEHMI_TERMOBOT_NAME " starts parsing its own "
                    "portion of document...");

  QStringList supportedVersions;
  supportedVersions
      << "http://michpolicht.github.io/CuteHMI/cutehmi_termobot_1/xsd/1.0/";

  xml::ParseHelper helper(&xmlReader, supportedVersions);
  helper << xml::ParseElement("cutehmi_termobot_1", 1, 1);

    while (helper.readNextRecognizedElement()) {
      if (xmlReader.name() == "cutehmi_termobot_1") {
        xml::ParseHelper nodeHelper(&helper);
        nodeHelper << xml::ParseElement(
            "termobot", {xml::ParseAttribute("id"),
            xml::ParseAttribute("name")}, 0);
        while (nodeHelper.readNextRecognizedElement()) {
          if (xmlReader.name() == "termobot")
            parseTermobot(nodeHelper, node,
                          xmlReader.attributes().value("id").toString());
        }
      }
    }
}

void ProjectPlugin::writeXML(QXmlStreamWriter &xmlWriter,
                             ProjectNode &node) const noexcept(false) {
  Q_UNUSED(xmlWriter);
  Q_UNUSED(node);
  throw Exception(
      "cutehmi::termobot::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseTermobot(const xml::ParseHelper &parentHelper,
                                  ProjectNode &node, const QString &name) {
    xml::ParseHelper helper(&parentHelper);
    helper << xml::ParseElement("client", 1, 1);

//    std::unique_ptr<Service> service;
    //  std::unique_ptr<DatabaseConnectionData> dbData;

    const QXmlStreamReader &xmlReader = helper.xmlReader();
    while (helper.readNextRecognizedElement()) {
      if (xmlReader.name() == "client") {
        xml::ParseHelper clientHelper(&helper);
        clientHelper << xml::ParseElement(
            "session", {xml::ParseAttribute("type", "SQL")}, 1, 1);

        while (clientHelper.readNextRecognizedElement()) {
          if (xmlReader.name() == "session") {
            xml::ParseHelper sessionHelper(&clientHelper);
            sessionHelper << xml::ParseElement(
                "dbms", {xml::ParseAttribute("name", "PostgreSQL")}, 1, 1);
            while (sessionHelper.readNextRecognizedElement()) {
              if (xmlReader.name() == "dbms") {
                  parsePostgres(sessionHelper);
              }
            }
          }
        }
      }
    }
}

void ProjectPlugin::parsePostgres(const xml::ParseHelper &parentHelper) {
    xml::ParseHelper helper(&parentHelper);
    helper << xml::ParseElement("postgresql", 1, 1);

    const QXmlStreamReader & xmlReader = helper.xmlReader();
    while (helper.readNextRecognizedElement()) {
        if (xmlReader.name() == "postgresql") {
            xml::ParseHelper postgresqlHelper(&helper);
            postgresqlHelper << xml::ParseElement("host", 1, 1)
                             << xml::ParseElement("port", 1, 1)
                             << xml::ParseElement("name", 1, 1)
                             << xml::ParseElement("user", 1, 1)
                             << xml::ParseElement("password", 1, 1);

            while (postgresqlHelper.readNextRecognizedElement()) {
                if (xmlReader.name() == "host")
                    CUTEHMI_LOG_DEBUG("host: '" + helper.readElementText() + "'");
                else if (xmlReader.name() == "port")
                    CUTEHMI_LOG_DEBUG("port: '" + helper.readElementText() + "'");
                else if (xmlReader.name() == "name")
                    CUTEHMI_LOG_DEBUG("name: '" + helper.readElementText() + "'");
                else if (xmlReader.name() == "user")
                    CUTEHMI_LOG_DEBUG("user: '" + helper.readElementText() + "'");
                else if (xmlReader.name() == "password")
                    CUTEHMI_LOG_DEBUG("password: '" + helper.readElementText() + "'");
            }
        }
    }
}

} // namespace plugin
} // namespace termobot
} // namespace cutehmi
