#pragma once

#include <QSGGeometryNode>
#include <QQuickItem>

struct Coefficients
{
    qreal x;
    qreal y;
    qreal w;
    qreal h;
    qreal tx;
    qreal ty;
    qreal tw;
    qreal th;
};

class ImageGeometryNode : public QSGGeometryNode
{
public:
    ImageGeometryNode(QQuickItem* item);

protected:
    void initGeometry();
    void initMaterial();

    void initVertexData();

    QQuickItem* m_item;
};
