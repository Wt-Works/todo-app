#include "ToDoApp.h"

#include <stdlib.h>

using namespace Wt;
using namespace Wt::Dbo;

WApplication *createApplication(const WEnvironment &env)
{
  return new ToDoApp(env);
}

int main(int argc, char **argv)
{
  srand(time(0));

  return WRun(argc, argv, &createApplication);
}
