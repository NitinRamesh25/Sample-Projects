#include "MyItemShader.h"

MyItemShader::MyItemShader()
{}

const char *MyItemShader::vertexShader() const
{
    return
        "attribute highp vec4 aVertex;                              \n"
        "attribute highp vec2 aTexCoord;                            \n"
        "uniform highp mat4 qt_Matrix;                              \n"
        "varying highp vec2 texCoord;                               \n"
        "void main() {                                              \n"
        "    gl_Position = qt_Matrix * aVertex;                     \n"
        "    texCoord = aTexCoord;                                  \n"
        "}";
}

const char *MyItemShader::fragmentShader() const
{
    return
        "uniform lowp float qt_Opacity;                             \n"
        "uniform lowp vec4 color;                                   \n"
        "varying highp vec2 texCoord;                               \n"
        "void main ()                                               \n"
        "{                                                          \n"
        "    gl_FragColor = texCoord.y * texCoord.x * color * qt_Opacity;  \n"
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

void MyItemShader::updateState(const State *newState, const State */*oldState*/)
{
    program()->setUniformValue(m_colorLocation, newState->color);
}


