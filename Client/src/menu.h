#ifndef TANJA84DK_DOCKERLIB_CLIENT_MENU_H
#define TANJA84DK_DOCKERLIB_CLIENT_MENU_H

#include <fmt/core.h>

namespace Client::Menues
{
    void showMain()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "        Main Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] Containers\n"
                   "[2] Images\n"
                   "[3] Networks\n"
                   "[99]\n");
    };

    void showContainer()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "        Container Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] List Containers\n"
                   "[2] Inspect Container\n"
                   "[3] Get container logs\n"
                   "[4] Start a Container\n"
                   "[5] Stop a container\n"
                   "[6] Restart a Container\n"
                   "[7] Kill a Container\n"
                   "[9] Info\n"
                   "[99] Exit\n");
    };

    void showImages()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "        Images Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] List Images\n"
                   "[2] Inspect Image\n"
                   "[3] History of image\n"
                   "[4] Search image\n"
                   "[99] Exit\n");
    };

    void showNetworks()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "        Images Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] List Networks\n"
                   "[2] Inspect Network\n"
                   "[3] Delete Network\n"
                   "[4] Create Network\n"
                   "[5] Connect container to Network\n"
                   "[6] Disconnect container from Network\n"
                   "[99] Exit\n");
    };
};

#endif // TANJA84DK_DOCKERLIB_CLIENT_MENU_H