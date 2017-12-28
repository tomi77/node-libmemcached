// Copyright 2017 Tomasz Jakub Rup <tomasz.rup@gmail.com>
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
        return Nan::ThrowError("memcache not initialized");
    }
    if (info.Length() != 1)
    {
        return Nan::ThrowError("Must pass a key");
    }

    std::string key = NANX_V8VALUE_TO_STRING(info[0]);
    std::vector<char> ret_val;
    uint32_t flags = 0;
    memcached_return_t rc;
    size_t value_length = 0;

    char *value = memcached_get(mcc->mcc, key.c_str(), key.length(),
                                &value_length, &flags, &rc);
    if (value != NULL && ret_val.empty())
    {
        ret_val.reserve(value_length + 1); // Always provide null
        ret_val.assign(value, value + value_length + 1);
        ret_val.resize(value_length);
        free(value);
        std::string ret_str(ret_val.begin(), ret_val.end());
        info.GetReturnValue().Set(NANX_STRING_TO_V8BUFFER(ret_str));
    }
}

}  // namespace memcache
