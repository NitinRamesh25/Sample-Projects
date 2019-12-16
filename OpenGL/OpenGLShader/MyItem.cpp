#include "MyItem.h"
#include "MyItemRenderer.h"

MyItem::MyItem(QQuickItem* parentItem)
    : QQuickFramebufferObject(parentItem)
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

QQuickFramebufferObject::Renderer* MyItem::createRenderer() const
{
    return new MyItemRenderer();
}

void MyItem::mousePressEvent(QMouseEvent */*event*/)
{
    update();
}

