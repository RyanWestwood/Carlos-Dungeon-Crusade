cd ../
set working_dir=%cd%
set library_binaries=%working_dir%/library_binaries
set cmake="cmake"
set ctest="ctest"
set generator="-G Visual Studio 17 2022"
set configuration="Release"

cd test
%cmake% %generator% -A x64 -DCMAKE_BUILD_TYPE=%configuration% -S ./ -B "build" -DCMAKE_PREFIX_PATH=%library_binaries%
%cmake% --build build --config %configuration% --parallel
cd build
%ctest% -C %configuration%
pause