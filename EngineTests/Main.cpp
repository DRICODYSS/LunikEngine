#pragma once
#pragma comment(lib, "Engine.lib")

#define TEST_ENTITY_COMPONENTS 1

#if TEST_ENTITY_COMPONENTS
#include "Tests/public/EngineTests/Test_EntityComponent.h" 
#endif



int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	EngineTests::Test_EntityComponent test;

	if (test.Init())
	{
		test.Run();
	}

	test.Shutdown();
	test.Print_result();

	return 0;
}