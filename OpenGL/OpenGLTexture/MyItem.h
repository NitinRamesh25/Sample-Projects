#pragma once

#include <QQuickFramebufferObject>

class MyItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    MyItem(QQuickItem* parent = nullptr);

    Renderer* createRenderer() const override;
};

