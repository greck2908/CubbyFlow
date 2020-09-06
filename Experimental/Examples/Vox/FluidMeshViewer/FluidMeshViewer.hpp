/*************************************************************************
> File Name: FluidMeshViewer.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Particle Viewer
> Created Time: 2020/08/11
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#ifndef CUBBYFLOW_FLUID_MESH_VIEWER
#define CUBBYFLOW_FLUID_MESH_VIEWER

#include <Vox/App.hpp>
#include <Vox/GLTypes.hpp>
#include <memory>

namespace Vox {
    class GeometryCacheManager;
    class RoundRobinAsyncBuffer;
    class PostProcessing;
    class Texture;
    class Program;
    class FrameBuffer;
};

class FluidMeshViewer : public Vox::App
{
public:
    //! Default Constructor
    FluidMeshViewer();
    //! Default Destructor
    ~FluidMeshViewer();
    
    //! Intiailize sample application.
    bool Initialize(const Vox::Path& scenePath) override;
    void DrawFrame() override;
    const char* GetWindowTitle() override { return "Particle Viewer"; };

protected:
    void OnSetWindowSize() override;
private:
    std::unique_ptr<Vox::RoundRobinAsyncBuffer> _buffer;
    std::shared_ptr<Vox::GeometryCacheManager> _cacheMgr;
    std::unique_ptr<Vox::PostProcessing> _postProcessing;
    std::shared_ptr<Vox::FrameBuffer> _mainPass;
    std::shared_ptr<Vox::Program> _meshShader;
    std::shared_ptr<Vox::Texture> _screenTexture;
};

#endif