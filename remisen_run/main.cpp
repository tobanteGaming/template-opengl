#include "application.hpp"

namespace tg = tobanteGaming;

int main()
{
    // Log
    tobanteGaming::Log::Init();
    LOG_INFO("Welcome to RemisenRun!");

    tg::Pointer<tg::Application> app;
    app.reset(new tg::Application("tobanteGaming: 3D"));
    app->Init();
    app->Run();

    return EXIT_SUCCESS;
}