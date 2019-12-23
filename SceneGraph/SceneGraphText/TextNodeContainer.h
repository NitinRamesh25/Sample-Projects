#pragma once
#include <private/qsgadaptationlayer_p.h>
#include <QSGGeometryNode>
#include <QTextLayout>
#include <QList>
#include <QString>
#include <QFont>

class TextNodeContainer
{
public:
    TextNodeContainer(QQuickItem* item);

    QSGGlyphNode* glyphNode(QSize& layoutSize);

    void setText(const QString& text);
    void setFont(const QFont& font);
    void setColor(const QColor& color);
    void setPosition(const QPoint& pos);

protected:
    void computeLayout(QTextLayout& layout);

    bool m_stateChanged;

    QString m_text;
    QFont m_font;
    QColor m_color;
    QPoint m_pos;

    QSize m_layoutSize;

    QSGGlyphNode* m_glyphNode;
};
