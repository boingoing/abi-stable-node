#ifndef SRC_NODE_API_ASYNC_TYPES_H_
#define SRC_NODE_API_ASYNC_TYPES_H_

// LIBUV API types are all opaque pointers for ABI stability
// typedef undefined structs instead of void* for compile time type safety
typedef struct napi_async_work__ *napi_async_work;

typedef void(*napi_async_callback)(napi_env env, void* data);

#endif  // SRC_NODE_API_ASYNC_TYPES_H_
