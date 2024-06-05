#ifndef PTHREADPOOL_H_
#define PTHREADPOOL_H_

#include <stddef.h>
#include <stdint.h>

typedef struct pthreadpool* pthreadpool_t;

// 定义各种维度的任务函数类型，用于不同维度的线程池并行化任务 每个函数类型接受一个上下文指针、一个索引和可选的线程ID或瓦片大小 1D至6D任务类型，以及它们的瓦片处理变体
typedef void (*pthreadpool_task_1d_t)(void*, size_t);
typedef void (*pthreadpool_task_1d_with_thread_t)(void*, size_t, size_t);
typedef void (*pthreadpool_task_1d_tile_1d_t)(void*, size_t, size_t);
typedef void (*pthreadpool_task_2d_t)(void*, size_t, size_t);
typedef void (*pthreadpool_task_2d_with_thread_t)(void*, size_t, size_t, size_t);
typedef void (*pthreadpool_task_2d_tile_1d_t)(void*, size_t, size_t, size_t);
typedef void (*pthreadpool_task_2d_tile_2d_t)(void*, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_t)(void*, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_1d_t)(void*, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_1d_with_thread_t)(void*, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_2d_t)(void*, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_4d_t)(void*, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_4d_tile_1d_t)(void*, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_4d_tile_2d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_5d_t)(void*, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_5d_tile_1d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_5d_tile_2d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_6d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_6d_tile_1d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_6d_tile_2d_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t, size_t, size_t);

typedef void (*pthreadpool_task_1d_with_id_t)(void*, uint32_t, size_t);
typedef void (*pthreadpool_task_2d_tile_1d_with_id_t)(void*, uint32_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_2d_tile_2d_with_id_t)(void*, uint32_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_1d_with_id_t)(void*, uint32_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_2d_with_id_t)(void*, uint32_t, size_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_4d_tile_2d_with_id_t)(void*, uint32_t, size_t, size_t, size_t, size_t, size_t, size_t);

typedef void (*pthreadpool_task_2d_tile_1d_with_id_with_thread_t)(void*, uint32_t, size_t, size_t, size_t, size_t);
typedef void (*pthreadpool_task_3d_tile_1d_with_id_with_thread_t)(void*, uint32_t, size_t, size_t, size_t, size_t, size_t);

/**
 * 在计算期间，尽可能最大限度地禁用对非规范化数字的支持。
 *
 * 处理非规范化浮点数通常在微代码中实现，并会导致显著的性能下降。
 这个提示指示线程池在运行计算之前，通过操作特定于架构的控制寄存器来禁用对非规范化数字的支持，
 并在计算完成后恢复控制寄存器的初始值。
 线程池会临时在所有参与计算的线程上禁用非规范化数字（即调用线程和潜在的工作线程）。
 *
 * 禁用非规范化数字可能会对结果的准确性产生轻微的负面影响。
 由于不同架构在控制非规范化数字处理方面的能力不同，使用此标志也可能损害结果在不同指令集架构间的可重复性。
 */
#define PTHREADPOOL_FLAG_DISABLE_DENORMALS 0x00000001

 /**
  * 操作完成后，将工作线程让给系统调度器。
  *
  * 强制工作线程在处理完此命令后，使用内核等待（而不是默认的主动自旋等待）来等待新命令。
  此标志仅影响此线程池的立即下一个操作。要使线程池始终使用内核等待，请将此标志传递给所有并行化函数。
  */
