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

NAN_METHOD(MemcachedClient::Delete)
{
    MemcachedClient *mcc = GetInstance(info);

    if (mcc->mcc == NULL)
    {
        Nan::ThrowError("memcache not initialized");
        return;
    }
    if (info.Length() != 1)
    {
        Nan::ThrowError("Must pass a key");
        return;
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);

    memcached_return_t rc = memcached_delete(mcc->mcc, key.c_str(), key.length(), 0);
    if (rc != MEMCACHED_SUCCESS)
    {
        Nan::ThrowError(memcached_strerror(mcc->mcc, rc));
        return;
    }

    info.GetReturnValue().Set(info.This());
}

}  // namespace memcache
