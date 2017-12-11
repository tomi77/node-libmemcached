#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "get.hpp"
#include "exist.hpp"
#include "touch.hpp"
#include "delete.hpp"

namespace memcache {

NAN_MODULE_INIT(MemcachedClient::Initialize) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
    t->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(t, "get", Get);
    Nan::SetPrototypeMethod(t, "exist", Exist);
    Nan::SetPrototypeMethod(t, "touch", Touch);
    Nan::SetPrototypeMethod(t, "delete", Delete);

    Nan::Set(target, Nan::New("MemcachedClient").ToLocalChecked(), Nan::GetFunction(t).ToLocalChecked());
}

NAN_METHOD(MemcachedClient::New) {
    assert(info.IsConstructCall());

    if (info.Length() != 1) {
        return Nan::ThrowError("Must pass a config to constructor");
    }

    Nan::Utf8String config(info[0]);

    MemcachedClient *mcc = new MemcachedClient(*config);
    mcc->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

static NAN_MODULE_INIT(Initialize) {
    Nan::HandleScope scope;

    MemcachedClient::Initialize(target);
}

}  // namespace memcache

extern "C" NAN_MODULE_INIT(init) {
  memcache::Initialize(target);
}

NODE_MODULE(memcache, init)
