@ECHO OFF

ECHO ###
ECHO ###     build for chat program
ECHO ###	author: Sam Shao 
ECHO ###     email: samshao1111@126.com
ECHO ###
ECHO ###
ECHO ###     CC	= g++ 
ECHO ###     BOOST_INCLUDE=-Id:\WorkProject\boost\include\boost-1_64\
ECHO ###     BOOST_LIB_HOME=d:\workproject\boost\lib\
ECHO ###     BOOST_LIB  = libboost_thread-mgw63-mt-d-1_64.a libboost_system-mgw63-mt-d-1_64.a 


REM g++ -o threadtest.exe threadtest.o -Ld:\workproject\boost\lib\ -llibboost_thread-mgw63-mt-d-1_64 -llibboost_system-mgw63-mt-d-1_64 
REM g++ -o threadtest.exe threadtest.o d:\workproject\boost\lib\libboost_thread-mgw63-mt-d-1_64.a d:\workproject\boost\lib\libboost_system-mgw63-mt-d-1_64.a 
REM g++  -g -Id:\WorkProject\boost\include\boost-1_64\ threadtest.cpp d:\workproject\boost\lib\libboost_thread-mgw63-mt-d-1_64.a d:\workproject\boost\lib\libboost_system-mgw63-mt-d-1_64.a   -o threadtest.exe


set  CC=g++ 
set  BOOST_INCLUDE=-Id:\WorkProject\boost\include\boost-1_64\
set  BOOST_LIB_HOME=d:\workproject\boost\lib\
set  BOOST_LIB=%BOOST_LIB_HOME%libboost_thread-mgw63-mt-d-1_64.a %BOOST_LIB_HOME%libboost_system-mgw63-mt-d-1_64.a


:clean
del MulThreadRW.exe
	

:*.o
%CC% %BOOST_INCLUDE% -c MulThreadRW.cpp

@ECHO ON
:exe
%CC% -o MulThreadRW.exe MulThreadRW.o %BOOST_LIB%
