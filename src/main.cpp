#include <auv_sonar/Multilateration.hpp>

int main(int argc, char *argv[]) {
  Multilateration m;
  m.findAllIntersections();
  // m.findPinger();
  return 0;
}
