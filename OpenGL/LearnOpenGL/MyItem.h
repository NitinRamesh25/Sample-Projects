#pragma once

#include <QQuickFramebufferObject>

class MyItem : public QQuickFramebufferObject
{
public:
    MyItem(QQuickItem* parentItem = nullptr);

    void refreshDrawing();

protected:
    QQuickFramebufferObject::Renderer* createRenderer() const override;
};
