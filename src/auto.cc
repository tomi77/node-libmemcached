#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"

namespace memcache {

NAN_METHOD(MemcachedClient::Increment) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() < 1)
        return Nan::ThrowError("Must pass a key");
    if (info.Length() >= 2 && !info[1]->IsInt32())
        return Nan::ThrowError("Offset must be a integer");
    if (info.Length() >= 3 && !info[2]->IsInt32())
        return Nan::ThrowError("Start must be a integer");

    Nan::Utf8String key(info[0]);
    uint32_t offset = 1;
    if (info.Length() >= 2)
        offset = info[1]->IntegerValue();
    uint64_t value;

    memcached_return_t rc = memcached_increment(mcc->mcc, *key, key.length(), offset, &value);
    if (rc != MEMCACHED_SUCCESS)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    // info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), value));
    info.GetReturnValue().Set(Nan::New<v8::Number>(value));
}

NAN_METHOD(MemcachedClient::Decrement) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() < 1)
        return Nan::ThrowError("Must pass a key");
    if (info.Length() >= 2 && !info[1]->IsInt32())
        return Nan::ThrowError("Offset must be a integer");
    if (info.Length() >= 3 && !info[2]->IsInt32())
        return Nan::ThrowError("Start must be a integer");

    Nan::Utf8String key(info[0]);
    uint32_t offset = 1;
    if (info.Length() >= 2)
        offset = info[1]->IntegerValue();
    uint64_t value;

    memcached_return_t rc = memcached_decrement(mcc->mcc, *key, key.length(), offset, &value);
    if (rc != MEMCACHED_SUCCESS)
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    // info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), value));
    info.GetReturnValue().Set(Nan::New<v8::Number>(value));
}

}  // namespace memcache
