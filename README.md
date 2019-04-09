# UnitTestNoStdLibPkg
This is an EDK2 package that ports the embUnit unit test framework into the EDK2 and includes a small sample.

This is not a true init test framework as it is not performed host side. 
The number of mocks needed for even the base UEFI API is a very large task for one person let alone a team. 
However, a test can be run from the shell of a system that matches the the target archetecture of the compiled binary.
This project seems laregly like a dead end now but it's left here for reference as it might prove useful in the future. 
