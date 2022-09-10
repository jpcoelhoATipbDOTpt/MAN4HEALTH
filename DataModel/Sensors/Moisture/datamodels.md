# Moisture

Defines a given humidity sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be moisture. One of : `Moisture`.
   -  Attribute type: **Property**. 
   -  Required
-  `measuringMedium`: Define the medium from where the measurement is taken
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measurementValue`: Measured humidity (in percentage)
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
        "id": "urn:ngsi-ld:Moisture:AF95DdfR5",
        "type": "Moisture",
        "measuringMedium": "soil",
        "dephtOrAltitude": {
            "value": 525,
            "unitCode": "CMT"
        },
        "measuredValue": {
            "value": 45,
            "unitCode": "P1",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "refDevice": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Moisture/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:ngsi-ld:Moisture:AF95DdfR5",
        "type": "Moisture",
        "measuringMedium": {
            "type": "Property",
            "value": "soil"
        },
        "dephtOrAltitude": {
            "type": "Property",
            "value": 5,
            "unitCode": "CMT"
        },
        "measurementValue": {
            "type": "Property",
            "value": 65,
            "unitCode": "P1",
            "observedAt": "2022-08-12T07:58:07+00:00Z"            
        },
        "refDevice": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q"
        },

        "@context": [
        "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
        "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Sensors/Moisture/Context/context-normalized.jsonld"
        ]
    }
]
```