#define PTHREADPOOL_FLAG_YIELD_WORKERS 0x00000002

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 创建一个具有指定线程数量的线程池。
	 *
	 * @param  threads_count  线程池中的线程数量。
	 *    值为0具有特殊解释：它创建一个线程池，线程数量与系统中的逻辑处理器数量相同。
	 *
	 * @returns  如果调用成功，返回指向不透明线程池对象的指针；如果调用失败，返回NULL指针。
	 */
	pthreadpool_t pthreadpool_create(size_t threads_count);

	/**
	 * 查询线程池中的线程数量。
	 *
	 * @param  threadpool  要查询的线程池。
	 *
	 * @returns  线程池中的线程数量。
	 */
	size_t pthreadpool_get_threads_count(pthreadpool_t threadpool);

	/**
	 * 在一维网格上处理项目。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, i);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个项目要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range       要处理的一维网格上的项目数量。指定的函数将为每个项目调用一次。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_t function,
		void* context,
		size_t range,
		uint32_t flags);

	/**
	 * 在一维网格上处理项目，并传递当前线程ID。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, thread_index, i);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个项目要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range       要处理的一维网格上的项目数量。指定的函数将为每个项目调用一次。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_1d_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_with_thread_t function,
		void* context,
		size_t range,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数在一维网格上处理项目。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, uarch_index, i);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个项目要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range                要处理的一维网格上的项目数量。指定的函数将为每个项目调用一次。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_1d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range,
		uint32_t flags);

	/**
	 * 使用指定的最大瓦片大小在一维网格上处理项目。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range; i += tile)
	 *     function(context, i, min(range - i, tile));
	 *
	 * 当调用返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range       要处理的一维网格上的项目数量。
	 * @param tile        一次函数调用中要处理的一维网格上的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_1d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_tile_1d_t function,
		void* context,
		size_t range,
		size_t tile,
		uint32_t flags);

	/**
	 * 在二维网格上处理项目。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       function(context, i, j);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个项目要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     二维网格的第一个维度上要处理的项目数量。
	 * @param range_j     二维网格的第二个维度上要处理的项目数量。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		uint32_t flags);

	/**
	 * 在二维网格上处理项目，并传递当前线程ID。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       function(context, thread_index, i, j);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个项目要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     二维网格第一个维度上要处理的项目数量。
	 * @param range_j     二维网格第二个维度上要处理的项目数量。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_with_thread_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		uint32_t flags);

	/**
	 * 在二维网格上处理项目，并指定最后一个网格维度的最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, i, j, min(range_j - j, tile_j));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     二维网格第一个维度上要处理的项目数量。
	 * @param range_j     二维网格第二个维度上要处理的项目数量。
	 * @param tile_j      一次函数调用中二维网格第二个维度上要处理的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_tile_1d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t tile_j,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数，在二维网格上处理项目，并指定最后一个网格维度的最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, i, j, min(range_j - j, tile_j));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个瓦片要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range_i              二维网格第一个维度上要处理的项目数量。
	 * @param range_j              二维网格第二个维度上要处理的项目数量。
	 * @param tile_j               一次函数调用中二维网格第二个维度上要处理的最大项目数。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_tile_1d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_tile_1d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t tile_j,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数，在二维网格上处理项目，并指定最后一个网格维度的最大瓦片大小，同时传递当前线程ID。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, thread_index, i, j, min(range_j - j, tile_j));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个瓦片要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range_i              二维网格第一个维度上要处理的项目数量。
	 * @param range_j              二维网格第二个维度上要处理的项目数量。
	 * @param tile_j               一次函数调用中二维网格第二个维度上要处理的最大项目数。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_tile_1d_with_uarch_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_tile_1d_with_id_with_thread_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t tile_j,
		uint32_t flags);

	/**
	 * 在二维网格上处理项目，并为每个网格维度指定最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i += tile_i)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, i, j,
	 *         min(range_i - i, tile_i), min(range_j - j, tile_j));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     二维网格第一个维度上要处理的项目数量。
	 * @param range_j     二维网格第二个维度上要处理的项目数量。
	 * @param tile_i      一次函数调用中二维网格第一个维度上要处理的最大项目数。
	 * @param tile_j      一次函数调用中二维网格第二个维度上要处理的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_tile_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_tile_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t tile_i,
		size_t tile_j,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数，在二维网格上处理项目，并为每个网格维度指定最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i += tile_i)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, i, j,
	 *         min(range_i - i, tile_i), min(range_j - j, tile_j));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个瓦片要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range_i              二维网格第一个维度上要处理的项目数量。
	 * @param range_j              二维网格第二个维度上要处理的项目数量。
	 * @param tile_i               一次函数调用中二维网格第一个维度上要处理的最大项目数。
	 * @param tile_j               一次函数调用中二维网格第二个维度上要处理的最大项目数。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_2d_tile_2d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_tile_2d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t tile_i,
		size_t tile_j,
		uint32_t flags);

	/**
	 * 在三维网格上处理项目。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         function(context, i, j, k);
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个项目要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     三维网格第一个维度上要处理的项目数量。
	 * @param range_j     三维网格第二个维度上要处理的项目数量。
	 * @param range_k     三维网格第三个维度上要处理的项目数量。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_3d(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		uint32_t flags);

	/**
	 * 在三维网格上处理项目，并指定最后一个网格维度的最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, i, j, k, min(range_k - k, tile_k));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     三维网格第一个维度上要处理的项目数量。
	 * @param range_j     三维网格第二个维度上要处理的项目数量。
	 * @param range_k     三维网格第三个维度上要处理的项目数量。
	 * @param tile_k      一次函数调用中三维网格第三个维度上要处理的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_3d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_1d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_k,
		uint32_t flags);

	/**
	 * 在三维网格上处理项目，并指定最后一个网格维度的最大瓦片大小，同时传递当前线程ID。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, thread_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     三维网格第一个维度上要处理的项目数量。
	 * @param range_j     三维网格第二个维度上要处理的项目数量。
	 * @param range_k     三维网格第三个维度上要处理的项目数量。
	 * @param tile_k      一次函数调用中三维网格第三个维度上要处理的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_3d_tile_1d_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_1d_with_thread_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_k,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数，在三维网格上处理项目，并指定最后一个网格维度的最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, uarch_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个瓦片要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range_i              三维网格第一个维度上要处理的项目数量。
	 * @param range_j              三维网格第二个维度上要处理的项目数量。
	 * @param range_k              三维网格第三个维度上要处理的项目数量。
	 * @param tile_k               一次函数调用中三维网格第三个维度上要处理的最大项目数。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_3d_tile_1d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_1d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_k,
		uint32_t flags);

	/**
	 * 使用微架构感知的任务函数，在三维网格上处理项目，并指定最后一个网格维度的最大瓦片大小，同时传递当前线程ID。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, uarch_index, thread_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool           用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function             对于每个瓦片要调用的函数。
	 * @param context              传递给指定函数的第一个参数。
	 * @param default_uarch_index  当pthreadpool未配置cpuinfo，cpuinfo初始化失败，或cpuinfo_get_current_uarch_index()返回的索引超过max_uarch_index值时使用的微架构索引。
	 * @param max_uarch_index      指定函数预期的最大微架构索引。如果cpuinfo_get_current_uarch_index()返回的索引超过此值，则将使用default_uarch_index。default_uarch_index可以超过max_uarch_index。
	 * @param range_i              三维网格第一个维度上要处理的项目数量。
	 * @param range_j              三维网格第二个维度上要处理的项目数量。
	 * @param range_k              三维网格第三个维度上要处理的项目数量。
	 * @param tile_k               一次函数调用中三维网格第三个维度上要处理的最大项目数。
	 * @param flags                一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_3d_tile_1d_with_uarch_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_1d_with_id_with_thread_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_k,
		uint32_t flags);

	/**
	 * Process items on a 3D grid with the specified maximum tile size along the
	 * last two grid dimensions.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, i, j, k,
	 *           min(range_j - j, tile_j), min(range_k - k, tile_k));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 3D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 3D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 3D grid.
	 * @param tile_j      the maximum number of items along the second dimension of
	 *    the 3D grid to process in one function call.
	 * @param tile_k      the maximum number of items along the third dimension of
	 *    the 3D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_3d_tile_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_j,
		size_t tile_k,
		uint32_t flags);

	/**
	 * Process items on a 3D grid with the specified maximum tile size along the
	 * last two grid dimensions using a microarchitecture-aware task function.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, uarch_index, i, j, k,
	 *           min(range_j - j, tile_j), min(range_k - k, tile_k));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool           the thread pool to use for parallelisation. If
	 *    threadpool is NULL, all items are processed serially on the calling
	 *    thread.
	 * @param function             the function to call for each tile.
	 * @param context              the first argument passed to the specified
	 *    function.
	 * @param default_uarch_index  the microarchitecture index to use when
	 *    pthreadpool is configured without cpuinfo, cpuinfo initialization failed,
	 *    or index returned by cpuinfo_get_current_uarch_index() exceeds the
	 *    max_uarch_index value.
	 * @param max_uarch_index      the maximum microarchitecture index expected by
	 *    the specified function. If the index returned by
	 *    cpuinfo_get_current_uarch_index() exceeds this value, default_uarch_index
	 *    will be used instead. default_uarch_index can exceed max_uarch_index.
	 * @param range_i              the number of items to process along the first
	 *    dimension of the 3D grid.
	 * @param range_j              the number of items to process along the second
	 *    dimension of the 3D grid.
	 * @param range_k              the number of items to process along the third
	 *    dimension of the 3D grid.
	 * @param tile_j               the maximum number of items along the second
	 *    dimension of the 3D grid to process in one function call.
	 * @param tile_k               the maximum number of items along the third
	 *    dimension of the 3D grid to process in one function call.
	 * @param flags                a bitwise combination of zero or more optional
	 *    flags (PTHREADPOOL_FLAG_DISABLE_DENORMALS or
	 *    PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_3d_tile_2d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_3d_tile_2d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_j,
		size_t tile_k,
		uint32_t flags);

	/**
	 * Process items on a 4D grid.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           function(context, i, j, k, l);
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 4D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 4D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 4D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 4D grid.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_4d(
		pthreadpool_t threadpool,
		pthreadpool_task_4d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		uint32_t flags);

	/**
	 * Process items on a 4D grid with the specified maximum tile size along the
	 * last grid dimension.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l += tile_l)
	 *           function(context, i, j, k, l, min(range_l - l, tile_l));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 4D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 4D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 4D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 4D grid.
	 * @param tile_l      the maximum number of items along the fourth dimension of
	 *    the 4D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_4d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_4d_tile_1d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t tile_l,
		uint32_t flags);

	/**
	 * Process items on a 4D grid with the specified maximum tile size along the
	 * last two grid dimensions.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         for (size_t l = 0; l < range_l; l += tile_l)
	 *           function(context, i, j, k, l,
	 *             min(range_k - k, tile_k), min(range_l - l, tile_l));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 4D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 4D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 4D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 4D grid.
	 * @param tile_k      the maximum number of items along the third dimension of
	 *    the 4D grid to process in one function call.
	 * @param tile_l      the maximum number of items along the fourth dimension of
	 *    the 4D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_4d_tile_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_4d_tile_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t tile_k,
		size_t tile_l,
		uint32_t flags);

	/**
	 * Process items on a 4D grid with the specified maximum tile size along the
	 * last two grid dimensions using a microarchitecture-aware task function.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         for (size_t l = 0; l < range_l; l += tile_l)
	 *           function(context, uarch_index, i, j, k, l,
	 *             min(range_k - k, tile_k), min(range_l - l, tile_l));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool           the thread pool to use for parallelisation. If
	 *    threadpool is NULL, all items are processed serially on the calling
	 *    thread.
	 * @param function             the function to call for each tile.
	 * @param context              the first argument passed to the specified
	 *    function.
	 * @param default_uarch_index  the microarchitecture index to use when
	 *    pthreadpool is configured without cpuinfo, cpuinfo initialization failed,
	 *    or index returned by cpuinfo_get_current_uarch_index() exceeds the
	 *    max_uarch_index value.
	 * @param max_uarch_index      the maximum microarchitecture index expected by
	 *    the specified function. If the index returned by
	 *    cpuinfo_get_current_uarch_index() exceeds this value, default_uarch_index
	 *    will be used instead. default_uarch_index can exceed max_uarch_index.
	 * @param range_i              the number of items to process along the first
	 *    dimension of the 4D grid.
	 * @param range_j              the number of items to process along the second
	 *    dimension of the 4D grid.
	 * @param range_k              the number of items to process along the third
	 *    dimension of the 4D grid.
	 * @param range_l              the number of items to process along the fourth
	 *    dimension of the 4D grid.
	 * @param tile_k               the maximum number of items along the third
	 *    dimension of the 4D grid to process in one function call.
	 * @param tile_l               the maximum number of items along the fourth
	 *    dimension of the 4D grid to process in one function call.
	 * @param flags                a bitwise combination of zero or more optional
	 *    flags (PTHREADPOOL_FLAG_DISABLE_DENORMALS or
	 *    PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_4d_tile_2d_with_uarch(
		pthreadpool_t threadpool,
		pthreadpool_task_4d_tile_2d_with_id_t function,
		void* context,
		uint32_t default_uarch_index,
		uint32_t max_uarch_index,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t tile_k,
		size_t tile_l,
		uint32_t flags);

	/**
	 * Process items on a 5D grid.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           for (size_t m = 0; m < range_m; m++)
	 *             function(context, i, j, k, l, m);
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 5D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 5D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 5D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 5D grid.
	 * @param range_m     the number of items to process along the fifth dimension
	 *    of the 5D grid.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_5d(
		pthreadpool_t threadpool,
		pthreadpool_task_5d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		uint32_t flags);

	/**
	 * Process items on a 5D grid with the specified maximum tile size along the
	 * last grid dimension.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           for (size_t m = 0; m < range_m; m += tile_m)
	 *             function(context, i, j, k, l, m, min(range_m - m, tile_m));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 5D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 5D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 5D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 5D grid.
	 * @param range_m     the number of items to process along the fifth dimension
	 *    of the 5D grid.
	 * @param tile_m      the maximum number of items along the fifth dimension of
	 *    the 5D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_5d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_5d_tile_1d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		size_t tile_m,
		uint32_t flags);

	/**
	 * Process items on a 5D grid with the specified maximum tile size along the
	 * last two grid dimensions.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l += tile_l)
	 *           for (size_t m = 0; m < range_m; m += tile_m)
	 *             function(context, i, j, k, l, m,
	 *               min(range_l - l, tile_l), min(range_m - m, tile_m));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 5D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 5D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 5D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 5D grid.
	 * @param range_m     the number of items to process along the fifth dimension
	 *    of the 5D grid.
	 * @param tile_l      the maximum number of items along the fourth dimension of
	 *    the 5D grid to process in one function call.
	 * @param tile_m      the maximum number of items along the fifth dimension of
	 *    the 5D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_5d_tile_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_5d_tile_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		size_t tile_l,
		size_t tile_m,
		uint32_t flags);

	/**
	 * Process items on a 6D grid.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           for (size_t m = 0; m < range_m; m++)
	 *             for (size_t n = 0; n < range_n; n++)
	 *               function(context, i, j, k, l, m, n);
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 6D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 6D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 6D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 6D grid.
	 * @param range_m     the number of items to process along the fifth dimension
	 *    of the 6D grid.
	 * @param range_n     the number of items to process along the sixth dimension
	 *    of the 6D grid.
	 * @param tile_n      the maximum number of items along the sixth dimension of
	 *    the 6D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_6d(
		pthreadpool_t threadpool,
		pthreadpool_task_6d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		size_t range_n,
		uint32_t flags);

	/**
	 * Process items on a 6D grid with the specified maximum tile size along the
	 * last grid dimension.
	 *
	 * The function implements a parallel version of the following snippet:
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           for (size_t m = 0; m < range_m; m++)
	 *             for (size_t n = 0; n < range_n; n += tile_n)
	 *               function(context, i, j, k, l, m, n, min(range_n - n, tile_n));
	 *
	 * When the function returns, all items have been processed and the thread pool
	 * is ready for a new task.
	 *
	 * @note If multiple threads call this function with the same thread pool, the
	 *    calls are serialized.
	 *
	 * @param threadpool  the thread pool to use for parallelisation. If threadpool
	 *    is NULL, all items are processed serially on the calling thread.
	 * @param function    the function to call for each tile.
	 * @param context     the first argument passed to the specified function.
	 * @param range_i     the number of items to process along the first dimension
	 *    of the 6D grid.
	 * @param range_j     the number of items to process along the second dimension
	 *    of the 6D grid.
	 * @param range_k     the number of items to process along the third dimension
	 *    of the 6D grid.
	 * @param range_l     the number of items to process along the fourth dimension
	 *    of the 6D grid.
	 * @param range_m     the number of items to process along the fifth dimension
	 *    of the 6D grid.
	 * @param range_n     the number of items to process along the sixth dimension
	 *    of the 6D grid.
	 * @param tile_n      the maximum number of items along the sixth dimension of
	 *    the 6D grid to process in one function call.
	 * @param flags       a bitwise combination of zero or more optional flags
	 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
	 */
	void pthreadpool_parallelize_6d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_6d_tile_1d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		size_t range_n,
		size_t tile_n,
		uint32_t flags);

	/**
	 * 在六维网格上处理项目，并指定最后两个网格维度的最大瓦片大小。
	 *
	 * 该函数实现了以下代码片段的并行版本：
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         for (size_t l = 0; l < range_l; l++)
	 *           for (size_t m = 0; m < range_m; m += tile_m)
	 *             for (size_t n = 0; n < range_n; n += tile_n)
	 *               function(context, i, j, k, l, m, n,
	 *                 min(range_m - m, tile_m), min(range_n - n, tile_n));
	 *
	 * 当函数返回时，所有项目都已处理完毕，线程池已准备好接受新任务。
	 *
	 * @note 如果多个线程使用相同的线程池调用此函数，则这些调用将被序列化。
	 *
	 * @param threadpool  用于并行化的线程池。如果threadpool为NULL，则在调用线程上串行处理所有项目。
	 * @param function    对于每个瓦片要调用的函数。
	 * @param context     传递给指定函数的第一个参数。
	 * @param range_i     六维网格第一个维度上要处理的项目数量。
	 * @param range_j     六维网格第二个维度上要处理的项目数量。
	 * @param range_k     六维网格第三个维度上要处理的项目数量。
	 * @param range_l     六维网格第四个维度上要处理的项目数量。
	 * @param range_m     六维网格第五个维度上要处理的项目数量。
	 * @param range_n     六维网格第六个维度上要处理的项目数量。
	 * @param tile_m      一次函数调用中六维网格第五个维度上要处理的最大项目数。
	 * @param tile_n      一次函数调用中六维网格第六个维度上要处理的最大项目数。
	 * @param flags       一个可选标志的按位组合（PTHREADPOOL_FLAG_DISABLE_DENORMALS 或 PTHREADPOOL_FLAG_YIELD_WORKERS）
	 */
	void pthreadpool_parallelize_6d_tile_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_6d_tile_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t range_m,
		size_t range_n,
		size_t tile_m,
		size_t tile_n,
		uint32_t flags);

	/**
	 * 终止线程池中的线程并释放相关资源。
	 *
	 * @warning 在调用此函数后访问线程池将导致未定义行为，并可能导致数据损坏。
	 *
	 * @param[in,out]  threadpool  要销毁的线程池。
	 */
	void pthreadpool_destroy(pthreadpool_t threadpool);

