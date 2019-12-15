#include "FramebufferRendererFactory.h"
#include "MyItemRenderer.h"

FramebufferRendererFactoryPtr FramebufferRendererFactory::m_instance = nullptr;

FramebufferRendererFactoryPtr FramebufferRendererFactory::instance()
{
    if(nullptr == m_instance)
    {
        m_instance.reset(new FramebufferRendererFactory());
    }
    return m_instance;
}

QQuickFramebufferObject::Renderer* FramebufferRendererFactory::createRenderer(FramebufferRendererFactory::RendererType type)
{
    QQuickFramebufferObject::Renderer* renderer = nullptr;
    switch (type)
    {
    case MY_ITEM_RENDERER:
        renderer = new MyItemRenderer();
        break;

    default:
        break;
    }
    return renderer;
}

