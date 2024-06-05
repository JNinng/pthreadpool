#ifndef PTHREADPOOL_H_
#define PTHREADPOOL_H_

#include <stddef.h>
#include <stdint.h>

typedef struct pthreadpool* pthreadpool_t;

// �������ά�ȵ����������ͣ����ڲ�ͬά�ȵ��̳߳ز��л����� ÿ���������ͽ���һ��������ָ�롢һ�������Ϳ�ѡ���߳�ID����Ƭ��С 1D��6D�������ͣ��Լ����ǵ���Ƭ�������
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
 * �ڼ����ڼ䣬����������޶ȵؽ��öԷǹ淶�����ֵ�֧�֡�
 *
 * ����ǹ淶��������ͨ����΢������ʵ�֣����ᵼ�������������½���
 �����ʾָʾ�̳߳������м���֮ǰ��ͨ�������ض��ڼܹ��Ŀ��ƼĴ��������öԷǹ淶�����ֵ�֧�֣�
 ���ڼ�����ɺ�ָ����ƼĴ����ĳ�ʼֵ��
 �̳߳ػ���ʱ�����в��������߳��Ͻ��÷ǹ淶�����֣��������̺߳�Ǳ�ڵĹ����̣߳���
 *
 * ���÷ǹ淶�����ֿ��ܻ�Խ����׼ȷ�Բ�����΢�ĸ���Ӱ�졣
 ���ڲ�ͬ�ܹ��ڿ��Ʒǹ淶�����ִ������������ͬ��ʹ�ô˱�־Ҳ�����𺦽���ڲ�ָͬ��ܹ���Ŀ��ظ��ԡ�
 */
#define PTHREADPOOL_FLAG_DISABLE_DENORMALS 0x00000001

 /**
  * ������ɺ󣬽������߳��ø�ϵͳ��������
  *
  * ǿ�ƹ����߳��ڴ�����������ʹ���ں˵ȴ���������Ĭ�ϵ����������ȴ������ȴ������
  �˱�־��Ӱ����̳߳ص�������һ��������Ҫʹ�̳߳�ʼ��ʹ���ں˵ȴ����뽫�˱�־���ݸ����в��л�������
  */
