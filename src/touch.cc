// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache
{

NAN_METHOD(MemcachedClient::Touch)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() != 2)
    {
        Nan::ThrowError("Must pass a key and expiration time");
        return;
    }
    if (not info[1]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);
    time_t expiration = NANX_V8VALUE_TO_INTEGER(info[1]);

    memcached_return_t rc = memcached_touch(mcc->mcc, key.c_str(), key.length(), expiration);
    if (memcached_failed(rc))
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
