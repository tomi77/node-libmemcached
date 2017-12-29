/**
 * node-libmemcached
 * Copyright (C) 2017 Tomasz Jakub Rup
 *
 * Use and distribution licensed under the MIT license.  See
 * the LICENSE file in the parent directory for full text.
 */

#include <v8.h>
#include "nan.h"

#pragma once

#define NANX_V8VALUE_TO_STRING(param) std::string(*(v8::String::Utf8Value(param->ToString())))

#define NANX_V8VALUE_TO_INTEGER(param) param->IntegerValue()

#define NANX_V8VALUE_TO_DOUBLE(param) Nan::To<double>(param).FromJust()

#define NANX_INTEGER_TO_V8NUMBER(i) Nan::New<v8::Number>(i)

#define NANX_STRING_TO_V8BUFFER(v) Nan::CopyBuffer(v.c_str(), v.length()).ToLocalChecked()
