#include "MyItem.h"
#include "ImageGeometryNode.h"

MyItem::MyItem(QQuickItem* parent)
    : QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode* MyItem::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData *)
{
    auto* node = dynamic_cast<ImageGeometryNode*>(oldNode);
    if(!node)
    {
        node = new ImageGeometryNode(this);
    }

    node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return node;
}
