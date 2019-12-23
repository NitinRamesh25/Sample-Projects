#include "MyItem.h"
#include "RectGeometryNode.h"
#include "TextNodeContainer.h"

#include <QSGSimpleMaterial>

MyItem::MyItem(QQuickItem* parentItem)
    : QQuickItem(parentItem)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

QSGNode *MyItem::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData *)
{
    auto* rectGeometryNode = dynamic_cast<RectGeometryNode*>(oldNode);
    if(!rectGeometryNode)
    {
        rectGeometryNode = new RectGeometryNode();

        TextNodeContainer textNodeContainer(this);
        textNodeContainer.setText("Hello World");
        textNodeContainer.setColor(Qt::white);
        textNodeContainer.setPosition(QPoint(static_cast<int>(width() / 2),
                                             static_cast<int>(height() / 2)));

        QSize textBoundingSize;
        QSGGlyphNode* textNode = textNodeContainer.glyphNode(textBoundingSize);

        rectGeometryNode->appendChildNode(textNode);
    }

    auto* geometry = rectGeometryNode->geometry();
    QSGGeometry::updateTexturedRectGeometry(geometry, boundingRect(), QRectF(0, 0, 1, 1));

    auto* material = dynamic_cast<QSGSimpleMaterial<RectMaterialState>*>(rectGeometryNode->material());
    material->state()->m_color = m_color;
    material->state()->m_alternateColor = m_alternateColor;



    rectGeometryNode->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return rectGeometryNode;
}

void MyItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    auto tempColor = m_color;
    m_color = m_alternateColor;
    m_alternateColor = tempColor;

    emit colorChanged();
    emit alternateColorChanged();
    update();
}

QColor MyItem::color() const
{
    return m_color;
}

void MyItem::setColor(const QColor &color)
{
    if(m_color != color)
    {
        m_color = color;
        emit colorChanged();
        update();
    }
}

QColor MyItem::alternateColor() const
{
    return m_alternateColor;
}

void MyItem::setAlternateColor(const QColor &color)
{
    if(m_alternateColor != color)
    {
        m_alternateColor = color;
        emit alternateColorChanged();
        update();
    }
}

