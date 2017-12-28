// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache {

NAN_METHOD(MemcachedClient::Set) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        return Nan::ThrowError("memcache not initialized");
    }
    if (info.Length() < 2)
    {
        return Nan::ThrowError("Must pass a key and value");
    }
    if (info.Length() >= 3 && !info[3]->IsInt32())
    {
        return Nan::ThrowTypeError("Expiration time must be a integer");
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsString())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(NANX_V8VALUE_TO_INTEGER(info[1]));
    }
    else if (info[1]->IsNumber())
    {
        value = std::to_string(NANX_V8VALUE_TO_DOUBLE(info[1]));
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = NANX_V8VALUE_TO_INTEGER(info[2]);
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_set(mcc->mcc, key.c_str(), key.length(),
                                          value.c_str(), value.length(),
                                          expiration, flags);
    if (rc != MEMCACHED_SUCCESS)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Add) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        return Nan::ThrowError("memcache not initialized");
    }
    if (info.Length() < 2)
    {
        return Nan::ThrowError("Must pass a key and value");
    }
    if (info.Length() >= 3 && !info[3]->IsInt32())
    {
        return Nan::ThrowTypeError("Expiration time must be a integer");
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsString())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(NANX_V8VALUE_TO_INTEGER(info[1]));
    }
    else if (info[1]->IsNumber())
    {
        value = std::to_string(NANX_V8VALUE_TO_DOUBLE(info[1]));
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = NANX_V8VALUE_TO_INTEGER(info[2]);
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_add(mcc->mcc, key.c_str(), key.length(),
                                          value.c_str(), value.length(),
                                          expiration, flags);
    if (rc != MEMCACHED_SUCCESS && rc != MEMCACHED_NOTSTORED)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Replace) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        return Nan::ThrowError("memcache not initialized");
    }
    if (info.Length() < 2)
    {
        return Nan::ThrowError("Must pass a key and value");
    }
    if (info.Length() >= 3 && !info[3]->IsInt32())
    {
        return Nan::ThrowTypeError("Expiration time must be a integer");
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsString())
    {
        value = NANX_V8VALUE_TO_STRING(info[1]);
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(NANX_V8VALUE_TO_INTEGER(info[1]));
    }
    else if (info[1]->IsNumber())
    {
        value = std::to_string(NANX_V8VALUE_TO_DOUBLE(info[1]));
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = NANX_V8VALUE_TO_INTEGER(info[2]);
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_replace(mcc->mcc, key.c_str(), key.length(),
                                              value.c_str(), value.length(),
                                              expiration, flags);
    if (rc != MEMCACHED_SUCCESS && rc != MEMCACHED_NOTSTORED)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
