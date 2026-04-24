#include "InjectorCore.h"

int main() {
    return RunInjector(
        "XiaomiAICreator Injector",
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\XiaomiAICreatorClient.exe",
        "XiaomiAICreatorClient.exe",
        "错误：未能从小米AI创作注册表获取安装路径，请检查程序是否安装！"
    );
}
