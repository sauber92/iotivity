//******************************************************************
//
// Copyright 2014 Intel Mobile Communications GmbH All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#ifndef OC_RANDOM_H
#define OC_RANDOM_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARDUINO
// MEGA has 16 input pins whereas Due has only 12 input pins
#define ANALOG_IN (10)
#endif

 /* Number of bytes in a UUID. */
#define UUID_SIZE (16)

/*
 * Size of a UUID string.
 * IoTivity formats UUIDs as strings following RFC 4122, Section 3.
 * For example, "f81d4fae-7dec-11d0-a765-00a0c91e6bf6".
 * This requires 36 characters, plus one for the null terminator.
 */
#define UUID_STRING_SIZE (37)

/**
 * Generate a uniformly distributed 32-bit random number.
 * @retval On success, it returns the random value.
 */
uint32_t OCGetRandom();

/**
 * Generate an array of uniformly distributed random bytes.
 * @param[out] output
 *              Array to fill with random bytes
 * @param[in] len
 *              Length of array
 * @retval true for success, otherwise false and an error is logged
 */
bool OCGetRandomBytes(uint8_t * output, size_t len);

/**
 * Generate a uniformly distributed number in a given range.
 * @param[in] firstBound
 *              The output is greater than or equal to firstBound
 * @param[in] secondBound
 *              The output is less than or equal to secondBound
 */
uint32_t OCGetRandomRange(uint32_t firstBound, uint32_t secondBound);

/**
 * Generate a Uniformly Unique Identifier based on RFC4122 and
 * provide it as UUID_SIZE bytes.
 *
 * @param[out] uuid
 *               UUID_SIZE array to hold the new UUID
 *
 * @retval true for success, otherwise false and an error is logged
 */
bool OCGenerateUuid(uint8_t uuid[UUID_SIZE]);

/**
 * Convert a UUID generated by OCGenerateUuid to a C string
 * based on RFC 4122.
 *
 * @param[in]  uuid
 *              Array of length UUID_SIZE bytes with output of OCGenerateUuid
 * @param[out] uuidString
 *              A UUID_STRING_SIZE length string to hold the string
 *              representation of the input UUID.
 * @retval true for success, otherwise false and an error is logged
 */
bool OCConvertUuidToString(const uint8_t uuid[UUID_SIZE],
        char uuidString[UUID_STRING_SIZE]);

/**
 * Convert a C style string to a UUID based on RFC 4122
 *
 * @param[in] uuidString
 *              a 37 byte length string to fill with the string
 *              representation of the passed UUID.
 * @param[out]  uuid
 *              The 16 byte array filled with UUID data
 * @retval true for success, otherwise false and an error is logged
 */
bool OCConvertStringToUuid(const char uuidString[UUID_STRING_SIZE],
                                         uint8_t uuid[UUID_SIZE]);

/**
 * Check if the provided uuid is valid.
 * 1. The length of uuids should always be 36.
 * 2. Hyphens are expected at positions {9, 14, 19, 24}.
 * 3. The rest charcters should be simple xdigits.
 *
 * @param[in] uuid    uuid extracted from uri
 *
 * @retval true for success, otherwise false and an error is logged
 */
bool OCIsUUID(const char *uuid);

#ifdef __cplusplus
}
#endif

#endif // OC_RANDOM_H
