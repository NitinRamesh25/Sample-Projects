#ifndef MYITEM_H
#define MYITEM_H

#include <QQuickFramebufferObject>
#include <QQuickWindow>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>


class MyItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    MyItem(QQuickItem* parent = nullptr);

    Renderer* renderer() const;

protected:
    Renderer * createRenderer() const override;

private:
    Renderer* m_renderer;
};


class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions
{

public:
    MyItemRenderer();

    void synchronize(QQuickFramebufferObject *item) override;

    void render() override;

    QOpenGLFramebufferObject * createFramebufferObject(const QSize &size) override;

private:
    QQuickWindow* window_;

    QScopedPointer<QOpenGLShaderProgram> shader_;

    uint positionAttr_;
    uint colorAttr_;
    int matrixAttr_;
};

#endif // MYITEM_H
