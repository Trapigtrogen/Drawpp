@echo off

set docs=OFF
set crt=OFF
set mode=Release
set plat=x64

if "%1"=="-f" goto update_modules

:query_docs
set "docs_q=n"
set /p "docs_q=Include documentation? (y/n): "

if "%docs_q%" == "y" set docs=ON & goto query_crt
if "%docs_q%" == "Y" set docs=ON & goto query_crt
if "%docs_q%" == "yes" set docs=ON & goto query_crt
if "%docs_q%" == "YES" set docs=ON & goto query_crt
if "%docs_q%" == "n" set docs=OFF & goto query_crt
if "%docs_q%" == "N" set docs=OFF & goto query_crt
if "%docs_q%" == "no" set docs=OFF & goto query_crt
if "%docs_q%" == "NO" set docs=OFF & goto query_crt
goto query_docs

:query_crt
set "crt_q=n"
set /p "crt_q=Use static crt? (y/n): "

if "%crt_q%" == "y" set crt=ON & goto query_debug
if "%crt_q%" == "Y" set crt=ON & goto query_debug
if "%crt_q%" == "yes" set crt=ON & goto query_debug
if "%crt_q%" == "YES" set crt=ON & goto query_debug
if "%crt_q%" == "n" set crt=OFF & goto query_debug
if "%crt_q%" == "N" set crt=OFF & goto query_debug
if "%crt_q%" == "no" set crt=OFF & goto query_debug
if "%crt_q%" == "NO" set crt=OFF & goto query_debug
goto query_crt

:query_debug
set "dbg_q=n"
set /p "dbg_q=Debug build? (y/n): "

if "%dbg_q%" == "y" set mode=Debug & goto query_plat
if "%dbg_q%" == "Y" set mode=Debug & goto query_plat
if "%dbg_q%" == "yes" set mode=Debug & goto query_plat
if "%dbg_q%" == "YES" set mode=Debug & goto query_plat
if "%dbg_q%" == "n" set mode=Release & goto query_plat
if "%dbg_q%" == "N" set mode=Release & goto query_plat
if "%dbg_q%" == "no" set mode=Release & goto query_plat
if "%dbg_q%" == "NO" set mode=Release & goto query_plat
goto query_debug

:query_plat
set "plat_q=n"
set /p "plat_q=x86 build? (y/n): "

if "%plat_q%" == "y" set plat=win32 & goto update_modules
if "%plat_q%" == "Y" set plat=win32 & goto update_modules
if "%plat_q%" == "yes" set plat=win32 & goto update_modules
if "%plat_q%" == "YES" set plat=win32 & goto update_modules
if "%plat_q%" == "n" set plat=x64 & goto update_modules
if "%plat_q%" == "N" set plat=x64 & goto update_modules
if "%plat_q%" == "no" set plat=x64 & goto update_modules
if "%plat_q%" == "NO" set plat=x64 & goto update_modules
goto query_plat

:update_modules
git submodule update --init --recursive

if not exist release\_dpp_tmp_release_build mkdir release\_dpp_tmp_release_build

cd release\_dpp_tmp_release_build

cmake ..\.. -A %plat% -DDPP_BUILD_DOCS=OFF -DDPP_BUILD_TESTS=OFF -DDPP_BUILD_EXAMPLES=OFF

::use cmake to get msbuild path
mkdir .\vs_loc
cd .\vs_loc
echo cmake_minimum_required(VERSION 3.13.4)>CMakeLists.txt
echo file(WRITE loc_out ${CMAKE_MAKE_PROGRAM})>>CMakeLists.txt
echo message(FATAL_ERROR)>>CMakeLists.txt
cmake .
set /p msb=<loc_out
cd ..

::if static crt, find and replace every instance of 'DLL', in project files with a blank.
::only place where 'DLL' is present, is the RuntimeLibrary option, so this should not break anything.
::if any other subprojects are added, copy paste the for loop and replace the filename.
if %crt%==OFF goto skip_crt

setlocal enableextensions disabledelayedexpansion

set "glfwproj=external\glfw\src\glfw.vcxproj"

