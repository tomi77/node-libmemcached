/**
 * node-libmemcached
 * Copyright (C) 2017 Tomasz Jakub Rup
 *
 * Use and distribution licensed under the MIT license.  See
 * the LICENSE file in the parent directory for full text.
 */

#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache
{

NAN_METHOD(MemcachedClient::Set)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 2)
    {
        Nan::ThrowError("Must pass a key and value");
        return;
    }
    if (info.Length() >= 3 && not info[3]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
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
        Nan::ThrowTypeError("Unsupported type");
        return;
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
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Add)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 2)
    {
        Nan::ThrowError("Must pass a key and value");
        return;
    }
    if (info.Length() >= 3 && not info[3]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
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
        Nan::ThrowTypeError("Unsupported type");
        return;
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
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Replace)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 2)
    {
        Nan::ThrowError("Must pass a key and value");
        return;
    }
    if (info.Length() >= 3 && not info[3]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
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
        Nan::ThrowTypeError("Unsupported type");
        return;
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
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Append)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 2)
    {
        Nan::ThrowError("Must pass a key and value");
        return;
    }
    if (info.Length() >= 3 && not info[3]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
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
        Nan::ThrowTypeError("Unsupported type");
        return;
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = NANX_V8VALUE_TO_INTEGER(info[2]);
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_append(mcc->mcc, key.c_str(), key.length(),
                                             value.c_str(), value.length(),
                                             expiration, flags);
    if (rc != MEMCACHED_SUCCESS && rc != MEMCACHED_NOTSTORED)
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(MemcachedClient::Prepend)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() < 2)
    {
        Nan::ThrowError("Must pass a key and value");
        return;
    }
    if (info.Length() >= 3 && not info[3]->IsInt32())
    {
        Nan::ThrowTypeError("Expiration time must be a integer");
        return;
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
        Nan::ThrowTypeError("Unsupported type");
        return;
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = NANX_V8VALUE_TO_INTEGER(info[2]);
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_prepend(mcc->mcc, key.c_str(), key.length(),
                                              value.c_str(), value.length(),
                                              expiration, flags);
    if (rc != MEMCACHED_SUCCESS && rc != MEMCACHED_NOTSTORED)
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
