#include "MyItem.h"
#include "MyItemGeometry.h"
#include "MyItemShader.h"


MyItem::MyItem()
{
    setFlag(QQuickItem::ItemHasContents, true);
}

void MyItem::setColor(const QColor &color)
{
    if(color != m_color)
    {
        m_color = color;
        emit colorChanged();
        update();
    }
}

QColor MyItem::color() const
{
    return m_color;
}

QSGNode *MyItem::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData *)
{
    auto myGeometryNode = dynamic_cast<MyItemGeometry*>(oldNode);
    if(!myGeometryNode)
    {
        myGeometryNode = new MyItemGeometry();
    }

    QSGGeometry::updateTexturedRectGeometry(myGeometryNode->geometry(), boundingRect(), QRectF(0, 0, 1, 1));

    auto mySimpleMaterial = dynamic_cast<QSGSimpleMaterial<State>*>(myGeometryNode->material());
    mySimpleMaterial->state()->color = m_color;

    myGeometryNode->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return myGeometryNode;
}
