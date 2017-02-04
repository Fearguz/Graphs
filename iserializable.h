#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <string>

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Graphs
{

class IXmlSerializable
{
public:
    virtual std::string serialize() const = 0;
    virtual void fromXml(std::string const& xml) = 0;
};

}

#endif // ISERIALIZABLE_H
