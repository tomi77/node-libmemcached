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

NAN_METHOD(MemcachedClient::Get)
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
    uint32_t flags = 0;
    memcached_return_t rc;
    size_t value_length = 0;

    char *value = memcached_get(mcc->mcc, key.c_str(), key.length(),
                                &value_length, &flags, &rc);
    if (value != NULL)
    {
        std::string ret_str(value);
        free(value);
        info.GetReturnValue().Set(NANX_STRING_TO_V8BUFFER(ret_str));
    }
}

}  // namespace memcache
