#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <sys/capsicum.h>
#include "capsicumize.h"

static bool
limit_rights_on_file(FILE* file, unsigned long long right, const char* error_msg) {
  cap_rights_t rights;
  cap_rights_init(&rights, right);
  if (cap_rights_limit(fileno(file), &rights) < 0 && errno != ENOSYS) {
    err(1, "%s", error_msg);
    return false;
  }
  return true;
}

static bool
limit_rights(void) {
  if(cap_enter() < 0 && errno != ENOSYS) {
    err(1, "Unable to enter capability mode.");
    return false;
  }
  return true;
}

bool
capsicumize(void) {
  return limit_rights_on_file(
       stdin,
       CAP_READ,
       "Unable to limit rights for stdin.") &&
    limit_rights_on_file(
       stdout,
       CAP_WRITE,
       "Unable to limit rights for stdout.") &&
    limit_rights();
}
