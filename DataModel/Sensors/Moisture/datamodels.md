# moisture

Defines a given humidity sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `measuringMedium`: Define the medium from where the measurement is taken
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measuredValue`: Measured humidity (in percentage)
   -  Attribute type: **Property**. 
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339
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
        "id": "urn:device:moisture:AF95DdfR5",
        "type": "moisture",
        "measuringMedium": "soil",
        "dephtOrAltitude": 5,
        "measuredValue": 45,
        "dateObserved": "2022-08-12T07:58:07+00:00",
        "refDevice": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Moisture/Context/context-normalized.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:device:moisture:AF95DdfR5",
        "type": "moisture",
        "measuringMedium": {
            "type": "Property",
            "value": "soil"
        },
        "dephtOrAltitude": {
            "type": "Property",
            "value": 5
        },
        "measuredValue": {
            "type": "Property",
            "value": 45
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
            "iudx:moisture"
        ]
    }
]
```
