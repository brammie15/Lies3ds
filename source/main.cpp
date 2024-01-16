#include "../include/Engine/Core.h"

int main(int argc, char *args[]) {
  srand(time(NULL));

  Initialize();

  Run();

  Cleanup();

  return 0;
}