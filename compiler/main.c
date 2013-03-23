#include "main.h"

int main(int argc, const char *argv[])
{
	LLVMContextRef mainContext = LLVMGetGlobalContext();
	LLVMModuleRef mainModule = LLVMModuleCreateWithNameInContext("main", mainContext);

	if (argc <= 1) {
		free(mainModule);
		free(mainContext);
		printf("Usage:\n\tlol2 [-flags] filename\n\t\t-i\tInterpret the file\n\t\t-c\tCompile the file\n");
		exit(0);
	}


	LLVMDumpModule(mainModule);

	return 0;
}
