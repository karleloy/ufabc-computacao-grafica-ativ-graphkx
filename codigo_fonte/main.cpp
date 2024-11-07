#include "window.hpp"

int main(int argc, char **Argv) {
    try {
        abcg::Application app(argc, Argv);

        Window window;
        window.setWindowSettings(
            {.width = 800, .height = 600, .title = "Jogo da Memória Matemática"});

        app.run(window);
    } catch (std::exception const &exception) {
        fmt::print(stderr, "{}\n", exception.what());
        return -1;
    }
    return 0;
}