#ifndef PTHREADPOOL_NO_DEPRECATED_API

	/* 兼容性API，用于与预先存在的用户兼容（例如 NNPACK） */
#if defined(__GNUC__)
#define PTHREADPOOL_DEPRECATED __attribute__((__deprecated__))
#else
#define PTHREADPOOL_DEPRECATED
#endif

	typedef void (*pthreadpool_function_1d_t)(void*, size_t);
	typedef void (*pthreadpool_function_1d_tiled_t)(void*, size_t, size_t);
	typedef void (*pthreadpool_function_2d_t)(void*, size_t, size_t);
	typedef void (*pthreadpool_function_2d_tiled_t)(void*, size_t, size_t, size_t, size_t);
	typedef void (*pthreadpool_function_3d_tiled_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t);
	typedef void (*pthreadpool_function_4d_tiled_t)(void*, size_t, size_t, size_t, size_t, size_t, size_t, size_t, size_t);

	void pthreadpool_compute_1d(
		pthreadpool_t threadpool,
		pthreadpool_function_1d_t function,
		void* argument,
		size_t range) PTHREADPOOL_DEPRECATED;

	void pthreadpool_compute_1d_tiled(
		pthreadpool_t threadpool,
		pthreadpool_function_1d_tiled_t function,
		void* argument,
		size_t range,
		size_t tile) PTHREADPOOL_DEPRECATED;

	void pthreadpool_compute_2d(
		pthreadpool_t threadpool,
		pthreadpool_function_2d_t function,
		void* argument,
		size_t range_i,
		size_t range_j) PTHREADPOOL_DEPRECATED;

	void pthreadpool_compute_2d_tiled(
		pthreadpool_t threadpool,
		pthreadpool_function_2d_tiled_t function,
		void* argument,
		size_t range_i,
		size_t range_j,
		size_t tile_i,
		size_t tile_j) PTHREADPOOL_DEPRECATED;

	void pthreadpool_compute_3d_tiled(
		pthreadpool_t threadpool,
		pthreadpool_function_3d_tiled_t function,
		void* argument,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t tile_i,
		size_t tile_j,
		size_t tile_k) PTHREADPOOL_DEPRECATED;

	void pthreadpool_compute_4d_tiled(
		pthreadpool_t threadpool,
		pthreadpool_function_4d_tiled_t function,
		void* argument,
		size_t range_i,
		size_t range_j,
		size_t range_k,
		size_t range_l,
		size_t tile_i,
		size_t tile_j,
		size_t tile_k,
		size_t tile_l) PTHREADPOOL_DEPRECATED;

