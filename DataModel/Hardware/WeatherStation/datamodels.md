# WeatherStation

Masurements obtained from a weather station
-  `id`: Weather Station ID
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. One of : `WeatherStation`.
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Required
-  `airTemperature`: Air temperature (in degree Celsius)
   -  Attribute type: **Property**. 
   -  Optional
-  `airMoisture`: Air moisture (in percentage)
   -  Attribute type: **Property**. 
   -  Optional
-  `atmosphericPressure`: Atmospheric Pressure (in Pa)
   -  Attribute type: **Property**. 
   -  Optional
-  `solarIlluminance`: Solar illuminance (in Lux)
   -  Attribute type: **Property**. 
   -  Optional
-  `solarIrradiance`: Esttimated solar irradiance from illuminance (in W/m2)
   -  Attribute type: **Property**. 
   -  Optional
-  `refTerrain`: Reference of the -Terrain- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Optional



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:WeatherStation:SenseCAP01",
        "type": "WeatherStation",
        "airTemperature": {
            "value": 27.05,
            "unirCode": "CEL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "airMoisture": {
            "value": 55.28,
            "unirCode": "CEL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "atmosphericPressure": {
            "value": 989.9,
            "unirCode": "PAL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "solarIlluminance": {
            "value": 25000,
            "unirCode": "LUX",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "solarIrradiance": {
            "value": 820,
            "unirCode": "D54",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "refTerrain": "urn:ngsi-ld:Terrain:MRDL01",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/WeatherStation/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:ngsi-ld:WeatherStation:SenseCAP01",
        "type": "WeatherStation",
        "airTemperature": {
            "type": "Property",
            "value": 27.05,
            "unirCode": "CEL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "airMoisture": {
            "type": "Property",
            "value": 55.28,
            "unirCode": "CEL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "atmosphericPressure": {
            "type": "Property",
            "value": 989.9,
            "unirCode": "PAL",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "solarIlluminance": {
            "type": "Property",
            "value": 25000,
            "unirCode": "LUX",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "solarIrradiance": {
            "type": "Property",
            "value": 820,
            "unirCode": "D54",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "refDevice": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/WeatherStation/Context/context-keyvalues.jsonld"
        ]
    }
]
```
