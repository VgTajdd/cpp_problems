set VS2019AUXBUILD=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\

@call "%VS2019AUXBUILD%vcvarsall.bat" x64 %*
@call nmake