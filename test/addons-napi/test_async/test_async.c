#include <node_api.h>
#include <string.h>

char globalString[] = "Something";

void Execute(napi_env env, void* data) {
}

void Complete(napi_env env, void* data) {
}

void Destroy(napi_env env, void* data) {
}

void Test(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_async_work w;
  
  status = napi_create_async_work(
    env, Execute, Complete, Destroy, globalString, &w);
}

void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
  napi_status status;

  napi_property_descriptor descriptors[] = {
      { "Test", Test, 0, 0, 0, napi_default, 0 }
  };

  status = napi_define_properties(
      env, exports, sizeof(descriptors) / sizeof(*descriptors), descriptors);
  if (status != napi_ok) return;
}

NAPI_MODULE(addon, Init)
