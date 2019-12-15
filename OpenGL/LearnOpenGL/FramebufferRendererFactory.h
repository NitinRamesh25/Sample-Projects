#pragma once

#include <memory>
#include <QQuickFramebufferObject>

class FramebufferRendererFactory;
typedef std::shared_ptr<FramebufferRendererFactory> FramebufferRendererFactoryPtr;

class FramebufferRendererFactory
{
public:
    enum RendererType
    {
        MY_ITEM_RENDERER
    };

    static FramebufferRendererFactoryPtr instance();

    QQuickFramebufferObject::Renderer* createRenderer(RendererType type);

private:
    FramebufferRendererFactory() = default;

    static FramebufferRendererFactoryPtr m_instance;
};


