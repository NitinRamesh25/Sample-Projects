#include "MyItem.h"
#include "MyItemRenderer.h"

MyItem::MyItem()
{

}

QQuickFramebufferObject::Renderer *MyItem::createRenderer() const
{
    return new MyItemRenderer();
}
