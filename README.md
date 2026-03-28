为 PC 版小爱同学 2.1 进行 DLL 注入

仅供学习参考，代码绝大部分都使用 Gemini 生成

编译：
```powershell
windres resource.rc -O coff -o resource.o
```
```powershell
g++ XiaoaiAgentInjector.cpp resource.o -o XiaoaiAgentInjector.exe -static -static-libgcc -static-libstdc++ -luser32 -mwindows
```