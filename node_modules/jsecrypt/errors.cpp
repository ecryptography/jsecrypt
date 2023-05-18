/*
 * Copyright (c) 2019 Cossack Labs Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "errors.hpp"

#include <string>

#include <nan.h>
#include <node.h>

namespace jsecrypt
{

static inline void ExportStatusCode(v8::Local<v8::Object>& exports, const char* name, ecrypt_status_t status)
{
    Nan::Set(exports, Nan::New(name).ToLocalChecked(), Nan::New(status));
}

void Errors::Init(v8::Local<v8::Object> exports)
{
    ExportStatusCode(exports, "SUCCESS", ECRYPT_SUCCESS);
    ExportStatusCode(exports, "FAIL", ECRYPT_FAIL);
    ExportStatusCode(exports, "INVALID_PARAMETER", ECRYPT_INVALID_PARAMETER);
    ExportStatusCode(exports, "NO_MEMORY", ECRYPT_NO_MEMORY);
    ExportStatusCode(exports, "BUFFER_TOO_SMALL", ECRYPT_BUFFER_TOO_SMALL);
    ExportStatusCode(exports, "DATA_CORRUPT", ECRYPT_DATA_CORRUPT);
    ExportStatusCode(exports, "INVALID_SIGNATURE", ECRYPT_INVALID_SIGNATURE);
    ExportStatusCode(exports, "NOT_SUPPORTED", ECRYPT_NOT_SUPPORTED);
    ExportStatusCode(exports, "SSESSION_KA_NOT_FINISHED", ECRYPT_SSESSION_KA_NOT_FINISHED);
    ExportStatusCode(exports, "SSESSION_TRANSPORT_ERROR", ECRYPT_SSESSION_TRANSPORT_ERROR);
    ExportStatusCode(exports,
                     "SSESSION_GET_PUB_FOR_ID_CALLBACK_ERROR",
                     ECRYPT_SSESSION_GET_PUB_FOR_ID_CALLBACK_ERROR);
    ExportStatusCode(exports, "SCOMPARE_NOT_READY", ECRYPT_SCOMPARE_NOT_READY);
}

static const char* ErrorDescription(ecrypt_status_t status)
{
    switch (status) {
    case ECRYPT_SUCCESS:
        return "success";
    case ECRYPT_FAIL:
        return "failure";
    case ECRYPT_INVALID_PARAMETER:
        return "invalid parameter";
    case ECRYPT_NO_MEMORY:
        return "out of memory";
    case ECRYPT_BUFFER_TOO_SMALL:
        return "buffer too small";
    case ECRYPT_DATA_CORRUPT:
        return "corrupted data";
    case ECRYPT_INVALID_SIGNATURE:
        return "invalid signature";
    case ECRYPT_NOT_SUPPORTED:
        return "operation not supported";
    default:
        return "unknown error";
    }
}

static const char* ErrorDescriptionSecureSession(ecrypt_status_t status)
{
    switch (status) {
    case ECRYPT_SSESSION_SEND_OUTPUT_TO_PEER:
        return "send key agreement data to peer";
    case ECRYPT_SSESSION_KA_NOT_FINISHED:
        return "key agreement not finished";
    case ECRYPT_SSESSION_TRANSPORT_ERROR:
        return "transport layer error";
    case ECRYPT_SSESSION_GET_PUB_FOR_ID_CALLBACK_ERROR:
        return "failed to get public key for ID";
    default:
        return ErrorDescription(status);
    }
}

static const char* ErrorDescriptionSecureComparator(ecrypt_status_t status)
{
    switch (status) {
    case ECRYPT_SCOMPARE_SEND_OUTPUT_TO_PEER:
        return "send comparison data to peer";
    case ECRYPT_SCOMPARE_NOT_READY:
        return "comparator not ready";
    case ECRYPT_SCOMPARE_MATCH:
        return "data matches";
    case ECRYPT_SCOMPARE_NO_MATCH:
        return "data does not match";
    default:
        return ErrorDescription(status);
    }
}

static v8::Local<v8::Value> WithStatus(v8::Local<v8::Value> error, ecrypt_status_t status)
{
    v8::Local<v8::Object> object = error.As<v8::Object>();
    Nan::Set(object, Nan::New("code").ToLocalChecked(), Nan::New(status));
    return error;
}

void ThrowError(const char* domain, ecrypt_status_t status)
{
    std::string message;
    message += domain;
    message += ": ";
    message += ErrorDescription(status);
    Nan::ThrowError(WithStatus(Nan::Error(message.c_str()), status));
}

void ThrowTypeError(const char* domain, const char* description)
{
    std::string message;
    message += "ecrypt.";
    message += domain;
    message += ": ";
    message += description;
    Nan::ThrowError(Nan::TypeError(message.c_str()));
}

void ThrowParameterError(const char* domain, const char* description)
{
    std::string message;
    message += domain;
    message += ": ";
    message += description;
    Nan::ThrowError(WithStatus(Nan::Error(message.c_str()), ECRYPT_INVALID_PARAMETER));
}

void ThrowSecureSessionError(const char* domain, ecrypt_status_t status)
{
    std::string message;
    message += domain;
    message += ": ";
    message += ErrorDescriptionSecureSession(status);
    Nan::ThrowError(WithStatus(Nan::Error(message.c_str()), status));
}

void ThrowSecureComparatorError(const char* domain, ecrypt_status_t status)
{
    std::string message;
    message += domain;
    message += ": ";
    message += ErrorDescriptionSecureComparator(status);
    Nan::ThrowError(WithStatus(Nan::Error(message.c_str()), status));
}

} // namespace jsecrypt