#endif /* PTHREADPOOL_NO_DEPRECATED_API */

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus

namespace libpthreadpool {
	namespace detail {
		namespace {
			template<class T>
			void call_wrapper_1d(void* arg, size_t i) {
				(*static_cast<const T*>(arg))(i);
			}

			template<class T>
			void call_wrapper_1d_tile_1d(void* arg, size_t range_i, size_t tile_i) {
				(*static_cast<const T*>(arg))(range_i, tile_i);
			}

			template<class T>
			void call_wrapper_2d(void* functor, size_t i, size_t j) {
				(*static_cast<const T*>(functor))(i, j);
			}

			template<class T>
			void call_wrapper_2d_tile_1d(void* functor,
				size_t i, size_t range_j, size_t tile_j)
			{
				(*static_cast<const T*>(functor))(i, range_j, tile_j);
			}

			template<class T>
			void call_wrapper_2d_tile_2d(void* functor,
				size_t range_i, size_t range_j,
				size_t tile_i, size_t tile_j)
			{
				(*static_cast<const T*>(functor))(range_i, range_j, tile_i, tile_j);
			}

			template<class T>
			void call_wrapper_3d(void* functor, size_t i, size_t j, size_t k) {
				(*static_cast<const T*>(functor))(i, j, k);
			}

