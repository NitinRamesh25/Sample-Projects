# Qt OpenGL Notes

1. Custom item class should inherit from **QQuickFramebufferObject** so that **OpenGL** rendering can happen on **Qt Scene**

```
class MyItem : public QQuickFramebufferObject
{
public:
    MyItem(QQuickItem* parentItem = nullptr);

protected:
    QQuickFramebufferObject::Renderer* createRenderer() const override;
};
```

2. Another class should inherit from **QQuickFramebufferObject::Renderer** and **QOpenGLFunctions** for using OpenGL commands.

```

class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions
{
public:
    MyItemRenderer();

protected:
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    void synchronize(QQuickFramebufferObject *item) override;

    void render() override;
};
```
3. QOpenGL functions:

    * In order to use OpenGL functions, in the constructor of the ItemRenderer call _initializeOpenGLFunctions()_

    * Set the _glViewPort(0,0,width,height)_ in which OpenGL rendering happens.

    * We must clear previous existing color of the viewPort and set new color using _glClearColor(0.2f, 0.3f, 0.3f, 1.0f)_ and the new color gets filled by calling _glClear(GL_COLOR_BUFFER_BIT)_

    * Initialize a vertex array, and create memory buffers to be sent to the GPU 
    ```
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    glGenBuffers(bufferSize, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    ```

    * After setting the vertex data to GPU, the GPU must know how to interpret or parse this data,
    ```
    GLuint vertexIndex = 0; // As we mentioned location as 0 for vertexShader
    GLuint vertexAttributeSize = 3; // As there are three vertices for the triangle
    GLenum dataType = GL_FLOAT;
    GLboolean normalizeData = GL_FALSE;
    GLsizei vertexStride = 3 * sizeof(float); // Next vertex comes after x,y,z float vals.
    GLvoid* offsetPointer = 0;

    glVertexAttribPointer(vertexIndex, vertexAttributeSize, dataType, normalizeData,
                          vertexStride, offsetPointer);
    glEnableVertexAttribArray(vertexIndex);
    ```

    * Configure Vertex shader
    ```
    const GLuint shaderSourceCount = 1;
    const GLchar* shaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                       "}\0";
    GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderId, shaderSourceCount, &shaderSource, NULL);
    glCompileShader(shaderId);

    verifyShaderObjectCompilation(shaderId, GL_VERTEX_SHADER);
    ```

    * Configure Fragment Shader
    ```
    const GLuint shaderSourceCount = 1;
    const GLchar* shaderSource = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                         "}\0";
    GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderId, shaderSourceCount, &shaderSource, NULL);
    glCompileShader(shaderId);

    verifyShaderObjectCompilation(shaderId, GL_FRAGMENT_SHADER);
    ```

    * The shader objects have been compiled and have to be attached to shader program so that they can be executed in order.
    ```
    GLuint shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);

    glLinkProgram(shaderProgramId); // Makes sure the input and output of each shader is correct
    glUseProgram(shaderProgramId); // Runs program

    // Delete shaders once they have been attached to the program.
    glDeleteShader(vertexShaderId); 
    glDeleteShader(fragmentShaderId); 
    ```

    * Draw the triangle
    ```
    glDrawArrays(GL_TRIANGLES, 0, 3);
    ```

    * at the bottom of _render()_ call _m_window->resetOpenGLState()_
    