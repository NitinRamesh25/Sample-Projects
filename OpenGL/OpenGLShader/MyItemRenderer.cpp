#include "MyItemRenderer.h"
#include "MyItem.h"

MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();

    createGeometry();
    createShaderProgram();
}

void MyItemRenderer::createGeometry()
{
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void MyItemRenderer::createShaderProgram()
{
    const char *vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "out vec3 ourColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "   ourColor = aColor;\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec3 ourColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(ourColor, 1.0f);\n"
                                       "}\n\0";

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    verifyShaderProgramCompilation(m_shaderProgram);
    verifyShaderObjectCompilation(vertexShader, GL_VERTEX_SHADER);
    verifyShaderObjectCompilation(fragmentShader, GL_FRAGMENT_SHADER);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
    auto* myItem = qobject_cast<MyItem*>(item);
    m_size = myItem->size();
    m_window = myItem->window();
}

void MyItemRenderer::render()
{
    glViewport(0, 0, 2 * m_size.width(), 2 * m_size.height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_window->resetOpenGLState();
}

bool MyItemRenderer::verifyShaderProgramCompilation(GLuint programId)
{
    int logMaxSize = 512;
    int  success;
    char infoLog[logMaxSize];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED";
        qDebug() << "InfoLog: " << infoLog << "\n";
        return false;
    }
    return true;
}

bool MyItemRenderer::verifyShaderObjectCompilation(GLuint shaderId, GLuint shaderType)
{
    int logMaxSize = 512;
    int  success;
    char infoLog[logMaxSize];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderId, logMaxSize, NULL, infoLog);
        qDebug() << "ERROR::SHADER_OBJECT::COMPILATION_FAILED";
        qDebug() << "ShaderType: " << shaderType;
        qDebug() << "InfoLog: " << infoLog << "\n";
        return false;
    }
    return true;
}
