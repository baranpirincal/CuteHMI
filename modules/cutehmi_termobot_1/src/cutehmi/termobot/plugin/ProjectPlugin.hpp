#ifndef TERM_PROJEG
#define TERM_PROJEG

#include "../../../../cutehmi.metadata.hpp"

#include <cutehmi/xml/IBackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>
#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

namespace cutehmi {
namespace termobot {
namespace plugin {

class ProjectPlugin : public QObject,
                      public IProjectPlugin,
                      public xml::IBackendPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
  Q_INTERFACES(cutehmi::IProjectPlugin)

public:
  // IProjectPlugin
  void init(ProjectNode &node) override;

  // xml::IBackendPlugin
  void readXML(QXmlStreamReader &xmlReader, ProjectNode &node); // override;

  // xml::IBackendPlugin
  void writeXML(QXmlStreamWriter &xmlWriter, ProjectNode &node) const
      noexcept(false); // override;

private:
  void parseTermobot(const xml::ParseHelper &parentHelper, ProjectNode &node, const QString &name);
  void parsePostgres(const xml::ParseHelper &parentHelper);
};

} // namespace plugin
} // namespace termobot
} // namespace cutehmi

#endif
