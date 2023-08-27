#ifndef TANJA84DK_DOCKERLIB_CLIENT_SETTINGS_H
#define TANJA84DK_DOCKERLIB_CLIENT_SETTINGS_H

class ClientSettings {
   public:
    virtual ~ClientSettings() {}
    virtual void do_something() = 0;
};

#endif  // TANJA84DK_DOCKERLIB_CLIENT_SETTINGS_H
