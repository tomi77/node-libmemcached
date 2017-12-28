// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
#include <libmemcached/memcached.h>
#include "nan.h"
#include "client.hpp"
#include "marshaling.h"

namespace memcache {

NAN_METHOD(MemcachedClient::Exist) {
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
        return Nan::ThrowError("memcache not initialized");
    if (info.Length() != 1)
        return Nan::ThrowError("Must pass a key");

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);

    memcached_return_t rc = memcached_exist(mcc->mcc, key.c_str(), key.length());
    if (rc == MEMCACHED_SUCCESS)
    {
        info.GetReturnValue().Set(Nan::True());
    }
    else if (rc == MEMCACHED_NOTFOUND)
    {
        info.GetReturnValue().Set(Nan::False());
    }
    else
    {
        return Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
    }
}

}  // namespace memcache
