#include "../include/sprk.h"
#include "sprk_ctx_private.h"
#include "executor.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    broker_t *broker = broker_new (
        "ipc://contexts.ipc", "ipc://executors.ipc");
    pthread_t broker_thread = broker_run_in_thread (&broker);

    zactor_t *executor = zactor_new (executor_actor, NULL);
    zstr_send (executor, "START");
    zsock_wait (executor);

    sprk_ctx_t *ctx = sprk_ctx_new("ipc://contexts.ipc");
    sprk_dataset_t *dataset = sprk_ctx_load_dense (ctx, "/tmp/gen.dat", 400);
    sleep (3);

    pthread_cancel (broker_thread);
    pthread_join (broker_thread, NULL);
    sprk_dataset_destroy (&dataset);
    zactor_destroy (&executor);
    sprk_ctx_destroy(&ctx);
}
