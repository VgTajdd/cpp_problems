set VS2017AUXBUILD=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\

@call "%VS2017AUXBUILD%vcvarsall.bat" x64 %*
@call nmake
@call app.exe