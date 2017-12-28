// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache
{

NAN_MODULE_INIT(MemcachedClient::Initialize)
{
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
    t->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(t, "get", Get);
    Nan::SetPrototypeMethod(t, "set", Set);
    Nan::SetPrototypeMethod(t, "add", Add);
    Nan::SetPrototypeMethod(t, "replace", Replace);
    Nan::SetPrototypeMethod(t, "exist", Exist);
    Nan::SetPrototypeMethod(t, "touch", Touch);
    Nan::SetPrototypeMethod(t, "delete", Delete);
    Nan::SetPrototypeMethod(t, "increment", Increment);
    Nan::SetPrototypeMethod(t, "decrement", Decrement);

    Nan::Set(target, Nan::New("MemcachedClient").ToLocalChecked(),
             Nan::GetFunction(t).ToLocalChecked());
}

NAN_METHOD(MemcachedClient::New)
{
    assert(info.IsConstructCall());

    if (info.Length() != 1)
    {
        return Nan::ThrowError("Must pass a config to constructor");
    }

    std::string config = NANX_V8VALUE_TO_STRING(info[0]);

    MemcachedClient *mcc = new MemcachedClient(config.c_str());
    mcc->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

MemcachedClient::MemcachedClient(const std::string &config) : Nan::ObjectWrap()
{
    mcc = memcached(config.c_str(), config.size());
    memcached_behavior_set(mcc, MEMCACHED_BEHAVIOR_USE_UDP, 0);
    memcached_behavior_set(mcc, MEMCACHED_BEHAVIOR_NO_BLOCK, 0);
}

MemcachedClient *
MemcachedClient::GetInstance(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    return Nan::ObjectWrap::Unwrap<MemcachedClient>(info.This());
}

static NAN_MODULE_INIT(Initialize)
{
    Nan::HandleScope scope;

    MemcachedClient::Initialize(target);
}

}  // namespace memcache

extern "C" NAN_MODULE_INIT(init)
{
  memcache::Initialize(target);
}

NODE_MODULE(memcache, init)
