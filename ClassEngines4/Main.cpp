#include <SDL.h>
#include "CoreEngine.h"
#include "Game1.h"



int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("Game 258 engine",800,600)) {
		Debug::FatalError("Failed to initialize engine", "CoreEngine.cpp", __LINE__);
		return 0;
	}
	CoreEngine::GetInstance()->run();

	return 0;
}


