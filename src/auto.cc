// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache
{

NAN_METHOD(MemcachedClient::Increment)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 1)
    {
        Nan::ThrowError("Must pass a key");
        return;
    }
    if (info.Length() >= 2 && not info[1]->IsInt32())
    {
        Nan::ThrowTypeError("Offset must be a integer");
        return;
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);
    uint32_t offset = 1;
    if (info.Length() >= 2)
    {
        offset = NANX_V8VALUE_TO_INTEGER(info[1]);
    }
    uint64_t value;

    memcached_return_t rc = memcached_increment(mcc->mcc, key.c_str(), key.length(),
                                                offset, &value);
    if (rc != MEMCACHED_SUCCESS)
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(NANX_INTEGER_TO_V8NUMBER(value));
}

NAN_METHOD(MemcachedClient::Decrement)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 1)
    {
        Nan::ThrowError("Must pass a key");
        return;
    }
    if (info.Length() >= 2 && not info[1]->IsInt32())
    {
        Nan::ThrowTypeError("Offset must be a integer");
        return;
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);
    uint32_t offset = 1;
    if (info.Length() >= 2)
    {
        offset = NANX_V8VALUE_TO_INTEGER(info[1]);
    }
    uint64_t value;

    memcached_return_t rc = memcached_decrement(mcc->mcc, key.c_str(), key.length(),
                                                offset, &value);
    if (rc != MEMCACHED_SUCCESS)
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(NANX_INTEGER_TO_V8NUMBER(value));
}

}  // namespace memcache
