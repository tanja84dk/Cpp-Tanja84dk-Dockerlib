#ifndef TANJA84DK_DOCKERLIB_CLIENT_MENU_H
#define TANJA84DK_DOCKERLIB_CLIENT_MENU_H

#include <fmt/core.h>

#include <array>
#include <string>

namespace menus {

enum main_menu_enum {
    Containers = 1,
    Images = 2,
    Networks = 3,
};

static std::array<std::string, 3> main_menu_array = {"Containers", "Images", "Networks"};

static std::array<std::string, 8> container_menu_array = {
    "List Containers",  "Inspect Container",   "Get container logs", "Start a Container",
    "Stop a container", "Restart a Container", "Kill a Container",   "Info"};

static std::array<std::string, 4> images_menu_array = {"List Images", "Inspect Image", "History of image",
                                                       "Search image"};

static std::array<std::string, 6> network_menu_array = {"List Networks",
                                                        "Inspect Network",
                                                        "Delete Network",
                                                        "Create Network",
                                                        "Connect container to Network",
                                                        "Disconnect container from Network"};

static void print_menu_label(const std::string &menu_title_string) {
    fmt::print(
        "\n"
        "------------------------------\n"
        "\t{}\n"
        "------------------------------\n"
        "\n",
        menu_title_string);
}

template <std::size_t size>
static void print_menu_options(const std::array<std::string, size> &menu_options_array) {
    for (std::size_t i = 0; i < size; ++i) {
        fmt::print("[{}]\t{}\n", (i + 1), menu_options_array[i]);
    }
    fmt::print("[99]\tExit\n");
}

void print_main_menu() noexcept {
    print_menu_label("Main Menu");
    print_menu_options(main_menu_array);
}

void print_container_menu() noexcept {
    print_menu_label("Containers Menu");
    print_menu_options(container_menu_array);
}

void print_images_menu() noexcept {
    print_menu_label("Images Menu");
    print_menu_options(images_menu_array);
}

void print_networks_menu() noexcept {
    print_menu_label("Networks Menu");
    print_menu_options(network_menu_array);
}
}  // namespace menus

#endif  // TANJA84DK_DOCKERLIB_CLIENT_MENU_H
