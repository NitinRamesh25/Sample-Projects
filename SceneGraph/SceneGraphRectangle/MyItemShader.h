#pragma once

#include <QColor>
#include <QSGSimpleMaterialShader>

struct State
{
    QColor color;

    int compare(const State *other) const
    {
        uint rgb = color.rgba();
        uint otherRgb = other->color.rgba();

        if (rgb == otherRgb)
        {
            return 0;
        }
        else if (rgb < otherRgb)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
};

class MyItemShader : public QSGSimpleMaterialShader<State>
{
    QSG_DECLARE_SIMPLE_COMPARABLE_SHADER(MyItemShader, State);

public:
    MyItemShader();

    const char* vertexShader() const override;
    const char* fragmentShader() const override;

    QList<QByteArray> attributes() const override;
    void resolveUniforms() override;

    void updateState(const State *newState, const State *oldState) override;

protected:
    int m_colorLocation;
};
