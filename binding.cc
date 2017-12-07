#include <assert.h>
#include <libmemcached-1.0/memcached.h>
#include <node.h>
#include "nan.h"

using namespace v8;
using namespace node;

namespace memcache {

class Memcache : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Initialize);
private:
    static NAN_METHOD(New);
    static NAN_METHOD(Get);

    Memcache(const std::string &config);
    static Memcache *GetMemcache(const Nan::FunctionCallbackInfo<Value>&);

    memcached_st *memc_;
};

NAN_MODULE_INIT(Memcache::Initialize) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> t = Nan::New<FunctionTemplate>(New);
    t->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(t, "get", Get);

    Nan::Set(target, Nan::New("Memcache").ToLocalChecked(), Nan::GetFunction(t).ToLocalChecked());
}

NAN_METHOD(Memcache::New) {
    assert(info.IsConstructCall());

    if (info.Length() != 1) {
        return Nan::ThrowError("Must pass a config to constructor");
    }

    Nan::Utf8String config(info[0]);

    Memcache *memcache = new Memcache(*config);
    memcache->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Memcache::Get) {
    Memcache *memc = GetMemcache(info);

    if (memc->memc_ == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 1)
        return Nan::ThrowError("Must pass a key");

    Nan::Utf8String nan_key(info[0]);
    std::string key(*nan_key);
    std::vector<char> ret_val;
    uint32_t flags = 0;
    memcached_return_t rc;
    size_t value_length = 0;
    v8::Isolate* isolate = info.GetIsolate();

    char *value= memcached_get(memc->memc_, key.c_str(), key.length(),
                               &value_length, &flags, &rc);
    if (value != NULL && ret_val.empty())
    {
        ret_val.reserve(value_length + 1); // Always provide null
        ret_val.assign(value, value + value_length + 1);
        ret_val.resize(value_length);
        free(value);
        std::string ret_str(ret_val.begin(), ret_val.end());
        // info.GetReturnValue().Set(String::NewFromUtf8(isolate, ret_str.c_str()));
        info.GetReturnValue().Set(Nan::CopyBuffer(ret_str.c_str(), ret_str.length()).ToLocalChecked());
    }
}

Memcache::Memcache(const std::string &config) : Nan::ObjectWrap() {
    memc_ = memcached(config.c_str(), config.size());
}

Memcache *
Memcache::GetMemcache(const Nan::FunctionCallbackInfo<Value>& info) {
    return Nan::ObjectWrap::Unwrap<Memcache>(info.This());
}

static NAN_MODULE_INIT(Initialize) {
    Nan::HandleScope scope;

    Memcache::Initialize(target);
}

}  // namespace memcache

extern "C" NAN_MODULE_INIT(init) {
  memcache::Initialize(target);
}

NODE_MODULE(memcache, init)
