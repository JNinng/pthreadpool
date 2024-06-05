#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <pthreadpool.h>

struct array_addition_context {
	double *augend;
	double *addend;
	double *sum;
};

static void add_arrays(struct array_addition_context* context, size_t i) {
	context->sum[i] = context->augend[i] + context->addend[i];
	printf("arrays: %lld\n", (long long)i);
}

#define ARRAY_SIZE 20

int main() {
	double augend[ARRAY_SIZE] = { 0 };
	double addend[ARRAY_SIZE] = { 0};
	double sum[ARRAY_SIZE] = {0};

	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		augend[i] = i;
		addend[i] = i;
	}

	pthreadpool_t threadpool = pthreadpool_create(0);
	assert(threadpool != NULL);

	const size_t threads_count = pthreadpool_get_threads_count(threadpool);
	printf("Created thread pool with %zu threads\n", threads_count);

	struct array_addition_context context = { augend, addend, sum };
	pthreadpool_parallelize_1d(threadpool,
		(pthreadpool_task_1d_t) add_arrays,
		(void**) &context,
		ARRAY_SIZE,
		PTHREADPOOL_FLAG_DISABLE_DENORMALS /* flags */);

	pthreadpool_destroy(threadpool);
	threadpool = NULL;

	for (size_t i = 1; i < ARRAY_SIZE; i++)
	{
		printf("%2.0f ", augend[i]);
	}
	printf("\n");
	for (size_t i = 1; i < ARRAY_SIZE; i++)
	{
		printf("%2.0f ", addend[i]);
	}
	printf("\n");
	for (size_t i = 1; i < ARRAY_SIZE; i++)
	{
		printf("%2.0f ", sum[i]);
	}

	return 0;
}
