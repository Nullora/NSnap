# NSnap
This tool takes all your projects and lists their functions. It is made for personal use so im not gonna spend too much time on this README.
# Usage
- build it with NUB or make your own makefile.
- copy the binary into /usr/local/bin
- run nsnap in any project you wish to apply it on.
- it will create a file for you, populate it with:
```c
filename = ~/path/to/code
```
- then run: **nsnap list filename**. This will list all the functions you have in that code wether its cpp, c, python...
- run: **nsnap get <function_name>**. This prints the full function directly in your terminal, stopping you from opening the project and manually copying it.
# Specifications
- To properly use this, each target file must be labeled beforehand. see example:
```c
//& HelloWorld
void HelloWorld(){
cout<<"hello world \n";
}
//!
```
Before each function, add: **//& funcname**, **MAKE SURE TO INCLUDE THE SPACE BETWEEN //& AND THE ACTUAL NAME**. After each function, add: **//!** to indicate function end. You can't use this on any foreign code base unless you took time to annotate each and every function..
- now if i run **nsnap list <filename>** on the file where HelloWorld() is, the function will be listed.
- **nsnap get HelloWorld** will return the full function.
# Note
Its a neat little shortcut i made and its poorly documented. If you truly think it might help you, check the code and learn how to use it. I made it for pure personal use and just posted it for fun.
