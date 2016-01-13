#include "sj_timers.h"

#include <stdlib.h>

#include "sj_v7_ext.h"

/* Currently can only handle one timer */
static enum v7_err global_set_timeout(struct v7 *v7, v7_val_t *res) {
  v7_val_t *cb;
  v7_val_t msecsv = v7_arg(v7, 1);
  int msecs;
  (void) res;

  cb = (v7_val_t *) malloc(sizeof(*cb));
  v7_own(v7, cb);
  *cb = v7_arg(v7, 0);

  if (!v7_is_callable(v7, *cb)) {
    printf("cb is not a function\n");
  } else if (!v7_is_number(msecsv)) {
    printf("msecs is not a double\n");
  } else {
    msecs = v7_to_number(msecsv);

    sj_set_timeout(msecs, cb);
  }

  return V7_OK;
}

void sj_init_timers(struct v7 *v7) {
  v7_set_method(v7, v7_get_global(v7), "setTimeout", global_set_timeout);
}
