# Battery

Defines the battery status of a given -Device-
-  `id`: Battery identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be battery. One of : `Battery`.
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryLevel`: Device battery level. It must be equal to 1.0 when battery is full. 0.0 when battery is empty. -1 when cannot be determined.
   -  Attribute type: **Property**. [Number](https://schema.org/Number)
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339.
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
   -  Optional
-  `batteryDetails`: Technical details about the batteries
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
        "id": "urn:dngsi-ld:Battery:B4t5DdfR5",
        "type": "Battery",
        "batteryLevel": 0.8,
        "dateObserved": "2022-08-12T07:58:07+00:00",
        "batteryDetails": {
            "batteryTechnology": "LiIon",
            "batteryCharge": 2200
        },
        "refDevice": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/Battery/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:ngsi-ld:Battery:B4t5DdfR5",
        "type": "Battery",
        "batteryLevel": {
            "type": "Property",
            "value": 0.8
        },
        "observationDateTime": {
            "type": "Property",
            "value": {
                "@type": "DateTime",
                "@value": "2022-08-12T07:58:07+00:00"
            }
        },
        "batteryDetails": {
            "batteryTechnology": {
                "type": "Property",
                "value": "LiIon"
            },
            "batteryCharge": {
                "type": "Property",
                "value": 2200
            }
        },
        "refDevice": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/Battery/Context/context-normalized.jsonld"
        ]
    }
]
```
