为PC版小爱同学2.0进行DLL注入

仅供学习参考，代码绝大部分都使用通义千问生成

编译：
```powershell
windres resource.rc -O coff -o resource.o
```
```powershell
g++ DLL_Injection_XiaoaiAgent.cpp resource.o -o Xiao.exe -static -static-libgcc -static-libstdc++ -luser32 -mwindows
```