			template<class T>
			void call_wrapper_3d_tile_1d(void* functor,
				size_t i, size_t j, size_t range_k,
				size_t tile_k)
			{
				(*static_cast<const T*>(functor))(i, j, range_k, tile_k);
			}

			template<class T>
			void call_wrapper_3d_tile_2d(void* functor,
				size_t i, size_t range_j, size_t range_k,
				size_t tile_j, size_t tile_k)
			{
				(*static_cast<const T*>(functor))(i, range_j, range_k, tile_j, tile_k);
			}

			template<class T>
			void call_wrapper_4d(void* functor, size_t i, size_t j, size_t k, size_t l) {
				(*static_cast<const T*>(functor))(i, j, k, l);
			}

			template<class T>
			void call_wrapper_4d_tile_1d(void* functor,
				size_t i, size_t j, size_t k, size_t range_l,
				size_t tile_l)
			{
				(*static_cast<const T*>(functor))(i, j, k, range_l, tile_l);
			}

			template<class T>
			void call_wrapper_4d_tile_2d(void* functor,
				size_t i, size_t j, size_t range_k, size_t range_l,
				size_t tile_k, size_t tile_l)
			{
				(*static_cast<const T*>(functor))(i, j, range_k, range_l, tile_k, tile_l);
			}

			template<class T>
			void call_wrapper_5d(void* functor, size_t i, size_t j, size_t k, size_t l, size_t m) {
				(*static_cast<const T*>(functor))(i, j, k, l, m);
			}

