@echo off
REM 设置构建目录
set BUILD_DIR=build

REM 创建构建目录
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

REM 进入构建目录
cd %BUILD_DIR%

REM 调用 CMake 配置项目，指定使用 MinGW 工具链
cmake .. -G "MinGW Makefiles"

REM 检查 CMake 是否成功
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM 使用 mingw32-make 编译项目
mingw32-make

REM 检查编译是否成功
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

REM 返回到项目根目录
cd ..

echo Build completed successfully!
pause