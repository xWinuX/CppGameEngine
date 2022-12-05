#include "src/Application.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

//------------------------------
// glfw: whenever the window size changed (by OS or user resize input) this callback function executes
//------------------------------

int main()
{
    const Application application = Application();
    application.Run();
    
    return 0;
}
