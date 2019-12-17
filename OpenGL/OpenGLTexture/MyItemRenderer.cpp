#include "MyItemRenderer.h"
#include "MyItem.h"

#include <QImage>

MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();
    initShaderProgram();
    initBufferMemory();
    initTexture();
}

MyItemRenderer::~MyItemRenderer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);

    glDeleteProgram(m_shaderProgram);
    glDeleteTextures(1, &m_texture);
}

QOpenGLFramebufferObject *MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    auto* myItem = qobject_cast<MyItem*>(item);
    m_window = myItem->window();
    m_size = myItem->size();
}

void MyItemRenderer::render()
{
    glViewport(0, 0, 2 * m_size.width(), 2 * m_size.height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);

    glBindVertexArray(m_vao);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_window->resetOpenGLState();
}


void MyItemRenderer::initShaderProgram()
{
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec2 aTexCoord;\n"
                                     "out vec3 vertexColor;\n"
                                     "out vec2 texCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "gl_Position = vec4(aPos, 1.0f);\n"
                                     "vertexColor = aColor;\n"
                                     "texCoord = aTexCoord;\n"
                                     "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
                                       "in vec3 vertexColor;\n"
                                       "in vec2 texCoord;\n"
                                       "uniform sampler2D Texture0;\n"
                                       "out vec4 fragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "fragColor = texture(Texture0, texCoord);\n"
                                       "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    verifyShaderCompilation(vertexShader, "vertexShader");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    verifyShaderCompilation(fragmentShader, "fragmentShader");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    verifyShaderProgramCompilation(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void MyItemRenderer::initBufferMemory()
{
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // interpreting vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // interpreting vertex colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // interpreting texture vertices
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void MyItemRenderer::initTexture()
{
    int location = glGetUniformLocation(m_shaderProgram, "Texture0");
    glUniform1i(location, 0);

    glGenTextures(1, &m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Setting wrap and filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); // WRAP S coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); // WRAP T coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // MIN filter is used when texture maps to an area greater than 1 texture element
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // MAX filter is used when texture maps to an area smaller than 1 texture element

    QImage image(":/stars.jpg");
    if(!image.isNull())
    {
        uchar* data = image.bits();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        qDebug()<<image.format();
    }
    else
    {
        qDebug() << "Failed to load image";
    }
}

void MyItemRenderer::verifyShaderCompilation(GLuint shader, const QString& shaderType)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        qDebug() << "Shader Compilation failed: " << shaderType << " " << infoLog;
    }
}

void MyItemRenderer::verifyShaderProgramCompilation(GLuint program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        qDebug() << "Shader Program Link failed: " << infoLog;
    }
}
