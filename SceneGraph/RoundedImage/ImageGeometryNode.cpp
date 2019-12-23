#include "ImageGeometryNode.h"

#include <QSGGeometry>
#include <QSGOpaqueTextureMaterial>
#include <QQuickWindow>
#include <QtMath>

ImageGeometryNode::ImageGeometryNode(QQuickItem* item)
    : m_item(item)
{
    initGeometry();
    initMaterial();
    initVertexData();
}

void ImageGeometryNode::initGeometry()
{
    int segmentCount = 360;

    auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), segmentCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);
}

void ImageGeometryNode::initMaterial()
{
    QImage image(":/dog.jpg");
    if(image.isNull())
    {
        qDebug() << "Could not read image";
    }

    QQuickWindow* window = m_item->window();
    auto texture = window->createTextureFromImage(image);

    auto material = new QSGOpaqueTextureMaterial();
    material->setTexture(texture);
    material->setFiltering(QSGTexture::Linear);
    material->setMipmapFiltering(QSGTexture::Linear);
    setMaterial(material);

    setFlag(QSGNode::OwnsOpaqueMaterial);
}

void ImageGeometryNode::initVertexData()
{
   QSGGeometry::TexturedPoint2D *vertices = geometry()->vertexDataAsTexturedPoint2D();
   int vertexCount = geometry()->vertexCount();

   double xRadius = m_item->width() / 2;
   double yRadius = m_item->height() / 2;

   // circle should be drawn at 0,0 of quickitem instead at the center
   double xOffset = xRadius;
   double yOffset = yRadius;

   float tWMultiplier = 1 / m_item->width();
   float tHMultiplier = 1 / m_item->height();

   for(int degree = 0; degree < vertexCount; degree++)
   {
       double rad = M_PI / 180 * degree;
       float x = xOffset + xRadius * cos(rad);
       float y = yOffset + yRadius * sin(rad);

       vertices[degree].set(x, y, x * tWMultiplier, y * tHMultiplier);
   }
}
