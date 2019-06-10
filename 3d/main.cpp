#include "application.hpp"

namespace tg = tobanteGaming;

int main()
{
    tg::Pointer<tg::Application> app;
    app.reset(new tg::Application("tobanteGaming: 3D"));
    app->Init();
    app->Run();

    return EXIT_SUCCESS;
}