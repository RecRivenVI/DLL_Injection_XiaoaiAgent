#include "InjectorCore.h"

int main() {
    return RunInjector(
        "XiaoaiAgent Injector",
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\XiaoaiAgent.exe",
        "XiaoaiAgent.exe",
        "错误：未能从小爱注册表获取安装路径，请检查程序是否安装！"
    );
}
