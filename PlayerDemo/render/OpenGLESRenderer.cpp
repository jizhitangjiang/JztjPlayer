#include "OpenGLESRenderer.h"

#include <QPainter>
#include <QDebug>

static const char *vShaderSource =
        "varying   vec2 Texcoord;\n"
        "attribute vec3 aPos;\n"
        "attribute vec2 aTexCoord;\n"
        "void main(){\n"
            "gl_Position  = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "Texcoord = aTexCoord;\n"
        "}\n";

static const char *fShaderSource =
        "varying  vec2 Texcoord;\n"
        "uniform  sampler2D us2_SamplerY;\n"
        "uniform  sampler2D us2_SamplerU;\n"
        "uniform  sampler2D us2_SamplerV;\n"
        "void main()\n"
        "{\n"
            "vec3 yuv;\n"
            "vec3 rgb;\n"
            "yuv.x = (texture2D(us2_SamplerY, Texcoord).r);\n"
            "yuv.y = (texture2D(us2_SamplerU, Texcoord).r - 0.5);\n"
            "yuv.z = (texture2D(us2_SamplerV, Texcoord).r - 0.5);\n"
            "rgb = mat3( 1, 1, 1, 0,-0.39465, 2.03211, 1.13983, -0.58060, 0)*yuv;\n"
            "gl_FragColor = vec4(rgb, 1);\n"
        "}\n";

namespace xes {
namespace renderer {

OpenGLESRenderer::OpenGLESRenderer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    qDebug()<<__FUNCTION__;
}

OpenGLESRenderer::~OpenGLESRenderer()
{

}

void OpenGLESRenderer::updateImage(int width, int height,
                                   int yStride, int uStride, int vStride,
                                   uchar *yBuffer, uchar *uBuffer, uchar *vBuffer)
{
    makeCurrent();

    glBindTexture(GL_TEXTURE_2D, m_textureY);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, yBuffer);

    glBindTexture(GL_TEXTURE_2D, m_textureU);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width/2, height/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, uBuffer);

    glBindTexture(GL_TEXTURE_2D, m_textureV);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width/2, height/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, vBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    qDebug()<<Q_FUNC_INFO<<yBuffer<<uBuffer<<vBuffer;
    update();
}

void OpenGLESRenderer::initializeGL()
{
    initializeOpenGLFunctions();

    if (!initShader()) {
        qDebug()<<Q_FUNC_INFO<<"initShader failed";
        return;
    }

    if (!initModule()) {
        qDebug()<<Q_FUNC_INFO<<"initModule failed";
        return;
    }

    if (!initTextures()) {
        qDebug()<<Q_FUNC_INFO<<"initTextures failed";
        return;
    }

   // GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
     //const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
     //const GLubyte* OpenGLVersion =glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
}

void OpenGLESRenderer::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_programId);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureY);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textureU);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_textureV);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void OpenGLESRenderer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

bool OpenGLESRenderer::initModule()
{
//    float vertices[] = {
//        // positions          // texture coords
//         1.0f,  1.0f, 0.0f,   1.0f, 0.0f,
//         1.0f, -1.0f, 0.0f,   1.0f, 1.0f,
//        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,
//        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f,
//        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,
//         1.0f,  1.0f, 0.0f,   1.0f, 0.0f
//    };

    float yuvVertices[] = {
        // positions          // texture coords
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         1.0f, 1.0f, 0.0f,    1.0, 0.0f,
    };

//    glGenVertexArrays(1, &m_vao);
//    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(yuvVertices), yuvVertices, GL_STATIC_DRAW);

    int attribute1 = glGetAttribLocation(m_programId, "aPos");
    glVertexAttribPointer(attribute1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0));
    glEnableVertexAttribArray(attribute1);

    int attribute2 = glGetAttribLocation(m_programId, "aTexCoord");
    glVertexAttribPointer(attribute2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(attribute2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    return true;
}

bool OpenGLESRenderer::initShader()
{
    //shader编译链接
    unsigned int vertexID = 0, fragID = 0;
    char infoLog[512] = { 0 };
    int successFlag = 0;

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vShaderSource, NULL);
    glCompileShader(vertexID);
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &successFlag);
    if (!successFlag) {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        qDebug() << Q_FUNC_INFO << infoLog;
        return false;
    }

    fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fShaderSource, NULL);
    glCompileShader(fragID);
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &successFlag);
    if (!successFlag) {
        glGetShaderInfoLog(fragID, 512, NULL, infoLog);
        qDebug() << Q_FUNC_INFO << infoLog;
        return false;
    }

    //连接
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexID);
    glAttachShader(m_programId, fragID);
    glLinkProgram(m_programId);
    glGetProgramiv(m_programId, GL_LINK_STATUS, &successFlag);
    if (!successFlag) {
        glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
        qDebug() << Q_FUNC_INFO << infoLog;
        return false;
    }

    glUseProgram(m_programId);
    glUniform1i(glGetUniformLocation(m_programId, "us2_SamplerY"), 0);
    glUniform1i(glGetUniformLocation(m_programId, "us2_SamplerU"), 1);
    glUniform1i(glGetUniformLocation(m_programId, "us2_SamplerV"), 2);
    glUseProgram(0);

    glDeleteShader(vertexID);
    glDeleteShader(fragID);

    return true;
}

bool OpenGLESRenderer::initTextures()
{
    glGenTextures(1, &m_textureY);
    glBindTexture(GL_TEXTURE_2D, m_textureY);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &m_textureU);
    glBindTexture(GL_TEXTURE_2D, m_textureU);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &m_textureV);
    glBindTexture(GL_TEXTURE_2D, m_textureV);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

}
}
