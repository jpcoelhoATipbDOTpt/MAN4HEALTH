# Temperature

Defines a given temperature sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be temperature. One of : `Temperature`.
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Required
-  `measuringMedium`: Define tthe medium from where the measurement is taken. One of : `air`, `soil`, `water`.
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measurementValue`: Measured temperature (in degrees Celsius)
   -  Attribute type: **Property**. 
   -  Optional
-  `refDevice`: Reference of the -Device- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Required



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:Temperature:B4t5DdfR5",
        "type": "Temperature",
        "measuringMedium": "air",
        "dephtOrAltitude": 525,
        "measuredValue": -2,
        "dateObserved": "2022-08-12T07:58:07+00:00",
        "refDevice": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Temperature/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    "{\n    \"id\": \"urn:ngsi-ld:Temperature:B4t5DdfR5\",\n    \"type\": \"Temperature\",\n    \"measuringMedium\": {\n        \"type\": \"Property\",\n        \"value\": \"air\"\n    },\n    \"dephtOrAltitude\": {\n        \"type\": \"Property\",\n        \"value\": 525\n        \"unitCode\": \"CMT\",\n    },\n    \"measurementValue\": {\n        \"type\": \"Property\",\n        \"value\": -2,\n        \"unitCode\": \"CEL\",\n        \"observedAt\": \"2022-08-12T07:58:07+00:00Z\"\n    },\n    \"refDevice\": {\n        \"type\": \"Relationship\",\n        \"object\": \"urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q\"\n    },\n\n  \"@context\": [\n  \"https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld\",\n  \"https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Temperature/Context/context-normalized.jsonld\"\n  ]\n}\n"
]
```
