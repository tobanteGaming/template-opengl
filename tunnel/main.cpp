#include <cstdlib>
#include <memory>

#include "application.hpp"
#include "util.hpp"

int main(int argc, char* argv[])
{
    ignoreUnused(argc);
    ignoreUnused(argv);

    auto app = std::make_unique<tobanteGaming::Application>("Test");
    app->Init();
    app->Run();
    return EXIT_SUCCESS;
}
