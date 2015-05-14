/*
  * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  * 
  * Licensed under the Apache License, Version 2.0 (the "License").
  * You may not use this file except in compliance with the License.
  * A copy of the License is located at
  * 
  *  http://aws.amazon.com/apache2.0
  * 
  * or in the "license" file accompanying this file. This file is distributed
  * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
  * express or implied. See the License for the specific language governing
  * permissions and limitations under the License.
  */

#pragma once

#include <aws/core/Core_EXPORTS.h>

#include <memory>

namespace Aws
{
namespace Utils
{
namespace RateLimits
{
    class RateLimiterInterface;
} // namespace RateLimits
} // namespace Utils

namespace Http
{

class HttpRequest;
class HttpResponse;

/**
  * Abstract HttpClient. All it does is make HttpRequests and return their response.
  */
class AWS_CORE_API HttpClient
{
public:
    virtual ~HttpClient() {}

    /*
    * Takes http request, makes it, and returns the newly allocated HttpResponse
    */
    virtual std::shared_ptr<HttpResponse> MakeRequest(HttpRequest& request, 
                                                      Aws::Utils::RateLimits::RateLimiterInterface* readLimiter = nullptr, 
                                                      Aws::Utils::RateLimits::RateLimiterInterface* writeLimiter = nullptr) const = 0;

};

} // namespace Http
} // namespace Aws


