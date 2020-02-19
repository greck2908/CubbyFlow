/*************************************************************************
> File Name: main.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Visualize CubbyFlow examples with OpenGL3.
> Created Time: 2020/02/15
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#include <../ClaraUtils.h>

#include <Core/Utils/Logging.h>
#include <Framework/Common.h>
#include <Clara/include/clara.hpp>
#include <pystring/pystring.h>

#ifdef CUBBYFLOW_WINDOWS
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include <Framework/Application.h>
#include <Framework/GL3/Headless/EGLApp.h>
#include <Framework/Window.h>
#include <Framework/GL3/Headless/EGLWindow.h>
#include <Framework/Media/ScreenRecorder.h>

#include <memory>
#include <fstream>
#include <iostream>
#include <string>

#define APP_NAME "GL3Examples"

using namespace CubbyFlow;
using namespace CubbyRender;

int main(int argc, char* argv[])
{
    bool showHelp = false;
    bool headless = true;
    int numberOfFrames = 100;
    double fps = 60.0;
    std::string logFileName = APP_NAME ".log";
    std::string outputDir = APP_NAME "_output";
    std::string format = "tga";

    // Parsing
    auto parser =
        clara::Help(showHelp) |
        clara::Opt(headless, "headless mode")
        ["-h"]["--head-less"]
        ("simulation rendering mode (default is not headless mode, that is, create screen and show)") |
        clara::Opt(numberOfFrames, "numberOfFrames")
        ["-f"]["--frames"]
        ("total number of frames (default is 100)") |
        clara::Opt(fps, "fps")
        ["-p"]["--fps"]
        ("frames per second (default is 60.0)") |
        clara::Opt(logFileName, "logFileName")
        ["-l"]["--log"]
        ("log file name (default is " APP_NAME ".log)") |
        clara::Opt(outputDir, "outputDir")
        ["-o"]["--output"]
        ("output directory name (default is " APP_NAME "_output)") |
        clara::Opt(format, "format")
        ["-m"]["--format"]
        ("simulation output format (mp4 or tga. default is mp4)");

    auto result = parser.parse(clara::Args(argc, argv));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(EXIT_FAILURE);
    }

    if (showHelp)
    {
        std::cout << ToString(parser) << '\n';
        exit(EXIT_SUCCESS);
    }

#ifdef CUBBYFLOW_WINDOWS
    _mkdir(outputDir.c_str());
#else
    mkdir(outputDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
#endif

    std::ofstream logFile(logFileName.c_str());
    if (logFile)
    {
        Logging::SetAllStream(&logFile);
    }

    ScreenRecorder recorder;
    ApplicationPtr application;
    if (headless == true) //! Headless rendering mode with EGL library.
    {
        application = std::make_shared<EGLApp>();
        if (application->initialize())
        {
            CUBBYFLOW_ERROR << "Initialize EGLApplication failed.";
            return -1;
        }

        auto window = application->createWindow("Test Rendering", 256, 256);
        application->runWithLimitedFrames(numberOfFrames, fps, &recorder);
    }
    else //! with display, rendering with glfw library
    {
        UNUSED_VARIABLE(application);
        //! Do nothing.
    }

    if (format == "mp4")
    {
        // recorder.saveVideo(outputDir + APP_NAME);
    }
    else if (format == "tga")
    {
        // recorder.saveScreenShot();
    }

    UNUSED_VARIABLE(recorder);

    return EXIT_SUCCESS;
}