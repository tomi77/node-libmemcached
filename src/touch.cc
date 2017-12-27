#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache {

NAN_METHOD(MemcachedClient::Touch) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 2)
        return Nan::ThrowError("Must pass a key and expiration time");
    if (!info[1]->IsInt32())
        return Nan::ThrowTypeError("Expiration time must be a integer");

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);
    time_t expiration = NANX_V8VALUE_TO_INTEGER(info[1]);

    memcached_return_t rc = memcached_touch(mcc->mcc, key.c_str(), key.length(), expiration);
    if (memcached_failed(rc))
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
