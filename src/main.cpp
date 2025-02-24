#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <Windows.h>

#include "globals.h"
#include "options.h"
#include "nlohmann/json.hpp"
#include "cryptography.h"
#include "app.h"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    Application app;

    app.run();

    return 0;
}
