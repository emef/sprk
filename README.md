### sprk

light-weight implementation of distributed data processing ala apache
spark.

```c
sprk_ctx_t *context = sprk_ctx_new();
sprk_dataset_t *dataset = sprk_dataset_new(context, "pathlist");

sprk_dataset_mul(dataset, 2);
sprk_dataset_checkpoint(dataset);  // evaluate and cache dataset
double sum = sprk_dataset_sum(dataset); // only has to perform sum
double sum2 = sprk_dataset_sum(dataset); // only has to perform sum

sprk_dataset_destroy(dataset);
sprk_ctx_destroy(context);

```

sprk_ctx_t *context = sprk_ctx_new();
  - get list of executor hostnames/ports
  - create mapping of executor-id -> hostname:port
  - maintain this list as clients join cluster and disconnect
  - this context will manage all communication to executors
    - e.g. assign_block(block_t) -> executor-id

sprk_dataset_t *dataset = sprk_dataset_new(context, "pathlist");
  - create a dataset-id
  - parse pathlist into paths
  - break paths into blocks (id, path, offset, length)

sprk_dataset_mul(dataset, 2);
  - append mul(2) transformation to all blocks in dataset

sprk_dataset_checkpoint(dataset);
  - causes a resolution of transformations in executors
  - blocking
  - broadcast (block-id, new-block-id, transformations)
    - only broadcast blocks which we know have been assigned
  - executors are subscribed to block-ids they own
  - executors accept the transformation work and send an ack
  - context receives acks that work was received
  - for block-ids that were not acked, then context.assign_block(new_block)
  - context.assign_block() all blocks which have never been assigned

double sum = sprk_dataset_sum(dataset);
  - causes sum compututations in executors
  - blocking
  - broadcast (dataset-id, sum())
  - executors ack when they accept the work
  - for block-ids that were not acked, then
    context.assign_block_with_computation(block, sum())
  - subscribe to (block-id, sum(), result) messages
  - aggregate as results come in
  - when all blocks accounted for, return.
