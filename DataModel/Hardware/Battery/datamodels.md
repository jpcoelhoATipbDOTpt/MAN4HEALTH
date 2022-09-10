# Battery

Defines the battery status of a given -Battery-
-  `id`: Battery identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be battery. One of : `Battery`.
   -  Attribute type: **Property**. 
   -  Required
-  `batteryLevel`: Device battery level. It must be equal to 1.0 when battery is full. 0.0 when battery is empty. -1 when cannot be determined.
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryTechnology`: Battery technology. One of : `LiPo`, `LiIon`, `LiFePO`, `NiCd`, `NiMH`, `Lead-Acid`, `Non-recheargeable`, `Other`.
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `batteryCharge`: Battery charge value expressed in mAh. In the case of battery packs, this is the charge sum of all batteries in the pack.
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
        "id": "urn:ngsi-ld:Battery:B4t5DdfR5",
        "type": "Battery",
        "batteryLevel": 0.8,
        "dateObserved": "2022-08-12T07:58:07+00:00Z",
        "batteryTechnology": "LiIon",
        "batteryCharge": 2200,
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
            "value": "0.8 \"unitCode\"; \"P1\"",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "batteryTechnology": {
            "type": "Property",
            "value": "LiIon"
        },
        "batteryCharge": {
            "type": "Property",
            "value": 2200,
            "unitCode": "E01"
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
