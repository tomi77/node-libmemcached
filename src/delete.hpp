#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"

#pragma once

namespace memcache {

NAN_METHOD(MemcachedClient::Delete) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 1)
        return Nan::ThrowError("Must pass a key");

    Nan::Utf8String nan_key(info[0]);
    std::string key(*nan_key);

    memcached_return_t rc = memcached_delete(mcc->mcc, key.c_str(), key.length(), 0);
    if (rc != MEMCACHED_SUCCESS)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
