#pragma once
#include <QQuickItem>

class MyItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor alternateColor READ alternateColor WRITE setAlternateColor NOTIFY alternateColorChanged)
public:
    MyItem(QQuickItem* parentItem = nullptr);

    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;

    void mousePressEvent(QMouseEvent *event) override;

    QColor color() const;
    void setColor(const QColor& color);

    QColor alternateColor() const;
    void setAlternateColor(const QColor& color);


signals:
    void colorChanged();
    void alternateColorChanged();

protected:
    QColor m_color;
    QColor m_alternateColor;
};
