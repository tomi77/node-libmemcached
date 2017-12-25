#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"

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

    Nan::Utf8String key(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsString())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(info[1]->IntegerValue());
    }
    else if (info[1]->IsNumber())
    {
        Nan::Maybe<double> nan_value = Nan::To<double>(info[1]);
        double num_value = nan_value.FromJust();
        value = std::to_string(num_value);
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = info[3]->IntegerValue();
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_set(mcc->mcc, *key, key.length(),
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

    Nan::Utf8String key(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsString())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(info[1]->IntegerValue());
    }
    else if (info[1]->IsNumber())
    {
        Nan::Maybe<double> nan_value = Nan::To<double>(info[1]);
        double num_value = nan_value.FromJust();
        value = std::to_string(num_value);
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = info[3]->IntegerValue();
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_add(mcc->mcc, *key, key.length(),
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

    Nan::Utf8String key(info[0]);

    std::string value;
    if (info[1]->IsArrayBufferView())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsString())
    {
        Nan::Utf8String nan_value(info[1]);
        value = *nan_value;
    }
    else if (info[1]->IsInt32())
    {
        value = std::to_string(info[1]->IntegerValue());
    }
    else if (info[1]->IsNumber())
    {
        Nan::Maybe<double> nan_value = Nan::To<double>(info[1]);
        double num_value = nan_value.FromJust();
        value = std::to_string(num_value);
    }
    else
    {
        return Nan::ThrowTypeError("Unsupported type");
    }

    time_t expiration = 0;
    if (info.Length() >= 3)
    {
        expiration = info[3]->IntegerValue();
    }

    uint32_t flags = 0;

    memcached_return_t rc = memcached_replace(mcc->mcc, *key, key.length(),
                                              value.c_str(), value.length(),
                                              expiration, flags);
    if (rc != MEMCACHED_SUCCESS && rc != MEMCACHED_NOTSTORED)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
