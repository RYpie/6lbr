#include "coap-common.h"
#include "device-resource.h"

#if WITH_NVM
#include "nvm-config.h"
#endif

/*---------------------------------------------------------------------------*/

#if REST_RES_DEVICE_BATCH
#define REST_RES_DEVICE_BATCH_RESOURCE BATCH_RESOURCE
#else
#define REST_RES_DEVICE_BATCH_RESOURCE(...)
#endif

#if REST_RES_DEVICE_MANUFACTURER
#define REST_RES_DEVICE_MANUFACTURER_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_MANUFACTURER_REF &resource_device_manufacturer,
#else
#define REST_RES_DEVICE_MANUFACTURER_RESOURCE(...)
#define REST_RES_DEVICE_MANUFACTURER_REF
#endif

#if REST_RES_DEVICE_MODEL
#define REST_RES_DEVICE_MODEL_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_MODEL_REF &resource_device_model,
#else
#define REST_RES_DEVICE_MODEL_RESOURCE(...)
#define REST_RES_DEVICE_MODEL_REF
#endif

#if REST_RES_DEVICE_MODEL_HW
#define REST_RES_DEVICE_MODEL_HW_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_MODEL_HW_REF &resource_device_model_hw,
#else
#define REST_RES_DEVICE_MODEL_HW_RESOURCE(...)
#define REST_RES_DEVICE_MODEL_HW_REF
#endif

#if REST_RES_DEVICE_MODEL_SW
#define REST_RES_DEVICE_MODEL_SW_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_MODEL_SW_REF &resource_device_model_sw,
#else
#define REST_RES_DEVICE_MODEL_SW_RESOURCE(...)
#define REST_RES_DEVICE_MODEL_SW_REF
#endif

#if REST_RES_DEVICE_SERIAL
#define REST_RES_DEVICE_SERIAL_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_SERIAL_REF &resource_device_serial,
#else
#define REST_RES_DEVICE_SERIAL_RESOURCE(...)
#define REST_RES_DEVICE_SERIAL_REF
#endif

#if REST_RES_DEVICE_NAME
#define REST_RES_DEVICE_NAME_RESOURCE REST_ACTUATOR
#define REST_RES_DEVICE_NAME_REF &resource_device_name,
#else
#define REST_RES_DEVICE_NAME_RESOURCE(...)
#define REST_RES_DEVICE_NAME_REF
#endif

#if REST_RES_DEVICE_TIME
#define REST_RES_DEVICE_TIME_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_TIME_REF &resource_device_time,
#else
#define REST_RES_DEVICE_TIME_RESOURCE(...)
#define REST_RES_DEVICE_TIME_REF
#endif

#if REST_RES_DEVICE_UPTIME
#define REST_RES_DEVICE_UPTIME_RESOURCE REST_RESOURCE
#define REST_RES_DEVICE_UPTIME_REF &resource_device_uptime,
#else
#define REST_RES_DEVICE_UPTIME_RESOURCE(...)
#define REST_RES_DEVICE_UPTIME_REF
#endif

/*---------------------------------------------------------------------------*/

#ifdef RES_CONF_DEVICE_MANUFACTURER_VALUE
#define RES_DEVICE_MANUFACTURER_VALUE RES_CONF_DEVICE_MANUFACTURER_VALUE
#else
#ifdef CONTIKI_TARGET_SKY
#define RES_DEVICE_MANUFACTURER_VALUE "Moteiv"
#elif defined CONTIKI_TARGET_Z1
#define RES_DEVICE_MANUFACTURER_VALUE "Zolertia"
#elif defined CONTIKI_TARGET_WISMOTE
#define RES_DEVICE_MANUFACTURER_VALUE "Arago"
#elif defined CONTIKI_TARGET_ECONOTAG
#define RES_DEVICE_MANUFACTURER_VALUE "Redwire"
#elif defined CONTIKI_TARGET_CC2538DK
#define RES_DEVICE_MANUFACTURER_VALUE "TI"
#else
#define RES_DEVICE_MANUFACTURER_VALUE "Unknown"
#endif
#endif

#ifdef RES_CONF_DEVICE_MODEL_VALUE
#define RES_DEVICE_MODEL_VALUE RES_CONF_DEVICE_MODEL_VALUE
#else
#ifdef CONTIKI_TARGET_SKY
#define RES_DEVICE_MODEL_VALUE "Sky"
#elif defined CONTIKI_TARGET_Z1
#define RES_DEVICE_MODEL_VALUE "Z1"
#elif defined CONTIKI_TARGET_WISMOTE
#define RES_DEVICE_MODEL_VALUE "Wismote"
#elif defined CONTIKI_TARGET_ECONOTAG
#define RES_DEVICE_MODEL_VALUE "Econotag"
#elif defined CONTIKI_TARGET_CC2538DK
#define RES_DEVICE_MODEL_VALUE "CC2538DK"
#else
#define RES_DEVICE_MODEL_VALUE "Unknown"
#endif
#endif

