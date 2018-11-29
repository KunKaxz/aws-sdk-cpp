﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#include <aws/lambda/model/LayerVersionsListItem.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include <utility>

using namespace Aws::Utils::Json;
using namespace Aws::Utils;

namespace Aws
{
namespace Lambda
{
namespace Model
{

LayerVersionsListItem::LayerVersionsListItem() : 
    m_layerVersionArnHasBeenSet(false),
    m_version(0),
    m_versionHasBeenSet(false),
    m_descriptionHasBeenSet(false),
    m_createdDateHasBeenSet(false),
    m_compatibleRuntimesHasBeenSet(false),
    m_licenseInfoHasBeenSet(false)
{
}

LayerVersionsListItem::LayerVersionsListItem(JsonView jsonValue) : 
    m_layerVersionArnHasBeenSet(false),
    m_version(0),
    m_versionHasBeenSet(false),
    m_descriptionHasBeenSet(false),
    m_createdDateHasBeenSet(false),
    m_compatibleRuntimesHasBeenSet(false),
    m_licenseInfoHasBeenSet(false)
{
  *this = jsonValue;
}

LayerVersionsListItem& LayerVersionsListItem::operator =(JsonView jsonValue)
{
  if(jsonValue.ValueExists("LayerVersionArn"))
  {
    m_layerVersionArn = jsonValue.GetString("LayerVersionArn");

    m_layerVersionArnHasBeenSet = true;
  }

  if(jsonValue.ValueExists("Version"))
  {
    m_version = jsonValue.GetInt64("Version");

    m_versionHasBeenSet = true;
  }

  if(jsonValue.ValueExists("Description"))
  {
    m_description = jsonValue.GetString("Description");

    m_descriptionHasBeenSet = true;
  }

  if(jsonValue.ValueExists("CreatedDate"))
  {
    m_createdDate = jsonValue.GetString("CreatedDate");

    m_createdDateHasBeenSet = true;
  }

  if(jsonValue.ValueExists("CompatibleRuntimes"))
  {
    Array<JsonView> compatibleRuntimesJsonList = jsonValue.GetArray("CompatibleRuntimes");
    for(unsigned compatibleRuntimesIndex = 0; compatibleRuntimesIndex < compatibleRuntimesJsonList.GetLength(); ++compatibleRuntimesIndex)
    {
      m_compatibleRuntimes.push_back(RuntimeMapper::GetRuntimeForName(compatibleRuntimesJsonList[compatibleRuntimesIndex].AsString()));
    }
    m_compatibleRuntimesHasBeenSet = true;
  }

  if(jsonValue.ValueExists("LicenseInfo"))
  {
    m_licenseInfo = jsonValue.GetString("LicenseInfo");

    m_licenseInfoHasBeenSet = true;
  }

  return *this;
}

JsonValue LayerVersionsListItem::Jsonize() const
{
  JsonValue payload;

  if(m_layerVersionArnHasBeenSet)
  {
   payload.WithString("LayerVersionArn", m_layerVersionArn);

  }

  if(m_versionHasBeenSet)
  {
   payload.WithInt64("Version", m_version);

  }

  if(m_descriptionHasBeenSet)
  {
   payload.WithString("Description", m_description);

  }

  if(m_createdDateHasBeenSet)
  {
   payload.WithString("CreatedDate", m_createdDate);

  }

  if(m_compatibleRuntimesHasBeenSet)
  {
   Array<JsonValue> compatibleRuntimesJsonList(m_compatibleRuntimes.size());
   for(unsigned compatibleRuntimesIndex = 0; compatibleRuntimesIndex < compatibleRuntimesJsonList.GetLength(); ++compatibleRuntimesIndex)
   {
     compatibleRuntimesJsonList[compatibleRuntimesIndex].AsString(RuntimeMapper::GetNameForRuntime(m_compatibleRuntimes[compatibleRuntimesIndex]));
   }
   payload.WithArray("CompatibleRuntimes", std::move(compatibleRuntimesJsonList));

  }

  if(m_licenseInfoHasBeenSet)
  {
   payload.WithString("LicenseInfo", m_licenseInfo);

  }

  return payload;
}

} // namespace Model
} // namespace Lambda
} // namespace Aws