for /f "delims=" %%i in ('type "%glfwproj%" ^& break ^> "%glfwproj%" ') do (
	set "line=%%i"
	setlocal enabledelayedexpansion
	>>"%glfwproj%" echo(!line:DLL=!
	endlocal
)

set "gllibproj=Drawpp_tmp.vcxproj"

for /f "delims=" %%i in ('type "%gllibproj%" ^& break ^> "%gllibproj%" ') do (
	set "line=%%i"
	setlocal enabledelayedexpansion
	>>"%gllibproj%" echo(!line:DLL=!
	endlocal
)

endlocal

:skip_crt

"%msb%" Drawpp.sln /p:Configuration=%mode%

if %errorlevel%==0 goto success

echo "Build failed, aborting release generation"
cd ..
goto end

:success
cd ..
copy "_dpp_tmp_release_build\lib\Drawpp.lib" "Drawpp.lib"

if not exist include mkdir include
cd include
copy "..\..\include\application.hpp"    "application.hpp"
copy "..\..\include\color.hpp"          "color.hpp"
copy "..\..\include\hsbcolor.hpp"       "hsbcolor.hpp"
copy "..\..\include\colors.hpp"         "colors.hpp"
copy "..\..\include\drawpp.hpp"         "drawpp.hpp"
copy "..\..\include\graphics.hpp"       "graphics.hpp"
copy "..\..\include\image.hpp"          "image.hpp"
copy "..\..\include\keys.hpp"           "keys.hpp"
copy "..\..\include\matrix4.hpp"        "matrix4.hpp"
copy "..\..\include\noise.hpp"          "noise.hpp"
copy "..\..\include\random.hpp"         "random.hpp"
copy "..\..\include\shape.hpp"          "shape.hpp"
copy "..\..\include\vector3.hpp"        "vector3.hpp"
copy "..\..\include\font.hpp"           "font.hpp"
copy "..\..\include\path.hpp"           "path.hpp"
copy "..\..\include\constants.hpp"      "constants.hpp"
copy "..\..\include\filter.hpp"         "filter.hpp"

cd ..

if not exist examples mkdir examples

xcopy ..\examples examples /E /I /Y /Q

cd examples

::create CMakeLists for examples
echo cmake_minimum_required(VERSION 3.13.4)>CMakeLists.txt
echo set(CMAKE_CXX_STANDARD 11)>>CMakeLists.txt
echo set(CMAKE_CXX_STANDARD_REQUIRED ON)>>CMakeLists.txt
echo set(CMAKE_GENERATOR_PLATFORM %plat%)>>CMakeLists.txt
echo project(Drawpp_Examples)>>CMakeLists.txt
echo set(CMAKE_CONFIGURATION_TYPES %mode%)>>CMakeLists.txt
echo link_libraries(${CMAKE_SOURCE_DIR}/../Drawpp.lib)>>CMakeLists.txt

if %crt%==OFF goto dll_crt

echo set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")>>CMakeLists.txt
echo set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")>>CMakeLists.txt

if %mode%==Release echo link_libraries(libcmt.lib)>>CMakeLists.txt & goto end_crt
echo link_libraries(libcmtd.lib)>>CMakeLists.txt
goto end_crt

:dll_crt
echo set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")>>CMakeLists.txt
echo set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")>>CMakeLists.txt

if %mode%==Release echo link_libraries(msvcrt.lib)>>CMakeLists.txt & goto end_crt
echo link_libraries(msvcrtd.lib)>>CMakeLists.txt

:end_crt

echo include_directories(${CMAKE_SOURCE_DIR}/../include)>>CMakeLists.txt
echo set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)>>CMakeLists.txt
::add example files here like this
echo add_executable(example_buttons example_buttons.cpp)>>CMakeLists.txt
echo add_executable(example_de-jong-attractor example_de-jong-attractor.cpp)>>CMakeLists.txt
echo add_executable(example_color_mousewheel example_color_mousewheel.cpp)>>CMakeLists.txt
echo add_executable(example_draw example_draw.cpp)>>CMakeLists.txt

echo set_property(TARGET>>CMakeLists.txt

::add example names here to change working dir
echo example_buttons>>CMakeLists.txt
echo example_de-jong-attractor>>CMakeLists.txt
echo example_color_mousewheel>>CMakeLists.txt
echo example_draw>>CMakeLists.txt

echo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")>>CMakeLists.txt

::set button example to be the startup project
echo set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example_buttons)>>CMakeLists.txt

cd ..

if %docs%==OFF goto end

if not exist _dpp_tmp_docs_build mkdir _dpp_tmp_docs_build
cd _dpp_tmp_docs_build

echo cmake_minimum_required(VERSION 3.13.4)>CMakeLists.txt
echo project(Drawpp_Examples_Docs)>>CMakeLists.txt
echo find_package(Doxygen)>>CMakeLists.txt
echo if (DOXYGEN_FOUND)>>CMakeLists.txt
echo set(DOXYGEN_ALWAYS_DETAILED_SEC YES)>>CMakeLists.txt
echo set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)>>CMakeLists.txt
echo set(doxyfile ${CMAKE_BINARY_DIR}/doxyfile)>>CMakeLists.txt
echo set(DOXYGEN_OUTPUT_DIRECTORY ./docs)>>CMakeLists.txt
echo doxygen_add_docs(doxygen ALL ${CMAKE_SOURCE_DIR}/../include)>>CMakeLists.txt
echo elseif(NOT DOXYGEN_FOUND)>>CMakeLists.txt
echo message(SEND_ERROR "Doxygen executable not found")>>CMakeLists.txt
echo endif (DOXYGEN_FOUND)>>CMakeLists.txt

cmake .

"%msb%" Drawpp_Examples_Docs.sln

cd ..
xcopy _dpp_tmp_docs_build\docs docs /E /I /Y /Q
rmdir _dpp_tmp_docs_build /s /q

:end
rmdir _dpp_tmp_release_build /s /q