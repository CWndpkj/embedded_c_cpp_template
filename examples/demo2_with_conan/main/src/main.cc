
#include "global_config.h"
#include "global_build_info_time.h"
#include "global_build_info_version.h"
#include "spdlog/spdlog.h"
int main()
{
    spdlog::info("hello world");
    spdlog::warn("This is a warn message");
    return 0;
}