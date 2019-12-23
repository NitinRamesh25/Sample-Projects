#pragma once
#include <QSGGeometryNode>
#include <QSGSimpleMaterialShader>
#include <QColor>

struct RectMaterialState
{
    QColor m_color;
    QColor m_alternateColor;
};

class RectMaterialShader : public QSGSimpleMaterialShader<RectMaterialState>
{
    QSG_DECLARE_SIMPLE_SHADER(RectMaterialShader, RectMaterialState)

public:
    RectMaterialShader();

protected:
    void updateState(const RectMaterialState *newState, const RectMaterialState *oldState) override;

    QList<QByteArray> attributes() const override;
    void resolveUniforms() override;

    const char* vertexShader() const override;
    const char* fragmentShader() const override;

    struct UniformLocation
    {
        int m_color;
        int m_alternateColor;
    }m_uniformLocation;
};

class RectGeometryNode : public QSGGeometryNode
{
public:
    RectGeometryNode();
};
