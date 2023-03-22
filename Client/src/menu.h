#ifndef TANJA84DK_DOCKERLIB_CLIENT_MENU_H
#define TANJA84DK_DOCKERLIB_CLIENT_MENU_H

#include <fmt/core.h>
#include <array>
#include <string>

namespace Client::Menues
{
    static std::array<std::string, 3> arrayMainMenu = {"Containers",
                                                       "Images",
                                                       "Networks"};

    static std::array<std::string, 8> arrayContainerMenu = {"List Containers",
                                                            "Inspect Container",
                                                            "Get container logs",
                                                            "Start a Container",
                                                            "Stop a container",
                                                            "Restart a Container",
                                                            "Kill a Container",
                                                            "Info"};

    static std::array<std::string, 4> arrayImagesMenu = {"List Images",
                                                         "Inspect Image",
                                                         "History of image",
                                                         "Search image"};

    static std::array<std::string, 6> arrayNetworkMenu = {"List Networks",
                                                          "Inspect Network",
                                                          "Delete Network",
                                                          "Create Network",
                                                          "Connect container to Network",
                                                          "Disconnect container from Network"};

    static void printLabel(const std::string &menuTitle)
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "\t{}\n"
                   "------------------------------\n"
                   "\n",
                   menuTitle);
    }

    template <size_t size>
    static void printMenu(const std::array<std::string, size> &array)
    {
        for (size_t i = 0; i < size; ++i)
        {
            fmt::print("[{}]\t{}\n", (i + 1), array[i]);
        }
        fmt::print("[99]\tExit\n");
    }

    static void showMain()
    {
        Client::Menues::printLabel("Main Menu");
        Client::Menues::printMenu(arrayMainMenu);
    }

    void showContainer()
    {
        Client::Menues::printLabel("Containers Menu");
        Client::Menues::printMenu(arrayContainerMenu);
    }

    void showImages()
    {
        Client::Menues::printLabel("Images Menu");
        Client::Menues::printMenu(arrayImagesMenu);
    }

    void showNetworks()
    {
        Client::Menues::printLabel("Networks Menu");
        Client::Menues::printMenu(arrayNetworkMenu);
    }
}

#endif // TANJA84DK_DOCKERLIB_CLIENT_MENU_H
