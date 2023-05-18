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

#ifndef JSECRYPT_ERRORS_HPP_
#define JSECRYPT_ERRORS_HPP_

#include <nan.h>

#include <ecrypt/ecrypt.h>

namespace jsecrypt
{

namespace Errors
{

void Init(v8::Local<v8::Object> exports);

} // namespace Errors

void ThrowError(const char* domain, ecrypt_status_t status);

void ThrowTypeError(const char* domain, const char* description);

void ThrowParameterError(const char* domain, const char* description);

void ThrowSecureSessionError(const char* domain, ecrypt_status_t status);

void ThrowSecureComparatorError(const char* domain, ecrypt_status_t status);

} // namespace jsecrypt

#endif /* JSECRYPT_ERRORS_HPP_ */
