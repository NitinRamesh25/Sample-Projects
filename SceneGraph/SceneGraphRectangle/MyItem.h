#pragma once

#include <QQuickItem>

#include <QColor>

class MyItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    MyItem();

    void setColor(const QColor& color);
    QColor color() const;

signals:
    void colorChanged();

protected:
    QSGNode* updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

    QColor m_color;
};
