#include "TextNodeContainer.h"

#include <QFontMetrics>
#include <private/qquickitem_p.h>

// default font properties
const QString FONT_FAMILY = "Arial";
const int POINT_SIZE = 18;
const int FONT_WEIGHT = QFont::Normal;
const bool ITALIC = false;

TextNodeContainer::TextNodeContainer(QQuickItem* item)
    : m_stateChanged(true)
    , m_text("")
    , m_font(QFont(FONT_FAMILY, POINT_SIZE, FONT_WEIGHT, ITALIC))
    , m_color(Qt::black)
    , m_pos(QPoint(0, 0))
    , m_layoutSize(QSize(0, 0))
{
    QSGRenderContext* context = QQuickItemPrivate::get(item)->sceneGraphRenderContext();
    m_glyphNode = context->sceneGraphContext()->createGlyphNode(context, false);
    m_glyphNode->setOwnerElement(item);
    m_glyphNode->setFlag(QSGNode::OwnedByParent);
}

QSGGlyphNode* TextNodeContainer::glyphNode(QSize& layoutSize)
{
    if(m_stateChanged)
    {
        m_stateChanged = false;

        QTextLayout layout;
        computeLayout(layout);

        QList<QGlyphRun> glyphRunList = layout.glyphRuns();
        if(!glyphRunList.isEmpty())
        {
            m_glyphNode->setColor(m_color);
            m_glyphNode->setGlyphs(m_pos, glyphRunList[0]);
            m_glyphNode->update();
        }
    }

    layoutSize = m_layoutSize;
    return m_glyphNode;
}


void TextNodeContainer::computeLayout(QTextLayout& layout)
{
    layout.setText(m_text);
    layout.setFont(m_font);

    layout.beginLayout();

    QFontMetrics fontMetric(m_font);
    auto lineWidth = fontMetric.width(m_text);

    QTextLine line = layout.createLine();
    line.setLineWidth(lineWidth);
    line.setPosition(QPointF(0, 0));

    layout.endLayout();

    auto boundingRect = layout.boundingRect();
    m_layoutSize = QSize(static_cast<int>(boundingRect.width()), static_cast<int>(boundingRect.height()));
}

void TextNodeContainer::setText(const QString &text)
{
    if(m_text.compare(text) != 0)
    {
        m_text = text;
        m_stateChanged = true;
    }
}

void TextNodeContainer::setFont(const QFont &font)
{
    if(m_font != font)
    {
        m_font = font;
        m_stateChanged = true;
    }
}

void TextNodeContainer::setColor(const QColor &color)
{
    if(m_color != color)
    {
        m_color = color;
        m_stateChanged = true;
    }
}

void TextNodeContainer::setPosition(const QPoint &pos)
{
    if(m_pos != pos)
    {
        m_pos = pos;
        m_stateChanged = true;
    }
}
