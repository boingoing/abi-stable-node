#define NAPI_ASSERT(env, assertion, message)                             \
  if (!(assertion)) {                                                    \
    napi_throw_error(                                                    \
        (env),                                                           \
        "assertion (" #assertion ") failed: " message);                  \
    return NULL;                                                         \
  }

#define GET_AND_THROW_LAST_ERROR(env)                                    \
  const napi_extended_error_info* error;                                 \
  napi_get_last_error_info((env), &error);                               \
  const char* error_message = error->error_message;                      \
  error_message = error_message ? error_message : "empty error message"; \
  napi_throw_error((env), error_message);

#define NAPI_CALL(env, the_call)                                         \
  if ((the_call) != napi_ok) {                                           \
    GET_AND_THROW_LAST_ERROR((env));                                     \
    return NULL;                                                         \
  }

#define NAPI_CALL_NO_RETURN(env, the_call)                               \
  if ((the_call) != napi_ok) {                                           \
    GET_AND_THROW_LAST_ERROR((env));                                     \
  }

#define DECLARE_NAPI_PROPERTY(name, func)                                \
  { name, 0, func, 0, 0, 0, napi_default, 0 }