			template<class T>
			void call_wrapper_5d_tile_1d(void* functor,
				size_t i, size_t j, size_t k, size_t l, size_t range_m,
				size_t tile_m)
			{
				(*static_cast<const T*>(functor))(i, j, k, l, range_m, tile_m);
			}

			template<class T>
			void call_wrapper_5d_tile_2d(void* functor,
				size_t i, size_t j, size_t k, size_t range_l, size_t range_m,
				size_t tile_l, size_t tile_m)
			{
				(*static_cast<const T*>(functor))(i, j, k, range_l, range_m, tile_l, tile_m);
			}

			template<class T>
			void call_wrapper_6d(void* functor, size_t i, size_t j, size_t k, size_t l, size_t m, size_t n) {
				(*static_cast<const T*>(functor))(i, j, k, l, m, n);
			}

			template<class T>
			void call_wrapper_6d_tile_1d(void* functor,
				size_t i, size_t j, size_t k, size_t l, size_t m, size_t range_n,
				size_t tile_n)
			{
				(*static_cast<const T*>(functor))(i, j, k, l, m, range_n, tile_n);
			}

			template<class T>
			void call_wrapper_6d_tile_2d(void* functor,
				size_t i, size_t j, size_t k, size_t l, size_t range_m, size_t range_n,
				size_t tile_m, size_t tile_n)
			{
				(*static_cast<const T*>(functor))(i, j, k, l, range_m, range_n, tile_m, tile_n);
			}
		}  /* namespace */
	}  /* namespace detail */
}  /* namespace libpthreadpool */

