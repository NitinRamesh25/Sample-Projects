#include "MyItemShader.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QDebug>


MyItemShader::MyItemShader()
{}

const char *MyItemShader::vertexShader() const
{
    return
        "attribute vec4 aVertex;"
        "attribute vec2 aTexCoord;"
        "uniform mat4 qt_Matrix;"
        "varying vec2 texCoord;"
        "void main()"
        "{"
        "    gl_Position = qt_Matrix * aVertex;"
        "    texCoord = aTexCoord;"
        "}";
}

const char *MyItemShader::fragmentShader() const
{
    return
        "uniform float qt_Opacity;"
        "uniform vec4 color;"
        "varying vec2 texCoord;"
        "void main ()"
        "{"
        "    gl_FragColor = texCoord.y * texCoord.x * color * qt_Opacity;"
        "}";
}

QList<QByteArray> MyItemShader::attributes() const
{
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void MyItemShader::resolveUniforms()
{
    m_colorLocation = program()->uniformLocation("color");
}

void MyItemShader::updateState(const State *newState, const State *oldState)
{
    program()->setUniformValue(m_colorLocation, newState->color);
    Q_UNUSED(oldState)
}
