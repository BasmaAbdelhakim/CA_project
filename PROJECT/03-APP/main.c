#include "../../../04-lib/STD_TYPES.h"
#include "../../05-OS/SCHEDULER_interface.h"
#include "APP/APP.h"



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"



int main(int argc, char* argv[])
{
	APP_Init();

	SCHEDULER_Init();

	SCHEDULER_Start();
}




#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
