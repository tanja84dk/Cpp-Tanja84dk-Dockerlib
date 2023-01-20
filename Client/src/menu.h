#ifndef TANJA84DK_DOCKERLIB_CLIENT_MENU_H
#define TANJA84DK_DOCKERLIB_CLIENT_MENU_H

#include <fmt/core.h>

namespace Client::Menues
{
    void showMain()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "\tMain Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] \tContainers\n"
                   "[2] \tImages\n"
                   "[3] \tNetworks\n"
                   "[99] \tExit\n");
    };

    void showContainer()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "\tContainer Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] \tList Containers\n"
                   "[2] \tInspect Container\n"
                   "[3] \tGet container logs\n"
                   "[4] \tStart a Container\n"
                   "[5] \tStop a container\n"
                   "[6] \tRestart a Container\n"
                   "[7] \tKill a Container\n"
                   "[9] \tInfo\n"
                   "[99] \tExit\n");
    };

    void showImages()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "\tImages Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] \tList Images\n"
                   "[2] \tInspect Image\n"
                   "[3] \tHistory of image\n"
                   "[4] \tSearch image\n"
                   "[99] \tExit\n");
    };

    void showNetworks()
    {
        fmt::print("\n"
                   "------------------------------\n"
                   "\tImages Menu\n"
                   "------------------------------\n"
                   "\n"
                   "[1] \tList Networks\n"
                   "[2] \tInspect Network\n"
                   "[3] \tDelete Network\n"
                   "[4] \tCreate Network\n"
                   "[5] \tConnect container to Network\n"
                   "[6] \tDisconnect container from Network\n"
                   "[99] \tExit\n");
    };
};

#endif // TANJA84DK_DOCKERLIB_CLIENT_MENU_H