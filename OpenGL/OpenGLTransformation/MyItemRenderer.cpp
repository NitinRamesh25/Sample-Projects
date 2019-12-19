#include "MyItemRenderer.h"
#include "MyItem.h"

#include <QDebug>

MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();
    createShader();
    createBuffer();
}

QOpenGLFramebufferObject* MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    auto* myItem = dynamic_cast<MyItem*>(item);
    if(nullptr != myItem)
    {
        m_window = myItem->window();
        m_size = myItem->size();
    }
}

void MyItemRenderer::render()
{
    glViewport(0, 0, 2 * m_size.width(), 2 * m_size.height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);
    glUniform4f(m_colorLocation, 1.0f, 0.0f, 0.0f, 1.0f);

    applyTransform();

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    m_window->resetOpenGLState();
}

void MyItemRenderer::createShader()
{
    const char* vertexShaderSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 transform;\n"
        "void main()\n"
        "{\n"
        "gl_Position = transform * vec4(aPos, 1.0f);\n"
        "}\0";

    const char* fragmentShaderSrc =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "uniform vec4 myColor;\n"
        "void main()\n"
        "{\n"
        "fragColor = myColor;\n"
        "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    verifyShaderCompilation(vertexShader, "VertexShader");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    verifyShaderCompilation(fragmentShader, "FragmentShader");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    verifyProgramLink(m_shaderProgram);

    m_colorLocation = glGetUniformLocation(m_shaderProgram, "myColor");
    m_transformLocation = glGetUniformLocation(m_shaderProgram, "transform");
}

void MyItemRenderer::createBuffer()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // topLeft
        -0.5f, 0.5f, 0.0f,  // bottomLeft
        0.5f, 0.5f, 0.0f,   // bottomRight
        0.5, -0.5f, 0.0f    // topRight
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
}

bool MyItemRenderer::verifyShaderCompilation(GLuint shader, QString shaderName)
{
    bool returnFlag = true;
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(!status)
    {
        returnFlag = false;
        GLchar* infoLog;
        glGetShaderInfoLog(shader, 1000, NULL, infoLog);
        qDebug() << shaderName << " compilation failed: " << infoLog;
    }
    return returnFlag;
}

bool MyItemRenderer::verifyProgramLink(GLuint program)
{
    bool returnFlag = true;
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(!status)
    {
        returnFlag = false;
        GLchar* infoLog;
        glGetProgramInfoLog(program, 1000, NULL, infoLog);
        qDebug() << "Shader Program Link Failed";
    }
}

void MyItemRenderer::applyTransform()
{
    QMatrix4x4 transformMatrix;
    transformMatrix.setToIdentity();

    transformMatrix.rotate(45, 0.0f, 0.0f, 1.0f);
    transformMatrix.scale(1.0f, 1.5f);
    transformMatrix.translate(0.3f, 0.2f);

    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, transformMatrix.data());
}
