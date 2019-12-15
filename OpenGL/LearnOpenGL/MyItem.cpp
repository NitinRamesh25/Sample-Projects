#include "MyItem.h"
#include "MyItemRenderer.h"

MyItem::MyItem(QQuickItem* parentItem)
    : QQuickFramebufferObject(parentItem)
{}

void MyItem::refreshDrawing()
{
    update();
}

QQuickFramebufferObject::Renderer *MyItem::createRenderer() const
{
    return new MyItemRenderer();
}
