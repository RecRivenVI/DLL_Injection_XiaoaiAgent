cmake_minimum_required(VERSION 3.10)
project(DLL_Injection_XiaoaiAgent)

# 设置源文件
set(SOURCE_FILES DLL_Injection_XiaoaiAgent.cpp)

# 添加资源文件
set(RESOURCE_FILES resource.rc)

# 添加可执行文件
add_executable(DLL_Injection_XiaoaiAgent ${SOURCE_FILES} ${RESOURCE_FILES})

# 设置图标
target_sources(DLL_Injection_XiaoaiAgent PRIVATE $<IF:$<PLATFORM_ID:Windows>,${RESOURCE_FILES},>)
