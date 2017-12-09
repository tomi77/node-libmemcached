#include <libmemcached/memcached.h>
#include <node.h>
#include "nan.h"
#include "client.hpp"

#pragma once

using namespace v8;
using namespace node;

namespace memcache {

NAN_METHOD(MemcachedClient::Exist) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 1)
        return Nan::ThrowError("Must pass a key");

    Nan::Utf8String nan_key(info[0]);
    std::string key(*nan_key);

    memcached_return_t rc = memcached_exist(mcc->mcc, key.c_str(), key.length());
    if (rc == MEMCACHED_SUCCESS)
    {
        info.GetReturnValue().Set(Nan::True());
    }
    else
    {
        info.GetReturnValue().Set(Nan::False());
    }
}

}  // namespace memcache
