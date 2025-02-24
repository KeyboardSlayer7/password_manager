#ifndef APP_H
#define APP_H

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Application
{
public:
    Application();
    ~Application();

    void init();
    void run();
private:
    bool _running = false;
    // json _passwords;
};

#endif // APP_H