#pragma once

#include <QQuickItem>

class MyItem : public QQuickItem
{
    Q_OBJECT
public:
    MyItem(QQuickItem* parent = nullptr);

    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData *) override;
};
