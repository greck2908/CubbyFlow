#include "pch.h"

#include <Framework/Application/Application.h>
#include <Framework/Window/Window.h>
#include <Framework/Renderer/Renderer.h>
#include <Framework/Utils/ImageLoader.h>
#include <GL3/Application/GL3Application.h>
#include <GL3/Utils/GL3Debugging.h>
#include <GL3/Texture/GL3Texture2D.h>
#include <Core/Array/Array1.h>

using namespace CubbyFlow;
using namespace CubbyRender;

#ifdef CUBBYFLOW_USE_GL

TEST(GL3Texture2D, Constructor)
{
	ApplicationPtr application = std::make_shared<GL3Application>();
    EXPECT_EQ(0, application->initialize());
    
    TestWindowPtr window = std::make_shared<TestWindow>("TestWindow", 600, 400);
    application->setMainWindow(window);
    RendererPtr gl = application->getMainWindow()->getRenderer();

    ImageLoader loader;
    EXPECT_EQ(true, loader.loadImage(RESOURCES_DIR "textures/metal.png"));
    
    Size2 textureSize = loader.getImageSize();
    TextureParams params; //! default setting.

    Texture2DPtr texture = gl->createTexture2D(params, textureSize, static_cast<void*>(loader.getImageAccessor().data()));
    EXPECT_EQ(0, CUBBYFLOW_CHECK_GLERROR());
}

#endif