#ifdef RES_CONF_DEVICE_MODEL_HW_VALUE
#define RES_DEVICE_MODEL_HW_VALUE RES_CONF_DEVICE_MODEL_HW_VALUE
#else
#define RES_DEVICE_MODEL_HW_VALUE "0"
#endif

#ifdef RES_CONF_DEVICE_MODEL_SW_VALUE
#define RES_DEVICE_MODEL_SW_VALUE RES_CONF_DEVICE_MODEL_SW_VALUE
#else
#define RES_DEVICE_MODEL_SW_VALUE CONTIKI_VERSION_STRING
#endif

#ifdef RES_CONF_DEVICE_SERIAL_VALUE
#define RES_DEVICE_SERIAL_VALUE RES_CONF_DEVICE_SERIAL_VALUE
#else
#define RES_DEVICE_SERIAL_VALUE "0"
#endif

#ifdef RES_CONF_DEVICE_NAME_VALUE
#define RES_DEVICE_NAME_VALUE RES_CONF_DEVICE_NAME_VALUE
#else
#define RES_DEVICE_NAME_VALUE "Unknown"
#endif

#if WITH_NVM
#define DEVICE_NAME_VALUE nvm_data.device_name
#else
#define MAX_DEVICE_NAME_LENGTH 40
static char device_name_value[MAX_DEVICE_NAME_LENGTH+1];

#define DEVICE_NAME_VALUE device_name_value
#endif

inline int device_name_set(uint8_t const* name, int len) {
  if (len <= MAX_DEVICE_NAME_LENGTH) {
    strcpy(DEVICE_NAME_VALUE, (char const *)name);
#if WITH_NVM
    store_nvm_config();
#endif
    return 1;
  } else {
    return 0;
  }
}

#ifdef RES_CONF_DEVICE_TIME_VALUE
#define RES_DEVICE_TIME_VALUE RES_CONF_DEVICE_TIME_VALUE
#else
#define RES_DEVICE_TIME_VALUE clock_seconds()
#endif

#ifdef RES_CONF_DEVICE_UPTIME_VALUE
#define RES_DEVICE_UPTIME_VALUE RES_CONF_DEVICE_UPTIME_VALUE
#else
#define RES_DEVICE_UPTIME_VALUE clock_seconds()
#endif
/*---------------------------------------------------------------------------*/

REST_RES_DEVICE_MANUFACTURER_RESOURCE(device_manufacturer,
    ,
    IF_RO_PARAMETER,
    DEVICE_MANUFACTURER_RT,
    REST_FORMAT_ONE_STR("mfg", RES_DEVICE_MANUFACTURER_VALUE))

REST_RES_DEVICE_MODEL_RESOURCE(device_model,
    ,
    IF_RO_PARAMETER,
    DEVICE_MODEL_RT,
    REST_FORMAT_ONE_STR("model", RES_DEVICE_MODEL_VALUE))

REST_RES_DEVICE_MODEL_HW_RESOURCE(device_model_hw,
    ,
    IF_RO_PARAMETER,
    DEVICE_MODEL_HW_RT,
    REST_FORMAT_ONE_STR("hw", RES_DEVICE_MODEL_HW_VALUE))

REST_RES_DEVICE_MODEL_SW_RESOURCE(device_model_sw,
    ,
    IF_RO_PARAMETER,
    DEVICE_MODEL_SW_RT,
    REST_FORMAT_ONE_STR("sw", RES_DEVICE_MODEL_SW_VALUE))

REST_RES_DEVICE_SERIAL_RESOURCE(device_serial,
    ,
    IF_RO_PARAMETER,
    DEVICE_SERIAL_RT,
    REST_FORMAT_ONE_STR("serial", RES_DEVICE_SERIAL_VALUE))

REST_RES_DEVICE_NAME_RESOURCE(device_name,
    ,
    IF_PARAMETER,
    DEVICE_NAME_RT,
    REST_FORMAT_ONE_STR("name", DEVICE_NAME_VALUE), REST_PARSE_ONE_STR, device_name_set)

REST_RES_DEVICE_TIME_RESOURCE(device_time,
    ,
    IF_RO_PARAMETER,
    DEVICE_TIME_RT,
    REST_FORMAT_ONE_ULONG("time", RES_DEVICE_TIME_VALUE))

REST_RES_DEVICE_UPTIME_RESOURCE(device_uptime,
    ,
    IF_SENSOR,
    DEVICE_UPTIME_RT,
    REST_FORMAT_ONE_ULONG("uptime", RES_DEVICE_UPTIME_VALUE))

/*---------------------------------------------------------------------------*/
REST_RES_DEVICE_BATCH_RESOURCE(device, IF_BATCH, DEVICE_RT,
    REST_RES_DEVICE_MANUFACTURER_REF
    REST_RES_DEVICE_MODEL_REF
    REST_RES_DEVICE_MODEL_HW_REF
    REST_RES_DEVICE_MODEL_SW_REF
    REST_RES_DEVICE_SERIAL_REF
    REST_RES_DEVICE_NAME_REF
    REST_RES_DEVICE_TIME_REF
    REST_RES_DEVICE_UPTIME_REF
    )
/*---------------------------------------------------------------------------*/