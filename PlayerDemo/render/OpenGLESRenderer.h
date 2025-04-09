#ifndef OPENGLESRENDERER_H
#define OPENGLESRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_2_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

namespace xes {
namespace renderer {

class OpenGLESRenderer : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit OpenGLESRenderer(QWidget *parent = 0);
    ~OpenGLESRenderer();

public:
    void updateImage(int width, int height, int yStride, int uStride, int vStride,
                     uchar *yBuffer, uchar *uBuffer, uchar *vBuffer);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    bool initModule();
    bool initShader();
    bool initTextures();

private:
    unsigned int m_vbo=0;
    unsigned int m_vao = 0;

    unsigned int m_texture = 0;
    unsigned int m_textureY = 0;
    unsigned int m_textureU = 0;
    unsigned int m_textureV = 0;

    GLuint               m_programId;
    QOpenGLShaderProgram m_program;
};

} // namespace renderer
} // namespace xes

#endif // OPENGLESRENDERER_H
