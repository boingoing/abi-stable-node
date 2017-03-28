#include "node_api_async.h"
#include "uv.h"

namespace uvimpl {

// Wrapper around uv_work_t which calls user-provided callbacks.
class Work {
 private:
  explicit Work(napi_env env,
                napi_async_callback execute,
                napi_async_callback complete,
                napi_async_callback destroy,
                void* data)
     : _env(env),
     _data(data),
     _execute(execute),
     _complete(complete),
     _destroy(destroy) {
    _request = new uv_work_t;
    _request->data = this;
  }

  ~Work() { };

 public:
  static Work* New(napi_env env,
                   napi_async_callback execute,
                   napi_async_callback complete,
                   napi_async_callback destroy,
                   void* data) {
    return new Work(env, execute, complete, destroy, data);
  }

  static void Delete(Work* work) {
    delete work->_request;
    delete work;
  }

  static napi_status Queue(Work* work) {
    // Consider: Choose a different loop based on the napi_env?
    int result = uv_queue_work(uv_default_loop(),
                               work->_request,
                               ExecuteCallback,
                               CompleteCallback);

    if (result != 0) {
      return napi_generic_failure;
    }
    return napi_ok;
  }

  static void ExecuteCallback(uv_work_t* req) {
    Work* work = reinterpret_cast<Work*>(req->data);
    work->_execute(work->_env, work->_data);
  }

  static void CompleteCallback(uv_work_t* req, int status) {
    // Consider: Pass the status into the complete callback?
    Work* work = reinterpret_cast<Work*>(req->data);
    work->_complete(work->_env, work->_data);
    work->_destroy(work->_env, work->_data);
  }

 private:
   napi_env _env;
   void* _data;
   uv_work_t* _request;
   napi_async_callback _execute;
   napi_async_callback _complete;
   napi_async_callback _destroy;
};
}

napi_status napi_create_async_work(napi_env env,
                                   napi_async_callback execute,
                                   napi_async_callback complete,
                                   napi_async_callback destroy,
                                   void* data,
                                   napi_async_work* result) {
  uvimpl::Work* work = uvimpl::Work::New(env,
                                         execute,
                                         complete,
                                         destroy,
                                         data);
  *result = reinterpret_cast<napi_async_work>(work);
  return napi_ok;
}

napi_status napi_delete_async_work(napi_env env, napi_async_work work) {
  uvimpl::Work::Delete(reinterpret_cast<uvimpl::Work*>(work));
  return napi_ok;
}

napi_status napi_queue_async_work(napi_env env, napi_async_work work) {
  return uvimpl::Work::Queue(reinterpret_cast<uvimpl::Work*>(work));
}
