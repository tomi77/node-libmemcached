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

    MemcachedClient(const std::string &config);
    static MemcachedClient *GetInstance(const Nan::FunctionCallbackInfo<Value>&);

    memcached_st *mcc;
};

MemcachedClient::MemcachedClient(const std::string &config) : Nan::ObjectWrap() {
    mcc = memcached(config.c_str(), config.size());
}

MemcachedClient *
MemcachedClient::GetInstance(const Nan::FunctionCallbackInfo<Value>& info) {
    return Nan::ObjectWrap::Unwrap<MemcachedClient>(info.This());
}

}  // namespace memcache
