#include "RectGeometryNode.h"

RectMaterialShader::RectMaterialShader()
{}

void RectMaterialShader::updateState(const RectMaterialState *newState, const RectMaterialState *oldState)
{
    Q_UNUSED(oldState)
    program()->setUniformValue(m_uniformLocation.m_color, newState->m_color);
    program()->setUniformValue(m_uniformLocation.m_alternateColor, newState->m_alternateColor);
}

QList<QByteArray> RectMaterialShader::attributes() const
{
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void RectMaterialShader::resolveUniforms()
{
    m_uniformLocation.m_color = program()->uniformLocation("uColor");
    m_uniformLocation.m_alternateColor = program()->uniformLocation("uAlternateColor");
}

const char *RectMaterialShader::vertexShader() const
{
    return
        "attribute vec4 aVertex;                    \n"
        "attribute vec2 aTexCoord;                  \n"
        "uniform mat4 qt_Matrix;                    \n"
        "varying vec2 vTexCoord;                    \n"
        "void main()                                \n"
        "{                                          \n"
        "   gl_Position = qt_Matrix * aVertex;      \n"
        "   vTexCoord = aTexCoord;                  \n"
        "}                                          \0";

}

const char *RectMaterialShader::fragmentShader() const
{
    return
        "uniform lowp float qt_Opacity;                                                                 \n"
        "varying vec2 vTexCoord;                                                                        \n"
        "uniform vec4 uColor;                                                                           \n"
        "uniform vec4 uAlternateColor;                                                                  \n"
        "void main()                                                                                    \n"
        "{                                                                                              \n"
        "   gl_FragColor = qt_Opacity * (uColor * (1.0f - vTexCoord.y) + uAlternateColor * vTexCoord.y); \n"
        "}                                                                                              \0";
}

RectGeometryNode::RectGeometryNode()
{
    auto* rectGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4);
    setGeometry(rectGeometry);

    auto* rectMaterial = RectMaterialShader::createMaterial();
    rectMaterial->setFlag(QSGMaterial::Blending);
    setMaterial(rectMaterial);

    setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial | QSGNode::OwnedByParent);
}
