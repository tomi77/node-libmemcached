#include <libmemcached/memcached.h>
#include <node.h>
#include "nan.h"
#include "client.hpp"

#pragma once

namespace memcache {

NAN_METHOD(MemcachedClient::Touch) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 2)
        return Nan::ThrowError("Must pass a key and expiration time");
    if (!info[1]->IsInt32())
        return Nan::ThrowError("Expiration time must be a integer");

    Nan::Utf8String nan_key(info[0]);
    std::string key(*nan_key);
    time_t expiration = info[1]->IntegerValue();

    memcached_return_t rc = memcached_touch(mcc->mcc, key.c_str(), key.length(), expiration);
    if (memcached_failed(rc))
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
