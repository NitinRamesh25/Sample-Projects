#pragma once

#include <QQuickFramebufferObject>

class MyItem : public QQuickFramebufferObject
{
public:
    MyItem();

    Renderer* createRenderer() const override;
};
