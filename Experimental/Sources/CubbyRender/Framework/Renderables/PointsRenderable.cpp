/*************************************************************************
> File Name: PointsRenderable.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Abstract base rendererable for Renderer object.
> Created Time: 2020/03/29
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/

#include <Framework/Renderable/PointsRenderable.h>
#include <Framework/Renderable/Material.h>
#include <Framework/Buffer/VertexBuffer.h>
#include <Framework/Buffer/IndexBuffer.h>
#include <Framework/Buffer/InputLayout.h>
#include <Framework/Buffer/Vertex.h>
#include <Framework/Renderer/Renderer.h>
#include <Framework/Shader/Shader.h>
#include <Framework/Utils/Common.h>

namespace CubbyFlow {
namespace CubbyRender {
    
    PointsRenderable::PointsRenderable()
    {
        //! Do nothing.
    }

    PointsRenderable::PointsRenderable(const ConstArrayAccessor1<Vector3F>& positions,
                                       const ConstArrayAccessor1<Vector4F>& colors,
                                       float radius)
    {
        update(positions, colors, radius);
    }


    PointsRenderable::~PointsRenderable()
    {
        release();
    }

    void PointsRenderable::update(const ConstArrayAccessor1<Vector3F>& positions,
                                  const ConstArrayAccessor1<Vector4F>& colors)
    {
        update(positions, colors, _radius);
    }

    void PointsRenderable::update(const ConstArrayAccessor1<Vector3F>& positions,
                                  const ConstArrayAccessor1<Vector4F>& colors,
                                  float radius)
    {
        _radius = radius;
        const size_t totalSize = positions.size() * 3 + colors.size() * 4;

        std::lock_guard<std::mutex> lock(_dataMutex);
        _vertices.Resize(totalSize);
        for (size_t i = 0; i < totalSize / size_t(7); ++i)
        {
            _vertices[  i  ] = positions[i].x;
            _vertices[i + 1] = positions[i].y;
            _vertices[i + 2] = positions[i].z;
            _vertices[i + 3] = colors[i].x;
            _vertices[i + 4] = colors[i].y;
            _vertices[i + 5] = colors[i].z;
            _vertices[i + 6] = colors[i].w;
        }

        invalidateResources();
    }

    void PointsRenderable::onInitializeResource(RendererPtr renderer)
    {
        if (_material == nullptr)
        {
            _material = renderer->createMaterial();
            ShaderPtr shader = renderer->createShaderPreset("point_shader");
            _material->setShader(shader);
        }
        auto params = _material->getShader()->getParameters();
        params.setParameter("Radius", _radius);
        
        if (_inputLayout == nullptr)
        {
            _inputLayout = renderer->createInputLayout();
            VertexBufferPtr buffer = renderer->createVertexBuffer(_vertices.ConstAccessor(), 
                                                                  static_cast<size_t>(_vertices.size() / size_t(7)),  
                                                                  VertexFormat::Position3Color4);
            _inputLayout->attachVertexBuffer(renderer, _material, buffer);
        }
        else
        {
            _inputLayout->updateVertexBuffer(renderer, _vertices.ConstAccessor(), VertexFormat::Position3Color4);
        }

        _primitiveType = PrimitiveType::Point;
    }

    void PointsRenderable::onRender(RendererPtr renderer)
    {
        renderer->bindMaterial(_material);
        renderer->bindInputLayout(_inputLayout);
        renderer->setPrimitiveType(_primitiveType);
        renderer->draw(_inputLayout);
        renderer->unbindInputLayout(_inputLayout);
        renderer->unbindMaterial(_material);
    }

    void PointsRenderable::onRelease()
    {
        //! Do nothing.
    }

    void PointsRenderable::setRadius(float radius)
    {
        _radius = radius;
    }

    float PointsRenderable::getRadius() const
    {
        return _radius;
    }

} 
}