/**
 * Process items on a 1D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range; i++)
 *     functor(i);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each item.
 * @param range       the number of items on the 1D grid to process. The
 *    specified functor will be called once for each item.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range,
		flags);
}

/**
 * Process items on a 1D grid with specified maximum tile size.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range; i += tile)
 *     functor(i, min(range - i, tile));
 *
 * When the call returns, all items have been processed and the thread pool is
 * ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool,
 *    the calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range       the number of items on the 1D grid to process.
 * @param tile        the maximum number of items on the 1D grid to process in
 *    one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_1d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range,
	size_t tile,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_1d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_1d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range,
		tile,
		flags);
}

/**
 * Process items on a 2D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       functor(i, j);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each item.
 * @param range_i     the number of items to process along the first dimension
 *    of the 2D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 2D grid.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		flags);
}

/**
 * Process items on a 2D grid with the specified maximum tile size along the
 * last grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j += tile_j)
 *       functor(i, j, min(range_j - j, tile_j));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 2D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 2D grid.
 * @param tile_j      the maximum number of items along the second dimension of
 *    the 2D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_2d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t tile_j,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_2d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_2d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		tile_j,
		flags);
}

/**
 * Process items on a 2D grid with the specified maximum tile size along each
 * grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i += tile_i)
 *     for (size_t j = 0; j < range_j; j += tile_j)
 *       functor(i, j,
 *         min(range_i - i, tile_i), min(range_j - j, tile_j));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 2D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 2D grid.
 * @param tile_j      the maximum number of items along the first dimension of
 *    the 2D grid to process in one functor call.
 * @param tile_j      the maximum number of items along the second dimension of
 *    the 2D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_2d_tile_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t tile_i,
	size_t tile_j,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_2d_tile_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_2d_tile_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		tile_i,
		tile_j,
		flags);
}

/**
 * Process items on a 3D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         functor(i, j, k);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 3D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 3D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 3D grid.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_3d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_3d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_3d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		flags);
}

/**
 * Process items on a 3D grid with the specified maximum tile size along the
 * last grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k += tile_k)
 *         functor(i, j, k, min(range_k - k, tile_k));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 3D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 3D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 3D grid.
 * @param tile_k      the maximum number of items along the third dimension of
 *    the 3D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_3d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t tile_k,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_3d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_3d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		tile_k,
		flags);
}

/**
 * Process items on a 3D grid with the specified maximum tile size along the
 * last two grid dimensions.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j += tile_j)
 *       for (size_t k = 0; k < range_k; k += tile_k)
 *         functor(i, j, k,
 *           min(range_j - j, tile_j), min(range_k - k, tile_k));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 3D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 3D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 3D grid.
 * @param tile_j      the maximum number of items along the second dimension of
 *    the 3D grid to process in one functor call.
 * @param tile_k      the maximum number of items along the third dimension of
 *    the 3D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_3d_tile_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t tile_j,
	size_t tile_k,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_3d_tile_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_3d_tile_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		tile_j,
		tile_k,
		flags);
}

/**
 * Process items on a 4D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           functor(i, j, k, l);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 4D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 4D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 4D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 4D grid.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_4d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_4d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_4d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		flags);
}

/**
 * Process items on a 4D grid with the specified maximum tile size along the
 * last grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l += tile_l)
 *           functor(i, j, k, l, min(range_l - l, tile_l));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 4D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 4D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 4D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 4D grid.
 * @param tile_l      the maximum number of items along the fourth dimension of
 *    the 4D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_4d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t tile_l,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_4d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_4d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		tile_l,
		flags);
}

/**
 * Process items on a 4D grid with the specified maximum tile size along the
 * last two grid dimensions.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k += tile_k)
 *         for (size_t l = 0; l < range_l; l += tile_l)
 *           functor(i, j, k, l,
 *             min(range_k - k, tile_k), min(range_l - l, tile_l));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 4D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 4D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 4D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 4D grid.
 * @param tile_k      the maximum number of items along the third dimension of
 *    the 4D grid to process in one functor call.
 * @param tile_l      the maximum number of items along the fourth dimension of
 *    the 4D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_4d_tile_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t tile_k,
	size_t tile_l,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_4d_tile_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_4d_tile_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		tile_k,
		tile_l,
		flags);
}

/**
 * Process items on a 5D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           for (size_t m = 0; m < range_m; m++)
 *             functor(i, j, k, l, m);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 5D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 5D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 5D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 5D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 5D grid.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_5d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_5d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_5d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		flags);
}

/**
 * Process items on a 5D grid with the specified maximum tile size along the
 * last grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           for (size_t m = 0; m < range_m; m += tile_m)
 *             functor(i, j, k, l, m, min(range_m - m, tile_m));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 5D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 5D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 5D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 5D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 5D grid.
 * @param tile_m      the maximum number of items along the fifth dimension of
 *    the 5D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_5d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	size_t tile_m,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_5d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_5d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		tile_m,
		flags);
}

/**
 * Process items on a 5D grid with the specified maximum tile size along the
 * last two grid dimensions.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l += tile_l)
 *           for (size_t m = 0; m < range_m; m += tile_m)
 *             functor(i, j, k, l, m,
 *               min(range_l - l, tile_l), min(range_m - m, tile_m));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 5D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 5D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 5D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 5D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 5D grid.
 * @param tile_l      the maximum number of items along the fourth dimension of
 *    the 5D grid to process in one functor call.
 * @param tile_m      the maximum number of items along the fifth dimension of
 *    the 5D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_5d_tile_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	size_t tile_l,
	size_t tile_m,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_5d_tile_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_5d_tile_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		tile_l,
		tile_m,
		flags);
}

/**
 * Process items on a 6D grid.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           for (size_t m = 0; m < range_m; m++)
 *             for (size_t n = 0; n < range_n; n++)
 *               functor(i, j, k, l, m, n);
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 6D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 6D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 6D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 6D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 6D grid.
 * @param range_n     the number of items to process along the sixth dimension
 *    of the 6D grid.
 * @param tile_n      the maximum number of items along the sixth dimension of
 *    the 6D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_6d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	size_t range_n,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_6d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_6d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		range_n,
		flags);
}

/**
 * Process items on a 6D grid with the specified maximum tile size along the
 * last grid dimension.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           for (size_t m = 0; m < range_m; m++)
 *             for (size_t n = 0; n < range_n; n += tile_n)
 *               functor(i, j, k, l, m, n, min(range_n - n, tile_n));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 6D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 6D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 6D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 6D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 6D grid.
 * @param range_n     the number of items to process along the sixth dimension
 *    of the 6D grid.
 * @param tile_n      the maximum number of items along the sixth dimension of
 *    the 6D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_6d_tile_1d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	size_t range_n,
	size_t tile_n,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_6d_tile_1d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_6d_tile_1d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		range_n,
		tile_n,
		flags);
}

/**
 * Process items on a 6D grid with the specified maximum tile size along the
 * last two grid dimensions.
 *
 * The function implements a parallel version of the following snippet:
 *
 *   for (size_t i = 0; i < range_i; i++)
 *     for (size_t j = 0; j < range_j; j++)
 *       for (size_t k = 0; k < range_k; k++)
 *         for (size_t l = 0; l < range_l; l++)
 *           for (size_t m = 0; m < range_m; m += tile_m)
 *             for (size_t n = 0; n < range_n; n += tile_n)
 *               functor(i, j, k, l, m, n,
 *                 min(range_m - m, tile_m), min(range_n - n, tile_n));
 *
 * When the function returns, all items have been processed and the thread pool
 * is ready for a new task.
 *
 * @note If multiple threads call this function with the same thread pool, the
 *    calls are serialized.
 *
 * @param threadpool  the thread pool to use for parallelisation. If threadpool
 *    is NULL, all items are processed serially on the calling thread.
 * @param functor     the functor to call for each tile.
 * @param range_i     the number of items to process along the first dimension
 *    of the 6D grid.
 * @param range_j     the number of items to process along the second dimension
 *    of the 6D grid.
 * @param range_k     the number of items to process along the third dimension
 *    of the 6D grid.
 * @param range_l     the number of items to process along the fourth dimension
 *    of the 6D grid.
 * @param range_m     the number of items to process along the fifth dimension
 *    of the 6D grid.
 * @param range_n     the number of items to process along the sixth dimension
 *    of the 6D grid.
 * @param tile_m      the maximum number of items along the fifth dimension of
 *    the 6D grid to process in one functor call.
 * @param tile_n      the maximum number of items along the sixth dimension of
 *    the 6D grid to process in one functor call.
 * @param flags       a bitwise combination of zero or more optional flags
 *    (PTHREADPOOL_FLAG_DISABLE_DENORMALS or PTHREADPOOL_FLAG_YIELD_WORKERS)
 */
template<class T>
inline void pthreadpool_parallelize_6d_tile_2d(
	pthreadpool_t threadpool,
	const T& functor,
	size_t range_i,
	size_t range_j,
	size_t range_k,
	size_t range_l,
	size_t range_m,
	size_t range_n,
	size_t tile_m,
	size_t tile_n,
	uint32_t flags = 0)
{
	pthreadpool_parallelize_6d_tile_2d(
		threadpool,
		&libpthreadpool::detail::call_wrapper_6d_tile_2d<const T>,
		const_cast<void*>(static_cast<const void*>(&functor)),
		range_i,
		range_j,
		range_k,
		range_l,
		range_m,
		range_n,
		tile_m,
		tile_n,
		flags);
}

#endif  /* __cplusplus */

#endif /* PTHREADPOOL_H_ */
