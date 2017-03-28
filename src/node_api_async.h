#ifndef SRC_NODE_API_ASYNC_H_
#define SRC_NODE_API_ASYNC_H_

#include <stdlib.h>
#include "node_api.h"
#include "node_api_async_types.h"

EXTERN_C_START

napi_status napi_create_async_work(napi_env env,
                                   napi_async_callback execute,
                                   napi_async_callback complete,
                                   napi_async_callback destroy,
                                   void* data,
                                   napi_async_work* result);
napi_status napi_delete_async_work(napi_env env, napi_async_work work);
napi_status napi_queue_async_work(napi_env env, napi_async_work work);

EXTERN_C_END

#endif  // SRC_NODE_API_ASYNC_H_