#define PTHREADPOOL_FLAG_YIELD_WORKERS 0x00000002

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ����һ������ָ���߳��������̳߳ء�
	 *
	 * @param  threads_count  �̳߳��е��߳�������
	 *    ֵΪ0����������ͣ�������һ���̳߳أ��߳�������ϵͳ�е��߼�������������ͬ��
	 *
	 * @returns  ������óɹ�������ָ��͸���̳߳ض����ָ�룻�������ʧ�ܣ�����NULLָ�롣
	 */
	pthreadpool_t pthreadpool_create(size_t threads_count);

	/**
	 * ��ѯ�̳߳��е��߳�������
	 *
	 * @param  threadpool  Ҫ��ѯ���̳߳ء�
	 *
	 * @returns  �̳߳��е��߳�������
	 */
	size_t pthreadpool_get_threads_count(pthreadpool_t threadpool);

	/**
	 * ��һά�����ϴ�����Ŀ��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, i);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ĿҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range       Ҫ�����һά�����ϵ���Ŀ������ָ���ĺ�����Ϊÿ����Ŀ����һ�Ρ�
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
	 */
	void pthreadpool_parallelize_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_t function,
		void* context,
		size_t range,
		uint32_t flags);

	/**
	 * ��һά�����ϴ�����Ŀ�������ݵ�ǰ�߳�ID��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, thread_index, i);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ĿҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range       Ҫ�����һά�����ϵ���Ŀ������ָ���ĺ�����Ϊÿ����Ŀ����һ�Ρ�
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
	 */
	void pthreadpool_parallelize_1d_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_with_thread_t function,
		void* context,
		size_t range,
		uint32_t flags);

	/**
	 * ʹ��΢�ܹ���֪����������һά�����ϴ�����Ŀ��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range; i++)
	 *     function(context, uarch_index, i);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ĿҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range                Ҫ�����һά�����ϵ���Ŀ������ָ���ĺ�����Ϊÿ����Ŀ����һ�Ρ�
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��ָ���������Ƭ��С��һά�����ϴ�����Ŀ��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range; i += tile)
	 *     function(context, i, min(range - i, tile));
	 *
	 * �����÷���ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range       Ҫ�����һά�����ϵ���Ŀ������
	 * @param tile        һ�κ���������Ҫ�����һά�����ϵ������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
	 */
	void pthreadpool_parallelize_1d_tile_1d(
		pthreadpool_t threadpool,
		pthreadpool_task_1d_tile_1d_t function,
		void* context,
		size_t range,
		size_t tile,
		uint32_t flags);

	/**
	 * �ڶ�ά�����ϴ�����Ŀ��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       function(context, i, j);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ĿҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά����ĵ�һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ĵڶ���ά����Ҫ�������Ŀ������
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
	 */
	void pthreadpool_parallelize_2d(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		uint32_t flags);

	/**
	 * �ڶ�ά�����ϴ�����Ŀ�������ݵ�ǰ�߳�ID��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       function(context, thread_index, i, j);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ĿҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
	 */
	void pthreadpool_parallelize_2d_with_thread(
		pthreadpool_t threadpool,
		pthreadpool_task_2d_with_thread_t function,
		void* context,
		size_t range_i,
		size_t range_j,
		uint32_t flags);

	/**
	 * �ڶ�ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, i, j, min(range_j - j, tile_j));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param tile_j      һ�κ��������ж�ά����ڶ���ά����Ҫ����������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��΢�ܹ���֪�����������ڶ�ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, i, j, min(range_j - j, tile_j));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ƬҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range_i              ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j              ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param tile_j               һ�κ��������ж�ά����ڶ���ά����Ҫ����������Ŀ����
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��΢�ܹ���֪�����������ڶ�ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��ͬʱ���ݵ�ǰ�߳�ID��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, thread_index, i, j, min(range_j - j, tile_j));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ƬҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range_i              ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j              ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param tile_j               һ�κ��������ж�ά����ڶ���ά����Ҫ����������Ŀ����
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * �ڶ�ά�����ϴ�����Ŀ����Ϊÿ������ά��ָ�������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i += tile_i)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, i, j,
	 *         min(range_i - i, tile_i), min(range_j - j, tile_j));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param tile_i      һ�κ��������ж�ά�����һ��ά����Ҫ����������Ŀ����
	 * @param tile_j      һ�κ��������ж�ά����ڶ���ά����Ҫ����������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��΢�ܹ���֪�����������ڶ�ά�����ϴ�����Ŀ����Ϊÿ������ά��ָ�������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i += tile_i)
	 *     for (size_t j = 0; j < range_j; j += tile_j)
	 *       function(context, uarch_index, i, j,
	 *         min(range_i - i, tile_i), min(range_j - j, tile_j));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ƬҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range_i              ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j              ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param tile_i               һ�κ��������ж�ά�����һ��ά����Ҫ����������Ŀ����
	 * @param tile_j               һ�κ��������ж�ά����ڶ���ά����Ҫ����������Ŀ����
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ����ά�����ϴ�����Ŀ��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k++)
	 *         function(context, i, j, k);
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ĿҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k     ��ά���������ά����Ҫ�������Ŀ������
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ����ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, i, j, k, min(range_k - k, tile_k));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k     ��ά���������ά����Ҫ�������Ŀ������
	 * @param tile_k      һ�κ�����������ά���������ά����Ҫ����������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ����ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��ͬʱ���ݵ�ǰ�߳�ID��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, thread_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k     ��ά���������ά����Ҫ�������Ŀ������
	 * @param tile_k      һ�κ�����������ά���������ά����Ҫ����������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��΢�ܹ���֪��������������ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, uarch_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ƬҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range_i              ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j              ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k              ��ά���������ά����Ҫ�������Ŀ������
	 * @param tile_k               һ�κ�����������ά���������ά����Ҫ����������Ŀ����
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ʹ��΢�ܹ���֪��������������ά�����ϴ�����Ŀ����ָ�����һ������ά�ȵ������Ƭ��С��ͬʱ���ݵ�ǰ�߳�ID��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
	 *
	 *   uint32_t uarch_index = cpuinfo_initialize() ?
	 *       cpuinfo_get_current_uarch_index() : default_uarch_index;
	 *   if (uarch_index > max_uarch_index) uarch_index = default_uarch_index;
	 *   for (size_t i = 0; i < range_i; i++)
	 *     for (size_t j = 0; j < range_j; j++)
	 *       for (size_t k = 0; k < range_k; k += tile_k)
	 *         function(context, uarch_index, thread_index, i, j, k, min(range_k - k, tile_k));
	 *
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool           ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function             ����ÿ����ƬҪ���õĺ�����
	 * @param context              ���ݸ�ָ�������ĵ�һ��������
	 * @param default_uarch_index  ��pthreadpoolδ����cpuinfo��cpuinfo��ʼ��ʧ�ܣ���cpuinfo_get_current_uarch_index()���ص���������max_uarch_indexֵʱʹ�õ�΢�ܹ�������
	 * @param max_uarch_index      ָ������Ԥ�ڵ����΢�ܹ����������cpuinfo_get_current_uarch_index()���ص�����������ֵ����ʹ��default_uarch_index��default_uarch_index���Գ���max_uarch_index��
	 * @param range_i              ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j              ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k              ��ά���������ά����Ҫ�������Ŀ������
	 * @param tile_k               һ�κ�����������ά���������ά����Ҫ����������Ŀ����
	 * @param flags                һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ����ά�����ϴ�����Ŀ����ָ�������������ά�ȵ������Ƭ��С��
	 *
	 * �ú���ʵ�������´���Ƭ�εĲ��а汾��
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
	 * ����������ʱ��������Ŀ���Ѵ�����ϣ��̳߳���׼���ý���������
	 *
	 * @note �������߳�ʹ����ͬ���̳߳ص��ô˺���������Щ���ý������л���
	 *
	 * @param threadpool  ���ڲ��л����̳߳ء����threadpoolΪNULL�����ڵ����߳��ϴ��д���������Ŀ��
	 * @param function    ����ÿ����ƬҪ���õĺ�����
	 * @param context     ���ݸ�ָ�������ĵ�һ��������
	 * @param range_i     ��ά�����һ��ά����Ҫ�������Ŀ������
	 * @param range_j     ��ά����ڶ���ά����Ҫ�������Ŀ������
	 * @param range_k     ��ά���������ά����Ҫ�������Ŀ������
	 * @param range_l     ��ά������ĸ�ά����Ҫ�������Ŀ������
	 * @param range_m     ��ά��������ά����Ҫ�������Ŀ������
	 * @param range_n     ��ά���������ά����Ҫ�������Ŀ������
	 * @param tile_m      һ�κ�����������ά��������ά����Ҫ����������Ŀ����
	 * @param tile_n      һ�κ�����������ά���������ά����Ҫ����������Ŀ����
	 * @param flags       һ����ѡ��־�İ�λ��ϣ�PTHREADPOOL_FLAG_DISABLE_DENORMALS �� PTHREADPOOL_FLAG_YIELD_WORKERS��
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
	 * ��ֹ�̳߳��е��̲߳��ͷ������Դ��
	 *
	 * @warning �ڵ��ô˺���������̳߳ؽ�����δ������Ϊ�������ܵ��������𻵡�
	 *
	 * @param[in,out]  threadpool  Ҫ���ٵ��̳߳ء�
	 */
	void pthreadpool_destroy(pthreadpool_t threadpool);

#ifndef PTHREADPOOL_NO_DEPRECATED_API

	/* ������API��������Ԥ�ȴ��ڵ��û����ݣ����� NNPACK�� */
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
