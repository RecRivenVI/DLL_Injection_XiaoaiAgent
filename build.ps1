# 编译小爱同学资源文件
windres -c 65001 XiaoaiAgent.rc -O coff -o XiaoaiAgent_res.o
Write-Host "[+] XiaoaiAgent.rc 编译完成" -ForegroundColor Green

# 编译 小爱同学 注入器
g++ XiaoaiAgentInjector.cpp XiaoaiAgent_res.o -o XiaoaiAgentInjector.exe -static -static-libgcc -static-libstdc++ -luser32 -mwindows -finput-charset=UTF-8 -fexec-charset=GBK
if ($?) { Write-Host "[+] XiaoaiAgentInjector.exe 编译成功" -ForegroundColor Green } else { Write-Host "[-] XiaoaiAgentInjector.exe 编译失败" -ForegroundColor Red }

# 编译小米AI创作资源文件
windres -c 65001 XiaomiAICreator.rc -O coff -o XiaomiAICreator_res.o
Write-Host "[+] XiaomiAICreator.rc 编译完成" -ForegroundColor Green

# 编译 小米AI创作 注入器
g++ XiaomiAICreatorInjector.cpp XiaomiAICreator_res.o -o XiaomiAICreatorInjector.exe -static -static-libgcc -static-libstdc++ -luser32 -mwindows -finput-charset=UTF-8 -fexec-charset=GBK
if ($?) { Write-Host "[+] XiaomiAICreatorInjector.exe 编译成功" -ForegroundColor Green } else { Write-Host "[-] XiaomiAICreatorInjector.exe 编译失败" -ForegroundColor Red }

# 清理生成的对象文件
Remove-Item XiaoaiAgent_res.o, XiaomiAICreator_res.o -ErrorAction SilentlyContinue
Write-Host "[*] 清理临时文件完成" -ForegroundColor Yellow