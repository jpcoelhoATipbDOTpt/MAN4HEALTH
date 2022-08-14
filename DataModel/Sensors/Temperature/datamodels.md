# temperature

Defines a given temperature sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be temperature. One of : `temperature`.
   -  Attribute type: **Property**. 
   -  Optional
-  `measuringMedium`: Define tthe medium from where the measurement is taken
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measuredValue`: Measured temperature (in degrees Celsius)
   -  Attribute type: **Property**. 
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339.
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
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
        "id": "urn:device:temperature:B4t5DdfR5",
        "type": "moisture",
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
    {
        "id": "urn:device:temperature:B4t5DdfR5",
        "type": "temperature",
        "measuringMedium": {
            "type": "Property",
            "value": "air"
        },
        "dephtOrAltitude": {
            "type": "Property",
            "value": 525
        },
        "measuredValue": {
            "type": "Property",
            "value": -2
        },
        "observationDateTime": {
            "type": "Property",
            "value": {
                "@type": "DateTime",
                "@value": "2022-08-12T07:58:07+00:00"
            }
        },
        "refDevice": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Temperature/Context/context-normalized.jsonld"
        ]
    }
]
```
