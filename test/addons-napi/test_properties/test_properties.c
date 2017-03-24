#include <node_api.h>
#include "..\common.h"

static double value_ = 1;

napi_value GetValue(napi_env env, napi_callback_info info) {
  size_t argc = 0;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, NULL, NULL, NULL));

  NAPI_ASSERT(env, argc == 0, "Wrong number of arguments");

  napi_value number;
  NAPI_CALL(env, napi_create_number(env, value_, &number));

  return number;
}

napi_value SetValue(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

  NAPI_ASSERT(env, argc == 1, "Wrong number of arguments");

  NAPI_CALL(env, napi_get_value_double(env, args[0], &value_));

  return NULL;
}

napi_value Echo(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

  NAPI_ASSERT(env, argc == 1, "Wrong number of arguments");

  return args[0];
}

void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
  napi_value number;
  NAPI_CALL_RETURN_VOID(env, napi_create_number(env, value_, &number));

  napi_property_descriptor properties[] = {
    { "echo", 0, Echo, 0, 0, 0, napi_default, 0 },
    { "accessorValue", 0, 0, GetValue, SetValue, 0, napi_default, 0 },
    { "readwriteValue", 0, 0, 0, 0, number, napi_default, 0 },
    { "readonlyValue", 0, 0, 0, 0, number, napi_read_only, 0 },
    { "hiddenValue", 0, 0, 0, 0, number, napi_read_only | napi_dont_enum, 0 },
  };

  NAPI_CALL_RETURN_VOID(env, napi_define_properties(
    env, exports, sizeof(properties) / sizeof(*properties), properties));
}

NAPI_MODULE(addon, Init)
