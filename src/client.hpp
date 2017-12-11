#include <assert.h>
#include <libmemcached/memcached.h>
#include <node.h>
#include "nan.h"

#pragma once

using namespace v8;
using namespace node;

namespace memcache {

class MemcachedClient : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Initialize);
private:
    static NAN_METHOD(New);
    static NAN_METHOD(Get);
    static NAN_METHOD(Exist);
    static NAN_METHOD(Touch);

    MemcachedClient(const std::string &config);
    static MemcachedClient *GetInstance(const Nan::FunctionCallbackInfo<Value>&);

    memcached_st *mcc;
};

MemcachedClient::MemcachedClient(const std::string &config) : Nan::ObjectWrap() {
    mcc = memcached(config.c_str(), config.size());
    memcached_behavior_set(mcc, MEMCACHED_BEHAVIOR_USE_UDP, 0);
}

MemcachedClient *
MemcachedClient::GetInstance(const Nan::FunctionCallbackInfo<Value>& info) {
    return Nan::ObjectWrap::Unwrap<MemcachedClient>(info.This());
}

}  // namespace memcache
