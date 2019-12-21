#include "MyItemGeometry.h"
#include "MyItemShader.h"

#include <QSGSimpleMaterial>

MyItemGeometry::MyItemGeometry()
    : m_geometry(QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4))
{
    setGeometry(&m_geometry);

    auto material = MyItemShader::createMaterial();
    material->setFlag(QSGMaterial::Blending);
    setMaterial(material);

    setFlags(OwnsMaterial | OwnsGeometry);
}
