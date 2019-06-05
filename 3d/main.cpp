#include <cstdlib>
#include <memory>

#include "application.hpp"
#include "warning.hpp"

int main(int argc, char* argv[])
{
    namespace tg = tobanteGaming;

    tg::ignoreUnused(argc);
    tg::ignoreUnused(argv);

    auto app = std::make_unique<tg::Application>("3D Demo");
    app->Init();
    app->Run();
    return EXIT_SUCCESS;
}
