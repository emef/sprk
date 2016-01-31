@ECHO OFF
ECHO Generating native JNI headers...
IF EXIST ..\..\..\src\native\include\org_zeromq_sprk_SprkCtx.h GOTO HAVE_SprkCtx
"%JAVA_HOME%\bin\javah.exe" -d ..\..\..\src\native\include -classpath ..\..\..\src\main\java org.zeromq.sprk.SprkCtx
:HAVE_SprkCtx
IF EXIST ..\..\..\src\native\include\org_zeromq_sprk_SprkDataset.h GOTO HAVE_SprkDataset
"%JAVA_HOME%\bin\javah.exe" -d ..\..\..\src\native\include -classpath ..\..\..\src\main\java org.zeromq.sprk.SprkDataset
:HAVE_SprkDataset
