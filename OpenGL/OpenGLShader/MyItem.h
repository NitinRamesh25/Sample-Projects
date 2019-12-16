#pragma once

#include <QQuickFramebufferObject>

class MyItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    MyItem(QQuickItem* parentItem = nullptr);

protected:
    QQuickFramebufferObject::Renderer* createRenderer() const override;

    void mousePressEvent(QMouseEvent *event) override;
};

