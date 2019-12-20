#pragma once

#include <QSGGeometryNode>

class MyItemGeometry : public QSGGeometryNode
{
public:
    MyItemGeometry();

protected:
    QSGGeometry m_geometry;
};
