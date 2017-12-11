#include "nan.h"

#pragma once

namespace memcache {

class MemcachedClient : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Initialize);
private:
    static NAN_METHOD(New);
    static NAN_METHOD(Get);
    static NAN_METHOD(Exist);
    static NAN_METHOD(Touch);
    static NAN_METHOD(Delete);

    MemcachedClient(const std::string &config);
    static MemcachedClient *GetInstance(const Nan::FunctionCallbackInfo<v8::Value>&);

    memcached_st *mcc;
};

}  // namespace memcache
