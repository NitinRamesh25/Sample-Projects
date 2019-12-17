#include "MyItem.h"
#include "MyItemRenderer.h"

MyItem::MyItem(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{

}

QQuickFramebufferObject::Renderer *MyItem::createRenderer() const
{
    return new MyItemRenderer();
}
